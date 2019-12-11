#include "textnoteitem.h"
#include "uiutil.h"
#include "intancer.h"
#include <DPalette>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <DApplicationHelper>
#include <DFontSizeManager>

TextNoteItem::TextNoteItem(const bool isAddByButton, NOTE textNote, NoteController *noteCtr, QString searchKey, QWidget *parent)
    : DWidget(parent), m_isTextConverted(false)
{
    m_textEdit = nullptr;
    this->m_textNote = textNote;
    this->m_noteCtr = noteCtr;
    m_searchKey = searchKey;
    m_menuBtnState = 0;
    m_isEdited = false;
    m_mouseIsIn = false;

    m_bakContent = textNote.contentText;//liuyang 3550 3547 3528

    initUI(isAddByButton);
    initConnection();
}

TextNoteItem::~TextNoteItem()
{

}

void TextNoteItem::init()
{
    if(nullptr != m_timeLabel)
    {
        QPalette pe;
        //pe.setColor(QPalette::WindowText,QColor(QRgb(0x001A2E)));
        pe.setColor(QPalette::WindowText,QColor(00,26,46));
        m_timeLabel->setPalette(pe);

        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        m_timeLabel->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.5);
    }
}

int TextNoteItem::getId()
{
    return m_textNote.id;
}

NOTE_TYPE TextNoteItem::getType()
{
    return m_textNote.noteType;
}

//liuyang 3550 3547 3528
NOTE TextNoteItem::getTextNote()
{
    return  m_textNote;
}
//liuyang 3550 3547 3528

QPoint TextNoteItem::remapToGlobalMenbtn(QPoint GlobalPoint)
{
    QPoint pGlobal = m_menuBtn->mapToGlobal(GlobalPoint);
    return pGlobal;
}

void TextNoteItem::initUI(const bool isAddByButton)
{

    //this->setFixedHeight(150);
    //this->setFixedHeight(140);
    this->setFixedHeight(TEXTNOTE_HEIGHT);
    //this->resize(500, this->height());
    m_timeLabel = new DLabel(this);

//    QFont timeLabelFont;
//    timeLabelFont.setFamily("PingFangSC-Regular");
//    timeLabelFont.setPointSize(8);
//    QFont timeLabelFont = DFontSizeManager::instance()->get(DFontSizeManager::T9);
//    m_timeLabel->setFont(timeLabelFont);
    DFontSizeManager::instance()->bind(m_timeLabel,DFontSizeManager::T9);
    m_timeLabel->setFixedHeight(16);

    m_bgWidget = new DTextEdit(this);
    m_bgWidget->setReadOnly(true);
    //m_bgWidget = new DFrame(this);
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    pb.setBrush(DPalette::Button, pb.color(DPalette::ItemBackground));
    //pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_bgWidget->setPalette(pb);

    DStyle::setFocusRectVisible(m_bgWidget,false);

    //m_bgWidget->setFixedHeight(105);
    m_bgWidget->setFixedHeight(140);
//    QSizePolicy sp1 = m_bgWidget->sizePolicy();
//    sp.setVerticalPolicy(QSizePolicy::Fixed);
//    m_bgWidget->setSizePolicy(sp1);
    m_itemLayout = new QVBoxLayout();
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    m_itemLayout->addSpacing(6);
    m_itemLayout->addWidget(m_timeLabel);
    m_itemLayout->addSpacing(2);
    m_itemLayout->addWidget(m_bgWidget);
    m_itemLayout->addSpacing(6);
    m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);
    this->setLayout(m_itemLayout);
