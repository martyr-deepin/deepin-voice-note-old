#ifndef MYSLIDER_H
#define MYSLIDER_H

#include "mysliderbar.h"
#include "sliderhandle.h"
#include "replaysliderbar.h"

#include <QWidget>
#include <DLabel>
#include <DPalette>

#define SLIDER_DEFAULT_HEIGHT 141
#define SLIDER_HANDLE_TEXT_HEIGHT 33


DWIDGET_USE_NAMESPACE

//录音拖拽slider
class MySlider : public DWidget
{
    Q_OBJECT
public:
    MySlider(QWidget *parent = 0);
    MySlider(Qt::Orientation orientation, QWidget *parent = 0);
    ~MySlider();


    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;
    int getHandlerWidth();
    void setSliderPostion(int sliderPos);
    void setPageStep(int ti);
    void setRange(int min, int max);
    int m_defaultHeight;
    int m_handleTextHeight;
    int sliderPosition();
    void setTimeText(QString time);
    //QPixmap renderSVG(const QString &filePath, const QSize &size);
    int getSliderHandlerWidth();
    int gethandlePos();
    void showSlider();

signals:
    void sliderMoved(int value);
    void sliderPressed();
    void sliderReleased();
    void sigSliderPos(int pos);

public slots:
    void changeTheme();
    void OnSliderMoved(int newTime);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


private:
    //DSlider *m_replaySliderBar;
    //ReplaySliderBar *m_replaySliderBar;
    MySliderBar *m_mySliderBar;
    SliderHandle *m_sliderHandler;
    int m_sliderPos;
    bool m_isPressed;
    bool m_withMouse;
    int m_mouseX;
    //SliderHandler *m_sliderHandler;

    void initUI();
    void initConnection();
};

#endif // MYSLIDER_H
