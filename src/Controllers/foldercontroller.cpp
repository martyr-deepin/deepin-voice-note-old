#include "foldercontroller.h"

#include <folderoper.h>

FolderController::FolderController()
{

}

FolderController::~FolderController()
{

}


QList<FOLDER> FolderController::getFolderList()
{
    return FolderOper::getFolderList( );
}