//    QSizePolicy sp = m_bgWidget->sizePolicy();
//    sp.setHorizontalStretch(1);
//    m_bgWidget->setSizePolicy(sp);

    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setText("   " + UiUtil::convertDateTime(m_textNote.createTime));

    m_bgWidget->setObjectName("widget");
    m_hBoxLayout = new QHBoxLayout(m_bgWidget);
    m_hBoxLayout->setContentsMargins(14, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");

    m_textEdit = new TextNoteEdit(m_textNote, m_bgWidget, m_noteCtr);

    //m_textEdit->setBgTextEdit(m_bgWidget);

    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_textEdit->toPlainText():"), m_textEdit->toPlainText());

    if (!isAddByButton) {
        m_textEdit->setTextNote(m_textNote, m_searchKey);
    }

    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_textEdit->toPlainText():"), m_textEdit->toPlainText());

//    QFont labelFont;
//    labelFont.setFamily("PingFangSC-Regular");
//    labelFont.setPointSize(9);
//    QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T8);
//    m_textEdit->setFont(labelFont);
    DFontSizeManager::instance()->bind(m_textEdit,DFontSizeManager::T8);
    //m_textEdit->setFixedHeight(133);
    m_textEdit->setFixedHeight(120);
    m_textEdit->document()->setDocumentMargin(1);

    m_hBoxLayout->addSpacing(3);
    m_hBoxLayout->addWidget(m_textEdit);
    m_hBoxLayout->addSpacing(5);

    DStyle::setFocusRectVisible(m_textEdit,false);
    DPalette pl = DApplicationHelper::instance()->palette(m_textEdit);
    pl.setBrush(DPalette::Button, QColor(0,0,0,0));
    m_textEdit->setPalette(pl);

//    QFont labelFontForWidth;
//    labelFontForWidth.setFamily("PingFangSC-Regular");
//    labelFontForWidth.setPointSize(10);
    QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T8);
    //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, (m_textEdit->width() + 26) * 5, m_isTextConverted);
    //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, 536 * 5, m_isTextConverted);
    //qDebug() << "m_isTextConverted: " << m_isTextConverted;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_isTextConverted:"), QString::number(m_isTextConverted));
    if (m_isTextConverted)
    {
        m_textEdit->setReadOnly(true);
        m_isEdited = true;
    }

    m_textEdit->setFrameShape(QFrame::NoFrame);
    m_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_MenuBtnBackground = new DWidget(m_bgWidget);
    //m_MenuBtnBackground->setFixedSize(QSize(40,m_bgWidget->height()));
    m_MenuBtnBackground->setFixedSize(QSize(48,m_bgWidget->height()));




    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        m_menuBtn = new MyRecodeButtons(
                    ":/image/icon/normal/more_normal.svg",
                    ":/image/icon/press/more_press.svg",
                    ":/image/icon/hover/more_hover.svg",
                    ":/image/icon/disabled/more_disabled.svg",
                    ":/image/icon/focus/more_focus.svg",
                    QSize(44,44),
                    m_MenuBtnBackground);
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        m_menuBtn = new MyRecodeButtons(
                    ":/image/icon_dark/normal/more_normal_dark.svg",
                    ":/image/icon_dark/press/more_press_dark.svg",
                    ":/image/icon_dark/hover/more_hover_dark.svg",
                    ":/image/icon_dark/disabled/more_disabled_dark.svg",
                    ":/image/icon_dark/focus/more_focus_dark.svg",
                    QSize(44,44),
                    m_MenuBtnBackground);
    }

//   QPalette pa; //= DApplicationHelper::instance()->palette(m_menuBtn);
//   pa.setBrush(DPalette::Highlight, pa.color(DPalette::Base));
//   m_menuBtn->setBtnPalette(pa);
    //m_menuBtn = new DImageButton(m_MenuBtnBackground);
    //m_menuBtn->setFixedSize(QSize(40, 40));
    //chengjinwei 2019 11 29 bug3790
    //m_menuBtn->move(0,13);
    m_menuBtn->move(6,13);
    //chengjinwei 2019 11 29 bug3790
    //m_menuBtn->setIcon(QIcon(":/image/icon/normal/more_normal.svg"));
    //m_menuBtn->setIconSize(QSize(20,20));
    //m_menuBtn->setIconSize(QSize(40,18));
    //m_menuBtn->setIconSize(QSize(10,18));
    m_menuBtn->setDisabled(true);

    if(themeType == DGuiApplicationHelper::LightType)
    {
        m_detailBtn = new MyRecodeButtons(
                    ":/image/icon/normal/detail-normal.svg",
                    ":/image/icon/press/detail-press.svg",
                    ":/image/icon/hover/detail-hover.svg",
                    "",
                    "",
                    QSize(44,44),
                    m_MenuBtnBackground
                );
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        m_detailBtn = new MyRecodeButtons(
                    ":/image/icon_dark/normal/detail-normal.svg",
                    ":/image/icon_dark/press/detail-press.svg",
                    ":/image/icon_dark/hover/detail-hover.svg",
                    "",
                    "",
                    QSize(44,44),
                    m_MenuBtnBackground
                );
    }

    m_detailBtn->setVisible(false);

    //chengjinwei 2019 11 29 bug3790
    m_detailBtn->move(6,m_MenuBtnBackground->height() - m_detailBtn->height() - 16);
    //chengjinwei 2019 11 29 bug3790

    m_hBoxLayout->addWidget(m_MenuBtnBackground);
    m_hBoxLayout->addSpacing(8);

    textAreaChanged();

