#ifndef NOTEOPER_H
#define NOTEOPER_H

#include <QList>
#include "consts.h"



class NoteOper
{
public:
    NoteOper();
    static QList<NOTE> getNoteListByFolderId(int folderId);
    static bool addNote(NOTE noteInfo);
    static bool updateNote(NOTE noteInfo);
};

#endif // NOTEOPER_H
