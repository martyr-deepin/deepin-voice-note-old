#ifndef RIGHTVIEW_H
#define RIGHTVIEW_H

#include "recordPage.h"
#include "rightnotelist.h"

#include <QListWidget>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QWidget>
#include <dimagebutton.h>
//#include <DImageButton>
#include <QObject>

DWIDGET_USE_NAMESPACE
//右侧文字语音记录View
class RightView : public QFrame
{
    Q_OBJECT
public:
    RightView();
    ~RightView();

    void updateNoteList();
    void searchNoteList(QString searchKey);
signals:
    void textEditClicked(NOTE textNote);

public slots:
    void handleSelFolderChg(int folderId);
    void handleSearchNote(int folderId, QString searchKey);
    void addTextNote();
    void handleStartRecord();
    void handleStopRecord(VOICE_INFO voiceInfo);
    void handleClearNote();
private:
    void initUI();
    void initConnection();
    void initNoteList();
    void initRecordStackedWidget();

    int m_currFolderId;
    QStackedWidget *m_stackedWidget;
    QLayout *m_stackedWidgetLayout;
    QWidget *m_noteListPage;
    QWidget *m_detailPage;
    QPlainTextEdit *m_plainTextEdit;
    QLayout *m_noteListLayout;
    RightNoteList *m_noteListWidget;
    DImageButton *m_addVoiceBtn;
    DImageButton *m_addTextBtn;
    NoteController *m_noteController;
    RecordPage *m_recordPage;
    QStackedWidget *m_recordStackedWidget;
};

#endif // RIGHTVIEW_H
