#include "uiutil.h"
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>
#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include <QDBusObjectPath>
#include <QDBusInterface>
#include <QDBusReply>

//extern "C"
//{
//#include "libavcodec/avcodec.h"
//#include "libavformat/avformat.h"
//}

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

QPixmap UiUtil::PixmapToRound(QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

DDialog* UiUtil::createChooseDialog(const QString &title, const QString &content, QWidget *parent, QString cancelStr, QString okStr)
{
    DDialog *dialog = new DDialog(title, content, parent);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowStaysOnTopHint);
    //dialog->setIcon(QIcon(":/image/voice-note-32px 2.svg"));
    dialog->setIcon(QIcon(UiUtil::renderSVG(":/image/voice-note-32px 2.svg", QSize(32,32),qApp)));
    dialog->addButton(cancelStr, false, DDialog::ButtonNormal);
    dialog->addButton(okStr, false, DDialog::ButtonWarning);

    return dialog;
}

QString UiUtil::getElidedText(QFont font, QString str, int MaxWidth, bool& isConverted)
{
    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);  //计算字符串宽度
    //int CorMaxWidth = MaxWidth - 20;
    int CorMaxWidth = MaxWidth;
    if(width >= CorMaxWidth)  //当字符串宽度大于最大宽度时进行转换
    {
        isConverted = true;
        //由于…要在地5行末尾出现，所以需要调整一下计算…出现的位置
        str = fontWidth.elidedText(str, Qt::ElideRight, CorMaxWidth);  //右部显示省略号
        //str = fontWidth.elidedText(str, Qt::ElideRight, MaxWidth);  //右部显示省略号
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
    QDir musicDirectory = QDir(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first());
    QString subDirectory("voicenote");
    //QString subDirectory = tr("voicenote");
    musicDirectory.mkdir(subDirectory);

    return musicDirectory.filePath(subDirectory);
}

QString UiUtil::formatMillisecondToSecAndMil(int millisecond)
{
    QString time;
    if (millisecond / 1000 < 3600) {
        // At least need return 1 seconds.
        time = QDateTime::fromTime_t(std::max(1, qRound(millisecond / 1000.0))).toUTC().toString("mm:ss"); //ynb 20191109
        time = time.replace(":", "\'").append("\'\'");
        //time = QDateTime::fromTime_t(std::max(1, millisecond / 1000)).toUTC().toString("mm:ss");
    } else {
        time = QString("60\'00\"");
        //time = QString(tr("60\'00\""));
        //time = QDateTime::fromTime_t(qRound(millisecond / 1000.0)).toUTC().toString("mm:ss");   //ynb 20191109
        //time = QDateTime::fromTime_t(millisecond / 1000).toUTC().toString("mm:ss");
    }

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

QString UiUtil::getHtmlText(QString src, int fontSize, QString searchKey, RICH_TEXT_COLOR color)
{

    //src.replace("<","&#60;");
    src.replace("<","&lt;");
    //QString richText = "<p  style=\"font-size:%1px\">%2</p>";
    QString searchStr = "<font color=#349ae8>%1</font>";
    if(BLUE == color)
    {
        searchStr.clear();
        searchStr = "<font color=#349ae8>%1</font>";
    }
    else if(WHITE == color)
    {
        searchStr.clear();
        searchStr = "<font color=#ffffff>%1</font>";
    }
    QString destSrc = src;

    QString n = "\n";
    QString br = "<br/>";
    destSrc = destSrc.replace(n,br);


    QString space = " ";
    QString RichSpace = "&nbsp;";
    destSrc = destSrc.replace(space,RichSpace);

    QString tab = "\t";
    QString Richtab = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
    destSrc = destSrc.replace(tab,Richtab);

    if (!searchKey.isEmpty())
    {
        destSrc = destSrc.replace(searchKey, searchStr.arg(searchKey));
    }

    return destSrc;
//    QString tmpText = richText.arg(fontSize).arg(destSrc);

//    return tmpText;

}

bool UiUtil::saveTxt(QString path, QString content)
{
    //QString sFilePath="./wltest.txt";
    QFile file(path);
    //QFile file(sFilePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"saveTxt failed";
        return false;
    }
    QTextStream textStream(&file);
    textStream << content;
    file.close();
    return true;
}

