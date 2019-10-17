#include "textnoteitem.h"
#include "uiutil.h"
#include <DPalette>
#include <QDebug>
#include <QGraphicsOpacityEffect>

TextNoteItem::TextNoteItem(NOTE textNote, NoteController *noteCtr, QString searchKey) : m_isTextConverted(false)
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

void TextNoteItem::initUI()
{

    //this->setFixedHeight(150);
    //this->setFixedHeight(140);
    this->setFixedHeight(123);
    //this->resize(500, this->height());
    m_timeLabel = new DLabel();

    QFont timeLabelFont;
    timeLabelFont.setFamily("PingFangSC-Regular");
    timeLabelFont.setPointSize(8);
    m_timeLabel->setFont(timeLabelFont);
    m_timeLabel->setFixedHeight(16);

    m_bgWidget = new DBlurEffectWidget(this);


//    m_bgWidget->setFixedHeight(124);//orig
    m_bgWidget->setFixedHeight(93);
//    QSizePolicy sp1 = m_bgWidget->sizePolicy();
//    sp.setVerticalPolicy(QSizePolicy::Fixed);
//    m_bgWidget->setSizePolicy(sp1);
    m_itemLayout = new QVBoxLayout();
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    m_itemLayout->addSpacing(2);
    m_itemLayout->addWidget(m_timeLabel);
    m_itemLayout->addWidget(m_bgWidget);
    m_itemLayout->addSpacing(6);
    m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);
    this->setLayout(m_itemLayout);
//    QSizePolicy sp = m_bgWidget->sizePolicy();
//    sp.setHorizontalStretch(1);
//    m_bgWidget->setSizePolicy(sp);

    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setText("   " + UiUtil::convertDateTime(m_textNote.createTime));

    //m_bgWidget->setGeometry(QRect(0, 40, this->width(), 91));
    m_bgWidget->setObjectName("widget");
//    QPalette pal;
//    pal.setColor(QPalette::Background,Qt::red);
//    m_bgWidget->setAutoFillBackground(true);
//    m_bgWidget->setPalette(pal);
//    m_bgWidget->setStyleSheet("background: #f5f5f5");

    m_bgWidget->setBlurRectXRadius(8);
    m_bgWidget->setBlurRectYRadius(8);

    QPalette pb;
    pb.setColor(QPalette::Background,QColor(00,00,00));
    m_bgWidget->setPalette(pb);
    m_bgWidget->setMaskAlpha(14);

    //UiUtil::setWidgetBackground(m_bgWidget, ":/image/text_bg.png");
//   self.horizontalLayoutWidget = QtWidgets.QWidget(self.widget)
//   self.horizontalLayoutWidget.setGeometry(QtCore.QRect(0, 0, 691, 91))
//   self.horizontalLayoutWidget.setObjectName("horizontalLayoutWidget")
    m_hBoxLayout = new QHBoxLayout(m_bgWidget);
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");


//    m_stackedWidget = new QStackedWidget(m_bgWidget);
//    QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(m_stackedWidget->sizePolicy().hasHeightForWidth());
//    m_stackedWidget->setSizePolicy(sizePolicy);
//    m_stackedWidget->setObjectName("stackedWidget");
//    m_page1Widget = new QWidget();
//    m_page1Widget->setObjectName("page1");
//    m_textLabel = new QLabel(m_page1Widget);
//    m_textLabel->setGeometry(QRect(10, 10, 581, 71));
//    m_textLabel->setObjectName("label");
//    m_textLabel->setText(m_textNote.contentText);
//    m_stackedWidget->addWidget(m_page1Widget);
//    m_page2Widget = new QWidget();
////    QSizePolicy sizePolicy1 = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
////    sizePolicy1.setHorizontalStretch(0);
////    sizePolicy1.setVerticalStretch(0);
////    sizePolicy1.setHeightForWidth(m_stackedWidget->sizePolicy().hasHeightForWidth());

////    sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding);
////    sizePolicy.setHorizontalStretch(0);
////    sizePolicy.setVerticalStretch(0);
////    sizePolicy.setHeightForWidth(self.page_2.sizePolicy().hasHeightForWidth());
//    m_page2Widget->setSizePolicy(sizePolicy);
//    m_page2Widget->setObjectName("page2");
//    m_plainTextEdit = new QPlainTextEdit(m_page2Widget);
//    m_plainTextEdit->setGeometry(QRect(10, 0, 591, 91));
////    self.plainTextEdit.setObjectName("plainTextEdit");
//    m_plainTextEdit->setPlainText(m_textNote.contentText);
//    m_stackedWidget->addWidget(m_page2Widget);
//    m_hBoxLayout->addWidget(m_stackedWidget);
//    m_stackedWidget->setCurrentIndex(1);

    m_textEdit = new TextNoteEdit(m_textNote, m_bgWidget, m_noteCtr);
    QFont labelFont;
    labelFont.setFamily("PingFangSC-Regular");
    labelFont.setPointSize(9);
    m_textEdit->setFont(labelFont);

    m_hBoxLayout->addWidget(m_textEdit);
    QPalette pl = m_textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
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

