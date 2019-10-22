#ifndef TEXTNOTEITEM_H
#define TEXTNOTEITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <DLabel>
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
#include <DBlurEffectWidget>
#include <DIconButton>
DWIDGET_USE_NAMESPACE
//右侧文字记录Item
class TextNoteItem : public DWidget
{
    Q_OBJECT
public:
    TextNoteItem(NOTE m_textNote, NoteController *noteCtr, QString searchKey);
    ~TextNoteItem();

    NOTE m_textNote;
    QString m_bakContent;
    DLabel *m_timeLabel;
    DBlurEffectWidget *m_bgWidget;
    DWidget *m_MenuBtnBackground;
    QVBoxLayout *m_itemLayout;
    QHBoxLayout *m_hBoxLayout;
    QLabel *m_textLabel;
    QPlainTextEdit *m_plainTextEdit;
    //DImageButton *m_menuBtn;
    DIconButton *m_menuBtn;
    QStackedWidget *m_stackedWidget;
    QWidget *m_page1Widget;
    QWidget *m_page2Widget;
    TextNoteEdit *m_textEdit;
    void changeToEditMode();
    void readFromDatabase();
    void init();
    int getId();
signals:
    void textEditClicked(NOTE m_textNote);
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void sig_menuBtnPressed();
    void sig_menuBtnReleased();
    void sig_fouceOutAndEditEmpty(NOTE m_textNote);
    void sig_TextEditEmpty();
    void sig_TextEditNotEmpty();

public slots:
    void textAreaChanged();
    void handleTextEditClicked();
    void handleMenuBtnClicked();
    void handleTextEditFocusOut();
    void handleMenuBtnStateChanged();
    void tryToFouceout();

protected:
    void resizeEvent(QResizeEvent * event);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);

private:
    NoteController *m_noteCtr;
//    QMenu *m_contextMenu;
//    QAction *m_saveAsAction;
//    QAction *m_delAction;
    bool m_isTextConverted;
    QString m_searchKey;
    int m_menuBtnState;
    bool m_isEdited;
    bool m_mouseIsIn;
    void initUI();
    void initConnection();
    void updateNote();
};

#endif // TEXTNOTEITEM_H