//   QTextEdit *textEdit = new QTextEdit(this);
//   textEdit->setFixedSize(QSize(100,100));
//   textEdit->move(100,0);
}

void TextNoteItem::initConnection()
{
    connect(m_textEdit, &TextNoteEdit::clicked, this, &TextNoteItem::handleTextEditClicked);
    connect(m_textEdit, &TextNoteEdit::sigDelMyself, this, &TextNoteItem::tryToFouceout);
    connect(m_textEdit, &TextNoteEdit::SigTextEditGetFocus, this, &TextNoteItem::OnTextEditGetFocus); //Add bug 2587
    connect(m_textEdit, &TextNoteEdit::SigTextEditOutFocus, this, &TextNoteItem::OnTextEditOutFocus); //Add bug 2587
    connect(m_textEdit, &TextNoteEdit::sigDetailButtonChanged, this, &TextNoteItem::onDetailButtonChanged);

    //connect(m_textEdit, &TextNoteEdit::focusOutSignal, this, &TextNoteItem::handleTextEditFocusOutNotReadOly);
    //liuyang 3547
    connect(m_textEdit, &TextNoteEdit::sigTextChanged, this, &TextNoteItem::textEditChanged);
    connect(m_menuBtn, &QAbstractButton::pressed, this, &TextNoteItem::sig_menuBtnPressed);
    connect(m_menuBtn, &MyRecodeButtons::sigReleased, this, &TextNoteItem::handleMenuBtnClicked);
    //connect(m_menuBtn, &QAbstractButton::pressed, this, &TextNoteItem::handleMenuBtnClicked);
    connect(m_menuBtn, &MyRecodeButtons::sigReleased, this, &TextNoteItem::sig_menuBtnReleased);
    connect(m_menuBtn, &QAbstractButton::pressed, this, &TextNoteItem::buttonClicled);

    //connect(m_menuBtn, SIGNAL(pressed()), this, SIGNAL(buttonClicled()));

    connect(m_detailBtn, SIGNAL(clicked()), this, SLOT(OnToDetalPage()));

    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &TextNoteItem::changeTheme);

//    connect(m_menuBtn, &DImageButton::clicked, this, &TextNoteItem::handleMenuBtnClicked);
//    connect(m_menuBtn, &DImageButton::clicked, this, &TextNoteItem::handleMenuBtnClicked);
//    connect(m_menuBtn, &DImageButton::stateChanged, this, &TextNoteItem::handleMenuBtnStateChanged);
}

void TextNoteItem::changeToEditMode(int cursorpos)
//void TextNoteItem::changeToEditMode()
{
//    m_stackedWidget->setCurrentIndex(1);
//    QTextCursor textCursor = m_plainTextEdit->textCursor();
//    textCursor.movePosition(QTextCursor::End);

    if(nullptr != m_textEdit)
    {
        m_bakContent = m_textEdit->toPlainText();
        m_textEdit->setReadOnly(false);
        m_textEdit->setFocus();

        m_isEdited = true;

        //liuyang 3550 3547 3528
//        QTextCursor cursor = m_textEdit->textCursor();
//        cursor.movePosition(QTextCursor::End);
//        m_textEdit->setTextCursor(cursor);
        //liuyang 3550 3547 3528
        //3550-3547-3528 patch
        if(cursorpos > 0)
        {
            QTextCursor cursor = m_textEdit->textCursor();
            cursor.setPosition(cursorpos);
            m_textEdit->setTextCursor(cursor);
        }
        //3550-3547-3528 patch
    }
}

