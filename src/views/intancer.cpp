#include "intancer.h"
#include "consts.h"

#include <QDebug>

#include "uiutil.h"

Intancer * Intancer::instance_ = nullptr;

Intancer::Intancer(QObject *parent) : QObject(parent)
{
    m_app = nullptr;
    tryToDelEmptyTextNote = false;
    recording = false;
    isRenameRepeat = false;
    isListOverOnePage = false;
    isSearching = false;
    isMoveFolder_count = 0;
    wantScrollRightList = true;
    isVoiceToText = false;
    m_TransFromDetalToMainPage = false;

    m_RightListHeight = 0;
    m_RightViewHeight = 0;
    //start notify by yuanshuai 20191210 bug 4435
//    //start add by yuanshuai 20191128 bug 3731
//    isEndRecord = false;
//    //end
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
    //qDebug()<<"initHeightForRight()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("initHeightForRight():"), QString("initHeightForRight():"));
    m_RightListHeight = 0;
    m_RightViewHeight = 0;
}

void Intancer::clearHeightForRightList()
{
    //qDebug()<<"clearHeightForRightList()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("clearHeightForRightList():"), QString("clearHeightForRightList():"));
    m_RightListHeight = 0;
    emit sigLockAddTextBtnToTop();
}

void Intancer::addHeightForRightList(int addheight)
{
    //qDebug()<<"addheight:"<<addheight;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("addheight:"), QString::number(addheight,10));
    //qDebug()<<"m_RightListHeight1:"<<m_RightListHeight;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightListHeight1:"), QString::number(m_RightListHeight,10));
    m_RightListHeight += addheight;
    //qDebug()<<"m_RightListHeight2:"<<m_RightListHeight;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightListHeight2:"), QString::number(m_RightListHeight,10));
    if(m_RightListHeight > m_RightViewHeight)
    {
        emit sigLockAddTextBtnToBottom();
        isListOverOnePage = true;
    }
    else if(m_RightListHeight > SPACEITEM_HEIGHT_HEIGHT)
    {
        emit sigunLockAddTextBtnPos(m_RightListHeight);
        isListOverOnePage = false;
    }

    //qDebug()<<"m_RightViewHeight:"<<m_RightViewHeight;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightViewHeight:"), QString::number(m_RightViewHeight,10));
}

void Intancer::delHeightForRightList(int delheight)
{
    //qDebug()<<"delheight:"<<delheight;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("delheight:"), QString::number(delheight,10));
    //qDebug()<<"m_RightViewHeight1:"<<m_RightListHeight;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightViewHeight1:"), QString::number(m_RightListHeight,10));
    m_RightListHeight -= delheight;
    //qDebug()<<"m_RightListHeight2:"<<m_RightListHeight;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightListHeight2:"), QString::number(m_RightListHeight,10));
    if(m_RightListHeight <= SPACEITEM_HEIGHT_HEIGHT)
    {
//        m_RightListHeight = 0;
        emit sigLockAddTextBtnToTop();
    }
    else if(m_RightListHeight < m_RightViewHeight)
    {
        emit sigunLockAddTextBtnPos(m_RightListHeight);
        isListOverOnePage = false;
    }

    //qDebug()<<"m_RightViewHeight:"<<m_RightViewHeight;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightViewHeight:"), QString::number(m_RightViewHeight,10));
}

void Intancer::setViewHeightForRightList(int viewHeight)
{
    m_RightViewHeight = viewHeight;
    if(m_RightListHeight <= m_RightViewHeight)
    {
        if(isListOverOnePage)
        {
            isListOverOnePage = false;
            emit sigunLockAddTextBtnPos(m_RightListHeight);
        }
    }
    else
    {
        if(!isListOverOnePage)
        {
            emit sigLockAddTextBtnToBottom();
            isListOverOnePage = true;
        }
    }
    //qDebug()<<"m_RightViewHeight:"<<m_RightViewHeight;
    //qDebug()<<"m_RightListHeight:"<<m_RightListHeight;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightViewHeight:"), QString::number(m_RightViewHeight,10));
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_RightListHeight:"), QString::number(m_RightListHeight,10));
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

//bool Intancer::setViewAddTextButtonShowFlag(bool value)
//{
//    isViewAddTextButtonShow = value;
//}

//bool Intancer::getViewAddTextButtonShowFlag()
//{
//    return isViewAddTextButtonShow;
//}

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

void Intancer::setVoiceToTextFlag(bool value)
{
    isVoiceToText = value;
}

bool Intancer::getVoiceToTextFlag()
{
    return isVoiceToText;
}

void Intancer::setTransFromDetalToMainPage(bool value)
{
    m_TransFromDetalToMainPage = value;
}

bool Intancer::getTransFromDetalToMainPage()
{
    return m_TransFromDetalToMainPage;
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
//start notify by yuanshuai 20191210 bug 4435
////start add by yuanshuai 20191128 bug 3731
//void Intancer::setEndRecordFlag(bool value)
//{
//    isEndRecord = value;
//}

//bool Intancer::getEndRecordFlag()
//{
//    return isEndRecord;
//}
////end
//end

void Intancer::setSearchKeywords(const QString & text)
{
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("Intancer::setSearchKeywords():"), QString("Intancer::setSearchKeywords():"));
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("text:"), text);

    this->searchKeywords = text;
}

QString Intancer::getSearchKeywords()
{
    return this->searchKeywords;
}

void Intancer::setMainPageHandle(QWidget *p)
{
    m_MainPageHandle = p;
}

QWidget *Intancer::getMainPageHandle()
{
    return m_MainPageHandle;
}
