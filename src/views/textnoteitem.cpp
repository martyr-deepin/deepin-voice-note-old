#include "textnoteitem.h"
#include "uiutil.h"
#include "intancer.h"
#include <DPalette>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <DApplicationHelper>

TextNoteItem::TextNoteItem(NOTE textNote, NoteController *noteCtr, QString searchKey, QWidget *parent) :DWidget(parent), m_isTextConverted(false)
{
    this->m_textNote = textNote;
    this->m_noteCtr = noteCtr;
    m_searchKey = searchKey;
    m_menuBtnState = 0;
    m_isEdited = false;
    m_mouseIsIn = false;

    initUI();
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

void TextNoteItem::initUI()
{

    //this->setFixedHeight(150);
    //this->setFixedHeight(140);
    this->setFixedHeight(TEXTNOTE_HEIGHT);
    //this->resize(500, this->height());
    m_timeLabel = new DLabel(this);

    QFont timeLabelFont;
    timeLabelFont.setFamily("PingFangSC-Regular");
    timeLabelFont.setPointSize(8);
    m_timeLabel->setFont(timeLabelFont);
    m_timeLabel->setFixedHeight(16);

    m_bgWidget = new DFrame(this);
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    pb.setBrush(DPalette::Base, pb.color(DPalette::FrameBorder));
    m_bgWidget->setPalette(pb);

//    m_bgWidget->setFixedHeight(124);//orig
//    m_bgWidget->setFixedHeight(93);
    m_bgWidget->setFixedHeight(105);
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
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");


    m_textEdit = new TextNoteEdit(m_textNote, m_bgWidget, m_noteCtr);
    QFont labelFont;
    labelFont.setFamily("PingFangSC-Regular");
    labelFont.setPointSize(9);
    m_textEdit->setFont(labelFont);
    m_textEdit->setFixedHeight(97);

    m_hBoxLayout->addSpacing(16);
    m_hBoxLayout->addWidget(m_textEdit);
    m_hBoxLayout->addSpacing(10);
    QPalette pl = m_textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(0,0,0,0)));
    m_textEdit->setPalette(pl);

    QFont labelFontForWidth;
    labelFontForWidth.setFamily("PingFangSC-Regular");
    labelFontForWidth.setPointSize(10);
    //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, (m_textEdit->width() + 26) * 5, m_isTextConverted);
    QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, 536 * 5, m_isTextConverted);
    qDebug() << "m_isTextConverted: " << m_isTextConverted;
    if (m_isTextConverted)
    {
        m_textEdit->setReadOnly(true);
        m_isEdited = true;
        m_textEdit->setContextMenuPolicy(Qt::NoContextMenu);
    }

    m_textEdit->setFrameShape(QFrame::NoFrame);
    m_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_MenuBtnBackground = new DWidget(m_bgWidget);
    m_MenuBtnBackground->setFixedSize(QSize(40,m_bgWidget->height()));

    m_menuBtn = new MenuButton(m_MenuBtnBackground);
    //m_menuBtn = new MenuButton(DStyle::SP_SelectElement,m_MenuBtnBackground);

//   QPalette pa; //= DApplicationHelper::instance()->palette(m_menuBtn);
//   pa.setBrush(DPalette::Highlight, pa.color(DPalette::Base));
//   m_menuBtn->setBtnPalette(pa);
    //m_menuBtn = new DImageButton(m_MenuBtnBackground);
    m_menuBtn->setFixedSize(QSize(40, 40));
    m_menuBtn->setIcon(QIcon(":/image/icon/normal/more_normal.svg"));
    m_menuBtn->setIconSize(QSize(20,20));
    m_menuBtn->setDisabled(true);



    m_hBoxLayout->addWidget(m_MenuBtnBackground);
    m_hBoxLayout->addSpacing(8);

    textAreaChanged();

//   QTextEdit *textEdit = new QTextEdit(this);
//   textEdit->setFixedSize(QSize(100,100));
//   textEdit->move(100,0);
}

void TextNoteItem::initConnection()
{
    //connect(m_plainTextEdit, &QPlainTextEdit::textChanged, this, &TextNoteItem::updateNote);
    //connect(m_textEdit, &TextNoteEdit::textChanged, this, &TextNoteItem::updateNote);
    connect(m_textEdit, &TextNoteEdit::clicked, this, &TextNoteItem::handleTextEditClicked);
    //connect(m_textEdit, &TextNoteEdit::focusOutSignal, this, &TextNoteItem::handleTextEditFocusOutNotReadOly);
    connect(m_textEdit->document(), &QTextDocument::contentsChanged, this, &TextNoteItem::textAreaChanged);
    connect(m_textEdit, &TextNoteEdit::sigTextChanged, this, &TextNoteItem::textEditChanged);
    connect(m_menuBtn, &QAbstractButton::pressed, this, &TextNoteItem::sig_menuBtnPressed);
    connect(m_menuBtn, &QAbstractButton::released, this, &TextNoteItem::handleMenuBtnClicked);
    connect(m_menuBtn, &QAbstractButton::released, this, &TextNoteItem::sig_menuBtnReleased);
    connect(m_menuBtn, &QAbstractButton::pressed, this, &TextNoteItem::buttonClicled);

    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &TextNoteItem::changeTheme);

