#ifndef RIGHTVIEW_H
#define RIGHTVIEW_H

#include "rightnotelist.h"

#include <QListWidget>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QWidget>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

class RightView : public QFrame
{
public:
    RightView();
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
    NoteController *noteController;
};

#endif // RIGHTVIEW_H
