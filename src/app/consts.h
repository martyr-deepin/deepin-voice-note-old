#ifndef CONSTS_H
#define CONSTS_H

#include <QDateTime>
#include <QString>

#define TABLE_FOLDER "folder"

static QString DB_PATH = "/mnt/hgfs/D/voiceNoteDB.db";
static QString DEFAULT_FOLDER_IMG_PATH = ":/image/default_folder_img.png";

typedef struct
{
    int id;
    QString imgPath;
    QString folderName;
    QDateTime createTime;
}FOLDER;
#endif // CONSTS_H
