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


class waveForm : public tab
{
public:
    waveForm(std::shared_ptr<signalData> dataIn);

    /**
     * @brief adds a value to the data vector
     * 
     * @param val value to add
     */
    void addValue(int64_t val);

    /**
     * @brief removes all the data points from the tab
     * 
     */
    void eraseAllData();

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
    void update(sf::Vector2f topLeftWindowPos, sf::Vector2f bottomRightPos);

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


class waterFall : public tab
{
public:
    waterFall(std::shared_ptr<signalData> dataIn);

    /**
     * @brief recalculate the fft and update the waterfall
     * 
     */
    void recalculateFft();

    /**
     * @brief draw the waterfall
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
     * @brief ste the size of the fft
     * 
     * @param size size, must be a power of 2
     * @return true when the size is valid, false when valu eisn't changed
     */
    bool setFftSize(int size);

    /**
     * @brief add a data point to the signal
     * 
     */
    void addDataPoint(int64_t value);

    /**
     * @brief remove all the data
     * 
     */
    void eraseAllData();

private:
    std::vector<int64_t> dataPoints;

    std::vector<std::shared_ptr<std::vector<std::complex<float>>>> fftData;

    sf::Sprite fftSprite;
    sf::Image fftImage;
    sf::Texture fftTexture;

    int fftsize = 512;

    bool tempDebug = true;
};
