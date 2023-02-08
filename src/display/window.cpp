#include <display/window.hpp>


disp::disp(std::shared_ptr<sf::RenderWindow> windowIn)
:window(windowIn)
{
    data = std::make_shared<signalData>();
    waveFormWindow = std::make_unique<waveForm>(data);
    window->setView(currentView);

    waterfallWindow = std::make_unique<waterFall>(data);
}

void disp::update()
{
    window->setView(currentView);
    drawUI();

    if(currentTab == waveformTab){
        waveFormWindow->update(currentView.getCenter() - sf::Vector2f(currentView.getSize().x / 2, currentView.getSize().y / 2)
                             , currentView.getCenter() + sf::Vector2f(currentView.getSize().x / 2, currentView.getSize().y / 2));
        waveFormWindow->draw(window);
    }else
    if(currentTab == waterfallTab){
        waterfallWindow->update();
        waterfallWindow->draw(window);
    }

    drawTimeScale();
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
    //TODO: add automatic calculation of fft and a loading bar in gui
    Wav file(path);
    if( !file.checkValid()){
        addDebugText("opening file at path : " + path +" failed");
        return;
    }

    uint8_t channels = file.getAmountOfChannels();
    uint32_t samples = file.getAmountOfSamples();

    data->eraseWaveformData();
    data->setSampleRate(file.getSampleRate());
    addDebugText(std::to_string(samples) + "\n");

    //TODO: add support for multiple channels
    for (uint32_t i = 0; i < samples; i++)
    {
        data->addWaveformPoint(file.getSample(i));
    }
}

void disp::addDebugText(std::string text)
{
    debugStrings.push_back(text);
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
    }else
    if(currentTab == waterfallTab)
    {
        float currentPosX = currentView.getCenter().x / waterfallWindow->getZoomX();
        waterfallWindow->zoomX(amount);
        currentPosX *= waterfallWindow->getZoomX();
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
    }else
    if(currentTab == waterfallTab)
    {
        waterfallWindow->zoomY(amount);
    }
}

void disp::drawUI()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode); 

    ImGui::Begin("menu");

    ImGui::Text("file");
    ImGui::InputText("filename", &fileName);
    ImGui::Text(fileName.c_str());
    if(ImGui::Button("open file")){
        openWavFile(fileName);
    }
    // for debugging reasons
    if(ImGui::Button("open debug file")){
        openWavFile("test.wav");
    }

    // current window settings
    //TODO: add a loading bar after it (uses a variable that's shared by the fft thread)
    ImGui::Separator();
    ImGui::Text("current window");
    const char *windows[] = {"waveform", "waterfall"};
    const char *currentVisibleValue = windows[currentTab];
    if(ImGui::BeginCombo("current window", currentVisibleValue))
    {
        for(int i = 0; i < IM_ARRAYSIZE(windows); i++)
        {
            const bool isSelected = (currentTab == i);
            if(ImGui::Selectable(windows[i], isSelected)){
                currentTab = i;
            }
        }
        ImGui::EndCombo();
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

    // fft settings
    if(currentTab == waterfallTab)
    {
        ImGui::Separator();
        ImGui::Text("fft iteration offset");
        int currentOffset = waterfallWindow->getFftOffset();
        int maxOffset = waterfallWindow->getFftSize();
        ImGui::SliderInt("fft offset", &currentOffset, 1, maxOffset);
        waterfallWindow->setFftOffset(currentOffset);
        if(ImGui::Button("recalculate")){
            waterfallWindow->recalculateFft();
        }
    }

    ImGui::Text("time scale position");
    float timeScalePosTemp = timeScalePosition;
    ImGui::SliderFloat("position", &timeScalePosTemp, -20.0, 2000.0);
    timeScalePosition = timeScalePosTemp;

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
    if(currentTab == waterfallTab){
        return waterfallWindow->getZoomX();
    }
    return -1;
}

float disp::getZoomY()
{
    if(currentTab == waveformTab){
        return waveFormWindow->getZoomY();
    }
    if(currentTab == waterfallTab){
        return waterfallWindow->getZoomY();
    }
    return -1;
}

void disp::setZoomX(float value)
{
    float difference = 0;
    if(currentTab == waveformTab){
        difference = value - waveFormWindow->getZoomX();
    }else
    if(currentTab == waterfallTab){
        difference = value - waterfallWindow->getZoomX();
    }
    zoomX(difference);
}

void disp::setZoomY(float value)
{
    float difference = 0;
    if(currentTab == waveformTab){
        difference = value - waveFormWindow->getZoomY();
    }else
    if(currentTab == waterfallTab){
        difference = value - waterfallWindow->getZoomY();
    }
    zoomY(difference);
}

float disp::getDuration()
{
    return data->getWaveformSize() / (float)data->getSampleRate();
}

void disp::drawTimeScale()
{
    float duration = getDuration();

    /*if((int)duration < duration){
        duration += 1;
    }*/

    if(currentTab == waveformTab)
    {
        sf::RectangleShape tick;
        tick.setFillColor(sf::Color::White);
        int32_t sampleRate = data->getSampleRate();
        for (int32_t i = 0; i < duration * 10; i++)
        {
            if(i % 10 == 0){
                tick.setSize(sf::Vector2f(2, 20));
            }else{
                tick.setSize(sf::Vector2f(1, 10));
            }
            tick.setPosition(sf::Vector2f((i * getZoomX() * sampleRate) / 10.0, timeScalePosition));
            window->draw(tick);
        }
    }else
    if(currentTab == waterfallTab)
    {
        sf::RectangleShape tick;
        tick.setFillColor(sf::Color::White);
        int32_t sampleRate = data->getSampleRate();
        for (int32_t i = 0; i < duration * 10; i++)
        {
            if(i % 10 == 0){
                tick.setSize(sf::Vector2f(20, 2));
            }else{
                tick.setSize(sf::Vector2f(10, 1));
            }
            tick.setPosition(sf::Vector2f(timeScalePosition, (i * getZoomY() * sampleRate) / 10.0));
            window->draw(tick);
        }
    }
}

disp::~disp()
{

}
