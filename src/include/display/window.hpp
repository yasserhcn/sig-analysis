#pragma once

#include <SFML/Graphics.hpp>
#include <display/tab.hpp>
#include <memory>

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

    ~disp();
private:
    //sf::RenderWindow *window;
    std::shared_ptr<sf::RenderWindow> window;

    std::unique_ptr<waveForm> x = std::make_unique<waveForm>();

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

    bool mouseIsDown;

    sf::View currentView;

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

    void generateDebugData();
    char debugData[1000];
};
