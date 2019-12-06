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
    connect(m_lineEdit, &RenameEdit::sigCancelRename, this, &FolerWidgetItem::cancleRename);
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
    if ((nullptr != m_nameLabel) && (nullptr != m_createTimeLabel)) {

        m_clicked = true;
        m_BackGround->setVisible(false);
        m_BackGroundHoverd->setVisible(false);
        //m_BackGround->setVisible(false);

//        DPalette pe = DApplicationHelper::instance()->palette(m_nameLabel);
//        //pe.setBrush(DPalette::WindowText, pe.color(DPalette::TextLively));
//        pe.setBrush(DPalette::WindowText, QColor(Qt::white));
//        m_nameLabel->setPalette(pe);
        m_nameLabel->setForegroundRole(DPalette::HighlightedText);


//        DPalette pc = DApplicationHelper::instance()->palette(m_createTimeLabel);
//        //pc.setBrush(DPalette::WindowText, pc.color(DPalette::TextLively));
//        pc.setBrush(DPalette::WindowText, QColor(Qt::white));
//        m_createTimeLabel->setPalette(pc);
        m_createTimeLabel->setForegroundRole(DPalette::HighlightedText);

        bool isConverted = false;
        QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);

        QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
        this->setLabelText(folderNameElided);

        DFontSizeManager::instance()->bind(m_nameLabel, DFontSizeManager::T6);
        //m_BackGround->setVisible(false);
    }
}

void FolerWidgetItem::changeToUnClickMode()
{
    if ((nullptr != m_nameLabel) && (nullptr != m_createTimeLabel)) {
        if (m_clicked) {
            m_BackGround->setVisible(true);
//            DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
//            pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
//            m_BackGround->setPalette(pb);
//            m_BackGround->setBackgroundRole(DPalette::ItemBackground);
            m_clicked = false;
        }

//        DPalette pe;
//        //DPalette pe = DApplicationHelper::instance()->palette(m_createTimeLabel);
//        //pe.setBrush(DPalette::WindowText, pe.color(DPalette::TextTips));
//        pe.setColor(DPalette::WindowText,pe.color(DPalette::WindowText));
//        m_createTimeLabel->setPalette(pe);
        m_createTimeLabel->setForegroundRole(DPalette::TextTips);

//        DPalette pc;
//        //DPalette pc = DApplicationHelper::instance()->palette(m_nameLabel);
//        //pc.setBrush(DPalette::WindowText, pc.color(DPalette::WindowText));
//        pc.setColor(DPalette::WindowText,pc.color(DPalette::TextTips));
//        m_nameLabel->setPalette(pc);
//        //m_BackGround->setVisible(true);
        m_nameLabel->setForegroundRole(DPalette::TextTitle);

        bool isConverted = false;
        QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);

        QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
        this->setLabelText(folderNameElided);

        DFontSizeManager::instance()->bind(m_nameLabel, DFontSizeManager::T6);
    }
}