bool UiUtil::saveMP3(QString src, QString target)
{
    bool result = QFile::copy(src, target);
    if(!result)
    {
        qDebug()<<"saveMP3 failed";
    }
    return result;
}

//QString UiUtil::convertFolderDate(QDateTime dateTime)
//{
//    QString dayStr = "%1天前";
//    QString monthStr = "%1个月前";
//    QDate currDateTime = QDate::currentDate();
//    QDate folerDate = dateTime.date();
//    qint64 offset = folerDate.daysTo(currDateTime);
//    if (0 == offset)
//    {
//        return "今天";
//    }
//    else if ((offset < 30) && (offset > 0))
//    {
//        return dayStr.arg(offset);
//    }
//    else if (offset >= 30)
//    {
//        int month = offset / 30;
//        return monthStr.arg(month);
//    }
//    return "今天";
//}

QString UiUtil::convertDateTime(QDateTime dateTime)
{
    QDate currDateTime = QDate::currentDate();
    QDate folerDate = dateTime.date();
    QTime folerTime = dateTime.time();
    QString disptime;
    qint64 offset = folerDate.daysTo(currDateTime);
    if (0 == offset)
    {
        //今天：展示时间hh：mm ；
        int hour = folerTime.hour();
        int minute = folerTime.minute();
        QString strhour;
        QString strminute;
        if(hour < 10)
        {
            strhour.append("0" + QString::number(hour));
        }
        else
        {
            strhour.append(QString::number(hour));
        }

        if(minute < 10)
        {
            strminute.append("0" + QString::number(minute));
        }
        else
        {
            strminute.append(QString::number(minute));
        }
        disptime.append(strhour + ":" + strminute);
    }
    else if(1 == offset)
    {
        //昨天
        disptime.append("昨天");
    }
    else if(folerDate.year() == currDateTime.year())
    {
        //不跨年 其他时间：MM-DD（例如：9⽉27日）；
        disptime.append(QString::number(folerDate.month()) + "月" + QString::number(folerDate.day()) + "日");
    }
    else
    {
        //跨年:YYYY-MM-DD（例如2018年9月26日）；
        disptime.append(QString::number(folerDate.year()) + "年" + QString::number(folerDate.month()) + "月" + QString::number(folerDate.day()) + "日");
    }
    return disptime;
}

//QString UiUtil::convertNoteDate(QDateTime dateTime)
//{
//    QString dayStr = "%1天前";
//    QString hourStr = "%1个小时前";
//    QDateTime currDateTime = QDateTime::currentDateTime();
//    //QDate folerDate = dateTime.date();
//    qint64 offsetMS = dateTime.msecsTo(currDateTime);
//    qint64 offsetSec = offsetMS / (60 * 1000);
//    if (offsetSec >= 0 && offsetSec <= 60 )
//    {
//        return "刚刚";
//    }
//    else if((offsetSec > 60) && (offsetSec <= 24 * 60))
//    {
//        int hour = offsetSec / 60;
//        return hourStr.arg(hour);

//    }
//    else if (offsetSec > 24 * 60)
//    {
//        int day = offsetSec / (24 * 60);
//        return dayStr.arg(day);
//    }

//    return "刚刚";
//}

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
    bool ret = file.exists();
    return  ret;
}


