#ifndef NOTECONTROLLER_H
#define NOTECONTROLLER_H

#include "consts.h"
class NoteController
{
public:
    NoteController();
    ~NoteController();

    QList<NOTE> getNoteListByFolderId(int folderId);
    QList<NOTE> searchNote(int folderId, QString searchKey);
    bool addNote(NOTE &noteInfo);
    bool updateNote(NOTE noteInfo);
    bool deleteNote(int noteId);
};

#endif // NOTECONTROLLER_H
