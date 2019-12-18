#ifndef RIGHTVIEW_H
#define RIGHTVIEW_H

#include "recordPage.h"
#include "rightnotelist.h"
#include "foldercontroller.h"
#include "myrecodebuttons.h"
#include "voiceaudiodevicewatcher.h"
#include "voicevolumewatcher.h"
#include "loadwidget.h"
#include <QListWidget>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QWidget>
#include <DWidget>
#include <dimagebutton.h>
//#include <DImageButton>
#include <QObject>
#include <DFloatingButton>
#include <DBlurEffectWidget>
#include <QAudioDeviceInfo>
#include <DToolTip>

DWIDGET_USE_NAMESPACE
enum ADDTEXTBTN_STATE {TOP=0, MIDDLE=1, BOTTOM=2};
//右侧文字语音记录View
class RightView : public DWidget
//class RightView : public DBlurEffectWidget
{
    Q_OBJECT
public:
    RightView();
    ~RightView();

    void addNoteToNoteList(NOTE note);
    void updateNoteList();
    void searchNoteList(QString searchKey);
    void updateFromDetal(int ID);
    void stopAllPlayback();
    void cancleRecord();
    void checkAndDeleteEmptyTextNoteFromDatabase();
    int getFolderCount();
    //void initTxtFilesForDir();
    void OnlySaveRecord();
    void VoicePlayOrPause(); //Add bug 2587
    bool shortcutsDelete(); //Add bug 2587
    bool isAddVoiceBtnEnabled(); //Add createVoiceMemo 新建语音备忘录对应
    RightNoteList *m_noteListWidget;

signals:
    void textEditClicked(NOTE textNote);
    void sigBoardPress();
    void startRecoding();
    void stopRecoiding();
    void sig_research();
    void sigStartWatchVolume();
    void sigChangeCurFolderToTop(int folderID);
    void sigRvCheckFile();//by yuanshuai 20191120 2841
    void asrStart();  //转写开始    //Add 20191111
    void asrEnd();  //转写结束   //Add 20191111
    void sigToDetalVoicePage(QString contant);
    void sigShowVoiceDeviceError();
    void sigRecordVoiceCouldUse(); //Add createVoiceMemo 新建语音备忘录对应
public slots:
    void onShowNoResult();
    void handleSelFolderChg(int folderId);
    void handleSearchNote(int folderId, QString searchKey);
    void addTextNote();
    void handleStartRecord();
    void TryToDisEditAllText();
    void handleStopRecord(VOICE_INFO voiceInfo);
    void handlecancelRecord();
    void handleClearNote();
    void OnCurrentRowChanged(int curRow);
    void OnAllFolderGone();
    void OnAddAFolder();
    void onDisableAddBtn();
    void onAbleAddBtn(bool changed);
    void onViewAddTextShow();
    void onViewAddTextHide();
    void changeTheme();
    void oncheckCurPageVoiceForDelete();
    void onCheckRecordCouldUse(bool coulduse);
    void ShowRecodeTip();
    void handleStopRecord2(qint64 position); //ynb  20191109
    void OnTimeOut();
    void onMoveAddTextBtnToTop();
    void onMoveAddTextBtnToMiddle(int listheightContent);
    void onMoveAddTextBtnToBottom();

protected:
    void resizeEvent(QResizeEvent * event);

private:
    void initUI();
    void initConnection();
    void initNoteList();
    void initRecordStackedWidget();

    int m_currFolderId;
    AddTextBtn *m_AddButtonLocked;
    ADDTEXTBTN_STATE m_AddTextBtnState;
    DLabel *m_NoSearchResault;
    QStackedWidget *m_stackedWidget;
    QLayout *m_stackedWidgetLayout;
    QWidget *m_noteListPage;
    QWidget *m_detailPage;
    QPlainTextEdit *m_plainTextEdit;
    QVBoxLayout *m_noteListLayout;
    //DImageButton *m_addVoiceBtn;
    MyRecodeButtons *m_addVoiceBtn;
    //DFloatingButton *m_addVoiceBtn;
    NoteController *m_noteController;
    FolderController *m_FolderController;
    RecordPage *m_recordPage;
    QStackedWidget *m_recordStackedWidget;
//    DBlurEffectWidget *m_BottomBoard;
//    DBlurEffectWidget *m_AddBtnBoard;
    DWidget *m_BottomBoard;
    DWidget *m_AddBtnBoard;
    DDialog *m_noticeNoAudioInputs;
    VoiceAudioDeviceWatcher* m_pVoiceAudioDeviceWatcher;
    voiceVolumeWatcher* m_pVoiceVolumeWatcher;
    QThread *m_pVoiceVolumethread;
    DToolTip *m_pNotRecordToolTip;
    VOICE_INFO m_voiceinfo; //ynb  20191109
    QTimer *m_InitlateTimerOut;
    bool m_initing;
    LoadWidget *m_LoadWidget;

    WorkerController *workController;
};

#endif // RIGHTVIEW_H
