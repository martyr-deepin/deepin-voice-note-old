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
#include <DApplicationHelper>

#include "intancer.h"

//FolerWidgetItem::FolerWidgetItem()
FolerWidgetItem::FolerWidgetItem(FOLDER folder, FolderController *folderCtr, QString searchKey)
{
    this->m_folder = folder;
    this->m_folderCtr = folderCtr;
    this->m_searchKey = searchKey;
    m_clicked = false;
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

    m_nameLabel->setVisible(false);
    m_lineEdit->setVisible(true);
//    m_stackedWidget->setCurrentIndex(1);

    //Update DlineEidt没有这个接口了
    //m_lineEdit->setText(m_nameLabel->text());
    //m_lineEdit->lineEdit()->setCursorPosition(m_lineEdit->text().size());
    m_lineEdit->lineEdit()->setFocus();
    m_lineEdit->lineEdit()->selectAll();
    m_lineEdit->setToEdited(true);
    //m_lineEdit->setFocus(Qt::OtherFocusReason);

    m_createTimeLabel->setVisible(false);
    m_BakDefaultName = m_lineEdit->text();
}

void FolerWidgetItem::changeToClickMode()
{
    if((nullptr != m_nameLabel) && (nullptr != m_createTimeLabel))
    {

        m_clicked = true;
         m_BackGround->setVisible(false);

        //m_BackGround->setVisible(false);

        DPalette pe = DApplicationHelper::instance()->palette(m_nameLabel);
        //pe.setBrush(DPalette::WindowText, pe.color(DPalette::TextLively));
        pe.setBrush(DPalette::WindowText, QColor(Qt::white));
        m_nameLabel->setPalette(pe);


        DPalette pc = DApplicationHelper::instance()->palette(m_createTimeLabel);
        //pc.setBrush(DPalette::WindowText, pc.color(DPalette::TextLively));
        pc.setBrush(DPalette::WindowText, QColor(Qt::white));
        m_createTimeLabel->setPalette(pc);


        bool isConverted = false;
        QFont labelFontForWidth;
        labelFontForWidth.setFamily("SourceHanSansSC");
        labelFontForWidth.setPointSize(11);
        QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
        //m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey, WHITE));
        m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey, WHITE));
        //m_BackGround->setVisible(false);
    }
}

void FolerWidgetItem::changeToUnClickMode()
{
    if((nullptr != m_nameLabel) && (nullptr != m_createTimeLabel))
    {
        if(m_clicked)
        {
            m_BackGround->setVisible(true);
            m_clicked = false;
        }

        DPalette pe;
        //DPalette pe = DApplicationHelper::instance()->palette(m_createTimeLabel);
        //pe.setBrush(DPalette::WindowText, pe.color(DPalette::TextTips));
        pe.setColor(DPalette::WindowText,pe.color(DPalette::WindowText));
        m_createTimeLabel->setPalette(pe);

        DPalette pc;
        //DPalette pc = DApplicationHelper::instance()->palette(m_nameLabel);
        //pc.setBrush(DPalette::WindowText, pc.color(DPalette::WindowText));
        pc.setColor(DPalette::WindowText,pc.color(DPalette::TextTips));
        m_nameLabel->setPalette(pc);
        //m_BackGround->setVisible(true);

        bool isConverted = false;
        QFont labelFontForWidth;
        labelFontForWidth.setFamily("SourceHanSansSC");
        labelFontForWidth.setPointSize(11);
        QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
        m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey, BLUE));
    }
}

