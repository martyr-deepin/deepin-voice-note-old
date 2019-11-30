#ifndef INTANCER_H
#define INTANCER_H

#include <QObject>
#include <DApplication>

//#include <QDBus>
DWIDGET_USE_NAMESPACE

class Intancer : public QObject
{
    Q_OBJECT
public:
    explicit Intancer(QObject *parent = nullptr);
    ~Intancer();
    static Intancer* get_Intancer(){
        if(instance_ == nullptr){
          instance_ = new Intancer();
        }
        return instance_;
    }
    static void destroyIntance(){
        if(nullptr != instance_)
        {
            delete instance_;
        }
    }    

    void setApp(DApplication *pApp);
    DApplication * getApp();

    void initHeightForRight();
    void clearHeightForRightList();
    void addHeightForRightList(int addheight);
    void delHeightForRightList(int delheight);
    void setViewHeightForRightList(int viewHeight);

    void setTryToDelEmptyTextNote(bool value);
    bool getTryToDelEmptyTextNote();
    void setRecodingFlag(bool value);
    bool getRecodingFlag();
    void setRenameRepeatFlag(bool value);
    bool getRenameRepeatFlag();
    bool setViewAddTextButtonShowFlag(bool value);
    bool getViewAddTextButtonShowFlag();

    void setSearchingFlag(bool value);
    bool getSearchingFlag();

    void setWantScrollRightListFlag(bool value);
    bool getWantScrollRightListFlag();

    void initMoveFolderCount();
    void CountMoveFolderCount();
    int getMoveFolderFlag();

    void setAsrTxt(int FolderID,int ItemID, QString txt);  //Add 20191111
    QString getAsrTxt(int FolderID,int ItemID);       //Add 20191111

    void setApplicationName(QString appName);  //Add 20191111
    QString getApplicationName();       //Add 20191111

    //start add by yuanshuai 20191128 bug 3731
    void setEndRecordFlag(bool value);
    bool getEndRecordFlag();
    //end
signals:
    void sigShowViewAddTextButton();
    void sigHideViewAddTextButton();
    void sigDisAbleReplay();
    void sigEnAbleReplay();

private:
     static Intancer *instance_;
     bool tryToDelEmptyTextNote;
     bool recording;
     bool isRenameRepeat;
     bool isViewAddTextButtonShow;
     bool isSearching;
     bool wantScrollRightList;
     int  isMoveFolder_count;
     //start add by yuanshuai 20191128 bug 3731
     bool isEndRecord;
     //end
     int m_RightListHeight;
     int m_RightViewHeight;
     DApplication *m_app;

    QMultiMap <int,QMap<int,QString>> m_mapArsTxtByFolder;  //Add 20191111
    QString m_ApplicationName; //Add 20191111
};

#endif // INTANCER_H
