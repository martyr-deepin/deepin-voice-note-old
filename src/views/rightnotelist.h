#ifndef RIGHTNOTELIST_H
#define RIGHTNOTELIST_H

#include <QListWidget>
#include <notecontroller.h>
#include <consts.h>



class RightNoteList : public QListWidget
{
    Q_OBJECT
public:
    RightNoteList(NoteController *noteController);
    ~RightNoteList();
    void addWidgetItem(NOTE note);

private:
    void initUI();
    void initConnection();
};

#endif // RIGHTNOTELIST_H