void FolerWidgetItem::Init()
{
    this->setFixedSize(QSize(230, 64));


//    DPalette pa = DApplicationHelper::instance()->palette(this);
//    pa.setBrush(DPalette::Background, pa.color(DPalette::ItemBackground));
//    this->setPalette(pa);

    //this->setFixedSize(QSize(250, 74));
    this->setBlurEnabled(false);
    this->setBlurRectXRadius(8);
    this->setBlurRectYRadius(8);


//    m_BackBorad = new DBlurEffectWidget(this);
//    m_BackBorad->setFixedSize(this->size());
//    m_BackBorad->setMaskAlpha(0);
//    m_BackBorad->setVisible(true);


    m_BackGround = new DFrame(this);
    m_BackGround->move(0,0);
    m_BackGround->setFixedSize(230, 64);
    m_BackGround->setVisible(true);
//    m_BackGround->setBlurRectXRadius(8);
//    m_BackGround->setBlurRectYRadius(8);


    DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
    //pb.setBrush(DPalette::Base, QColor(255,255,255,13));
    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_BackGround->setPalette(pb);




    m_FolderImage = new FolderImage(this);
    //m_FolderImage = new FolderImage(m_BackGround);
    m_FolderImage->move(6,12);

    m_nameLabel = new DLabel(this);
    //m_nameLabel = new DLabel(m_BackGround);
    m_nameLabel->setFixedSize(QSize(110,21));
    m_nameLabel->move(53,13);
    //m_nameLabel->setGeometry(QRect(70, 10, 110, 21));
    m_nameLabel->setLineWidth(150);
    m_nameLabel->setObjectName("nameLabel");

    QFont labelFont;
    labelFont.setFamily("SourceHanSansSC");
    labelFont.setPointSize(14);
    m_nameLabel->setFont(labelFont);

    DPalette pe;
    pe.setColor(DPalette::WindowText,pe.color(DPalette::TextTips));
    m_nameLabel->setPalette(pe);


    bool isConverted = false;
    QFont labelFontForWidth;
    labelFontForWidth.setFamily("SourceHanSansSC");
    labelFontForWidth.setPointSize(11);
    //QString folderNameElided = UiUtil::getElidedText(m_nameLabel->font(), m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    //QString folderNameElided = UiUtil::getElidedText(m_nameLabel->font(), m_folder.folderName, m_nameLabel->width(), isConverted);
    QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey, BLUE));
    m_nameLabel->setMouseTracking(false);
    m_nameLabel->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    m_lineEdit = new RenameEdit(this);
    //m_lineEdit = new RenameEdit(m_BackGround);
    m_lineEdit->setFixedSize(QSize(160,36));
    m_lineEdit->move(57,(this->height() - m_lineEdit->height())/2);
    //m_lineEdit->move(57,(m_BackGround->height() - m_lineEdit->height())/2);
    //m_lineEdit->setGeometry(QRect(70, 10, 110, 21));
    m_lineEdit->setObjectName("nameEdit");


    DPalette pa = DApplicationHelper::instance()->palette(m_lineEdit->lineEdit());
    pa.setBrush(DPalette::Text, pa.color(DPalette::Base));
//    pa.setBrush(DPalette::Button, QColor(0,0,0,20));
//    pa.setBrush(DPalette::Base, QColor(0,0,0,20));
    pa.setBrush(DPalette::Button, pa.color(DPalette::FrameBorder));
    pa.setBrush(DPalette::Base, pa.color(DPalette::FrameBorder));
    //pa.setBrush(DPalette::Highlight, QColor(255,255,0,255));
    pa.setBrush(DPalette::Highlight, pa.color(DPalette::FrameBorder));
    m_lineEdit->lineEdit()->setPalette(pa);

//    QLineEdit * lineed = new QLineEdit(this);
//    lineed->setFixedSize(QSize(200,50));
//    lineed->move(0,0);
//    QPalette Palette = lineed->palette();
//   Palette.setBrush(QPalette::Text,QBrush(QColor(255,255,255,255)));//绿色
//   Palette.setBrush(QPalette::Button,QBrush(QColor(0,0,0,20)));//绿色
//       lineed->setPalette(Palette);//label2刷成绿色



    m_lineEdit->setClearButtonEnabled(false);
    m_lineEdit->setText(m_folder.folderName);
    m_lineEdit->setVisible(false);

//    m_stackedWidget = new QStackedWidget(m_BackGround);
//    m_stackedWidget->setFixedSize(QSize(110,21));
//    m_stackedWidget->move(53,13);
//    m_stackedWidget->setObjectName("stackedWidget");