void TextNoteItem::readFromDatabase()
{
    //m_textEdit->readFromDatabase();
    //liuyang 3547
    //m_bakContent = m_textEdit->onlyreadFromDatabase();
    QDateTime time;
    m_bakContent = m_textEdit->onlyreadFromDatabase(&time);
    //liuyang 3547

    //qDebug() << "m_bakContent: " << m_bakContent;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_bakContent:"), m_bakContent);

    m_textEdit->setPlainText(m_bakContent);
    m_textEdit->setLineHeight(24);

    //liuyang 3547
    if(time != m_textNote.createTime)
    {
        m_textNote.createTime = time;
        m_textNote.contentText = m_bakContent;
        emit sig_TextEditNotEmpty(true);
    }
    //liuyang 3547

    handleTextEditFocusOut();
}

void TextNoteItem::updateNote()
{
    NOTE note = m_textNote;
    note.contentText = m_textEdit->toPlainText();
    if(!m_noteCtr->updateNote(note))
    {
        //todo：弹出popup，保存失败
        //qDebug()<< "error: update text note fail!";
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("error: update text note fail!"), QString("error: update text note fail!"));
    }
    else
    {
        m_textNote.contentText = m_textEdit->toPlainText();
    }
}

void TextNoteItem::textAreaChanged()
{
    if(!m_textEdit->toPlainText().isEmpty())
    {
        //非空
        //m_textNote.contentText = m_textEdit->toPlainText();
        m_menuBtn->setDisabled(false);
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("text:"), m_textEdit->toPlainText());

        bool changed = false;
        QString tmp = m_textEdit->toPlainText();
        if(m_bakContent != tmp)
        {
            changed = true;
        }
        emit sig_TextEditNotEmpty(changed);
    }
    else {
        m_menuBtn->setDisabled(true);
        emit sig_TextEditEmpty();
    }
}


void TextNoteItem::handleTextEditClicked()
{
    if(!Intancer::get_Intancer()->getTryToDelEmptyTextNote())
    {
        if(m_isTextConverted)
        {
            m_textEdit->setReadOnly(true);
        }
        else
        {
            m_textEdit->setReadOnly(false);
        }
//        m_bakContent = m_textEdit->toPlainText();
//        if (m_isTextConverted)
//        {
//            emit textEditClicked(m_textNote);
//        }
//        else
//        {
//            m_textEdit->setReadOnly(false);
//            m_isEdited = true;
//            emit textEditTrueClicked(m_textNote);
//        }
    }
}

void TextNoteItem::handleMenuBtnClicked()
{
//    if((TEXT == m_textNote.noteType)&&(!m_textNote.contentText.isEmpty()))
//    {
        QPoint pGlobal = m_menuBtn->mapToGlobal(QPoint(0,0));
        QPoint arrowPoint(pGlobal.x() + m_menuBtn->width() / 2, pGlobal.y() +m_menuBtn->height());
        QPoint pParent = m_menuBtn->mapTo(this, QPoint(0,0));
        NOTE tmpNote = m_textNote;
        tmpNote.contentText = m_noteCtr->getConttextByNoteID(tmpNote.folderId, tmpNote.id);
        emit menuBtnClicked(arrowPoint, pParent, this, tmpNote);
//    }
}

