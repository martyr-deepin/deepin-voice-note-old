
#ifndef RIGHTNOTELIST_H
#define RIGHTNOTELIST_H

#include "fileexistsdialog.h"
#include "myslider.h"
#include "textnoteitem.h"
#include "voicenoteitem.h"
#include "addtextbtn.h"
#include <QDir>
#include <DListWidget>
#include <notecontroller.h>
#include <consts.h>
#include <QObject>
#include <darrowrectangle.h>
#include <DDialog>
#include <QMediaPlayer>
#include <DPushButton>
#include <DMenu>

//#include <DArrowRectangle>

DWIDGET_USE_NAMESPACE

#define SLIDER_PAGE_STEP 4
class RightNoteList;

class RightNoteListWorker : public QObject
{
    Q_OBJECT
public:
    explicit RightNoteListWorker(RightNoteList* parent);

public slots:
    void startLoading();

signals:
    void sigLoaded();

private:
    RightNoteList* m_parent;
};

class MMenu : public DMenu
{
    Q_OBJECT
public:
    explicit MMenu(QWidget *parent = nullptr);
    ~MMenu();

signals:
    void sigMMenu();

protected:
    void leaveEvent(QEvent* event);
    void paintEvent(QPaintEvent *event);
};

//右侧文字语音记录列表
class RightNoteList : public DListWidget
{
    Q_OBJECT
public:
    RightNoteList(NoteController *noteController);
    ~RightNoteList();
    void addWidgetItem(bool isAddByButton ,NOTE note, QString searchKey);
    void addAddTextBtn();
    void delAddTextBtn();
    void listAddTextShow();
    void listAddTextHide();
    void fouceOutAllTextItem();
    void delAllEmptyText();
    void getDurtimgByRecodefinised(QString filepath);  //ynb 20191109
    void OnlyTryToFouceOutEveryText();
    void VoicePlayOrPause(); //Add bug 2587
    bool shortcutsDelete();  //Add bug 2587
    QMediaPlayer *audioPlayer;
    bool isLoadedAudioPlayer = {false};
private:
    void adjustWidgetItemWidth();
signals:
    void textEditClicked(NOTE textNote);
    void addTextItem();
    void sigBoardPress();
    void sigBoardPressToLeft();
    void sig_TextEditEmpty();
    void sig_TextEditNotEmpty(bool changed);
    void sig_research();
    void sig_checkCurPageVoiceForDelete();
    void positionByfinishRecord(qint64 position); //ynb 20191109
    void sigChangeCurFolderToTop(int curFolder);
    void sig_CheckFileExist();//by yuanshuai 20191120 2841
    void sig_startloadingPlayer();
    void sig_EnablePlaybackButton();
    void sig_RecordButtonAvaliability(bool isAvaliable);

protected:
    //bool eventFilter(QObject *o, QEvent *e);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent * event);
    void wheelEvent(QWheelEvent *e);

public slots:
    void handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void handleDelItem(bool);
    void handleSaveAsItem(bool);
    void handleDelDialogClicked(int index, const QString &text);
    void handleCloseDialogClicked();
    void handlePlayingStateChanged(QMediaPlayer::State state);
    void play(VoiceNoteItem * voiceNoteItem, QString filepath, QRect waveformPos, NOTE note);  //Edit bug 2587
    //void play(VoiceNoteItem * voiceNoteItem, QString filepath, QRect waveformPos);
    void pause();
    void stop();
    void handleClickRecordButton();
    void handleAudioPositionChanged(qint64 position);
    void handleSliderReleased();
    void handleSliderPressed();
    void handleSliderMove(int value);
    void handleSaveFileEnd(bool);
    void handleMenuBtnPressed();
    void handleMenuBtnReleased();
    void OnActionHoverd();
    void OnLeaveContentMenu();
    void handleVScrollBarChanged(int value);
    void onDisableAddBtn();
    void onAbleAddBtn(bool changed);
    void onTextChangedFlagChange(bool changed);
    void onCallDelDialog(NOTE textNote);
    //void onSortItemByTime(NOTE note);
    void onCheckEditState(NOTE note);
    void onfouceOutAllTextItem();
    void getduration(qint64 position);   //获取音频总时间  ynb 20191109
    void onTextEditGetFocus(NOTE note); //Add bug 2587
    void onTextEditOutFocus(NOTE note); //Add bug 2587
    void loadedPlayer();
private:
    void testQMediaPlayer();


    MMenu *m_contextMenu;
    QAction *m_saveAsAction;
    QAction *m_delAction;
    NoteController *m_noteController;
    DArrowRectangle *m_arrowMenu;
    QListWidgetItem *m_currSelItem;
    NOTE m_currSelNote;
    NOTE m_currClickTextNote; //2719 fix liuyang
    DDialog *m_delConfirmDialog;
    DDialog *m_noticeNotExistDialog;
    VoiceNoteItem *m_currPlayingItem;
    MySlider *m_myslider;
    DSlider *m_TestSlider;
    FileExistsDialog *m_fileExistsDialog;
    DDialog *m_saveFileEndDialog;
    AddTextBtn *m_addTextBtn;

    QString m_defaultTxtName;
    QString m_defaultTxtPath;
    QString m_defaultAudioName;
    QString m_defaultAudioPath;
    QString m_defaultEditText;
    bool m_arrowButtonPressed;
    bool m_actionHoverd;
    int curWaveformPosWidth;
    bool m_Recodefinised;  //ynb 20191109
    bool m_IsSliderBarReleased; //ynb 20191109
    int seconds;   //ynb 20191109
    int duringTime;
    bool m_textClicked;
    bool m_textChanged;
    bool m_textGetFocus; //Add bug 2587
    bool m_voiceOperation; //对录音回访的操作时设为true  Add bug 2587

    //MyCustomSlider *m_myslider;
    void createDArrowMenu();
    void destroyDArrowMenu();
    void showDArrowMenu(int x, int y, NOTE_TYPE type);
    void hideDArrowMenu();
    void initUI();
    void initConnection();
    void showFileDialog(SAVE_INFO saveInfo);
    void scanData(const QDir &fromDir, const QString &filter, QStringList &files, QString compareText);
    void getNewName(QString &outName, QStringList files);
    QListWidgetItem *getListItemById(int id);
    QString getPlayingFilepath();
    void changeSliderPosByHand(int moveMovment);
    bool getRowByID(int id, NOTE_TYPE type, int &row);

    RightNoteListWorker* m_rightNoteListWorker;
    QThread * m_rightNoteListWorkerThread;
};

#endif // RIGHTNOTELIST_H
