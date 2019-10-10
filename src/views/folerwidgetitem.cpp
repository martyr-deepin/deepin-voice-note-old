#include "folerwidgetitem.h"

#include <QString>
#include <uiutil.h>
#include <DPalette>
#include <QPalette>
#include <QBrush>
#include <QLabel>
#include <QPalette>
#include <DWidget>
#include <QDebug>

//FolerWidgetItem::FolerWidgetItem()
FolerWidgetItem::FolerWidgetItem(FOLDER folder, FolderController *folderCtr, QString searchKey)
{
    this->m_folder = folder;
    this->m_folderCtr = folderCtr;
    this->m_searchKey = searchKey;
    this->Init();
}

FolerWidgetItem::~FolerWidgetItem()
{
}

void FolerWidgetItem::initConnection()
{
    connect(m_lineEdit, &DLineEdit::editingFinished, this, &FolerWidgetItem::checkNameValid);
    connect(m_lineEdit, &DLineEdit::textChanged, this, &FolerWidgetItem::checkNameLenth);
}


void FolerWidgetItem::setItemBackground(QString imgPath)
{
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap(imgPath)));
    this->setPalette(pal);
}

void FolerWidgetItem::setNormalBackground()
{

}

void FolerWidgetItem::changeToEditMode()
{
//    m_nameLabel->setVisible(false);
//    m_lineEdit->setVisible(true);
    m_stackedWidget->setCurrentIndex(1);

    //Update DlineEidt没有这个接口了

    m_lineEdit->lineEdit()->setCursorPosition(m_lineEdit->text().size());
    m_lineEdit->lineEdit()->selectAll();
    //m_lineEdit->setFocus(Qt::OtherFocusReason);

    m_createTimeLabel->setVisible(false);
    m_BakDefaultName = m_lineEdit->text();

}

void FolerWidgetItem::changeToClickMode()
{
    if((nullptr != m_nameLabel) && (nullptr != m_createTimeLabel) && (nullptr != m_BackGround))
    {
        QPalette pb;
        //pb.setColor(QPalette::Background,QColor(00,00,00));
        pb.setColor(QPalette::Background,QColor(00,129,255));
        m_BackGround->setPalette(pb);
        m_BackGround->setMaskAlpha(255);

        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::white);
        m_nameLabel->setPalette(pe);
        m_createTimeLabel->setPalette(pe);
        //m_BackGround->setVisible(false);
    }
}

void FolerWidgetItem::changeToUnClickMode()
{
    if((nullptr != m_nameLabel) && (nullptr != m_createTimeLabel) && (nullptr != m_BackGround))
    {
        QPalette pb;
        pb.setColor(QPalette::Background,QColor(00,00,00));
        //pe.setColor(QPalette::Background,QColor(00,129,255));
        m_BackGround->setPalette(pb);
        m_BackGround->setMaskAlpha(7);

        QPalette pe;
        pe.setColor(QPalette::WindowText,QColor(QRgb(0x001A2E)));
        m_nameLabel->setPalette(pe);
        pe.setColor(QPalette::WindowText,QColor(QRgb(0x526A7F)));
        m_createTimeLabel->setPalette(pe);
        //m_BackGround->setVisible(true);
    }
}

void FolerWidgetItem::Init()
{
    this->setFixedSize(QSize(250, 74));
    this->setBlurEnabled(false);

    m_BackBorad = new DBlurEffectWidget(this);
    m_BackBorad->setFixedSize(this->size());
    m_BackBorad->setMaskAlpha(255);

    m_BackGround = new DBlurEffectWidget(this);
    m_BackGround->move(0,5);
    m_BackGround->setFixedSize(230, 64);
    m_BackGround->setVisible(true);

    m_BackGround->setBlurRectXRadius(8);
    m_BackGround->setBlurRectYRadius(8);

    m_FolderImage = new FolderImage(m_BackGround);
    m_FolderImage->move(10,15);


//    QPalette pe;
//    pe.setColor(QPalette::Background,QColor(00,00,00));
//    //pe.setColor(QPalette::Background,QColor(00,129,255));
//    m_BackGround->setPalette(pe);
//    m_BackGround->setMaskAlpha(7);

//    m_ImageBoard = new DBlurEffectWidget(m_BackGround);


//    m_imageLabel = new QLabel(m_ImageBoard);
//    m_imageLabel->setFixedSize(QSize(40,40));
//    m_imageLabel->move(0,0);
//    //m_imageLabel->setGeometry(QRect(10, 15, 40, 40));
//    m_imageLabel->setObjectName("imageLabel");
//    //m_imageLabel->size();
//    //QPixmap pixmap = getPixmap(m_imageLabel->size(), m_folder.imgPath);

////    bool convertFlag = getPixmap(imageLabel->size(), folder.imgPath, pixmap);
////    if (convertFlag)
////    {
//    QPixmap docIcon = UiUtil::getPixmap(m_imageLabel->size(), m_folder.imgPath);
//    //QPixmap raddocIcon = UiUtil::PixmapToRound(docIcon,20);
//        //m_imageLabel->setPixmap(raddocIcon);
//    m_imageLabel->setPixmap(docIcon);
////    }

    m_nameLabel = new DLabel(m_BackGround);
    //m_nameLabel->setGeometry(QRect(70, 10, 110, 21));
    m_nameLabel->setLineWidth(150);
    m_nameLabel->setObjectName("nameLabel");

    QFont labelFont;
    labelFont.setFamily("SourceHanSansSC");
    labelFont.setPointSize(14);
    m_nameLabel->setFont(labelFont);

    QPalette pe;
    pe.setColor(QPalette::WindowText,QColor(QRgb(0x001A2E)));
    m_nameLabel->setPalette(pe);


    bool isConverted = false;
    QFont labelFontForWidth;
    labelFontForWidth.setFamily("SourceHanSansSC");
    labelFontForWidth.setPointSize(11);
    //QString folderNameElided = UiUtil::getElidedText(m_nameLabel->font(), m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    //QString folderNameElided = UiUtil::getElidedText(m_nameLabel->font(), m_folder.folderName, m_nameLabel->width(), isConverted);
    QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey));
    m_nameLabel->setMouseTracking(false);
    m_nameLabel->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    m_lineEdit = new DLineEdit();
    //m_lineEdit->setGeometry(QRect(70, 10, 110, 21));
    m_lineEdit->setObjectName("nameEdit");

    m_lineEdit->setText(m_folder.folderName);
    //m_lineEdit->setVisible(false);

    m_stackedWidget = new QStackedWidget(m_BackGround);
    m_stackedWidget->setGeometry(QRect(70, 15, 110, 21));
    m_stackedWidget->setObjectName("stackedWidget");

    m_stackedWidget->addWidget(m_nameLabel);
    m_stackedWidget->addWidget(m_lineEdit);
    m_stackedWidget->setCurrentIndex(0);



    m_createTimeLabel = new QLabel(m_BackGround);
    m_createTimeLabel->setGeometry(QRect(70, 36, 110, 18));
    //m_createTimeLabel->setGeometry(QRect(70, 40, 110, 16));
    //m_createTimeLabel->setLineWidth(150);
    m_createTimeLabel->setObjectName("createTimeLabel");



    labelFont.setPointSize(9);
    m_createTimeLabel->setFont(labelFont);
    pe.setColor(QPalette::WindowText,QColor(QRgb(0x526A7F)));
    m_createTimeLabel->setPalette(pe);
    //m_createTimeLabel->setText(getCreateTimeLabel(m_folder.createTime));
    //m_createTimeLabel->setText(UiUtil::convertFolderDate(m_folder.createTime));
    m_createTimeLabel->setText(UiUtil::convertDateTime(m_folder.createTime));
    initConnection();
    m_FolderImage->loadPic(m_folder.imgPath);
}

