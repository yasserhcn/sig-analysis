#pragma once

#include <display/tab.hpp>


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
