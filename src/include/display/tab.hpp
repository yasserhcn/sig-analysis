#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class tab
{
public:
    tab();

    /**
     * @brief draw the tab
     * 
     * @param windowIn pointer to the window
     */
    virtual void draw(sf::RenderWindow *windowIn) { }

    /**
     * @brief update function, runs every frame
     * 
     */
    virtual void update() { }

    ~tab();
private:

};


class waveForm : public tab
{
public:
    waveForm();

    /**
     * @brief adds a value to the data vector
     * 
     * @param val value to add
     */
    void addValue(u_int64_t val);

    /**
     * @brief draw the waveform
     * 
     */
    void draw(std::shared_ptr<sf::RenderWindow> windowIn);

    /**
     * @brief update the current waveform drawing
     * 
     */
    void update();

    ~waveForm();
private:
    std::vector<u_int64_t> dataPoints;

    sf::VertexArray graph;

    float currentZoom;
};
