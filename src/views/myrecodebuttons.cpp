#include "myrecodebuttons.h"
#include "uiutil.h"
#include <QPainter>
#include <QDebug>

MyRecodeButtons::MyRecodeButtons(QString normal, QString press, QString hover, QString disable, QString foucs, QSize size, QWidget *parent) : DPushButton(parent)
{
    this->setFixedSize(size);
    setPicChange(normal, press, hover,  disable, foucs);
    m_isPressed = false;
    m_isIn = false;
    m_isDisabled = false;
}

MyRecodeButtons::~MyRecodeButtons()
{

}

void MyRecodeButtons::setPicChange(QString normal,QString press,QString hover, QString disable, QString foucs)
{
    //Intancer::get_Intancer()->getApp()
    m_normal = UiUtil::renderSVG(normal, QSize(this->width(), this->height()),qApp);
    m_press = UiUtil::renderSVG(press, QSize(this->width(), this->height()),qApp);
    m_hover = UiUtil::renderSVG(hover, QSize(this->width(), this->height()),qApp);
    m_disable = UiUtil::renderSVG(disable, QSize(this->width(), this->height()),qApp);
    m_foucs = UiUtil::renderSVG(foucs, QSize(this->width(), this->height()),qApp);
}

void MyRecodeButtons::DisableBtn()
{
    this->setDisabled(true);
    m_isDisabled = true;
}

void MyRecodeButtons::EnAbkeBtn()
{
    this->setDisabled(false);
    m_isDisabled = false;
}

void MyRecodeButtons::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::HighQualityAntialiasing |
                            QPainter::SmoothPixmapTransform |
                            QPainter::Antialiasing);
    if(m_isDisabled)
    {
        //disable
        painter.drawPixmap(rect(), m_disable);
        qDebug()<<"disable disable disable disable disable disable";
    }
    else if(!m_isIn && !m_isDisabled)
    {
        //Normal
        painter.drawPixmap(rect(), m_normal);
        qDebug()<<"Normal Normal Normal Normal Normal Normal";
    }
    else if(!m_isPressed && m_isIn)
    {
        //hover
        painter.drawPixmap(rect(), m_hover);
        qDebug()<<"hover hover hover hover hover hover";
    }
    else if(m_isPressed && m_isIn)
    {
        //press
        painter.drawPixmap(rect(), m_press);
        qDebug()<<"press press press press press press";
    }

}

void MyRecodeButtons::mousePressEvent(QMouseEvent *event)
{
    DPushButton::mousePressEvent(event);
    m_isPressed = true;
    repaint();
    qDebug()<<"mousePressEvent m_isPressed:"<<m_isPressed;
}
void MyRecodeButtons::mouseReleaseEvent(QMouseEvent *event)
{
    DPushButton::mouseReleaseEvent(event);
    m_isPressed = false;
    qDebug()<<"mouseReleaseEvent m_isPressed:"<<m_isPressed;
}

void MyRecodeButtons::enterEvent(QEvent *event)
{
    DPushButton::enterEvent(event);
    m_isIn = true;
    qDebug()<<"enterEvent m_isIn:"<<m_isIn;
}
void MyRecodeButtons::leaveEvent(QEvent *event)
{
    DPushButton::leaveEvent(event);
    m_isIn = false;
    m_isPressed = false;
    qDebug()<<"leaveEvent m_isIn:"<<m_isIn;
}

void MyRecodeButtons::mouseMoveEvent(QMouseEvent *event)
{
    DPushButton::mouseMoveEvent(event);
}
