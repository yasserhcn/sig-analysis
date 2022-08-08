#include <display/window.hpp>


disp::disp(std::shared_ptr<sf::RenderWindow> windowIn)
:window(windowIn)
{
    data = std::make_shared<signalData>();
    waveFormWindow = std::make_unique<waveForm>(data);
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
                zoomY(0.05);
            }
            if(e.key.code == sf::Keyboard::Down)
            {
                zoomY(-0.05);
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
        addDebugText("opening file at path : " + path +" failed");
        return;
    }

    uint8_t channels = file.getAmountOfChannels();
    uint32_t samples = file.getAmountOfSamples();

    data->eraseWaveformData();
    data->setSampleRate(9600);

    if(currentTab == waveformTab)
    {
        for (uint32_t i = 0; i < samples; i++)
        {
            data->addWaveformPoint(file.getSample(i));
        }
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

    if(currentTab == waveformTab)
    {
        float currentPosX = currentView.getCenter().x / waveFormWindow->getZoomX();
        waveFormWindow->zoomX(amount);
        currentPosX *= waveFormWindow->getZoomX();
        currentView.setCenter(sf::Vector2f(currentPosX, currentView.getCenter().y));
    }
}

void disp::zoomY(float amount)
{
    if(amount > 1 || amount < -1){
        return;
    }

    if(currentTab == waveformTab)
    {
        waveFormWindow->zoomY(amount);
    }
}

void disp::drawUI()
{
    ImGui::Begin("hello world");

    ImGui::Text("file");
    ImGui::InputText("filename", &fileName);
    ImGui::Text(fileName.c_str());
    if(ImGui::Button("open file")){
        openWavFile(fileName);
    }

    // move settings 
    ImGui::Separator();
    ImGui::Text("move amount");
    ImGui::SliderFloat("##", getMoveAmountPtr(), 1, 100);

    // zoom settings
    ImGui::Separator();
    ImGui::Text("zoom");
    float windowWidth = getZoomX();
    float windowHeight = getZoomY();
    ImGui::SliderFloat("window width", &windowWidth, 0.09, 2);
    ImGui::SliderFloat("window height", &windowHeight, 0.001, 0.05);
    setZoomX(windowWidth);
    setZoomY(windowHeight);

    // current position
    if(currentTab == waveformTab &&  data->getSampleRate() > 0)
    {
        ImGui::Separator();
        ImGui::Text("current position");
        float currentPosition = currentView.getCenter().x / getZoomX() / data->getSampleRate();
        float maxVal = getDuration();
        ImGui::SliderFloat("view position", &currentPosition, 0, maxVal);
        if(currentPosition != currentView.getCenter().x / getZoomX() / data->getSampleRate())
        {
            currentView.setCenter(sf::Vector2f(currentPosition * getZoomX() * data->getSampleRate(), currentView.getCenter().y));
        }
    }

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

float disp::getZoomX()
{
    if(currentTab == waveformTab){
        return waveFormWindow->getZoomX();
    }
    return -1;
}

float disp::getZoomY()
{
    if(currentTab == waveformTab){
        return waveFormWindow->getZoomY();
    }
    return -1;
}

void disp::setZoomX(float value)
{
    float difference = 0;
    if(currentTab == waveformTab){
        difference = value - waveFormWindow->getZoomX();
    }
    zoomX(difference);
}

void disp::setZoomY(float value)
{
    float difference = 0;
    if(currentTab == waveformTab){
        difference = value - waveFormWindow->getZoomY();
    }
    zoomY(difference);
}

float disp::getDuration()
{
    return data->getWaveformSize() / data->getSampleRate();
}

disp::~disp()
{

}