//    connect(m_menuBtn, &DImageButton::clicked, this, &TextNoteItem::handleMenuBtnClicked);
    //connect(m_menuBtn, &DImageButton::clicked, this, &TextNoteItem::handleMenuBtnClicked);
    //connect(m_textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(textAreaChanged()));
//    connect(m_menuBtn, &DImageButton::stateChanged, this, &TextNoteItem::handleMenuBtnStateChanged);
}

void TextNoteItem::changeToEditMode()
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
    }
}

void TextNoteItem::readFromDatabase()
{
    m_textEdit->readFromDatabase();
    handleTextEditFocusOut();
}

void TextNoteItem::updateNote()
{
//    NOTE note = m_textNote;
//    note.contentText = m_plainTextEdit->toPlainText();
//    if(!m_noteCtr->updateNote(note))
//    {
//        //todo：弹出popup，保存失败
//        qDebug()<< "error: update text note fail!";
//    }
//    else
//    {
//        m_textNote.contentText = m_plainTextEdit->toPlainText();
//        m_textLabel->setText(m_plainTextEdit->toPlainText());
//    }

    NOTE note = m_textNote;
    note.contentText = m_textEdit->toPlainText();
    if(!m_noteCtr->updateNote(note))
    {
        //todo：弹出popup，保存失败
        qDebug()<< "error: update text note fail!";
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
        qDebug()<<"text: "<<m_textEdit->toPlainText();
        emit sig_TextEditNotEmpty();
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
        m_bakContent = m_textEdit->toPlainText();
        if (m_isTextConverted)
        {
            emit textEditClicked(m_textNote);
        }
        else
        {
            m_textEdit->setReadOnly(false);
            m_isEdited = true;
            emit textEditTrueClicked(m_textNote);
        }
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
    qDebug()<<"-------------------------------handleTextEditFocusOut()";
    this->m_textEdit->readFromDatabase();   //2567
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
        QFont labelFontForWidth;
        labelFontForWidth.setFamily("PingFangSC-Regular");
        labelFontForWidth.setPointSize(10);
        //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, m_textEdit->width() * 5, m_isTextConverted);
        QString elidedText = UiUtil::getElidedText(m_textEdit->font(), m_textNote.contentText, (m_textEdit->width() - 10) * 5, m_isTextConverted);

        if (m_isTextConverted)
        {
            qDebug() << "TextNoteItem::handleTextEditFocusOut setReadOnly(true)";
            m_textEdit->setReadOnly(true);
            m_textEdit->setContextMenuPolicy(Qt::NoContextMenu);
        }
        else
        {
            qDebug() << "TextNoteItem::handleTextEditFocusOut setReadOnly(false)";
            m_textEdit->setReadOnly(true);
            m_textEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
        }

        QString txt = UiUtil::getHtmlText(elidedText, 12, m_searchKey, BLUE);
        m_textEdit->setText(txt);
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
    qDebug()<<"handleMenuBtnCheckeChanged m_menuBtnState:"<<m_menuBtnState;

    if((preState == 1) && (m_menuBtnState == 2))
    {
        //press
        qDebug()<<"press";
        emit sig_menuBtnPressed();
    }
    else if((preState == 2) && (m_menuBtnState == 1))
    {
        //release
        qDebug()<<"release";
        emit sig_menuBtnReleased();
    }
}

void TextNoteItem::tryToFouceout()
{
//    if(m_isEdited && !m_mouseIsIn)
//    {
        qDebug()<<"tryToFouceout";
        //m_textEdit->focusOutSignal();
        handleTextEditFocusOut();
//    }
}

void TextNoteItem::textEditChanged(QString str)
{
    m_textNote.contentText = str;
}

void TextNoteItem::changeTheme()
{
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    pb.setBrush(DPalette::Base, pb.color(DPalette::FrameBorder));
    m_bgWidget->setPalette(pb);
}

void TextNoteItem::resizeEvent(QResizeEvent * event)
{
    int maxwidth = event->size().width();
    qDebug()<<"TextNoteItem width:"<<maxwidth;
    if(nullptr != m_textEdit)
    {
        QFont labelFontForWidth;
        labelFontForWidth.setFamily("PingFangSC-Regular");
        labelFontForWidth.setPointSize(10);
        QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, (maxwidth - 21) * 5, m_isTextConverted);
        //QString elidedText = UiUtil::getElidedText(labelFontForWidth, m_textNote.contentText, 614 * 5, m_isTextConverted);
        qDebug() << "m_isTextConverted: " << m_isTextConverted;
        if (m_isTextConverted)
        {
            m_textEdit->setReadOnly(true);
            m_textEdit->setContextMenuPolicy(Qt::NoContextMenu);
        }
        else
        {
            m_textEdit->setReadOnly(false);
            m_textEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
        }

        m_textEdit->setText(UiUtil::getHtmlText(elidedText, 12, m_searchKey, BLUE));
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
    return QWidget::leaveEvent(event);
}

void TextNoteItem::enterEvent(QEvent *event)
{
    m_mouseIsIn = true;
    return QWidget::enterEvent(event);
}
