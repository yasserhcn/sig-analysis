#pragma once

#include <SFML/Graphics.hpp>
#include <display/tab.hpp>

class disp
{
public:
    /**
     * @brief Construct a new disp object
     * 
     * @param windowIn pointer to the window
     */
    disp(sf::RenderWindow *windowIn);

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
    sf::RenderWindow *window;

    std::unique_ptr<waveForm> x = std::make_unique<waveForm>();

    sf::VertexArray waveFormDebugLine;

    void updateDebugLine(); 
    void generateDebugData();
    char debugData[100];

    
};