//    m_textEdit->setText(UiUtil::getHtmlText(elidedText, 12, m_searchKey));

//    QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(m_textEdit->sizePolicy().hasHeightForWidth());
//    m_textEdit->setSizePolicy(sizePolicy);
    m_textEdit->setFrameShape(QFrame::NoFrame);
    m_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


//    m_textLabel = new QLabel(m_bgWidget);
//    QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(m_textLabel->sizePolicy().hasHeightForWidth());
//    m_textLabel->setSizePolicy(sizePolicy);
//    m_textLabel->setText(textNote.contentText);
//    m_plainTextEdit = new QPlainTextEdit(m_bgWidget);

   //m_hBoxLayout->addWidget(m_textLabel);
//   m_menuBtn = new DImageButton(m_bgWidget);

   m_MenuBtnBackground = new DWidget(m_bgWidget);
   m_MenuBtnBackground->setFixedSize(QSize(40,m_bgWidget->height()));

   //m_menuBtn = new DIconButton(m_MenuBtnBackground);
   m_menuBtn = new DImageButton(m_MenuBtnBackground);
   m_menuBtn->setFixedSize(QSize(40, 40));
   m_menuBtn->move(0,7);
   //m_menuBtn->setIcon();
   m_menuBtn->setNormalPic(":/image/icon/normal/more_normal.svg");
   m_menuBtn->setHoverPic(":/image/icon/hover/more_hover.svg");
   m_menuBtn->setPressPic(":/image/icon/press/more_press.svg");
   m_menuBtn->setDisabled(true);

//   m_arrowMenu = new DArrowRectangle(DArrowRectangle::ArrowTop, DArrowRectangle::FloatWindow);
//   m_arrowMenu->setHeight(200);
//   m_arrowMenu->setWidth(200);
////   m_arrowMenu->move((m_menuBtn->x() + m_menuBtn->width() / 2), (m_menuBtn->y() + m_menuBtn->height() ));
//   qDebug() << "m_menuBtn->x():" << m_menuBtn->x() << ",m_menuBtn->width() / 2 :" << m_menuBtn->width() / 2 << ",m_menuBtn->y() :" << m_menuBtn->y() << ",m_menuBtn->height(): " << m_menuBtn->height();
//   //m_arrowMenu->move(100, 100);
////   m_arrowMenu->show(0, 0);
//   //m_arrowMenu->setContent(m_menuBtn);
//   //m_arrowMenu->setVisible(true);

//   m_arrowMenu->setContent(m_contextMenu);
//   m_arrowMenu->setBorderColor(QColor::fromRgb(255, 0, 0));
   m_hBoxLayout->addWidget(m_MenuBtnBackground);

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
    connect(m_textEdit, &TextNoteEdit::focusOutSignal, this, &TextNoteItem::handleTextEditFocusOut);
    connect(m_textEdit->document(), &QTextDocument::contentsChanged, this, &TextNoteItem::textAreaChanged);
    connect(m_menuBtn, &DImageButton::clicked, this, &TextNoteItem::handleMenuBtnClicked);
    //connect(m_textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(textAreaChanged()));
    connect(m_menuBtn, &DImageButton::stateChanged, this, &TextNoteItem::handleMenuBtnStateChanged);
}

void TextNoteItem::changeToEditMode()
{
//    m_stackedWidget->setCurrentIndex(1);
//    QTextCursor textCursor = m_plainTextEdit->textCursor();
//    textCursor.movePosition(QTextCursor::End);

    if(nullptr != m_textEdit)
    {
        m_textEdit->setReadOnly(false);
        m_textEdit->setFocus();
        m_isEdited = true;
    }
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
    }
}


void TextNoteItem::handleTextEditClicked()
{
    if (m_isTextConverted)
    {
        emit textEditClicked(m_textNote);
    }
    else
    {
        m_textEdit->setReadOnly(false);
        m_isEdited = true;
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
        //qDebug()<< "p.x: " << p.x() << ", p.y: " << p.y();
        //m_arrowMenu->show(p.x() + m_menuBtn->width() / 2, p.y() +m_menuBtn->height());
//    }
}

void TextNoteItem::handleTextEditFocusOut()
{
    m_textNote.contentText = m_textEdit->toPlainText();
    m_textNote.createTime = QDateTime::currentDateTime();
    m_timeLabel->setText("   " + UiUtil::convertDateTime(m_textNote.createTime));
    m_noteCtr->updateNote(m_textNote);
    if(m_textNote.contentText.isEmpty())
    {
        emit sig_TextEditEmpty(m_textNote);
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
    }
}

void TextNoteItem::handleMenuBtnStateChanged()
{
    int preState = m_menuBtnState;
    m_menuBtnState = m_menuBtn->getState();
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
    if(m_isEdited && !m_mouseIsIn)
    {
        m_textEdit->focusOutSignal();
    }
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
