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
};

#endif // FOLDERCONTROLLER_H
