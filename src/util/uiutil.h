#ifndef UIUTIL_H
#define UIUTIL_H

#include <QWidget>
#include <DDialog>
#include <QObject>
#include <QImageReader>
#include <DApplication>
//#include <DFrameWorkDBus>

//#include <ddialog.h>
#include "consts.h"

DWIDGET_USE_NAMESPACE
class UiUtil : public QObject
{
    Q_OBJECT
public:
    UiUtil();

    static void setWidgetBackground(QWidget *widget, QString imgPath);
    static QPixmap getPixmap(QSize size, QString imgPath);
    static DDialog *createChooseDialog(const QString &title, const QString &content, QWidget *parent, QString cancelStr, QString deleteStr);
    static DDialog *createConfirmDialog(const QString &title, const QString &content, QWidget *parent);
    static QString getElidedText(QFont font, QString str, int MaxWidth, bool& isConverted);
    static QString formatMillisecond(int millisecond);
    static QString formatMillisecondToSecAndMil(int millisecond);
    static QString getRecordingSaveDirectory();
    static QString convertFloatListToString(QList<float> list);
    static QList<float> convertStringToFloatList(QString str);
    static QString getHtmlText(QString src, int fontSize, QString searchKey,RICH_TEXT_COLOR color);
    static bool saveTxt(QString path, QString content);
    static bool saveMP3(QString src, QString target);
    //static QString convertFolderDate(QDateTime dateTime);
    static QString convertDateTime(QDateTime dateTime);
    //static QString convertNoteDate(QDateTime dateTime);
    static bool checkFileExtension(QString fileName, QString extension);
    static bool checkFileExist(QString filePath);
    static QString getRecordingVoiceFullPath(QString fileName);
    static QPixmap PixmapToRound(QPixmap &src, int radius);
    static QString getDefaultAvatarByRand();
    static bool canMicrophoneInput();
    static QVariant redDBusProperty(const QString &service, const QString &path, const QString &interface, const char *propert);
    static QPixmap renderSVG(const QString &filePath, const QSize &size, DApplication *pApp);

    //====start add 20191105  bug2162
    static bool DeleteFileOrFolder( const QString& strPath);
    static QString getRecordingTxtFullPath(QString fileName);
    static bool autoAddEditTxt(const NOTE &noteInfo);
    static bool autoDeleteTxt(const NOTE &noteInfo);
    //====end add 20191105  bug2162
};

#endif // UIUTIL_H
