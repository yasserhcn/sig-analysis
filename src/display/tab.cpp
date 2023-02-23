#include <display/tab.hpp>

tab::tab(std::shared_ptr<signalData> dataIn)
: data(dataIn)
{
}

void tab::zoomX(float value)
{
    zoomXAmount += value / 10;
}

void tab::zoomY(float value)
{
    zoomYAmount += value / 10;
}

float tab::getZoomX()
{
    return zoomXAmount;
}

float tab::getZoomY()
{
    return zoomYAmount;
}

std::shared_ptr<signalData> tab::getData()
{
    return data;
}

tab::~tab()
{
}