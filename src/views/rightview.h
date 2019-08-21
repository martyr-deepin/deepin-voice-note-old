#ifndef RIGHTVIEW_H
#define RIGHTVIEW_H

#include "rightnotelist.h"

#include <QListWidget>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QWidget>
#include <dimagebutton.h>
#include <QObject>

DWIDGET_USE_NAMESPACE

class RightView : public QFrame
{
    Q_OBJECT
public:
    RightView();
    ~RightView();
public slots:
    void handleSelFolderChg(int folderId);
    void addTextNote();
private:
    void initUI();
    void initConnection();
    void initNoteList();
    void updateNoteList();
    int m_currFolderId;
    QStackedWidget *m_stackedWidget;
    QWidget *m_noteListPage;
    QWidget *m_detailPage;
    QPlainTextEdit *m_plainTextEdit;
    QLayout *m_noteListLayout;
    RightNoteList *m_noteListWidget;
    DImageButton *m_addVoiceBtn;
    DImageButton *m_addTextBtn;
    NoteController *m_noteController;
};

#endif // RIGHTVIEW_H
