#include "notecontroller.h"

#include <noteoper.h>

NoteController::NoteController()
{

}

NoteController::~NoteController()
{

}


QList<NOTE> NoteController::getNoteListByFolderId(int folderId)
{
    return NoteOper::getNoteListByFolderId(folderId);
}
bool NoteController::addNote(NOTE noteInfo)
{
    //todo:检查文件夹id是否存在
    return NoteOper::addNote(noteInfo);
}

bool NoteController::updateNote(NOTE noteInfo)
{
    return NoteOper::updateNote(noteInfo);
}