void TextNoteItem::handleTextEditFocusOut()
{
    //this->m_textEdit->readFromDatabase();   //2567
    m_bakContent = m_textEdit->onlyreadFromDatabase();

    //liuyang 3550 3547 3528
//    if(m_bakContent == m_textEdit->getText())
//    //if(0 == m_bakContent.compare(m_textEdit->getText()))
//    {
//        return;
//    }
    //liuyang 3550 3547 3528

    //qDebug() << "m_bakContent: " << m_bakContent;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_bakContent:"), m_bakContent);

//    m_textEdit->setPlainText(m_bakContent);
//    m_textEdit->setLineHeight(24);

    m_textNote.contentText = m_textEdit->toPlainText();
    bool timechanged = false;
//    if(m_bakContent != m_textNote.contentText)
//    {
//        m_textNote.createTime = QDateTime::currentDateTime();
//        timechanged = true;
//    }
    m_timeLabel->setText("   " + UiUtil::convertDateTime(m_textNote.createTime));
    m_noteCtr->updateNote(m_textNote);
    if(m_textNote.contentText.isEmpty())
    {
        emit sig_fouceOutAndEditEmpty(m_textNote);
    }
    else
    {
//        QFont labelFontForWidth;
//        labelFontForWidth.setFamily("PingFangSC-Regular");
//        labelFontForWidth.setPointSize(10);
        QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T8);
        //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, m_textEdit->width() * 5, m_isTextConverted);
        //QString elidedText = UiUtil::getElidedText(m_textEdit->font(), m_textNote.contentText, (m_textEdit->width() - 10) * 5, m_isTextConverted);

        if (m_isTextConverted)
        {
            m_textEdit->setReadOnly(true);
        }
        else
        {
            m_textEdit->setReadOnly(true);
        }

        QString html = UiUtil::getHtmlText(m_textNote.contentText, 12, m_searchKey, BLUE);
        //qDebug() << "html: " << html;
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("html:"), html);

        m_textEdit->setHtml(html);
        m_textEdit->setLineHeight(24);

        m_bakContent = m_textEdit->toPlainText();
        m_isEdited = false;
        //m_textEdit->setHtml(txt);
        if(timechanged)
        {
            //emit sig_ItemTimeChanged(m_textNote);
        }
    }

}

void TextNoteItem::handleMenuBtnStateChanged()
{
    int preState = m_menuBtnState;
    //m_menuBtnState = m_menuBtn->getState();
    //qDebug()<<"handleMenuBtnCheckeChanged m_menuBtnState:"<<m_menuBtnState;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("handleMenuBtnCheckeChanged m_menuBtnState:"), QString::number(m_menuBtnState,10));

    if((preState == 1) && (m_menuBtnState == 2))
    {
        //press
        //qDebug()<<"press";
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("press"), QString("press"));
        emit sig_menuBtnPressed();
    }
    else if((preState == 2) && (m_menuBtnState == 1))
    {
        //release
        //qDebug()<<"release";
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("release"), QString("press"));
        emit sig_menuBtnReleased();
    }
}

void TextNoteItem::tryToFouceout()
{
//    if(m_isEdited && !m_mouseIsIn)
//    {
        //qDebug()<<"tryToFouceout";
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("tryToFouceout"), QString("tryToFouceout"));
        //m_textEdit->focusOutSignal();
        handleTextEditFocusOut();
//    }
}
void TextNoteItem::textEditChanged(const QString &str) //liuyang 3547
//void TextNoteItem::textEditChanged(QString str)
{
    m_textNote.contentText = str;
    //liuyang 3550 3547 3528
    m_textNote.createTime = m_textEdit->getUpdateTime();
    QString timeContent = "   " + UiUtil::convertDateTime(m_textNote.createTime);
    if(timeContent != m_timeLabel->text())
    {
       m_timeLabel->setText(timeContent);
    }
    //liuyang 3547
    if(str.isEmpty())
    {
        m_menuBtn->DisableBtn();
        handleTextEditFocusOut();
    }
    else
    {
        m_menuBtn->EnAbleBtn();
        emit sig_TextEditNotEmpty(true);
    }
    //liuyang 3547
    //liuyang 3550 3547 3528
}

void TextNoteItem::changeTheme()
{
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    pb.setBrush(DPalette::Button, pb.color(DPalette::ItemBackground));
    //pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_bgWidget->setPalette(pb);

    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();

    if(themeType == DGuiApplicationHelper::LightType)
    {
        if(nullptr != m_menuBtn)
        {
            m_menuBtn->setPicChange(
                        ":/image/icon/normal/more_normal.svg",
                        ":/image/icon/press/more_press.svg",
                        ":/image/icon/hover/more_hover.svg",
                        ":/image/icon/disabled/more_disabled.svg",
                        ":/image/icon/focus/more_focus.svg");
        }

        if(nullptr != m_detailBtn)
        {
            m_detailBtn->setPicChange(
                        ":/image/icon/normal/detail-normal.svg",
                        ":/image/icon/press/detail-press.svg",
                        ":/image/icon/hover/detail-hover.svg",
                        "",
                        "");
        }


    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        if(nullptr != m_menuBtn)
        {
            m_menuBtn->setPicChange(
                        ":/image/icon_dark/normal/more_normal_dark.svg",
                        ":/image/icon_dark/press/more_press_dark.svg",
                        ":/image/icon_dark/hover/more_hover_dark.svg",
                        ":/image/icon_dark/disabled/more_disabled_dark.svg",
                        ":/image/icon_dark/focus/more_focus_dark.svg");
        }
        if(nullptr != m_detailBtn)
        {
            m_detailBtn->setPicChange(
                        ":/image/icon_dark/normal/detail-normal.svg",
                        ":/image/icon_dark/press/detail-press.svg",
                        ":/image/icon_dark/hover/detail-hover.svg",
                        "",
                        "");
        }
    }
}

