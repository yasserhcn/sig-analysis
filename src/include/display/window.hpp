#pragma once

#include <SFML/Graphics.hpp>
#include <display/tab.hpp>
#include <memory>
#include <files/openWav.hpp>
#include <imgui/misc/cpp/imgui_stdlib.h>

class disp
{
public:
    /**
     * @brief Construct a new disp object
     * 
     * @param windowIn pointer to the window
     */
    disp(std::shared_ptr<sf::RenderWindow> windowIn);

    /**
     * @brief runs every tick, updates and draws the current running window
     * 
     */
    void update();

    /**
     * @brief called when there's a window event
     * 
     * @param e the event
     */
    void event(sf::Event e);

    /**
     * @brief update the move amount when a key is pressed
     * 
     * @param return pointer to move amount
     */
    float *getMoveAmountPtr();

    /**
     * @brief open a wav file to be displayed
     * 
     */
    void openWavFile(std::string path);

    /**
     * @brief add a text to the debug window
     * 
     * @param text the debug text
     */
    void addDebugText(std::string text);

    ~disp();
private:
    //sf::RenderWindow *window;
    std::shared_ptr<sf::RenderWindow> window;

    std::unique_ptr<waveForm> waveFormWindow = std::make_unique<waveForm>();

    enum windowEvents
    {
        mouseDrag,
        zoomIn,
        zoomOut,
        zoomXIn,
        zoomXOut,
        zoomYIn,
        zoomYOut,
        moveLeft,
        moveRight
    };

    enum tabs
    {
        waveformTab
    };
    
    std::string fileName;

    int currentTab = waveformTab;

    bool mouseIsDown;

    sf::View currentView;

    float moveAmount = 1;

    void generateDebugData();
    char debugData[1000];

    std::vector<std::string> debugStrings;

    /**
     * @brief move the view in a certain direction
     * 
     * @param direction the direction to move to
     */
    void moveView(sf::Vector2f direction);

    /**
     * @brief zoom the view in the X axis
     * 
     * @param amount the amount of zoom (negative to zoom in, positive to zoom out)
     */
    void zoomX(float amount);

    /**
     * @brief zoom the view in the Y axis
     * 
     * @param amount the amount of zoom (negative to zoom in, positive to zoom out)
     */
    void zoomY(float amount);

    /**
     * @brief Get the zoom in the x axis of the current window
     * 
     * @return float 
     */
    float getZoomX();

    /**
     * @brief Get the zoom in the y axis of the current window
     * 
     * @return float 
     */
    float getZoomY();

    /**
     * @brief Set the amount of zoom in the x axis of the current window
     * 
     * @param value zoom amount in the x axis
     */
    void setZoomX(float value);

    /**
     * @brief Set the amount of zoom in the y axis of the current window
     * 
     * @param value zoom amount in the y axis
     */
    void setZoomY(float value);

    /**
     * @brief draw the UI for movement
     * 
     */
    void drawUI();
};
