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

bool FolderController::addFolder(FOLDER folderInfo)
{
    return FolderOper::addFolder(folderInfo);
}

bool FolderController::checkFolderNameExist(FOLDER folderInfo)
{
    return false;
}

bool FolderController::updateFolder(FOLDER folderInfo)
{
    return FolderOper::updateFolderName(folderInfo);
}
