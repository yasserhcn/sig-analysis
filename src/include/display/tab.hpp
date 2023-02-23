#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <complex>
#include <fstream>
#include <../imgui/imgui.h>
#include <display/data.hpp>
#include <dsp/fft.hpp>

class tab
{
public:
    tab(std::shared_ptr<signalData> dataIn);

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

    /**
     * @brief Get the pointer to the data element
     * 
     * @return std::shared_ptr<signalData> 
     */
    std::shared_ptr<signalData> getData();

    ~tab();
private:
    float zoomXAmount = 0.08;
    float zoomYAmount = 0.01;

    std::shared_ptr<signalData> data;
};