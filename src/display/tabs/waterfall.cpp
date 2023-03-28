#include <display/tabs/waterfall.hpp>


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
    std::shared_ptr<std::vector<std::complex<double>>> tempData = std::make_shared<std::vector<std::complex<double>>>();
    int fftDuration = getData()->getWaveformSize() / fftOffset;
    
    for (int j = 0; j < fftDuration; j++)
    {
        for (int i = 0; i < fftsize; i++)
        {
            std::complex<double> dataPoint;
            dataPoint.real(getData()->getWaveformData(i + (j * fftOffset)));

            // apply blackman harris
            // TODO: add ability to change the windowing function to the UI
            dataPoint.real(applyBlackmanHarrisToSingleValue(dataPoint.real(), fftsize, i));

            tempData->push_back(dataPoint);
        }
        fftData.push_back(fft(tempData, fftsize));
        tempData->clear();
    }

    // update the image data
    if(fftTexture.create(fftsize, fftDuration) == 0){
        return;
    }
    
    fftImage.create(fftsize, fftDuration);

    for (int y = 0; y < fftDuration; y++)
    {
        for (int x = 0; x < fftsize; x++)
        {
            sf::Color pixel(0, 0, 0, 255);
            pixel.r = std::abs(fftData[y]->at(x).real()) / 20;
            pixel.g = std::abs(fftData[y]->at(x).real()) / 20;
            pixel.b = std::abs(fftData[y]->at(x).real()) / 20;

            fftImage.setPixel(x, y, pixel);
        }
        
    }

    fftTexture.loadFromImage(fftImage);
    fftSprite.setTexture(fftTexture);
    // seet th position to the middle of the camera
    fftSprite.setPosition(sf::Vector2f(0, 0));
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