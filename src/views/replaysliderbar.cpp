#include "replaysliderbar.h"

ReplaySliderBar::ReplaySliderBar(Qt::Orientation orientation, QWidget *parent) : DSlider(orientation, parent)
{
    this->slider()->hide();
}
