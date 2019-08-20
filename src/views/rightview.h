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
public slots:
    void handleSelFolderChg(int folderId);
private:
    void initUI();
    void initNoteList();
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