//    m_stackedWidget->addWidget(m_nameLabel);
//    m_stackedWidget->addWidget(m_lineEdit);
//    m_stackedWidget->setCurrentIndex(0);


    m_createTimeLabel = new QLabel(this);
    //m_createTimeLabel = new QLabel(m_BackGround);
    m_createTimeLabel->setFixedSize(QSize(110,18));
    m_createTimeLabel->move(53,32);
    //m_createTimeLabel->setGeometry(QRect(53, 36, 110, 18));
    //m_createTimeLabel->setGeometry(QRect(70, 40, 110, 16));
    //m_createTimeLabel->setLineWidth(150);
    m_createTimeLabel->setObjectName("createTimeLabel");



    labelFont.setPointSize(9);
    m_createTimeLabel->setFont(labelFont);
    //pe.setColor(QPalette::WindowText,QColor(QRgb(0x526A7F)));
    //DPalette pe;
    //DPalette pe = DApplicationHelper::instance()->palette(m_createTimeLabel);
    //pe.setBrush(DPalette::WindowText, pe.color(DPalette::TextTips));
    DPalette pc;
    pc.setColor(DPalette::WindowText,pc.color(DPalette::WindowText));
    m_createTimeLabel->setPalette(pc);
    //m_createTimeLabel->setText(getCreateTimeLabel(m_folder.createTime));
    //m_createTimeLabel->setText(UiUtil::convertFolderDate(m_folder.createTime));
    m_createTimeLabel->setText(UiUtil::convertDateTime(m_folder.createTime));
    initConnection();
    m_FolderImage->loadPic(m_folder.imgPath);
}

void FolerWidgetItem::checkNameValid()
{
    //if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() < 64)) {
    if ((m_lineEdit->text().length() >= 0) && (m_lineEdit->text().length() <= 64)) {
        //todo:更新数据库
        if(m_lineEdit->text().length() == 0)
        {
            m_folder.folderName = m_BakDefaultName;
            m_lineEdit->setText(m_BakDefaultName);
        }
        else
        {
            m_folder.folderName = m_lineEdit->text();
        }

        if (m_folderCtr->checkFolderNameExist(m_folder))
        {
            m_lineEdit->setAlert(true);
            m_lineEdit->showAlertMessage("目录名重复！");
            m_folder.folderName = m_BakDefaultName;
            m_lineEdit->setText(m_BakDefaultName);
            //Intancer::get_Intancer()->setRenameRepeatFlag(false);
        }
//        else
//        {
            if(!m_folderCtr->updateFolder(m_folder))
            {
                m_lineEdit->setAlert(true);
                m_lineEdit->showAlertMessage("修改目录名失败");

            }
            bool isConverted = false;

            QFont labelFont;
            labelFont.setFamily("SourceHanSansSC");
            labelFont.setPointSize(11);

            m_nameLabel->setText(UiUtil::getHtmlText(UiUtil::getElidedText(labelFont, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted), 14, m_searchKey, BLUE));

            m_nameLabel->setVisible(true);
            m_lineEdit->setVisible(false);
            m_createTimeLabel->setVisible(true);
            m_BakLineContent.clear();
            m_BakDefaultName.clear();
            Intancer::get_Intancer()->setRenameRepeatFlag(false);

//        }
        //m_createTimeLabel->setVisible(true);
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
    if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() <= 64))
    {
        m_BakLineContent.clear();
        m_BakLineContent = m_lineEdit->text();
    }

    if(m_lineEdit->text().length() > 64)
    {
        qDebug()<<"m_lineEdit->text().length():"<<m_lineEdit->text().length();
        //m_lineEdit->setAlert(true);
        m_lineEdit->showAlertMessage("输入字符长度必须在0-64位之间");
        m_lineEdit->setText(m_BakLineContent);
    }
}

void FolerWidgetItem::tryToFouceout()
{
    m_lineEdit->tryToFouceout();
}
