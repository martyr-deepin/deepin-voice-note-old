#include "myslider.h"
#include "uiutil.h"
#include "intancer.h"
#include <QDebug>
#include <QMouseEvent>
#include <QImageReader>
#include <DFontSizeManager>
#include <DApplicationHelper>



MySlider::MySlider(QWidget *parent) : DWidget(parent), m_defaultHeight(SLIDER_DEFAULT_HEIGHT), m_handleTextHeight(SLIDER_HANDLE_TEXT_HEIGHT)
{

    m_mouseX = 0;
    m_sliderPos = 0;
    m_withMouse = false;
    m_isPressed = false;
    initUI();
    initConnection();
}
MySlider::MySlider(Qt::Orientation orientation, QWidget *parent) : QWidget(parent), m_defaultHeight(SLIDER_DEFAULT_HEIGHT), m_handleTextHeight(SLIDER_HANDLE_TEXT_HEIGHT)
{

    m_mouseX = 0;
    m_sliderPos = 0;
    m_withMouse = false;
    m_isPressed = false;
    initUI();
    initConnection();

    m_mySliderBar->setOrientation(orientation);
    //m_replaySliderBar->slider()->setOrientation(orientation);
}
MySlider::~MySlider()
{

}

void MySlider::paintEvent(QPaintEvent *event)
{
    int curSliderPos = (m_mySliderBar->sliderPosition() * (m_mySliderBar->width())) / (m_mySliderBar->maximum());
    //int curSliderPos = (m_replaySliderBar->slider()->sliderPosition() * (m_replaySliderBar->width())) / (m_replaySliderBar->maximum());
    //int sliderPos = this->sliderPosition() - (m_sliderhandler->width() / 2);
//    qDebug() << "slider pos:" << sliderPos;
//    qDebug() << "maximum:" << this->maximum() << ", minimum:" << this->minimum() << ", value:" << this->value() << ", sliderPosition:" << this->sliderPosition();

    if(!m_withMouse)
    {
        m_sliderHandler->setGeometry(curSliderPos, 0, m_sliderHandler->width(), m_sliderHandler->height());
    }
    else
    {
        //start add by yuanshuai 20191119 bug 3360
        if(m_mouseX < 25)
        {
            m_mouseX = 25;
        }
        else if(m_mouseX > (m_mySliderBar->width() + 25))
        {
            m_mouseX = m_mySliderBar->width() + 25;
        }
        else
        {
            //do nothing
        }
        //end
        m_sliderHandler->setGeometry(m_mouseX - m_sliderHandler->width()/2, 0, m_sliderHandler->width(), m_sliderHandler->height());
    }

    m_mySliderBar->setGeometry(m_sliderHandler->width()/ 2, 0, this->width() - m_sliderHandler->width(), this->height());

    //m_replaySliderBar->setGeometry(m_sliderHandler->width()/ 2, 0, this->width() - m_sliderHandler->width(), this->height());


    if(m_sliderPos != curSliderPos)
    {
        m_sliderPos = curSliderPos;
        if(m_withMouse)
        {
            curSliderPos = m_mouseX - m_sliderHandler->width()/2;
        }

        qDebug()<<"MySlider::paintEvent curSliderPos:"<<curSliderPos;
        emit sigSliderPos(curSliderPos);
    }
}

void MySlider::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"slider press x:"<<event->x();
    //if((116 > event->y()) && (event->x() > 13)) //ynb 20191109
    //{
        qDebug()<<"mousePressEvent";
        m_mySliderBar->mousePressEvent(event);
        m_isPressed = true;
        m_withMouse = true;
        m_mouseX = event->x();

    //}
}
void MySlider::mouseReleaseEvent(QMouseEvent *event)
{
    //if((116 > event->y()) && (event->x() > 13)) //ynb 20191109
    {
        qDebug()<<"mouseReleaseEvent";
        m_isPressed = false;
        m_mouseX = event->x();
        m_mySliderBar->mouseReleaseEvent(event);
    }
}
void MySlider::mouseMoveEvent(QMouseEvent *event)
{
    //if((116 > event->y()) && (event->x() > 13)) //ynb 20191109
    {
        m_mouseX = event->x();
        m_mySliderBar->mouseMoveEvent(event);
        if(m_isPressed && m_withMouse)
        {
            int curSliderPos = m_mouseX - m_sliderHandler->width()/2;
            emit sigSliderPos(curSliderPos);
            qDebug()<<"curSliderPos:"<<curSliderPos;
            this->update();
        }
    }
}

void MySlider::wheelEvent(QWheelEvent *e)
{
    qDebug()<<"MySlider::wheelEvent";
}

int MySlider::getHandlerWidth()
{
    return m_sliderHandler->width();
}


