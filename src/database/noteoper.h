#ifndef NOTEOPER_H
#define NOTEOPER_H

#include <QList>
#include "consts.h"



class NoteOper
{
public:
    NoteOper();
    static void checkCleanDataBaseForVoiceByForderId(int folderId);
    static QList<NOTE> getNoteListByFolderId(int folderId);
    static QList<NOTE> searchNote(int folderId, QString searchKey);
    //static QString getConttextByNoteID(int folderID, int noteId);
    static QString getConttextByNoteID(int folderID, int noteId ,QDateTime *time = nullptr);//liuyang 3547
    static bool addNote(NOTE &noteInfo);
    static bool updateNote(const NOTE &noteInfo);
    static bool deleteNote(NOTE noteInfo);
};

#endif // NOTEOPER_H
