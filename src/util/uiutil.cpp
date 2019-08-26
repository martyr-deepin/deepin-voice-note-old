#include "uiutil.h"

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
