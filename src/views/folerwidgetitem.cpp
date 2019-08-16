#include "folerwidgetitem.h"

#include <QString>
QPixmap FolerWidgetItem::getPixmap(QSize size, QString imgPath)
{
    if ((nullptr == imgPath) || (imgPath.length() <= 0))
    {
        //todo:如果沒有圖片，要使用默認的圖片
    }
    QImage *img = new QImage();
    img->load(imgPath);
    // 设定图像大小自适应label窗口的大小
    *img = img->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return QPixmap::fromImage(*img);
}
QString FolerWidgetItem::getCreateTimeLabel(QDateTime createTime)
{
    return "一個月前";
}

//FolerWidgetItem::FolerWidgetItem()
FolerWidgetItem::FolerWidgetItem(FOLDER folder)
{
    this->folder = folder;
    initUI();
}

FolerWidgetItem::~FolerWidgetItem()
{
}

void FolerWidgetItem::initUI()
{

    //this->resize(196, 60);
    //setNormalBackground();
    //this->setStyleSheet("background: red");
    imageLabel = new QLabel(this);
    imageLabel->setGeometry(QRect(10, 10, 50, 40));
    imageLabel->setObjectName("imageLabel");
    imageLabel->size();
    QPixmap pixmap = getPixmap(imageLabel->size(), folder.imgPath);

//    bool convertFlag = getPixmap(imageLabel->size(), folder.imgPath, pixmap);
//    if (convertFlag)
//    {
        imageLabel->setPixmap(getPixmap(imageLabel->size(), folder.imgPath));
//    }

    nameLabel = new QLabel(this);

    nameLabel->setGeometry(QRect(70, 10, 150, 21));
    nameLabel->setLineWidth(150);
    nameLabel->setObjectName("nameLabel");
    nameLabel->setText(folder.folderName);
    createTimeLabel = new QLabel(this);
    createTimeLabel->setGeometry(QRect(70, 40, 150, 16));
    createTimeLabel->setObjectName("createTimeLabel");
    createTimeLabel->setText(getCreateTimeLabel(folder.createTime));
}

void FolerWidgetItem::setItemBackground(QString imgPath)
{
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap(imgPath)));
    this->setPalette(pal);
}
void FolerWidgetItem::setNormalBackground()
{
    setItemBackground(":/image/folder_normal.png");
}

