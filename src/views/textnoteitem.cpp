#include "textnoteitem.h"
#include "uiutil.h"
#include <QDebug>

TextNoteItem::TextNoteItem(NOTE textNote, NoteController *noteCtr) : m_isTextConverted(false)
{
    this->m_textNote = textNote;
    this->m_noteCtr = noteCtr;

//    this->setMinimumHeight(100);
//    this->setMaximumHeight(200);
    //this->setFixedHeight(64);
    initUI();
    initConnection();
//    this->setStyleSheet("background: blue");
//    qDebug()<< "TextNoteItem: m_timeLabel " << m_timeLabel->height();
//    qDebug()<< "TextNoteItem: m_bgWidget " << m_bgWidget->height();
//    qDebug()<< "TextNoteItem: parent " << this->height();
}

TextNoteItem::~TextNoteItem()
{

}

void TextNoteItem::initUI()
{
    m_timeLabel = new QLabel();
    QSizePolicy sp = m_timeLabel->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Fixed);
    m_timeLabel->setSizePolicy(sp);
    m_bgWidget = new QWidget();
    QSizePolicy sp1 = m_bgWidget->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Fixed);
    m_bgWidget->setSizePolicy(sp1);
    m_itemLayout = new QVBoxLayout();
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    m_itemLayout->addWidget(m_timeLabel);
    m_itemLayout->addWidget(m_bgWidget);
    m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);
    this->setLayout(m_itemLayout);
//    QSizePolicy sp = m_bgWidget->sizePolicy();
//    sp.setHorizontalStretch(1);
//    m_bgWidget->setSizePolicy(sp);

    m_timeLabel->setGeometry(QRect(10, 10, 161, 16));
    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setText(m_textNote.createTime.toString());

    //m_bgWidget->setGeometry(QRect(0, 40, this->width(), 91));
    m_bgWidget->setObjectName("widget");
    m_bgWidget->setStyleSheet("background: #f5f5f5");

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
    labelFont.setPointSize(12);
    m_textEdit->setFont(labelFont);
    QString elidedText = UiUtil::getElidedText(labelFont, m_textNote.contentText, 614 * 5, m_isTextConverted);
    m_textEdit->setText(elidedText);
//    QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(m_textEdit->sizePolicy().hasHeightForWidth());
//    m_textEdit->setSizePolicy(sizePolicy);
    m_textEdit->setFrameShape(QFrame::NoFrame);
    m_hBoxLayout->addWidget(m_textEdit);



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
   m_menuBtn = new DImageButton(m_bgWidget);
   m_menuBtn->setFixedSize(QSize(40, 40));
   m_menuBtn->setNormalPic(":/image/icon/normal/more_normal.svg");
   m_menuBtn->setHoverPic(":/image/icon/hover/more_hover.svg");
   m_menuBtn->setPressPic(":/image/icon/press/more_press.svg");

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
   m_hBoxLayout->addWidget(m_menuBtn);



   textAreaChanged();
}

void TextNoteItem::initConnection()
{
    //connect(m_plainTextEdit, &QPlainTextEdit::textChanged, this, &TextNoteItem::updateNote);
    //connect(m_textEdit, &TextNoteEdit::textChanged, this, &TextNoteItem::updateNote);
    connect(m_textEdit, &TextNoteEdit::clicked, this, &TextNoteItem::handleTextEditClicked);
    connect(m_textEdit->document(), &QTextDocument::contentsChanged, this, &TextNoteItem::textAreaChanged);
    connect(m_menuBtn, &DImageButton::clicked, this, &TextNoteItem::handleMenuBtnClicked);
    //connect(m_textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(textAreaChanged()));

}

void TextNoteItem::changeToEditMode()
{
//    m_stackedWidget->setCurrentIndex(1);
//    QTextCursor textCursor = m_plainTextEdit->textCursor();
//    textCursor.movePosition(QTextCursor::End);
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
//    QTextDocument *document = m_textEdit->document();
//    int newHeight = document->size().height() + 20;
//    m_textEdit->setFixedHeight(newHeight);
//    m_bgWidget->setFixedHeight(newHeight);
//    this->setFixedHeight(m_timeLabel->height() + newHeight);
}


void TextNoteItem::handleTextEditClicked()
{
    if (m_isTextConverted)
    {
        emit textEditClicked(m_textNote);
    }
}

void TextNoteItem::handleMenuBtnClicked()
{
    QPoint pGlobal = m_menuBtn->mapToGlobal(QPoint(0,0));
    QPoint arrowPoint(pGlobal.x() + m_menuBtn->width() / 2, pGlobal.y() +m_menuBtn->height());
    QPoint pParent = m_menuBtn->mapTo(this, QPoint(0,0));
    emit menuBtnClicked(arrowPoint, pParent, this, m_textNote);
    //qDebug()<< "p.x: " << p.x() << ", p.y: " << p.y();
    //m_arrowMenu->show(p.x() + m_menuBtn->width() / 2, p.y() +m_menuBtn->height());
}