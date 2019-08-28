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
//#include <darrowrectangle.h>
#include <QMenu>
#include <QAction>


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
//    DArrowRectangle *m_arrowMenu;
    void changeToEditMode();  
signals:
    void textEditClicked(NOTE m_textNote);
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, TextNoteItem *textNoteItem, NOTE note);

public slots:
    void textAreaChanged();
    void handleTextEditClicked();
    void handleMenuBtnClicked();




private:
    NoteController *m_noteCtr;
//    QMenu *m_contextMenu;
//    QAction *m_saveAsAction;
//    QAction *m_delAction;
    bool m_isTextConverted;
    void initUI();
    void initConnection();
    void updateNote();
};

#endif // TEXTNOTEITEM_H
