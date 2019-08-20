#ifndef NOTECONTROLLER_H
#define NOTECONTROLLER_H

#include "consts.h"
class NoteController
{
public:
    NoteController();
    ~NoteController();

    QList<NOTE> getNoteListByFolderId(int folderId);
    bool addNote(NOTE noteInfo);
};

#endif // NOTECONTROLLER_H
