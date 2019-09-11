#include "uiutil.h"

#include <QDateTime>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>

UiUtil::UiUtil()
{

}

void UiUtil::setWidgetBackground(QWidget *widget, QString imgPath)
{
    widget->setAutoFillBackground(true);
    QPalette pal;// = widget->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap(imgPath)));
    widget->setPalette(pal);
}

QPixmap UiUtil::getPixmap(QSize size, QString imgPath)
{
    QPixmap pixmap;
    if ((nullptr == imgPath) || (imgPath.length() <= 0))
    {
        return pixmap;
        //todo:如果沒有圖片，要使用默認的圖片
    }
    QImage img;
    img.load(imgPath);
    // 设定图像大小自适应label窗口的大小
    img = img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return QPixmap::fromImage(img);

//    QImage *img = new QImage();
//    img->load(imgPath);
//    // 设定图像大小自适应label窗口的大小
//    *img = img->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    return QPixmap::fromImage(*img);

}

DDialog* UiUtil::createChooseDialog(const QString &title, const QString &content, QWidget *parent, QString cancelStr, QString okStr)
{
    DDialog *dialog = new DDialog(title, content, parent);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowStaysOnTopHint);
    dialog->setIcon(QIcon(":/image/voice_note_logo.svg"));
    dialog->addButton(cancelStr, false, DDialog::ButtonNormal);
    dialog->addButton(okStr, false, DDialog::ButtonNormal);

    return dialog;
}

QString UiUtil::getElidedText(QFont font, QString str, int MaxWidth, bool& isConverted)
{
    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);  //计算字符串宽度
    if(width >= MaxWidth)  //当字符串宽度大于最大宽度时进行转换
    {
        isConverted = true;
        str = fontWidth.elidedText(str, Qt::ElideRight, MaxWidth);  //右部显示省略号
    }
    else
    {
        isConverted = false;
    }
    return str;   //返回处理后的字符串
}

QString UiUtil::formatMillisecond(int millisecond)
{
    if (millisecond / 1000 < 3600) {
        // At least need return 1 seconds.
        return QDateTime::fromTime_t(std::max(1, millisecond / 1000)).toUTC().toString("mm:ss");
    } else {
        return QDateTime::fromTime_t(millisecond / 1000).toUTC().toString("hh:mm:ss");
    }
}

QString UiUtil::getRecordingSaveDirectory()
{
    QDir musicDirectory = QDir(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first());
    QString subDirectory = tr("Recordings");
    musicDirectory.mkdir(subDirectory);

    return musicDirectory.filePath(subDirectory);
}

QString UiUtil::formatMillisecondToSecAndMil(int millisecond)
{
    QString time;
    if (millisecond / 1000 < 3600) {
        // At least need return 1 seconds.
        time = QDateTime::fromTime_t(std::max(1, millisecond / 1000)).toUTC().toString("mm:ss");
    } else {
        time = QDateTime::fromTime_t(millisecond / 1000).toUTC().toString("mm:ss");
    }
    time = time.replace(":", "\'").append("\'\'");
    return time;
}

QString UiUtil::convertFloatListToString(QList<float> list)
{
    QStringList strList;
    for (int i = 0; i < list.size(); i++)
    {
        strList << QString::number(list.at(i));
    }
    return strList.join(';');
}

QList<float> UiUtil::convertStringToFloatList(QString str)
{
    QStringList strList = str.split(';');
    QList<float> list;
    for (int i = 0; i < strList.size(); i++)
    {
        list << strList.at(i).toFloat();
    }
    return list;
}

QString UiUtil::getHtmlText(QString src, int fontSize, QString searchKey)
{
    QString richText = "<p  style=\"font-size:%1px\">%2</p>";
    QString searchStr = "<font color=#349ae8>%1</font>";
    QString destSrc = src;
    if (!searchKey.isEmpty())
    {
        destSrc = src.replace(searchKey, searchStr.arg(searchKey));
    }

    QString tmpText = richText.arg(fontSize).arg(destSrc);

    return tmpText;
}

bool UiUtil::saveTxt(QString path, QString content)
{
    //QString sFilePath="./wltest.txt";
    QFile file(path);
    //QFile file(sFilePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return false;
    }
    QTextStream textStream(&file);
    textStream << content;
    file.close();
    return true;
}

QString UiUtil::convertFolderDate(QDateTime dateTime)
{
    QString dayStr = "%1天前";
    QString monthStr = "%1个月前";
    QDate currDateTime = QDate::currentDate();
    QDate folerDate = dateTime.date();
    qint64 offset = folerDate.daysTo(currDateTime);
    if (0 == offset)
    {
        return "今天";
    }
    else if ((offset < 30) && (offset > 0))
    {
        return dayStr.arg(offset);
    }
    else if (offset >= 30)
    {
        int month = offset / 30;
        return monthStr.arg(month);
    }
    return "今天";
}

QString UiUtil::convertNoteDate(QDateTime dateTime)
{
    QString dayStr = "%1天前";
    QString hourStr = "%1个小时前";
    QDateTime currDateTime = QDateTime::currentDateTime();
    //QDate folerDate = dateTime.date();
    qint64 offsetMS = dateTime.msecsTo(currDateTime);
    qint64 offsetSec = offsetMS / (60 * 1000);
    if (offsetSec >= 0 && offsetSec <= 60 )
    {
        return "刚刚";
    }
    else if((offsetSec > 60) && (offsetSec <= 24 * 60))
    {
        int hour = offsetSec / 60;
        return hourStr.arg(hour);

    }
    else if (offsetSec > 24 * 60)
    {
        int day = offsetSec / (24 * 60);
        return dayStr.arg(day);
    }

    return "刚刚";
}

bool UiUtil::checkFileExtension(QString fileName, QString extension)
{
    if (fileName.toLower().endsWith(extension.toLower()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool UiUtil::checkFileExist(QString filePath)
{
    QFile file(filePath);
    return file.exists();
}

DDialog *UiUtil::createConfirmDialog(const QString &title, const QString &content, QWidget *parent)
{
    DDialog *dialog = new DDialog(title, content, parent);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowStaysOnTopHint);
    dialog->setIcon(QIcon(":/image/voice_note_logo.svg"));
    dialog->addButton(QString(QObject::tr("确认")), false, DDialog::ButtonNormal);
    return dialog;
    //dialog->addButton(okStr, false, DDialog::ButtonNormal);
}