void FolerWidgetItem::Init()
{
    this->setFixedSize(QSize(230, 64));
//    this->setBlurEnabled(false);
//    this->setBlurRectXRadius(8);
//    this->setBlurRectYRadius(8);


    m_BackGround = new DFrame(this);
    m_BackGround->move(0, 0);
    m_BackGround->setFixedSize(230, 64);
    m_BackGround->setVisible(true);


//    DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
//    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
//    m_BackGround->setPalette(pb);
    m_BackGround->setBackgroundRole(DPalette::ItemBackground);

    m_BackGroundHoverd = new DFrame(this);
    m_BackGroundHoverd->move(0, 0);
    m_BackGroundHoverd->setFixedSize(230, 64);
    m_BackGroundHoverd->setVisible(false);
    m_BackGroundHoverd->setBackgroundRole(DPalette::Light);

    m_FolderImage = new FolderImage(this);
    m_FolderImage->move(6, 12);

    m_nameLabel = new DLabel(this);
    m_nameLabel->setFixedSize(QSize(110, 21));
    m_nameLabel->move(53, 13);
    m_nameLabel->setLineWidth(150);
    m_nameLabel->setObjectName("nameLabel");


    //QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T6);
    //m_nameLabel->setFont(labelFont);
    DFontSizeManager::instance()->bind(m_nameLabel, DFontSizeManager::T6);

//    DPalette pe;
//    pe.setColor(DPalette::WindowText, pe.color(DPalette::TextTips));
//    m_nameLabel->setPalette(pe);
    m_nameLabel->setForegroundRole(DPalette::TextTitle);

    bool isConverted = false;
    QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);

    QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    this->setLabelText(folderNameElided);

    m_nameLabel->setMouseTracking(false);
    m_nameLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    m_lineEdit = new RenameEdit(this);
    //m_lineEdit->resize(QSize(160,36));
    m_lineEdit->setFixedSize(QSize(160, 36));
    m_lineEdit->move(57, (this->height() - m_lineEdit->height()) / 2);
    m_lineEdit->setObjectName("nameEdit");


    DPalette pa = DApplicationHelper::instance()->palette(m_lineEdit->lineEdit());
    pa.setBrush(DPalette::Text, pa.color(DPalette::Base));
    pa.setBrush(DPalette::Button, pa.color(DPalette::FrameBorder));
    pa.setBrush(DPalette::Base, pa.color(DPalette::FrameBorder));
    m_lineEdit->lineEdit()->setPalette(pa);
    m_lineEdit->setClearButtonEnabled(false);
    m_lineEdit->setText(m_folder.folderName);
    m_lineEdit->setVisible(false);


    m_createTimeLabel = new DLabel(this);
    m_createTimeLabel->setFixedSize(QSize(110, 18));
    m_createTimeLabel->move(53, 32);
    m_createTimeLabel->setObjectName("createTimeLabel");



//    QFont createTimeFont = DFontSizeManager::instance()->get(DFontSizeManager::T8);
//    m_createTimeLabel->setFont(createTimeFont);
    DFontSizeManager::instance()->bind(m_createTimeLabel, DFontSizeManager::T8);

//    DPalette pc;
//    pc.setColor(DPalette::WindowText,pc.color(DPalette::WindowText));
//    m_createTimeLabel->setPalette(pc);
    m_createTimeLabel->setForegroundRole(DPalette::TextTips);
    m_createTimeLabel->setText(UiUtil::convertDateTime(m_folder.createTime));
    initConnection();

    QPixmap pix(m_folder.imgPath);
    if (pix.isNull()) {
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

void FolerWidgetItem::cancleRename()
{
    m_folder.folderName = m_BakDefaultName;
    m_lineEdit->setText(m_BakDefaultName);

    bool isConverted = false;
    QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);

    QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
    this->setLabelText(folderNameElided);

    DFontSizeManager::instance()->bind(m_nameLabel, DFontSizeManager::T6);
    m_nameLabel->setVisible(true);
    m_lineEdit->setVisible(false);
    m_createTimeLabel->setVisible(true);
    m_BakLineContent.clear();
    m_BakDefaultName.clear();
    Intancer::get_Intancer()->setRenameRepeatFlag(false);
}

