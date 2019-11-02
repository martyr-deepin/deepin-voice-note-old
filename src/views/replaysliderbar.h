#ifndef REPLAYSLIDERBAR_H
#define REPLAYSLIDERBAR_H

#include <DSlider>


DWIDGET_USE_NAMESPACE

class ReplaySliderBar : public DSlider
{
    Q_OBJECT
public:
    explicit ReplaySliderBar(Qt::Orientation orientation = Qt::Horizontal ,QWidget *parent = nullptr);

signals:

public slots:
};

#endif // REPLAYSLIDERBAR_H
