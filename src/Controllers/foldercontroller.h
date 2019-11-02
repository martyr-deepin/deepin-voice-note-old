#ifndef FOLDERCONTROLLER_H
#define FOLDERCONTROLLER_H

#include <QList>
#include "consts.h"



class FolderController
{
public:
    FolderController();
    ~FolderController();

    QList<FOLDER> getFolderList();
    QList<FOLDER> searchFolder(QString searchKey);
    bool addFolder(FOLDER folderInfo);

    bool checkFolderNameExist(FOLDER folderInfo);
    bool updateFolder(FOLDER folderInfo);
    QString getNextFolderName();
    bool deleteFolder(int folderId);
};

#endif // FOLDERCONTROLLER_H
