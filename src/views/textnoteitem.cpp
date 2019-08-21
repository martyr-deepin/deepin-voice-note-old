#include "textnoteitem.h"
#include "uiutil.h"
#include <QDebug>

TextNoteItem::TextNoteItem(NOTE textNote, NoteController *noteCtr)
{
    this->m_textNote = textNote;
    this->m_noteCtr = noteCtr;
    initUI();
    initConnection();
}

TextNoteItem::~TextNoteItem()
{

}
//TEXT_NOTE textNote;
//QLabel *m_timeLabel;
//QWidget *m_bgWidget;
//QHBoxLayout *m_hBoxLayout;
//QLabel *m_textLabel;
//DImageButton *m_menuBtn;
void TextNoteItem::initUI()
{
    m_timeLabel = new QLabel(this);
    m_timeLabel->setGeometry(QRect(10, 10, 161, 16));
    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setText(m_textNote.createTime.toString());
    m_bgWidget = new QWidget(this);
    m_bgWidget->setGeometry(QRect(0, 40, this->width(), 91));
    m_bgWidget->setObjectName("widget");
    m_bgWidget->setStyleSheet("background: green");
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

    m_textEdit = new QTextEdit(m_bgWidget);
    m_textEdit->setText(m_textNote.contentText);
    QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_textEdit->sizePolicy().hasHeightForWidth());
    m_textEdit->setSizePolicy(sizePolicy);
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
   m_menuBtn = new DImageButton(m_bgWidget);
   m_menuBtn->setNormalPic(":/image/add_normal.svg");
   m_menuBtn->setHoverPic(":/image/add_hover.svg");
   m_menuBtn->setPressPic(":/image/add_press.svg");


   m_hBoxLayout->addWidget(m_menuBtn);
}

void TextNoteItem::initConnection()
{
    //connect(m_plainTextEdit, &QPlainTextEdit::textChanged, this, &TextNoteItem::updateNote);
    connect(m_textEdit, &QTextEdit::textChanged, this, &TextNoteItem::updateNote);
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

