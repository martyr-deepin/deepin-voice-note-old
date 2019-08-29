#include "uiutil.h"

#include <QDateTime>
#include <QDir>
#include <QStandardPaths>

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

DDialog* UiUtil::createDialog(const QString &title, const QString &content, QWidget *parent)
{
    DDialog *dialog = new DDialog(title, content, parent);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowStaysOnTopHint);
    dialog->setIcon(QIcon(":/image/voice_note_logo.svg"));
    dialog->addButton(QString(QObject::tr("Cancel")), false, DDialog::ButtonNormal);
    dialog->addButton(QString(QObject::tr("Delete")), false, DDialog::ButtonNormal);

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


