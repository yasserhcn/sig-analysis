#include <display/window.hpp>


disp::disp(std::shared_ptr<sf::RenderWindow> windowIn)
:window(windowIn)
{
    generateDebugData();
}

void disp::update()
{
    x->update();
    //window->draw(&waveFormDebugLine[0], 100, sf::LineStrip);
    x->draw(window);
}

void disp::event(sf::Event e)
{
    
}
void disp::generateDebugData()
{
    for (int i = 0; i < 1000; i++)
    {
        debugData[i] = rand()%255;
        x->addValue(debugData[i]);
    }
    
}

disp::~disp()
{

}
