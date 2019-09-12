#ifndef UIUTIL_H
#define UIUTIL_H

#include <QWidget>
#include <DDialog>
#include <QObject>
//#include <ddialog.h>


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
    static QString getHtmlText(QString src, int fontSize, QString searchKey);
    static bool saveTxt(QString path, QString content);
    static bool saveMP3(QString src, QString target);
    static QString convertFolderDate(QDateTime dateTime);
    static QString convertNoteDate(QDateTime dateTime);
    static bool checkFileExtension(QString fileName, QString extension);
    static bool checkFileExist(QString filePath);

};

#endif // UIUTIL_H
