#include "folerwidgetitem.h"

#include <QString>
#include <uiutil.h>


//FolerWidgetItem::FolerWidgetItem()
FolerWidgetItem::FolerWidgetItem(FOLDER folder, FolderController *folderCtr)
{
    this->m_folder = folder;
    this->m_folderCtr = folderCtr;
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
    m_imageLabel = new QLabel(this);
    m_imageLabel->setGeometry(QRect(10, 10, 50, 40));
    m_imageLabel->setObjectName("imageLabel");
    m_imageLabel->size();
    //QPixmap pixmap = getPixmap(m_imageLabel->size(), m_folder.imgPath);

//    bool convertFlag = getPixmap(imageLabel->size(), folder.imgPath, pixmap);
//    if (convertFlag)
//    {
        m_imageLabel->setPixmap(UiUtil::getPixmap(m_imageLabel->size(), m_folder.imgPath));
//    }

    m_nameLabel = new QLabel(this);

    m_nameLabel->setGeometry(QRect(70, 10, 110, 21));
    m_nameLabel->setLineWidth(150);
    m_nameLabel->setObjectName("nameLabel");

    QFont labelFont;
    labelFont.setFamily("SourceHanSansSC");
    labelFont.setPointSize(14);
    m_nameLabel->setFont(labelFont);
    bool isConverted = false;
    QString folderNameElided = UiUtil::getElidedText(m_nameLabel->font(), m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    m_nameLabel->setText(folderNameElided);

    m_lineEdit = new DLineEdit(this);
    m_lineEdit->setGeometry(QRect(70, 10, 110, 21));
    m_lineEdit->setObjectName("nameEdit");

    m_lineEdit->setText(m_folder.folderName);
    m_lineEdit->setVisible(false);
    m_createTimeLabel = new QLabel(this);
    m_createTimeLabel->setGeometry(QRect(70, 40, 110, 16));
    m_createTimeLabel->setObjectName("createTimeLabel");
    m_createTimeLabel->setText(getCreateTimeLabel(m_folder.createTime));
}

void FolerWidgetItem::initConnection()
{
    connect(m_lineEdit, &DLineEdit::editingFinished, this, &FolerWidgetItem::checkNameValid);
}

//QPixmap FolerWidgetItem::getPixmap(QSize size, QString imgPath)
//{
//    if ((nullptr == imgPath) || (imgPath.length() <= 0))
//    {
//        //todo:如果沒有圖片，要使用默認的圖片
//    }
//    QImage *img = new QImage();
//    img->load(imgPath);
//    // 设定图像大小自适应label窗口的大小
//    *img = img->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    return QPixmap::fromImage(*img);
//}
QString FolerWidgetItem::getCreateTimeLabel(QDateTime createTime)
{
//    int destDayOfYear = createTime.date().dayOfYear();
//    int currDayOfYear = QDateTime::currentDateTime().date().dayOfYear();
//    int oneMonthAgo = currDayOfYear - 30;
//    int destYear = createTime.date().year();
//    int currYear = QDateTime::currentDateTime().date().year();
//    int yearDiff = currYear - destYear;
//    if (yearDiff > 0)
//    {

//    }
//    else {

//    }
    return createTime.date().toString();
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
    m_nameLabel->setVisible(false);
    m_lineEdit->setVisible(true);
    m_lineEdit->selectAll();
}

void FolerWidgetItem::checkNameValid()
{
    if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() < 64)) {
        //todo:更新数据库
        m_folder.folderName = m_lineEdit->text();
        if (m_folderCtr->checkFolderNameExist(m_folder))
        {
            m_lineEdit->setAlert(true);
            m_lineEdit->showAlertMessage("目录名重复！");
        }
        else
        {
            if(!m_folderCtr->updateFolder(m_folder))
            {
                m_lineEdit->setAlert(true);
                m_lineEdit->showAlertMessage("修改目录名失败");

            }
            m_nameLabel->setText(m_lineEdit->text());
            m_nameLabel->setVisible(true);
            m_lineEdit->setVisible(false);
        }

    } else {
        //警告用户输入不能为空
        m_lineEdit->setAlert(true);
        m_lineEdit->showAlertMessage("输入字符长度必须在0-64位之间");
    }

}

