#include "notecontroller.h"

#include <noteoper.h>

NoteController::NoteController()
{

}

NoteController::~NoteController()
{

}

void NoteController::checkCleanDataBaseForVoiceByForderId(int folderId)
{
    NoteOper::checkCleanDataBaseForVoiceByForderId(folderId);
}

QList<NOTE> NoteController::getNoteListByFolderId(int folderId)
{
    return NoteOper::getNoteListByFolderId(folderId);
}

QString NoteController::getConttextByNoteID(int folderId , int noteID ,QDateTime *time)//liuyang 3547
//QString NoteController::getConttextByNoteID(int folderId , int noteID)
{
    //return NoteOper::getConttextByNoteID(folderId,noteID);
    return NoteOper::getConttextByNoteID(folderId,noteID,time);//liuyang 3547
}

bool NoteController::addNote(NOTE &noteInfo)
{
    //todo:检查文件夹id是否存在
    return NoteOper::addNote(noteInfo);
}

bool NoteController::updateNote(const NOTE &noteInfo)
{
    return NoteOper::updateNote(noteInfo);
}


bool NoteController::deleteNote(NOTE noteInfo)
{
    return NoteOper::deleteNote(noteInfo);
}

QList<NOTE> NoteController::searchNote(int folderId, QString searchKey)
{
    return NoteOper::searchNote(folderId, searchKey);
}