DDialog *UiUtil::createConfirmDialog(const QString &title, const QString &content, QWidget *parent)
{
    DDialog *dialog = new DDialog(title, content, parent);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowStaysOnTopHint);
    //dialog->setIcon(QIcon(":/image/voice-note-32px 2.svg"));
    dialog->setIcon(QIcon(UiUtil::renderSVG(":/image/voice-note-32px 2.svg", QSize(32,32),qApp)));
    dialog->addButton(QString(QObject::tr("OK")), false, DDialog::ButtonNormal);
    //dialog->addButton(QString(QObject::tr("确认")), false, DDialog::ButtonNormal);
    return dialog;
    //dialog->addButton(okStr, false, DDialog::ButtonNormal);
}

QString UiUtil::getRecordingVoiceFullPath(QString fileName)
{
    return QDir(getRecordingSaveDirectory()).filePath(fileName);
}

QString UiUtil::getDefaultAvatarByRand()
{
    QString ImgPath;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int rand = qrand()%MAX_FOLDERIMG_NUM;
    ImgPath = default_folder_imgpath.at(rand);
    return ImgPath;
}

QVariant UiUtil::redDBusProperty(const QString &service, const QString &path, const QString &interface, const char *propert)
{
    // 创建QDBusInterface接口
    QDBusInterface ainterface(service, path,
                              interface,
                              QDBusConnection::sessionBus());
    if (!ainterface.isValid())
    {
        qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
        QVariant v(0) ;
        return  v;
    }
    //调用远程的value方法
    QVariant v = ainterface.property(propert);
    return  v;
}

bool UiUtil::canMicrophoneInput()
{
//    com::deepin::daemon::Audio *m_audioInterface = new com::deepin::daemon::Audio(
//                com::deepin::daemon::Audio::staticInterfaceName(),
//                "/com/deepin/daemon/Audio",
//                QDBusConnection::sessionBus());

//    com::deepin::daemon::audio::Source *m_defaultSourceInterface = new com::deepin::daemon::audio::Source (
//                com::deepin::daemon::audio::Source::staticInterfaceName(),
//                //"com.deepin.daemon.Audio.Source",
//                m_audioInterface->defaultSource().path(),
//                QDBusConnection::sessionBus());
//    double volume = m_defaultSourceInterface->volume();
//    qDebug()<<"Volume:"<<volume;
//    if(0.0001 < volume)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }


    QVariant v = redDBusProperty("com.deepin.daemon.Audio", "/com/deepin/daemon/Audio",
                                            "com.deepin.daemon.Audio", "DefaultSource");
    if (v.isValid()) {
        QDBusObjectPath path = v.value<QDBusObjectPath>();
        //qDebug() <<"path: "<<path.path();
        QDBusInterface ainterface("com.deepin.daemon.Audio", path.path(),
                                  "com.deepin.daemon.Audio.Source",
                                  QDBusConnection::sessionBus());
        if (!ainterface.isValid())
        {
            return false;
        }
        //调用远程的value方法
        QDBusReply<QDBusObjectPath> reply = ainterface.call("GetMeter");
        if (reply.isValid()){
            path = reply.value();
            //qDebug()<<"path1" << path.path();
            QVariant v = redDBusProperty("com.deepin.daemon.Audio", path.path(),
                                                    "com.deepin.daemon.Audio.Meter", "Volume");
            if (v.isValid()) {
                double volume = v.toDouble();
                //qDebug()<<"volume:" <<volume;
                if(0.0001 < volume)
                {
                    return true;
                }
                else
                {
                    return false;
                }
                //return volume != 0.0;
            }
        } else {
           return  false;
        }
    }
    return false;

}

//struct MyStruct
//{
//    std::string s1;
//    std::string s2;
//    char b;
//};

//Q_DECLARE_METATYPE(MyStruct)

