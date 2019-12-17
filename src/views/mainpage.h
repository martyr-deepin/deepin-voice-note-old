#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "dfmsplitter.h"
#include "leftfolderlist.h"
#include "rightview.h"
#include "leftview.h"
#include <DMainWindow>
#include <QFrame>
#include <QObject>
#define DEFAULT_WINDOWS_WIDTH 820
#define DEFAULT_WINDOWS_HEIGHT 634


DWIDGET_USE_NAMESPACE

//第一层Page
class MainPage : public QWidget
{
    Q_OBJECT
public:
    MainPage();
    ~MainPage();
    void firstShowRightList();

public:
    void updateNoteList();
    bool searchFolder(QString searchKey, bool &hasNoFolder);
    void updateFromDetal(int id);
    void cancleRecord();
    void selectCurFolder();
    void checkAndDeleteEmptyTextNoteFromDatabase();
    int getFolderCount();
    void trueAddFolder();
    void saveRecorde();
    void ChangeCurFolderToTop(int folderID);
    int getAllFolderListNumFromDatabase();
    //Add start bug 2587
    void addFolder();
    void reNameFolder();
    void deleteFolder();
    void VoicePlayOrPause();
    bool shortcutsDeleteByRightlist();
    //Add end bug 2587
    void startRecording();  //Add createVoiceMemo 新建语音备忘录对应
    bool isAddVoiceBtnEnabled(); //Add createVoiceMemo 新建语音备忘录对应
signals:
    void textEditClicked(NOTE textNote);
    void clearSearch();
    void sig_research();
    void sigAllFolderDeleted();
    void sigNoSearchResult();
    void stopRecoiding();  //Add bug3470
    //start add by yuanshuai 20191121
    void sigMpCheckFile();
    //end
    void asrStart();  //转写开始    //Add 20191111
    void asrEnd();  //转写结束   //Add 20191111
    void sigToDetalVoicePage(QString contant);
    void sigShowVoiceDeviceError();
    void sigRecordVoiceCouldUse(); //Add createVoiceMemo 新建语音备忘录对应
public slots:
    void onAddFolder();

    //void addItemTest();

private:
     DFMSplitter *m_splitter;
     LeftView *m_leftView;

     RightView *m_rightView;

     //DListWidget *pList;
     //int count;

    void initUI();

    void initConnection();

    void initTitleBar();

    void initSplitter();

    void initLeftView();

    void initRightView();
};

#endif // MAINPAGE_H
