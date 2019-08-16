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
    initConnection();
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

    lineEdit = new DLineEdit(this);
    lineEdit->setGeometry(QRect(70, 10, 150, 21));
    lineEdit->setObjectName("nameEdit");
    lineEdit->setText(folder.folderName);
    lineEdit->setVisible(false);
    createTimeLabel = new QLabel(this);
    createTimeLabel->setGeometry(QRect(70, 40, 150, 16));
    createTimeLabel->setObjectName("createTimeLabel");
    createTimeLabel->setText(getCreateTimeLabel(folder.createTime));
}

void FolerWidgetItem::initConnection()
{
    connect(lineEdit, &DLineEdit::editingFinished, this, &FolerWidgetItem::checkNameValid);
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

void FolerWidgetItem::changeToEditMode()
{
    nameLabel->setVisible(false);
    lineEdit->setVisible(true);
}

void FolerWidgetItem::checkNameValid()
{
    if ((lineEdit->text().length() > 0) && (lineEdit->text().length() < 64)) {
        //todo:更新数据库
        nameLabel->setText(lineEdit->text());
        nameLabel->setVisible(true);
        lineEdit->setVisible(false);
    } else {
        //警告用户输入不能为空
        lineEdit->setAlert(true);
        lineEdit->showAlertMessage("输入字符长度必须在0-64位之间");
    }

}

