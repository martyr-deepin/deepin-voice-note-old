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
    bool updateNote(NOTE noteInfo);
    bool deleteNote(int noteId);
};

#endif // NOTECONTROLLER_H