void FolerWidgetItem::checkNameValid()
{
    //if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() < 64)) {
    if ((m_lineEdit->text().length() >= 0) && (m_lineEdit->text().length() <= 64)) {
        //todo:更新数据库
        qDebug() << "m_lineEdit->text().length():" << m_lineEdit->text().length();
        if (m_lineEdit->text().length() == 0) {
            m_folder.folderName = m_BakDefaultName;
            m_lineEdit->setText(m_BakDefaultName);
        } else {
            m_folder.folderName = m_lineEdit->text();
        }

        if (m_folderCtr->checkFolderNameExist(m_folder)) {
            m_lineEdit->setAlert(true);
            m_lineEdit->showAlertMessage("目录名重复！");
            m_folder.folderName = m_BakDefaultName;
            m_lineEdit->setText(m_BakDefaultName);
            //Intancer::get_Intancer()->setRenameRepeatFlag(false);
        }
//        else
//        {
        if (!m_folderCtr->updateFolderName(m_folder)) {
            m_lineEdit->setAlert(true);
            m_lineEdit->showAlertMessage("修改目录名失败");

        }

        bool isConverted = false;
        QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T6);

        QString folderNameElided = UiUtil::getElidedText(labelFontForWidth, m_folder.folderName, FOLDER_MAX_WIDTH, isConverted);
        this->setLabelText(folderNameElided);

        DFontSizeManager::instance()->bind(m_nameLabel, DFontSizeManager::T6);
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
    if ((m_lineEdit->text().length() > 0) && (m_lineEdit->text().length() <= 64)) {
        m_BakLineContent.clear();
        m_BakLineContent = m_lineEdit->text();
    }

    if (m_lineEdit->text().length() > 64) {
        qDebug() << "m_lineEdit->text().length():" << m_lineEdit->text().length();
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
    m_BackGround->setBackgroundRole(DPalette::ItemBackground);
    m_BackGroundHoverd->setBackgroundRole(DPalette::Light);
//    DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
//    //pb.setBrush(DPalette::Base, QColor(255,255,255,13));
//    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
//    m_BackGround->setPalette(pb);

    if (!m_clicked) {
        DPalette pc;
        pc.setColor(DPalette::WindowText, pc.color(DPalette::WindowText));
        m_createTimeLabel->setPalette(pc);
    }
}

//liuyang 3550 3547 3528
void FolerWidgetItem::updateTimeLable(const QDateTime &time)
{
    if (m_createTimeLabel != nullptr) {
        m_folder.createTime = time;
        m_createTimeLabel->setText(UiUtil::convertDateTime(m_folder.createTime));
    }
}
//liuyang 3550 3547 3528

void FolerWidgetItem::setLabelText(const QString text)
{
    QString textToSet = "";
    QString searchingKeywords = Intancer::get_Intancer()->getSearchKeywords();
    qDebug() << "searchingKeywords: " << searchingKeywords;

    if (!searchingKeywords.isEmpty()) {
        RICH_TEXT_COLOR color = BLUE;
        if (this->m_clicked) {
            color = WHITE;
        }
        else {
            color = BLUE;
        }

        textToSet = UiUtil::getHtmlText(text, 12, searchingKeywords, color);
        this->m_nameLabel->setTextFormat(Qt::RichText);
    }
    else {
        textToSet = text;
        this->m_nameLabel->setTextFormat(Qt::PlainText);
    }

    qDebug() << "textToSet: " << textToSet;
    this->m_nameLabel->setText(textToSet);
}

//liuyang 3794
void FolerWidgetItem::leaveEvent(QEvent *event)
{
//    DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
//    //pb.setBrush(DPalette::Base, pb.color(DPalette::FrameBorder));
//    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
//    m_BackGround->setPalette(pb);

//    m_BackGround->setBackgroundRole(DPalette::ItemBackground);
    if(m_clicked)
    {
        m_BackGround->setVisible(false);
        m_BackGroundHoverd->setVisible(false);
    }
    else
    {
        m_BackGround->setVisible(true);
        m_BackGroundHoverd->setVisible(false);
    }

    return QWidget::leaveEvent(event);
}
void FolerWidgetItem::enterEvent(QEvent *event)
{
//    DPalette pb = DApplicationHelper::instance()->palette(m_BackGround);
//    pb.setBrush(DPalette::Base, pb.color(DPalette::Light));
//    m_BackGround->setPalette(pb);
//    m_BackGround->setBackgroundRole(DPalette::Light);

    if(m_clicked)
    {
        m_BackGround->setVisible(false);
        m_BackGroundHoverd->setVisible(false);
    }
    else
    {
        m_BackGround->setVisible(false);
        m_BackGroundHoverd->setVisible(true);
    }
    return QWidget::enterEvent(event);
}
//liuyang 3794
