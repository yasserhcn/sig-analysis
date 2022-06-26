#pragma once

#include <SFML/Graphics.hpp>

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

    ~disp();
private:
    sf::RenderWindow *window;

    sf::VertexArray waveFormDebugLine;

    void updateDebugLine(); 
    void generateDebugData();
    char debugData[100];

};
