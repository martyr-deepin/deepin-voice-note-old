#ifndef CONSTS_H
#define CONSTS_H

#include <QDateTime>
#include <QTime>
#include <QString>

#define TABLE_FOLDER "folder"
#define TABLE_NOTE "note"
#define MAX_FOLDERIMG_NUM (10)
//#define TEXTNOTE_HEIGHT (123)
#define TEXTNOTE_HEIGHT (135)
#define VOICENOTE_HEIGHT (98)
#define ADDBUTTON_HEIGHT_HEIGHT (84)
//static QString DB_PATH = "./voiceNoteDB.db";
//static QString DB_PATH = "/mnt/hgfs/D/voiceNoteDB1.db";
static QString DEFAULT_FOLDER_IMG_PATH_1 = ":/image/icon/DefaultAvatar/1.svg";
static QString DEFAULT_FOLDER_IMG_PATH_2 = ":/image/icon/DefaultAvatar/2.svg";
static QString DEFAULT_FOLDER_IMG_PATH_3 = ":/image/icon/DefaultAvatar/3.svg";
static QString DEFAULT_FOLDER_IMG_PATH_4 = ":/image/icon/DefaultAvatar/4.svg";
static QString DEFAULT_FOLDER_IMG_PATH_5 = ":/image/icon/DefaultAvatar/5.svg";
static QString DEFAULT_FOLDER_IMG_PATH_6 = ":/image/icon/DefaultAvatar/6.svg";
static QString DEFAULT_FOLDER_IMG_PATH_7 = ":/image/icon/DefaultAvatar/7.svg";
static QString DEFAULT_FOLDER_IMG_PATH_8 = ":/image/icon/DefaultAvatar/8.svg";
static QString DEFAULT_FOLDER_IMG_PATH_9 = ":/image/icon/DefaultAvatar/9.svg";
static QString DEFAULT_FOLDER_IMG_PATH_10 = ":/image/icon/DefaultAvatar/10.svg";
static QStringList default_folder_imgpath=
{
    DEFAULT_FOLDER_IMG_PATH_1,
    DEFAULT_FOLDER_IMG_PATH_2,
    DEFAULT_FOLDER_IMG_PATH_3,
    DEFAULT_FOLDER_IMG_PATH_4,
    DEFAULT_FOLDER_IMG_PATH_5,
    DEFAULT_FOLDER_IMG_PATH_6,
    DEFAULT_FOLDER_IMG_PATH_7,
    DEFAULT_FOLDER_IMG_PATH_8,
    DEFAULT_FOLDER_IMG_PATH_9,
    DEFAULT_FOLDER_IMG_PATH_10
};
static const char * DEFAULT_FOLDER_NAME = "新记事";
static const char * FOLDER_MENU_RENAME = "重命名";
static const char * FOLDER_MENU_DELETE = "删除";
static const char * NOTE_MENU_SAVE_AS_TXT = "保存为TXT";
static const char * NOTE_MENU_SAVE_AS_MP3 = "保存为MP3";

enum NOTE_TYPE {VOICE=0, TEXT=1};
enum RICH_TEXT_COLOR {BLUE=0, WHITE=1};

typedef struct
{
    int id;
    QString imgPath;
    QString folderName;
    QDateTime createTime;
}FOLDER;



typedef struct
{
    int id;
    NOTE_TYPE noteType;
    QString contentText;
    QString contentPath;
    int voiceTime;
    QString voiceSampleData;
    int folderId;
    QDateTime createTime;
}NOTE;

typedef struct
{
    NOTE note;
    QString windowTitle;
    QString fileExtension;
}SAVE_INFO;

typedef struct
{
    QString voicePath;
    int voiceLength;
    QString voiceSampleData;
}VOICE_INFO;
#endif // CONSTS_H
