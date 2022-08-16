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

void waveForm::update()
{
    uint64_t amountOfPoints = getData()->getWaveformSize();
    if(amountOfPoints > graph.getVertexCount())
    {
        // using linestrip
        for (int i = 0; i < graph.getVertexCount(); i++)
        {
            int64_t val = getData()->getWaveformData(i);
            graph[i].position = sf::Vector2f(i * getZoomX(), -(val * getZoomY()) + 500);
        }

        for (int i = graph.getVertexCount(); i < amountOfPoints; i++)
        {
            int64_t val = getData()->getWaveformData(i);
            graph.append(sf::Vertex(sf::Vector2f(i * getZoomX(), -(val * getZoomY()) + 500)));
            graph[i].color = sf::Color::Green;
        }
        
    }else
    {
        for (int i = 0; i < amountOfPoints; i++)
        {
            int64_t val = getData()->getWaveformData(i);
            graph[i].position = sf::Vector2f(i * getZoomX(), -(val * getZoomY()) + 500);
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