void FolerWidgetItem::checkNameValid()
{
    //if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() < 64)) {
    if ((m_lineEdit->text().length() >= 0) && (m_lineEdit->text().length() < 64)) {
        //todo:更新数据库
        if(m_lineEdit->text().length() == 0)
        {
            m_folder.folderName = m_BakDefaultName;
        }
        else
        {
            m_folder.folderName = m_lineEdit->text();
        }

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
            bool isConverted = false;

            QFont labelFont;
            labelFont.setFamily("SourceHanSansSC");
            labelFont.setPointSize(11);

            //m_nameLabel->setText(UiUtil::getElidedText(m_nameLabel->font(), m_lineEdit->text(), m_nameLabel->width(), isConverted));

            //m_nameLabel->setText(UiUtil::getHtmlText(UiUtil::getElidedText(labelFont, m_lineEdit->text(), FOLDER_MAX_WIDTH, isConverted), 14, m_searchKey));
            m_nameLabel->setText(UiUtil::getHtmlText(UiUtil::getElidedText(labelFont, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted), 14, m_searchKey));

            //m_nameLabel->setText(UiUtil::getHtmlText(UiUtil::getElidedText(m_nameLabel->font(), m_lineEdit->text(), FOLDER_MAX_WIDTH, isConverted), 14, m_searchKey));
            m_stackedWidget->setCurrentIndex(0);
//            m_nameLabel->setVisible(true);
//            m_lineEdit->setVisible(false);
            m_BakLineContent.clear();
            m_BakDefaultName.clear();
        }
        m_createTimeLabel->setVisible(true);
    } else {
        //警告用户输入不能为空
//        m_folder.folderName = m_BakDefaultName;
//        if (m_folderCtr->checkFolderNameExist(m_folder))
//        {
//            m_lineEdit->setAlert(true);
//            m_lineEdit->showAlertMessage("目录名重复！");
//        }
//        else {
//            if(!m_folderCtr->updateFolder(m_folder))
//            {
//                m_lineEdit->setAlert(true);
//                m_lineEdit->showAlertMessage("修改目录名失败");

//            }

//            bool isConverted = false;

//            QFont labelFont;
//            labelFont.setFamily("SourceHanSansSC");
//            labelFont.setPointSize(11);
//            m_nameLabel->setText(UiUtil::getHtmlText(UiUtil::getElidedText(labelFont, m_BakLineContent, FOLDER_MAX_WIDTH, isConverted), 14, m_searchKey));
//            //m_lineEdit->setAlert(true);
//            //m_lineEdit->showAlertMessage("输入字符长度必须在0-64位之间");
//            m_stackedWidget->setCurrentIndex(0);
//            m_BakLineContent.clear();
//            m_BakDefaultName.clear();
//        }
    }
}

void FolerWidgetItem::checkNameLenth()
{
    if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() < 64))
    {
        m_BakLineContent.clear();
        m_BakLineContent = m_lineEdit->text();
    }

    if(m_lineEdit->text().length() >= 64)
    {
        qDebug()<<"m_lineEdit->text().length():"<<m_lineEdit->text().length();
        //m_lineEdit->setAlert(true);
        m_lineEdit->showAlertMessage("输入字符长度必须在0-64位之间");
        m_lineEdit->setText(m_BakLineContent);
    }
}

