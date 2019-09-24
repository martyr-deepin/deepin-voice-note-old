#ifndef NOTEOPER_H
#define NOTEOPER_H

#include <QList>
#include "consts.h"



class NoteOper
{
public:
    NoteOper();
    static QList<NOTE> getNoteListByFolderId(int folderId);
    static QList<NOTE> searchNote(int folderId, QString searchKey);
    static bool addNote(NOTE &noteInfo);
    static bool updateNote(NOTE noteInfo);
    static bool deleteNote(int id);
};

#endif // NOTEOPER_H
