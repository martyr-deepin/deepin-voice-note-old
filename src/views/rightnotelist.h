#ifndef RIGHTNOTELIST_H
#define RIGHTNOTELIST_H

#include <QListWidget>
#include <notecontroller.h>
#include <consts.h>
#include <QObject>



class RightNoteList : public QListWidget
{
    Q_OBJECT
public:
    RightNoteList(NoteController *noteController);
    ~RightNoteList();
    void addWidgetItem(NOTE note);

signals:
    void textEditClicked(NOTE textNote);

private:
    NoteController *m_noteController;
    void initUI();
    void initConnection();
};

#endif // RIGHTNOTELIST_H
