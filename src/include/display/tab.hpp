#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <../imgui/imgui.h>

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

    /**
     * @brief draw the ui for the current window
     * 
     */
    virtual void drawUI() { }

    /**
     * @brief increase/decrease the zoom on the x axis
     * 
     * @param value amount between -1 and 1
     */
    void zoomX(float value);

    /**
     * @brief increase/decrease the zoom on the y axis
     * 
     * @param value amount between -1 and 1
     */
    void zoomY(float value);

    /**
     * @brief Get the amount of zoom in the x axis
     * 
     * @return float 
     */
    float getZoomX();

    /**
     * @brief Get the amount of zoom in the y axis
     * 
     * @return float 
     */
    float getZoomY();

    ~tab();
private:
    float zoomXAmount = 0.08;
    float zoomYAmount = 0.01;
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
    void addValue(int64_t val);

    /**
     * @brief draw the waveform
     * 
     */
    void draw(std::shared_ptr<sf::RenderWindow> windowIn);

    /**
     * @brief draw the UI of the waveform window
     * 
     */
    void drawUI();

    /**
     * @brief update the current waveform drawing
     * 
     */
    void update();

    /**
     * @brief Get the Amount Data Points
     * 
     * @return int64_t 
     */
    int64_t getAmountDataPoints();

    ~waveForm();
private:
    std::vector<int64_t> dataPoints;

    sf::VertexArray graph;

    float currentZoom;
};
