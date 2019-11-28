#include "intancer.h"
#include <QDebug>
Intancer * Intancer::instance_ = nullptr;

Intancer::Intancer(QObject *parent) : QObject(parent)
{
    m_app = nullptr;
    tryToDelEmptyTextNote = false;
    recording = false;
    isRenameRepeat = false;
    isViewAddTextButtonShow = false;
    isSearching = false;
    isMoveFolder_count = 0;
    wantScrollRightList = true;

    m_RightListHeight = 0;
    m_RightViewHeight = 0;

    isTextNoteItemChanged = false;
    //start add by yuanshuai 20191128 bug 3731
    isEndRecord = false;
    //end
}

Intancer::~Intancer()
{

}

void Intancer::setApp(DApplication *pApp)
{
    m_app = pApp;
}

DApplication * Intancer::getApp()
{
    return m_app;
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
    if(value == true)
    {
        emit sigDisAbleReplay();
    }
    else
    {
        emit sigEnAbleReplay();
    }
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

void Intancer::setSearchingFlag(bool value)
{
    isSearching = value;
}

bool Intancer::getSearchingFlag()
{
    return isSearching;
}

void Intancer::setWantScrollRightListFlag(bool value)
{
    wantScrollRightList = value;
}

bool Intancer::getWantScrollRightListFlag()
{
    return wantScrollRightList;
}

void Intancer::initMoveFolderCount()
{
    isMoveFolder_count = 2;
}

void Intancer::CountMoveFolderCount()
{
    isMoveFolder_count--;
}

int Intancer::getMoveFolderFlag()
{
    return isMoveFolder_count;
}

bool Intancer::getTextNoteItemChangeState()
{
    return isTextNoteItemChanged;
}

void Intancer::setTextNoteItemChangeState(const bool isTextNoteItemChanged)
{
    this->isTextNoteItemChanged = isTextNoteItemChanged;
}

void Intancer::clearTextNoteItemChangeState()
{
    this->isTextNoteItemChanged = false;
}
//Add s 20191111
void Intancer::setAsrTxt(int FolderID,int ItemID, QString txt)
{
    QMap <int,QString> map;
    map[ItemID] = txt;
    m_mapArsTxtByFolder.insert(FolderID,map);
}
QString Intancer::getAsrTxt(int FolderID,int ItemID)
{
    QList<QMap<int,QString>> list = m_mapArsTxtByFolder.values(FolderID);
    for (int i=0;i<list.size();++i)
    {
      QMap<int,QString> map = list.at(i);
      auto find_index = map.find(ItemID);
      if(find_index!=map.end())
      {
          return find_index.value();
      }
    }
    return "";
}
void Intancer::setApplicationName(QString appName)
{
    m_ApplicationName = appName;
}
QString Intancer::getApplicationName()
{
    return m_ApplicationName;
}
//Add e 20191111
//start add by yuanshuai 20191128 bug 3731
void Intancer::setEndRecordFlag(bool value)
{
    isEndRecord = value;
}

bool Intancer::getEndRecordFlag()
{
    return isEndRecord;
}
//end
