#include <display/tab.hpp>

tab::tab()
{
}

tab::~tab()
{
}

////////////////////////////////////////////////////

waveForm::waveForm()
{

}

void waveForm::addValue(u_int64_t val)
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
            graph[i].position = sf::Vector2f(i * 5, -dataPoints[i] + 200);
        }

        for (int i = graph.getVertexCount(); i < dataPoints.size(); i++)
        {
            graph.append(sf::Vertex(sf::Vector2f(i * 5, -dataPoints[i] + 200)));
        }
        
    }else
    {
        for (int i = 0; i < dataPoints.size(); i++)
        {
            graph[i].position = sf::Vector2f(i * 5, -dataPoints[i] + 200);
        }
    }
}

void waveForm::drawUI()
{
    float n;
    ImGui::Begin("waveform");


    ImGui::Text("move amount");
    ImGui::SliderFloat("##", &n, 0, 5);


    ImGui::End();
}

waveForm::~waveForm()
{
    
}