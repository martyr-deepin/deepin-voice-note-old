#ifndef TEXTNOTEITEM_H
#define TEXTNOTEITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QWidget>
#include <dimagebutton.h>
#include <notecontroller.h>
#include "consts.h"
//#include "dtextedit.h"
#include <QTextEdit>
#include <QObject>
#include "textnoteedit.h"


DWIDGET_USE_NAMESPACE
class TextNoteItem : public QWidget
{
    Q_OBJECT
public:
    TextNoteItem(NOTE m_textNote, NoteController *noteCtr);
    ~TextNoteItem();

    NOTE m_textNote;
    QLabel *m_timeLabel;
    QWidget *m_bgWidget;
    QLayout *m_itemLayout;
    QHBoxLayout *m_hBoxLayout;
    QLabel *m_textLabel;
    QPlainTextEdit *m_plainTextEdit;
    DImageButton *m_menuBtn;
    QStackedWidget *m_stackedWidget;
    QWidget *m_page1Widget;
    QWidget *m_page2Widget;
    TextNoteEdit *m_textEdit;
    void changeToEditMode();  
signals:
    void textEditClicked(NOTE m_textNote);

public slots:
    void textAreaChanged();
    void handleTextEditClicked();



private:
    NoteController *m_noteCtr;
    void initUI();
    void initConnection();
    void updateNote();
};

#endif // TEXTNOTEITEM_H
