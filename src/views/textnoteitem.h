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
#include "menubutton.h"
#include "myrecodebuttons.h"
//#include <darrowrectangle.h>
#include <QMenu>
#include <QAction>
#include <DBlurEffectWidget>
#include <DIconButton>
#include <DFloatingButton>
#include <DFrame>

DWIDGET_USE_NAMESPACE
//右侧文字记录Item
class TextNoteItem : public DWidget
{
    Q_OBJECT
public:
    TextNoteItem(const bool isAddByButton, NOTE m_textNote, NoteController *noteCtr, QString searchKey, QWidget *parent = nullptr);
    ~TextNoteItem();

    NOTE m_textNote;
    QString m_bakContent;
    DLabel *m_timeLabel;
    DFrame *m_bgWidget;
    DFrame *m_bgWidgethoverd;
    DWidget *m_MenuBtnBackground;
    QVBoxLayout *m_itemLayout;
    QHBoxLayout *m_hBoxLayout;
    QLabel *m_textLabel;
    QPlainTextEdit *m_plainTextEdit;
    //DImageButton *m_menuBtn;
    MyRecodeButtons *m_menuBtn;
    //MenuButton *m_detailBtn;
    MyRecodeButtons *m_detailBtn;
    QStackedWidget *m_stackedWidget;
    QWidget *m_page1Widget;
    QWidget *m_page2Widget;
    TextNoteEdit *m_textEdit;
    QString m_searchKey;
    //void changeToEditMode();
    void changeToEditMode(int cursorpos = -1 );//3550-3547-3528 patch
    void readFromDatabase();
    void init();
    int getId();
    NOTE_TYPE getType();
    NOTE getTextNote();//liuyang 3550 3547 3528
    QPoint remapToGlobalMenbtn(QPoint GlobalPoint);
    int getTextEditCursorPos();//3550-3547-3528 patch

signals:
    void textEditTrueClicked(NOTE m_textNote);
    void textEditClicked(NOTE m_textNote);
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void sig_menuBtnPressed();
    void sig_menuBtnReleased();
    void sig_fouceOutAndEditEmpty(NOTE m_textNote);
    void sig_TextEditEmpty();
    void sig_TextEditNotEmpty(bool changed);
    void sig_ItemTimeChanged(NOTE noteID);
    void buttonClicled();
    void SigTextEditGetFocus(NOTE m_textNote); //Add bug 2587
    void SigTextEditOutFocus(NOTE m_textNote); //Add bug 2587

public slots:
    void textAreaChanged();
    void handleTextEditClicked();
    void handleMenuBtnClicked();
    void handleTextEditFocusOut();
    void handleMenuBtnStateChanged();
    void tryToFouceout();
    void textEditChanged(const QString &str);//liuyang 3547
    //void textEditChanged(QString str);
    void changeTheme();
    void OnToDetalPage();
    void OnTextEditGetFocus(); //Add bug 2587
    void OnTextEditOutFocus(); //Add bug 2587
    void onDetailButtonChanged(const bool isVisible);

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
    int m_menuBtnState;
    bool m_isEdited;
    bool m_mouseIsIn;
    void initUI(const bool isAddByButton);
    void initConnection();
    void updateNote();
};

#endif // TEXTNOTEITEM_H
