#include <display/tabs/waveform.hpp>


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