//bool UiUtil::canMicrophoneInput()
//{
//    QVariant v = redDBusProperty("com.deepin.daemon.Audio", "/com/deepin/daemon/Audio",
//                                            "com.deepin.daemon.Audio", "DefaultSource");
//    if (v.isValid()) {
//        QDBusObjectPath path = v.value<QDBusObjectPath>();
//        qDebug() <<"path: "<<path.path();
//        QDBusInterface ainterface("com.deepin.daemon.Audio", path.path(),
//                                  "com.deepin.daemon.Audio.Source",
//                                  QDBusConnection::sessionBus());
//        if (!ainterface.isValid())
//        {
//            return false;
//        }
//        //调用远程的value方法
//        QDBusReply<QDBusObjectPath> reply = ainterface.call("GetMeter");
//        if (reply.isValid()){
//            path = reply.value();
//            qDebug()<<"path1" << path.path();
//            QVariant v = redDBusProperty("com.deepin.daemon.Audio", path.path(),
//                                     //    "com.deepin.daemon.Audio.Meter", "ActivePort");
//                                         "com.deepin.daemon.Audio.Meter", "Volume");
//            if (v.isValid()) {
//                double volume = v.toDouble();

////                MyStruct stru = v.value<MyStruct>();
////                qDebug()<<"s1:" <<s.s1;
////                qDebug()<<"s2:" <<s.s2;
////                qDebug()<<"b:" <<s.b;
////                return stru.b != 0;
//                return volume != 0.0;
//            }
//        } else {
//           return  false;
//        }
//    }
//    return false;

//}

QPixmap UiUtil::renderSVG(const QString &filePath, const QSize &size,DApplication *pApp)
{
    QImageReader reader;
    QPixmap pixmap;

    reader.setFileName(filePath);

    if (reader.canRead()) {

        //const qreal ratio = qApp->devicePixelRatio();
        const qreal ratio = pApp->devicePixelRatio();
        reader.setScaledSize(size * ratio);
        pixmap = QPixmap::fromImage(reader.read());
        pixmap.setDevicePixelRatio(ratio);
    } else {
        pixmap.load(filePath);
    }

    return pixmap;
}

//====start add 20191105  bug2162
bool UiUtil::DeleteFileOrFolder( const QString& strPath )
{
    if( strPath.isEmpty() || !QDir().exists( strPath ) )
        return false;

    QFileInfo fileInfo( strPath );

    if( fileInfo.isFile() )
        QFile::remove( strPath );
    else if( fileInfo.isDir() )
    {
        QDir qDir( strPath );
        qDir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );
        QFileInfoList fileInfoLst = qDir.entryInfoList();
        foreach( QFileInfo qFileInfo, fileInfoLst )
        {
            if( qFileInfo.isFile() )
                qDir.remove( qFileInfo.absoluteFilePath() );
            else
            {
                DeleteFileOrFolder( qFileInfo.absoluteFilePath() );
                qDir.rmdir( qFileInfo.absoluteFilePath() );
            }
        }
        qDir.rmdir( fileInfo.absoluteFilePath() );
    }

    return true;
}

QString UiUtil::getRecordingTxtFullPath(QString fileName)
{
    return QDir(getRecordingSaveDirectory()).filePath(fileName);
}

bool UiUtil::autoAddEditTxt(const NOTE &noteInfo)
{
   QString current_date = noteInfo.createTime.toString("yyyyMMddhhmmsszzz");
   QString fileName = QString("%1 (%2).txt").arg(("New txt note")).arg(current_date);
   QString path = UiUtil::getRecordingTxtFullPath(fileName);
   if (!UiUtil::saveTxt(path, noteInfo.contentText))
   {
       return false;
   }
   return true;
}

bool UiUtil::autoDeleteTxt(const NOTE &noteInfo)
{
    QString current_date = noteInfo.createTime.toString("yyyyMMddhhmmsszzz");
    QString fileName = QString("%1 (%2).txt").arg(("New txt note")).arg(current_date);
    QString path = UiUtil::getRecordingTxtFullPath(fileName);
    if (!UiUtil::DeleteFileOrFolder(path))
    {
        return false;
    }
    return true;
}
//====end add 20191105  bug2162
