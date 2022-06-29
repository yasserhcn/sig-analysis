#include <display/window.hpp>


disp::disp(std::shared_ptr<sf::RenderWindow> windowIn)
:window(windowIn)
{
    generateDebugData();
}

void disp::update()
{
    updateDebugLine();
    x->update();
    //window->draw(&waveFormDebugLine[0], 100, sf::LineStrip);
    x->draw(window);
}

void disp::event(sf::Event e)
{
    
}

void disp::updateDebugLine()
{
    
    for (int i = 0; i < 100; i++)
    {
        waveFormDebugLine.append(sf::Vertex(sf::Vector2f(i*5, debugData[i] + 200)));
    }
    
}

void disp::generateDebugData()
{
    for (int i = 0; i < 100; i++)
    {
        debugData[i] = rand()%255;
        x->addValue(debugData[i]);
    }
    
}

disp::~disp()
{

}
