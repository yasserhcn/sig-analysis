#pragma once

#include <display/tab.hpp>

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

    /**
     * @brief get the offset of the fft
     * 
     * @return int the fft offset
     */
    int getFftOffset();

    /**
     * @brief Set the fft fffset
     * 
     * @param offset amount of offset
     */
    void setFftOffset(int offset);

    /**
     * @brief Get the size of the fft
     * 
     * @return int with the size
     */
    int getFftSize();

private:
    std::vector<int64_t> dataPoints;

    std::vector<std::shared_ptr<std::vector<std::complex<float>>>> fftData;

    sf::Sprite fftSprite;
    sf::Image fftImage;
    sf::Texture fftTexture;

    int fftsize = 2048;
    int fftOffset = 512;

    bool tempDebug = true;
};
