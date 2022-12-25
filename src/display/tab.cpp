#include <display/tab.hpp>

tab::tab(std::shared_ptr<signalData> dataIn)
: data(dataIn)
{
}

void tab::zoomX(float value)
{
    zoomXAmount += value / 10;
}

void tab::zoomY(float value)
{
    zoomYAmount += value / 10;
}

float tab::getZoomX()
{
    return zoomXAmount;
}

float tab::getZoomY()
{
    return zoomYAmount;
}

std::shared_ptr<signalData> tab::getData()
{
    return data;
}

tab::~tab()
{
}

////////////////////////////////////////////////////

waveForm::waveForm(std::shared_ptr<signalData> dataIn)
: tab(dataIn)
{

}

void waveForm::addValue(int64_t val)
{
    dataPoints.push_back(val);
}

void waveForm::eraseAllData()
{
    dataPoints.clear();
    graph.clear();
}

void waveForm::draw(std::shared_ptr<sf::RenderWindow> windowIn)
{
    windowIn->draw(&graph[0], graph.getVertexCount(), sf::LineStrip);
}

void waveForm::update(sf::Vector2f topLeftWindowPos, sf::Vector2f bottomRightPos)
{
    //updating only the vertices in view
    uint64_t firstPoint;
    uint64_t lastPoint;

    if(topLeftWindowPos.x < 0){
        firstPoint = 0;
    }else
    {
        firstPoint = topLeftWindowPos.x / getZoomX();
    }

    if(bottomRightPos.x < 0){
        lastPoint = 0;
    }else
    {
        lastPoint = bottomRightPos.x / getZoomX();
    }

    if(lastPoint > getAmountDataPoints()){
        lastPoint = getAmountDataPoints();
    }

    uint64_t amountOfPoints = lastPoint - firstPoint;

    if(amountOfPoints > graph.getVertexCount())
    {
        // using linestrip
        for (int i = 0; i < graph.getVertexCount(); i++)
        {
            int64_t val = getData()->getWaveformData(i + firstPoint);
            graph[i].position = sf::Vector2f((i+firstPoint) * getZoomX(), -(val * getZoomY()) + 500);
        }

        for (int i = graph.getVertexCount(); i < amountOfPoints; i++)
        {
            int64_t val = getData()->getWaveformData(i + firstPoint);
            graph.append(sf::Vertex(sf::Vector2f((i+firstPoint) * getZoomX(), -(val * getZoomY()) + 500)));
            graph[i].color = sf::Color::Green;
        }
        
    }else
    {
        graph.resize(amountOfPoints);
        for (int i = 0; i < amountOfPoints; i++)
        {
            int64_t val = getData()->getWaveformData(i + firstPoint);
            graph[i].position = sf::Vector2f((i+firstPoint) * getZoomX(), -(val * getZoomY()) + 500);
        }
    }
}

int64_t waveForm::getAmountDataPoints()
{
    return getData()->getWaveformSize();
}

void waveForm::drawUI()
{
    
}

waveForm::~waveForm()
{
    
}

////////////////////////////////////////////////////

waterFall::waterFall(std::shared_ptr<signalData> dataIn)
: tab(dataIn)
{
    zoomX(-getZoomX() * 10);
    zoomY(-getZoomY() * 10);
    zoomX(1);
    zoomY(0.25);
}

void waterFall::recalculateFft()
{
    // recalculate the fft data
    std::shared_ptr<std::vector<std::complex<float>>> tempData = std::make_shared<std::vector<std::complex<float>>>();
    int fftDuration = getData()->getWaveformSize() / fftOffset;

    //TODO: rewrite the multithreading crap
    // i accidentally deleted the file and now all the changes are gone
    // F. M. L.

    // update the image data
    if(fftTexture.create(fftsize, fftDuration) == 0){
        return;
    }
    fftImage.create(fftsize, fftDuration);

    recalculateFftMultithreaded(4, fftDuration);
    // seet th position to the middle of the camera
    fftSprite.setPosition(sf::Vector2f(0, 0));
}

void waterFall::recalculateFftMultithreaded(int threads, int dataSize)
{
    std::vector<std::shared_ptr<std::thread>> threadObjs;

    for(int i = 0; i < threads; i++)
    {
        std::shared_ptr<std::thread> t = std::make_shared<std::thread>
            (&waterFall::recalculatePartOfFft, this, (i/(float)threads) * dataSize, ((i/(float)threads) * dataSize) - 1);
        
        threadObjs.push_back(t);
    }

    for (int i = 0; i < threads; i++)
    {
        threadObjs[i]->join();
    }
    
}

void waterFall::recalculatePartOfFft(int start, int end)
{
    std::shared_ptr<std::vector<std::complex<float>>> tempData = std::make_shared<std::vector<std::complex<float>>>();
    
    for (int j = start; j < end; j++)
    {

        for (int i = 0; i < fftsize; i++)
        {
            std::complex<float> dataPoint;
            dataPoint.real(getData()->getWaveformData(i + (j * fftOffset)));
            tempData->push_back(dataPoint);
        }
        fftData.push_back(fft(tempData, fftsize));
        tempData->clear();
    }

    for (int y = start; y < end; y++)
    {
        for (int x = 0; x < fftsize; x++)
        {
            sf::Color pixel(0, 0, 0, 255);
            pixel.r = fftData[y]->at(x).real() / 20;
            pixel.g = fftData[y]->at(x).real() / 20;
            pixel.b = fftData[y]->at(x).real() / 20;

            fftImage.setPixel(x, y, pixel);
        }
        
    }

    fftTexture.loadFromImage(fftImage);
    fftSprite.setTexture(fftTexture);
}

void waterFall::draw(std::shared_ptr<sf::RenderWindow> windowIn)
{
    fftSprite.setScale(sf::Vector2f(((float)900)/fftsize * getZoomX()*10, getZoomY()*100));
    windowIn->draw(fftSprite);
}

void waterFall::drawUI()
{

}

void waterFall::update()
{
    if(tempDebug)
    {
        recalculateFft();
        tempDebug = false;
    }
}

bool waterFall::setFftSize(int size)
{
    if(size != 256 || size != 512 || size != 1024 || size != 2048 ){
        return false;
    }

    fftsize = size;
    return true;
}

void waterFall::addDataPoint(int64_t value)
{
    dataPoints.push_back(value);
}

int waterFall::getFftOffset()
{
    return fftOffset;
}

void waterFall::setFftOffset(int offset)
{
    fftOffset = offset;
}

int waterFall::getFftSize()
{
    return fftsize;
}

void waterFall::eraseAllData()
{

}