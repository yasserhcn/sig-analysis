#include <display/tab.hpp>

tab::tab()
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

tab::~tab()
{
}

////////////////////////////////////////////////////

waveForm::waveForm()
{

}

void waveForm::addValue(int64_t val)
{
    dataPoints.push_back(val);
}

void waveForm::draw(std::shared_ptr<sf::RenderWindow> windowIn)
{
    windowIn->draw(&graph[0], graph.getVertexCount(), sf::LineStrip);
}

void waveForm::update()
{
    if(dataPoints.size() > graph.getVertexCount())
    {
        // using linestrip
        for (int i = 0; i < graph.getVertexCount(); i++)
        {
            graph[i].position = sf::Vector2f(i * getZoomX(), -(dataPoints[i] * getZoomY()) + 500);
        }

        for (int i = graph.getVertexCount(); i < dataPoints.size(); i++)
        {
            graph.append(sf::Vertex(sf::Vector2f(i * getZoomX(), -(dataPoints[i] * getZoomY()) + 500)));
            graph[i].color = sf::Color::Green;
        }
        
    }else
    {
        for (int i = 0; i < dataPoints.size(); i++)
        {
            graph[i].position = sf::Vector2f(i * getZoomX(), -(dataPoints[i] * getZoomY()) + 500);
        }
    }
}

int64_t waveForm::getAmountDataPoints()
{
    return dataPoints.size();
}

void waveForm::drawUI()
{
    
}

waveForm::~waveForm()
{
    
}