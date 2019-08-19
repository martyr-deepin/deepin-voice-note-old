#ifndef CONSTS_H
#define CONSTS_H

#include <QDateTime>
#include <QString>

#define TABLE_FOLDER "folder"

static QString DB_PATH = "/mnt/hgfs/D/voiceNoteDB1.db";
static QString DEFAULT_FOLDER_IMG_PATH = ":/image/default_folder_img.png";
static QString DEFAULT_FOLDER_NAME = "新记事";

typedef struct
{
    int id;
    QString imgPath;
    QString folderName;
    QDateTime createTime;
}FOLDER;
#endif // CONSTS_H
