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
    drawUI();
    x->draw(window);
    window->setView(currentView);
}

void disp::event(sf::Event e)
{
    if(e.type == sf::Event::KeyPressed)
    {
        if(!e.key.shift)
        {
            int multiplier = 1;
            if(e.key.control)
            {
                multiplier = 5;
            }
            // move up
            if(e.key.code == sf::Keyboard::Up)
            {
                moveView(sf::Vector2f(0, -moveAmount * multiplier));
            }

            // move down
            if(e.key.code == sf::Keyboard::Down)
            {
                moveView(sf::Vector2f(0, moveAmount * multiplier));
            }

            // move left
            if(e.key.code == sf::Keyboard::Left)
            {
                moveView(sf::Vector2f(-moveAmount * multiplier, 0));
            }

            // move right
            if(e.key.code == sf::Keyboard::Right)
            {
                moveView(sf::Vector2f(moveAmount * multiplier, 0));
            }
        }else
        {
            if(e.key.code == sf::Keyboard::Up)
            {
                zoomY(0.2);
            }
            if(e.key.code == sf::Keyboard::Down)
            {
                zoomY(-0.2);
            }
            if(e.key.code == sf::Keyboard::Left)
            {
                zoomX(0.2);
            }
            if(e.key.code == sf::Keyboard::Right)
            {
                zoomX(-0.2);
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
    if(amount > 1 || amount < -1){
        return;
    }

    if(currentView.getViewport().width + amount < 0){
        return;
    }

    currentView.setViewport(sf::FloatRect(
        currentView.getViewport().left - (amount / 2),
        currentView.getViewport().top,
        currentView.getViewport().width + amount,
        currentView.getViewport().height
    ));
}

void disp::zoomY(float amount)
{
    if(amount > 1 || amount < -1){
        return;
    }

    if(currentView.getViewport().height + amount < 0){
        return;
    }

    currentView.setViewport(sf::FloatRect(
        currentView.getViewport().left,
        currentView.getViewport().top - (amount / 2),
        currentView.getViewport().width,
        currentView.getViewport().height + amount
    ));
}

void disp::drawUI()
{
    ImGui::Begin("hello world");

    ImGui::Separator();
    ImGui::Text("move amount");
    ImGui::SliderFloat("##", getMoveAmountPtr(), 1, 100);

    ImGui::End();
}

float *disp::getMoveAmountPtr()
{
    return &moveAmount;
}

disp::~disp()
{

}
