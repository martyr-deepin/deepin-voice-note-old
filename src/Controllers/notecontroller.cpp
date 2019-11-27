#include "notecontroller.h"

#include <noteoper.h>
#include "intancer.h"

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

QString NoteController::getConttextByNoteID(int folderId , int noteID)
{
    return NoteOper::getConttextByNoteID(folderId,noteID);
}

bool NoteController::addNote(NOTE &noteInfo)
{
    //todo:检查文件夹id是否存在
    return NoteOper::addNote(noteInfo);
}

bool NoteController::updateNote(NOTE noteInfo)
{
    Intancer::get_Intancer()->setTextNoteItemChangeState(true);
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
