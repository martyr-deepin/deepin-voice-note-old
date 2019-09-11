#include "myslider.h"
#include <QDebug>

MySlider::MySlider(QWidget *parent) : QWidget(parent), m_defaultHeight(DEFAULT_HEIGHT)
{
    initUI();
    initConnection();
}
MySlider::MySlider(Qt::Orientation orientation, QWidget *parent) : QWidget(parent), m_defaultHeight(DEFAULT_HEIGHT)
{
    initUI();
    initConnection();
    m_mySliderBar->setOrientation(orientation);
}
MySlider::~MySlider()
{

}

void MySlider::paintEvent(QPaintEvent *event)
{

    int sliderPos = (m_mySliderBar->sliderPosition() * (m_mySliderBar->width())) / (m_mySliderBar->maximum());
    //int sliderPos = this->sliderPosition() - (m_sliderhandler->width() / 2);
//    qDebug() << "slider pos:" << sliderPos;
//    qDebug() << "maximum:" << this->maximum() << ", minimum:" << this->minimum() << ", value:" << this->value() << ", sliderPosition:" << this->sliderPosition();

    m_sliderHandler->setGeometry(sliderPos, 0, m_sliderHandler->width(), m_sliderHandler->height());
    m_mySliderBar->setGeometry(m_sliderHandler->width()/ 2, 0, this->width() - m_sliderHandler->width(), this->height());
}

void MySlider::mousePressEvent(QMouseEvent *event)
{
    m_mySliderBar->mousePressEvent(event);
}
void MySlider::mouseReleaseEvent(QMouseEvent *event)
{
    m_mySliderBar->mouseReleaseEvent(event);
}
void MySlider::mouseMoveEvent(QMouseEvent *event)
{
    m_mySliderBar->mouseMoveEvent(event);
}

int MySlider::getHandlerWidth()
{
    return m_sliderHandler->width();
}


void MySlider::initUI()
{
    m_mySliderBar = new MySliderBar(this);
    m_sliderHandler = new SliderHandler(this);
    m_mySliderBar->setRange(0,100);
    m_mySliderBar->setPageStep(1);
    //this->setStyleSheet("background: green");
}

void MySlider::initConnection()
{
    //connect(m_mySliderBar, SIGNAL(sliderMoved(INT)), this, SIGNAL(sliderMoved(INT)));
    connect(m_mySliderBar, SIGNAL(sliderPressed()), this, SIGNAL(sliderPressed()));
    connect(m_mySliderBar, SIGNAL(sliderReleased()), this, SIGNAL(sliderReleased()));
}

void MySlider::setSliderPostion(int sliderPos)
{
    qDebug() << "setSliderPostion: " << sliderPos << ", max:" << m_mySliderBar->maximum();
    m_mySliderBar->setSliderPosition(sliderPos);
}

void MySlider::setPageStep(int ti)
{
    m_mySliderBar->setPageStep(ti);
}

void MySlider::setRange(int min, int max)
{
    m_mySliderBar->setRange(min, max);
}

int MySlider::sliderPosition()
{
    return m_mySliderBar->sliderPosition();
}

void MySlider::setTimeText(QString time)
{
    m_sliderHandler->m_timeLabel->setText(time);
}
