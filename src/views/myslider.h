#ifndef MYSLIDER_H
#define MYSLIDER_H

#include "mysliderbar.h"
#include "sliderhandle.h"

#include <QWidget>
#include <DLabel>

#define SLIDER_DEFAULT_HEIGHT 141
#define SLIDER_HANDLE_TEXT_HEIGHT 33


DWIDGET_USE_NAMESPACE

//录音拖拽slider
class MySlider : public QWidget
{
    Q_OBJECT
public:
    MySlider(QWidget *parent = 0);
    MySlider(Qt::Orientation orientation, QWidget *parent = 0);
    ~MySlider();



    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    int getHandlerWidth();
    void setSliderPostion(int sliderPos);
    void setPageStep(int ti);
    void setRange(int min, int max);
    int m_defaultHeight;
    int m_handleTextHeight;
    int sliderPosition();
    void setTimeText(QString time);

signals:
    void sliderMoved(int value);
    void sliderPressed();
    void sliderReleased();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


private:
    MySliderBar *m_mySliderBar;
    SliderHandle *m_sliderHandler;
    //SliderHandler *m_sliderHandler;

    void initUI();
    void initConnection();
};

#endif // MYSLIDER_H
