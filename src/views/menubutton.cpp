#include "menubutton.h"
#include "uiutil.h"
#include <DStyleOptionButton>
#include <DApplicationHelper>
#include <QDebug>
DWIDGET_USE_NAMESPACE

MenuButton::MenuButton(QWidget *parent) : DFloatingButton(parent)
{

}

MenuButton::MenuButton(QString normal, QString press, QString hover, QString disable, QString foucs, QSize size, QSize iconsize,QWidget *parent) : DFloatingButton(parent)
{
    this->setFixedSize(size);
    setPicChange(normal, press, hover,  disable, foucs);
    m_isPressed = false;
    m_isIn = false;
    m_isDisabled = false;
    m_iconSize = iconsize;
    this->setIcon(m_normal);
    this->setIconSize(m_iconSize);
}

void MenuButton::setPicChange(QString normal,QString press,QString hover, QString disable, QString foucs)
{
    //Intancer::get_Intancer()->getApp()
    m_normal = UiUtil::renderSVG(normal, QSize(this->width(), this->height()),qApp);
    m_press = UiUtil::renderSVG(press, QSize(this->width(), this->height()),qApp);
    m_hover = UiUtil::renderSVG(hover, QSize(this->width(), this->height()),qApp);
    m_disable = UiUtil::renderSVG(disable, QSize(this->width(), this->height()),qApp);
    m_foucs = UiUtil::renderSVG(foucs, QSize(this->width(), this->height()),qApp);
}

void MenuButton::DisableBtn()
{
    this->setDisabled(true);
    m_isDisabled = true;
    this->setIcon(m_disable);
    this->setIconSize(m_iconSize);
}

void MenuButton::EnAbleBtn()
{
    this->setDisabled(false);
    m_isDisabled = false;

    if(m_isIn)
    {
        this->setIcon(m_hover);
    }
    else
    {
        this->setIcon(m_normal);
    }

    this->setIconSize(m_iconSize);
}


void MenuButton::mousePressEvent(QMouseEvent *event)
{
    DFloatingButton::mousePressEvent(event);
    m_isPressed = true;
    if(m_isDisabled)
    {
        this->setIcon(m_disable);
    }
    else
    {
        this->setIcon(m_press);
    }

    this->setIconSize(m_iconSize);
    repaint();
    //qDebug()<<"mousePressEvent m_isPressed:"<<m_isPressed;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("mousePressEvent m_isPressed:"), QString::number(m_isPressed));
}

void MenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    DFloatingButton::mouseReleaseEvent(event);
    m_isPressed = false;
    if(m_isDisabled)
    {
        this->setIcon(m_disable);
    }
    else if(m_isIn)
    {
        this->setIcon(m_hover);
    }
    else
    {
        this->setIcon(m_normal);
    }
    this->setIconSize(m_iconSize);
    //qDebug()<<"mouseReleaseEvent m_isPressed:"<<m_isPressed;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("mouseReleaseEvent m_isPressed:"), QString::number(m_isPressed));
}

void MenuButton::enterEvent(QEvent *event)
{
    DFloatingButton::enterEvent(event);
    m_isIn = true;
    if(m_isDisabled)
    {
        this->setIcon(m_disable);
    }
    else
    {
        this->setIcon(m_hover);
    }
    this->setIconSize(m_iconSize);
    //qDebug()<<"enterEvent m_isIn:"<<m_isIn;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("enterEvent m_isIn:"), QString::number(m_isIn));
}
void MenuButton::leaveEvent(QEvent *event)
{
    DFloatingButton::leaveEvent(event);
    m_isIn = false;
    m_isPressed = false;
    //emit sigLeave();
    if(m_isDisabled)
    {
        this->setIcon(m_disable);
    }
    else
    {
        this->setIcon(m_normal);
    }
    this->setIconSize(m_iconSize);
    //qDebug()<<"leaveEvent m_isIn:"<<m_isIn;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("leaveEvent m_isIn:"), QString::number(m_isIn));
}

void MenuButton::mouseMoveEvent(QMouseEvent *event)
{
    DFloatingButton::mouseMoveEvent(event);
}

void MenuButton::initStyleOption(DStyleOptionButton *option) const
{
    DFloatingButton::initStyleOption(option);
    DPalette pa;
    DApplicationHelper::instance()->palette(this);
    //pa.setBrush(DPalette::Highlight, pa.color(DPalette::Base));
    //pa.setBrush(DPalette::Highlight, QColor(255,0,0,255));
    pa.setBrush(DPalette::Highlight, pa.color(DPalette::TextWarning));
    option->palette = pa;
}
