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
#include <DFontSizeManager>

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
    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &FolerWidgetItem::changeTheme);
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
        QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);
        QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
        m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey, WHITE));
        //m_nameLabel->setText(folderNameElided);
        DFontSizeManager::instance()->bind(m_nameLabel,DFontSizeManager::T6);
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
        QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);
        QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
        m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey, BLUE));
        DFontSizeManager::instance()->bind(m_nameLabel,DFontSizeManager::T6);
    }
}

void FolerWidgetItem::Init()
{
    this->setFixedSize(QSize(230, 64));

    this->setBlurEnabled(false);
    this->setBlurRectXRadius(8);
    this->setBlurRectYRadius(8);


    m_BackGround = new DFrame(this);
    m_BackGround->move(0,0);
    m_BackGround->setFixedSize(230, 64);
    m_BackGround->setVisible(true);


    DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_BackGround->setPalette(pb);




    m_FolderImage = new FolderImage(this);
    m_FolderImage->move(6,12);

    m_nameLabel = new DLabel(this);
    m_nameLabel->setFixedSize(QSize(110,21));
    m_nameLabel->move(53,13);
    m_nameLabel->setLineWidth(150);
    m_nameLabel->setObjectName("nameLabel");


    //QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T6);
    //m_nameLabel->setFont(labelFont);
    DFontSizeManager::instance()->bind(m_nameLabel,DFontSizeManager::T6);

    DPalette pe;
    pe.setColor(DPalette::WindowText,pe.color(DPalette::TextTips));
    m_nameLabel->setPalette(pe);


    bool isConverted = false;
    QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);
    QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    m_nameLabel->setText(UiUtil::getHtmlText(folderNameElided, 14, m_searchKey, BLUE));
    m_nameLabel->setMouseTracking(false);
    m_nameLabel->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    m_lineEdit = new RenameEdit(this);
    m_lineEdit->setFixedSize(QSize(160,36));
    m_lineEdit->move(57,(this->height() - m_lineEdit->height())/2);
    m_lineEdit->setObjectName("nameEdit");


    DPalette pa = DApplicationHelper::instance()->palette(m_lineEdit->lineEdit());
    pa.setBrush(DPalette::Text, pa.color(DPalette::Base));
    pa.setBrush(DPalette::Button, pa.color(DPalette::FrameBorder));
    pa.setBrush(DPalette::Base, pa.color(DPalette::FrameBorder));
    m_lineEdit->lineEdit()->setPalette(pa);
    m_lineEdit->setClearButtonEnabled(false);
    m_lineEdit->setText(m_folder.folderName);
    m_lineEdit->setVisible(false);


    m_createTimeLabel = new QLabel(this);
    m_createTimeLabel->setFixedSize(QSize(110,18));
    m_createTimeLabel->move(53,32);
    m_createTimeLabel->setObjectName("createTimeLabel");



//    QFont createTimeFont = DFontSizeManager::instance()->get(DFontSizeManager::T8);
//    m_createTimeLabel->setFont(createTimeFont);
    DFontSizeManager::instance()->bind(m_createTimeLabel,DFontSizeManager::T8);

    DPalette pc;
    pc.setColor(DPalette::WindowText,pc.color(DPalette::WindowText));
    m_createTimeLabel->setPalette(pc);
    m_createTimeLabel->setText(UiUtil::convertDateTime(m_folder.createTime));
    initConnection();

    QPixmap pix(m_folder.imgPath);
    if(pix.isNull())
    {
        m_folder.imgPath = UiUtil::getDefaultAvatarByRand();
    }

    m_FolderImage->loadPic(m_folder.imgPath);
}

void FolerWidgetItem::copy(FolerWidgetItem *pSourceFolder)
{
//    DLabel *m_nameLabel;
//    DLabel *m_createTimeLabel;
//    m_folder;
//    m_FolderImage;
//    m_BakLineContent;
//    m_BakDefaultName;
//    m_clicked;
//    m_searchKey;

//    pSourceFolder->
}

QString FolerWidgetItem::getSearchText()
{
    return m_searchKey;
}

void FolerWidgetItem::checkNameValid()
{
    //if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() < 64)) {
    if ((m_lineEdit->text().length() >= 0) && (m_lineEdit->text().length() <= 64)) {
        //todo:更新数据库
        qDebug()<<"m_lineEdit->text().length():"<<m_lineEdit->text().length();
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
            if(!m_folderCtr->updateFolderName(m_folder))
            {
                m_lineEdit->setAlert(true);
                m_lineEdit->showAlertMessage("修改目录名失败");

            }
            bool isConverted = false;


            QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T6);
            m_nameLabel->setText(UiUtil::getHtmlText(UiUtil::getElidedText(labelFont, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted), 14, m_searchKey, BLUE));
            DFontSizeManager::instance()->bind(m_nameLabel,DFontSizeManager::T6);
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

void FolerWidgetItem::changeTheme()
{
    DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
    //pb.setBrush(DPalette::Base, QColor(255,255,255,13));
    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_BackGround->setPalette(pb);
}