void TextNoteItem::OnToDetalPage()
{
    emit textEditClicked(m_textNote);
}

//Add start bug 2587
void TextNoteItem::OnTextEditGetFocus()
{
    //DStyle::setFocusRectVisible(m_bgWidget,true);
    //m_bgWidget->setFocus();
    emit SigTextEditGetFocus(m_textNote);
}
void TextNoteItem::OnTextEditOutFocus()
{
    //DStyle::setFocusRectVisible(m_bgWidget,false);
    //m_bgWidget->clearFocus();
    emit SigTextEditOutFocus(m_textNote);
}
//Add end bug 2587

void TextNoteItem::onDetailButtonChanged(const bool isVisible) {
    if(isVisible)
    {
        m_isTextConverted = true;
    }
    else {
        m_isTextConverted = false;
    }
    this->m_detailBtn->setVisible(isVisible);
}

void TextNoteItem::resizeEvent(QResizeEvent * event)
{
    int maxwidth = event->size().width();
    //qDebug()<<"TextNoteItem width:"<<maxwidth;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteItem width:"), QString::number(maxwidth,10));
    if(nullptr != m_textEdit)
    {
//        QFont labelFontForWidth;
//        labelFontForWidth.setFamily("PingFangSC-Regular");
//        labelFontForWidth.setPointSize(10);
        QFont labelFontForWidth = DFontSizeManager::instance()->get(DFontSizeManager::T8);
        //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, (maxwidth - 21) * 5, m_isTextConverted);
        //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, 614 * 5, m_isTextConverted);
        qDebug() << "m_isTextConverted: " << m_isTextConverted;
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_isTextConverted:"), QString::number(m_isTextConverted));
        if (m_isTextConverted)
        {
            m_textEdit->setReadOnly(true);
        }
        else
        {
            m_textEdit->setReadOnly(false);
        }


        //m_bakContent = elidedText;
        if(m_textNote.contentText != m_textEdit->getText())
        //2719 fix liuyang
        //if(elidedText != m_textEdit->getText())
        //2719 fix liuyang
        {
            QString html = UiUtil::getHtmlText(m_textNote.contentText, 12, m_searchKey, BLUE);
            //qDebug() << "html: " << html;
            UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("html:"), html);

            m_textEdit->setHtml(html);
            m_textEdit->setLineHeight(24);
        }

        //m_textEdit->setReadOnly(true);
        QTextCursor cursor = m_textEdit->textCursor();
//        cursor.movePosition(QTextCursor::End);
//        m_textEdit->setTextCursor(cursor);
        m_isEdited = false;
    }

    return QWidget::resizeEvent(event);
}

void TextNoteItem::leaveEvent(QEvent *event)
{
    m_mouseIsIn = false;
    //3152 liuyang
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    pb.setBrush(DPalette::Button, pb.color(DPalette::ItemBackground));
    //pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_bgWidget->setPalette(pb);
    //3152 liuyang
    return QWidget::leaveEvent(event);
}

void TextNoteItem::enterEvent(QEvent *event)
{
    m_mouseIsIn = true;
    //3152 liuyang
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    pb.setBrush(DPalette::Button, pb.color(DPalette::Light));
    //pb.setBrush(DPalette::Base, pb.color(DPalette::Light));
    m_bgWidget->setPalette(pb);
    //3152 liuyang
    return QWidget::enterEvent(event);
}

//3550-3547-3528 patch
int TextNoteItem::getTextEditCursorPos()
{
    return  m_textEdit != nullptr ? m_textEdit->textCursor().position() : -1;
}
//3550-3547-3528 patch
