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
    bool addFolder(FOLDER folderInfo);

    bool checkFolderNameExist(FOLDER folderInfo);
    bool updateFolder(FOLDER folderInfo);
};

#endif // FOLDERCONTROLLER_H
