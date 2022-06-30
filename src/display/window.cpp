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
        if(!e.key.shift)
        {
            int moveAmount = 10;
            if(e.key.control)
            {
                moveAmount = 80;
            }
            // move up
            if(e.key.code == sf::Keyboard::Up)
            {
                moveView(sf::Vector2f(0, -moveAmount));
            }

            // move down
            if(e.key.code == sf::Keyboard::Down)
            {
                moveView(sf::Vector2f(0, moveAmount));
            }

            // move left
            if(e.key.code == sf::Keyboard::Left)
            {
                moveView(sf::Vector2f(-moveAmount, 0));
            }

            // move right
            if(e.key.code == sf::Keyboard::Right)
            {
                moveView(sf::Vector2f(moveAmount, 0));
            }
        }else
        {
            if(e.key.code == sf::Keyboard::Up)
            {
                zoomX(-0.2);
                zoomY(-0.2);
            }
            if(e.key.code == sf::Keyboard::Down)
            {
                zoomX(0.2);
                zoomY(0.2);
            }
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

void disp::zoomX(float amount)
{
    currentView.setViewport(sf::FloatRect(
        currentView.getViewport().left,
        currentView.getViewport().top,
        currentView.getViewport().width + amount,
        currentView.getViewport().height
    ));
}

void disp::zoomY(float amount)
{
    currentView.setViewport(sf::FloatRect(
        currentView.getViewport().left,
        currentView.getViewport().top,
        currentView.getViewport().width,
        currentView.getViewport().height + amount
    ));
}

disp::~disp()
{

}
