#include "textnoteitem.h"
#include "uiutil.h"

TextNoteItem::TextNoteItem(NOTE textNote)
{
    this->textNote = textNote;
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
    m_timeLabel->setText(textNote.createTime.toString());
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
    m_textLabel = new QLabel(m_bgWidget);
    QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_textLabel->sizePolicy().hasHeightForWidth());
    m_textLabel->setSizePolicy(sizePolicy);
    m_textLabel->setText(textNote.contentText);

   m_hBoxLayout->addWidget(m_textLabel);
   m_menuBtn = new DImageButton(m_bgWidget);
   m_menuBtn->setNormalPic(":/image/add_normal.svg");
   m_menuBtn->setHoverPic(":/image/add_hover.svg");
   m_menuBtn->setPressPic(":/image/add_press.svg");


   m_hBoxLayout->addWidget(m_menuBtn);
}

void TextNoteItem::initConnection()
{

}
