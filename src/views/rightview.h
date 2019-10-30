#ifndef RIGHTVIEW_H
#define RIGHTVIEW_H

#include "recordPage.h"
#include "rightnotelist.h"

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

DWIDGET_USE_NAMESPACE
//右侧文字语音记录View
class RightView : public QFrame
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

signals:
    void textEditClicked(NOTE textNote);
    void sigBoardPress();
    void startRecoding();
    void stopRecoiding();

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
    void onAbleAddBtn();
    void onViewAddTextShow();
    void onViewAddTextHide();

protected:
    void resizeEvent(QResizeEvent * event);

private:
    void initUI();
    void initConnection();
    void initNoteList();
    void initRecordStackedWidget();

    int m_currFolderId;
    AddTextBtn *m_AddButtonLocked;
    DLabel *m_NoSearchResault;
    QStackedWidget *m_stackedWidget;
    QLayout *m_stackedWidgetLayout;
    QWidget *m_noteListPage;
    QWidget *m_detailPage;
    QPlainTextEdit *m_plainTextEdit;
    QVBoxLayout *m_noteListLayout;
    RightNoteList *m_noteListWidget;
    //DImageButton *m_addVoiceBtn;
    DFloatingButton *m_addVoiceBtn;
    NoteController *m_noteController;
    RecordPage *m_recordPage;
    QStackedWidget *m_recordStackedWidget;
    DBlurEffectWidget *m_BottomBoard;
    DDialog *m_noticeNoAudioInputs;

};

#endif // RIGHTVIEW_H
