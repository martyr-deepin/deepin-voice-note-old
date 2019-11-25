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

QList<FOLDER> FolderController::searchFolder(QString searchKey)
{
    return FolderOper::searchFolder(searchKey);
}

bool FolderController::addFolder(FOLDER folderInfo)
{
    return FolderOper::addFolder(folderInfo);
}

bool FolderController::checkFolderNameExist(FOLDER folderInfo)
{
    QList<FOLDER> folderList = FolderOper::getFolderByName(folderInfo.folderName);
    if (folderList.size() >= 2)
    {
        return true;
    }else if (folderList.size() == 1 && (folderInfo.id != folderList.at(0).id)){
        return true;
    }
    return false;
}

bool FolderController::updateFolderName(FOLDER folderInfo)
{
    return FolderOper::updateFolderName(folderInfo);
}

bool FolderController::updateFolderCreateTime(FOLDER folderInfo)
{
    return FolderOper::updateFolderTime(folderInfo);
}

QString FolderController::getNextFolderName()
{
    QStringList folderNameList = FolderOper::getFolderNameList();
    QString folderName = QString(QObject::tr("NewFolder"));
    //QString folderName = QString(QObject::tr("新记事"));

    //QString folderName = DEFAULT_FOLDER_NAME;
    int i = 1;
    bool findFlag = false;
    while (!findFlag)
    {
        if (folderNameList.contains(folderName))
        {
            folderName = folderName + QString::number(i);
            //folderName = DEFAULT_FOLDER_NAME + QString::number(i);
            i++;
        }
        else {
            findFlag = true;
        }
    }
    return folderName;

}

bool FolderController::deleteFolder(int folderId)
{
    return FolderOper::deleteFolder(folderId);
}
