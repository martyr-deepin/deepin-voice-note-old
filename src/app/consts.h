#ifndef CONSTS_H
#define CONSTS_H

#include <QDateTime>
#include <QString>

#define TABLE_FOLDER "folder"

static QString DB_PATH = "/mnt/hgfs/D/voiceNoteDB.db";

typedef struct
{
    int id;
    QString imgPath;
    QString folderName;
    QDateTime createTime;
}FOLDER;
#endif // CONSTS_H
