#include <display/window.hpp>


disp::disp(std::shared_ptr<sf::RenderWindow> windowIn)
:window(windowIn)
{
    generateDebugData();
    window->setView(currentView);
}

void disp::update()
{
    x->update();
    //window->draw(&waveFormDebugLine[0], 100, sf::LineStrip);
    x->draw(window);
    window->setView(currentView);
}

void disp::event(sf::Event e)
{
    if(e.type == sf::Event::KeyPressed)
    {
        // move up
        if(e.key.code == sf::Keyboard::Up && !e.key.shift)
        {
            moveView(sf::Vector2f(0, -10));
        }

        // move down
        if(e.key.code == sf::Keyboard::Down && ! e.key.shift)
        {
            moveView(sf::Vector2f(0, 10));
        }

        // move left
        if(e.key.code == sf::Keyboard::Left && !e.key.shift)
        {
            moveView(sf::Vector2f(-10, 0));
        }

        // move right
        if(e.key.code == sf::Keyboard::Right && !e.key.shift)
        {
            moveView(sf::Vector2f(10, 0));
        }
    }
}
void disp::generateDebugData()
{
    for (int i = 0; i < 1000; i++)
    {
        debugData[i] = rand()%255;
        x->addValue(debugData[i]);
    }
    
}

void disp::moveView(sf::Vector2f direction)
{
    currentView.setCenter( currentView.getCenter() + direction);
}

disp::~disp()
{

}
