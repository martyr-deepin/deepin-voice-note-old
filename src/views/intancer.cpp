#include "intancer.h"
#include <QDebug>
Intancer * Intancer::instance_ = nullptr;

Intancer::Intancer(QObject *parent) : QObject(parent)
{
    tryToDelEmptyTextNote = false;
    recording = false;
    isRenameRepeat = false;
    isViewAddTextButtonShow = false;

    m_RightListHeight = 0;
    m_RightViewHeight = 0;
}

Intancer::~Intancer()
{

}

void Intancer::initHeightForRight()
{
    m_RightListHeight = 0;
    m_RightViewHeight = 0;
}

void Intancer::clearHeightForRightList()
{
    m_RightListHeight = 0;
}

void Intancer::addHeightForRightList(int addheight)
{
    m_RightListHeight += addheight;
    if(m_RightListHeight > m_RightViewHeight)
    {
        emit sigShowViewAddTextButton();
        isViewAddTextButtonShow = true;
    }
    else
    {
        emit sigHideViewAddTextButton();
        isViewAddTextButtonShow = false;
    }
    qDebug()<<"m_RightViewHeight:"<<m_RightViewHeight;
    qDebug()<<"m_RightListHeight:"<<m_RightListHeight;
}

void Intancer::delHeightForRightList(int delheight)
{
    m_RightListHeight -= delheight;
    if(m_RightListHeight < 0)
    {
        m_RightListHeight = 0;
    }
    if(m_RightListHeight <= m_RightViewHeight)
    {
        emit sigHideViewAddTextButton();
        isViewAddTextButtonShow = false;
    }
    qDebug()<<"m_RightViewHeight:"<<m_RightViewHeight;
    qDebug()<<"m_RightListHeight:"<<m_RightListHeight;
}

void Intancer::setViewHeightForRightList(int viewHeight)
{
    m_RightViewHeight = viewHeight;
    if(m_RightListHeight <= m_RightViewHeight)
    {
        if(isViewAddTextButtonShow)
        {
            emit sigHideViewAddTextButton();
            isViewAddTextButtonShow = false;
        }
    }
    else
    {
        if(!isViewAddTextButtonShow)
        {
            emit sigShowViewAddTextButton();
            isViewAddTextButtonShow = true;
        }
    }
    qDebug()<<"m_RightViewHeight:"<<m_RightViewHeight;
    qDebug()<<"m_RightListHeight:"<<m_RightListHeight;
}

void Intancer::setTryToDelEmptyTextNote(bool value)
{
    tryToDelEmptyTextNote = value;
}

bool Intancer::getTryToDelEmptyTextNote()
{
    return tryToDelEmptyTextNote;
}

void Intancer::setRecodingFlag(bool value)
{
    recording = value;
}

bool Intancer::getRecodingFlag()
{
    return recording;
}

void Intancer::setRenameRepeatFlag(bool value)
{
    isRenameRepeat = value;
}

bool Intancer::getRenameRepeatFlag()
{
    return isRenameRepeat;
}

bool Intancer::setViewAddTextButtonShowFlag(bool value)
{
    isViewAddTextButtonShow = value;
}

bool Intancer::getViewAddTextButtonShowFlag()
{
    return isViewAddTextButtonShow;
}
