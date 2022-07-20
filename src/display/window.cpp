#include <display/window.hpp>


disp::disp(std::shared_ptr<sf::RenderWindow> windowIn)
:window(windowIn)
{
    generateDebugData();
    window->setView(currentView);
}

void disp::update()
{
    waveFormWindow->update();
    //window->draw(&waveFormDebugLine[0], 100, sf::LineStrip);
    drawUI();
    waveFormWindow->draw(window);
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

void disp::openWavFile(std::string path)
{
    Wav file(path);
    if( !file.checkValid()){
        return;
    }

    uint8_t channels = file.getAmountOfChannels();
    uint32_t samples = file.getAmountOfSamples();
    addDebugText(std::to_string(samples));
    addDebugText(std::to_string(channels));
    for (uint32_t i = 0; i < samples; i++)
    {
        waveFormWindow->addValue(file.getSample(i)/100);
    }
    
}

void disp::addDebugText(std::string text)
{
    debugStrings.push_back(text);
}

void disp::generateDebugData()
{
    for (int i = 0; i < 100; i++)
    {
        debugData[i] = rand()%255;
        waveFormWindow->addValue(debugData[i]);
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

    // move settings 
    ImGui::Separator();
    ImGui::Text("move amount");
    ImGui::SliderFloat("##", getMoveAmountPtr(), 1, 100);

    // zoom settings
    ImGui::Separator();
    ImGui::Text("zoom");
    float windowWidth = currentView.getViewport().width;
    float windowHeight = currentView.getViewport().height;
    ImGui::SliderFloat("window width", &windowWidth, 0.08, 25);
    ImGui::SliderFloat("window height", &windowHeight, 0.08, 2);
    currentView.setViewport(sf::FloatRect(
        currentView.getViewport().left,
        currentView.getViewport().top,
        windowWidth,
        windowHeight
    ));

    // debug stuff
    ImGui::Separator();
    if(ImGui::TreeNode("debug data"))
    {
        ImGui::BeginChild("debug text");
        for(int i = 0; i < debugStrings.size(); i++)
        {
            ImGui::Text(debugStrings[i].c_str());
        }
        ImGui::EndChild();
        ImGui::TreePop();
    }

    ImGui::End();
}

float *disp::getMoveAmountPtr()
{
    return &moveAmount;
}

disp::~disp()
{

}
