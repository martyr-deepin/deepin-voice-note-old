#ifndef RIGHTNOTELIST_H
#define RIGHTNOTELIST_H

#include "textnoteitem.h"

#include <QListWidget>
#include <notecontroller.h>
#include <consts.h>
#include <QObject>
#include <darrowrectangle.h>
#include <DDialog>
//#include <DArrowRectangle>

DWIDGET_USE_NAMESPACE

class RightNoteList : public QListWidget
{
    Q_OBJECT
public:
    RightNoteList(NoteController *noteController);
    ~RightNoteList();
    void addWidgetItem(NOTE note);

signals:
    void textEditClicked(NOTE textNote);


public slots:
    void handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void handleDelItem(bool);
    void handleSaveAsItem(bool);
    void handleDelDialogClicked(int index, const QString &text);


private:
    QMenu *m_contextMenu;
    QAction *m_saveAsAction;
    QAction *m_delAction;
    NoteController *m_noteController;
    DArrowRectangle *m_arrowMenu;
    QListWidgetItem *m_currSelItem;
    NOTE m_currSelNote;
    DDialog *m_delConfirmDialog;
    void initUI();
    void initConnection();
};

#endif // RIGHTNOTELIST_H