void MySlider::initUI()
{
    m_sliderHandler = new SliderHandle(this);
    QPalette pal;

    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();

    if(themeType == DGuiApplicationHelper::LightType)
    {
        pal.setBrush(QPalette::Background, QBrush(UiUtil::renderSVG(":/image/icon/normal/slider.svg", QSize(m_sliderHandler->width(), m_sliderHandler->height()),Intancer::get_Intancer()->getApp())));
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        pal.setBrush(QPalette::Background, QBrush(UiUtil::renderSVG(":/image/icon_dark/normal/slider_dark.svg", QSize(m_sliderHandler->width(), m_sliderHandler->height()),Intancer::get_Intancer()->getApp())));
    }
    m_sliderHandler->setAutoFillBackground(true);
    m_sliderHandler->setPalette(pal);
    m_sliderHandler->setAlignment(Qt::AlignHCenter| Qt::AlignTop);

//    QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T8);
//    m_sliderHandler->setFont(labelFont);
    DFontSizeManager::instance()->bind(m_sliderHandler,DFontSizeManager::T8);
    m_sliderHandler->setContentsMargins(0, 8, 0, 0);
    m_mySliderBar = new MySliderBar(this);
    //m_sliderHandler = new SliderHandler(this);
    m_mySliderBar->setRange(0,100);
    m_mySliderBar->setPageStep(1);
    m_mySliderBar->setVisible(false);

    //m_mySliderBar->setStyleSheet("background-color: rgb(255,255,0)");
    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &MySlider::changeTheme);
//    m_replaySliderBar = new DSlider(Qt::Horizontal,this);
//    m_replaySliderBar->setIconSize(QSize(1,20));
//    m_replaySliderBar->setAttribute(Qt::WA_TransparentForMouseEvents,true);
//    m_replaySliderBar->setWindowFlags(Qt::FramelessWindowHint);
//    m_replaySliderBar->setAttribute(Qt::WA_TranslucentBackground);

}


void MySlider::initConnection()
{
    //connect(m_mySliderBar, SIGNAL(sliderMoved(INT)), this, SIGNAL(sliderMoved(INT)));
    connect(m_mySliderBar, SIGNAL(sigMove(int)), this, SLOT(OnSliderMoved(int)));
    connect(m_mySliderBar, SIGNAL(sigRelease(int)), this, SLOT(OnSliderMoved(int)));
    connect(m_mySliderBar, SIGNAL(sliderPressed()), this, SIGNAL(sliderPressed()));
    connect(m_mySliderBar, SIGNAL(sliderReleased()), this, SIGNAL(sliderReleased()));

//    connect(m_replaySliderBar, SIGNAL(sliderMoved(INT)), this, SIGNAL(sliderMoved(INT)));
//    connect(m_replaySliderBar, SIGNAL(sliderPressed()), this, SIGNAL(sliderPressed()));
//    connect(m_replaySliderBar, SIGNAL(sliderReleased()), this, SIGNAL(sliderReleased()));
}

void MySlider::setSliderPostion(int sliderPos)
{
    //qDebug() << "setSliderPostion: " << sliderPos << ", max:" << m_mySliderBar->maximum();
    if(!m_isPressed)
    {
        m_withMouse = false;
    }

    m_mySliderBar->setSliderPosition(sliderPos);
    m_mySliderBar->setValue(sliderPos);

    //m_replaySliderBar->slider()->setSliderPosition(sliderPos);
    //m_replaySliderBar->setValue(sliderPos);
}

void MySlider::setPageStep(int ti)
{
    m_mySliderBar->setPageStep(ti);
    //m_replaySliderBar->setPageStep(ti);
}

void MySlider::setRange(int min, int max)
{
    m_mySliderBar->setRange(min, max);
//    m_replaySliderBar->setMinimum(min);
//    m_replaySliderBar->setMaximum(max);
}

int MySlider::sliderPosition()
{
    //return m_replaySliderBar->slider()->sliderPosition();
    return m_mySliderBar->sliderPosition();
}

void MySlider::setTimeText(QString time)
{
    //m_sliderHandler->m_timeLabel->setText(time);
    //m_sliderHandler->setText(time);
    if(!m_withMouse)
    {
        m_sliderHandler->setTime(time);
    }
}

// s ynb 20191109
int MySlider::getSliderHandlerWidth()
{
    int width = 0;
    if (nullptr != m_sliderHandler)
    {
        width = m_sliderHandler->width();
    }
    return width;
}
// e ynb 20191109

int MySlider::gethandlePos()
{
    return m_sliderPos;
}

void MySlider::showSlider()
{
    //m_replaySliderBar->setGeometry(0, 0, 300, 50);
}

void MySlider::changeTheme()
{
    QPalette pal;

    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();

    if(themeType == DGuiApplicationHelper::LightType)
    {
        pal.setBrush(QPalette::Background, QBrush(UiUtil::renderSVG(":/image/icon/normal/slider.svg", QSize(m_sliderHandler->width(), m_sliderHandler->height()),Intancer::get_Intancer()->getApp())));
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        pal.setBrush(QPalette::Background, QBrush(UiUtil::renderSVG(":/image/icon_dark/normal/slider_dark.svg", QSize(m_sliderHandler->width(), m_sliderHandler->height()),Intancer::get_Intancer()->getApp())));
    }
    m_sliderHandler->setAutoFillBackground(true);
    m_sliderHandler->setPalette(pal);
}

void MySlider::OnSliderMoved(int newTime)
{
    qDebug()<<"newTime:"<<newTime;
    //start add by yuanshuai 20191119 bug 3360
    if(newTime < 0)
    {
        newTime = 0;
    }
    else if(newTime > m_mySliderBar->maximum())
    {
        newTime = m_mySliderBar->maximum();
    }
    //end
    QTime curTime(0, 0, 0);
    curTime = curTime.addSecs(newTime);
    QString curTimeStr;
    if(curTime.hour())
    {
        curTimeStr = "60:00";
    }
    else
    {
        curTimeStr = curTime.toString(tr("mm:ss"));
    }

    m_sliderHandler->setTime(curTimeStr);
}
