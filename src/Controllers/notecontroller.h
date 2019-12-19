#ifndef NOTECONTROLLER_H
#define NOTECONTROLLER_H

#include "consts.h"
class NoteController
{
public:
    NoteController();
    ~NoteController();

    void checkCleanDataBaseForVoiceByForderId(int folderId);
    QList<NOTE> getNoteListByFolderId(int folderId);
    QList<NOTE> searchNote(int folderId, QString searchKey);
    //QString getConttextByNoteID(int folderId, int noteID);
    QString getConttextByNoteID(int folderId, int noteID,QDateTime *time = nullptr);
    bool addNote(NOTE &noteInfo);
    bool updateNote(const NOTE &noteInfo);
    bool deleteNote(NOTE noteInfo);
};

#endif // NOTECONTROLLER_H
