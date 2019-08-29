#include "voicenoteitem.h"
#include "uiutil.h"

VoiceNoteItem::VoiceNoteItem(NOTE note, NoteController *noteCtr):m_note(note), m_noteCtr(noteCtr)
{
    initUI();
}

VoiceNoteItem::~VoiceNoteItem()
{

}

void VoiceNoteItem::initUI()
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
    m_timeLabel->setText(m_note.createTime.toString());

    //m_bgWidget->setGeometry(QRect(0, 40, this->width(), 91));
    m_bgWidget->setObjectName("widget");
    m_bgWidget->setStyleSheet("background: green");

    m_hBoxLayout = new QHBoxLayout(m_bgWidget);
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");

    m_ctrlBtn = new DImageButton(m_bgWidget);
    m_ctrlBtn->setFixedSize(QSize(40, 40));
    m_ctrlBtn->setNormalPic(":/image/add_normal.svg");
    m_ctrlBtn->setHoverPic(":/image/add_hover.svg");
    m_ctrlBtn->setPressPic(":/image/add_press.svg");
    m_voiceShape = new QWidget();
    QSizePolicy spShape = m_voiceShape->sizePolicy();
    sp.setHorizontalStretch(1);
    m_voiceShape->setSizePolicy(spShape);
    m_menuBtn = new DImageButton(m_bgWidget);
    m_menuBtn->setFixedSize(QSize(40, 40));
    m_menuBtn->setNormalPic(":/image/icon/normal/more_normal.svg");
    m_menuBtn->setHoverPic(":/image/icon/hover/more_hover.svg");
    m_menuBtn->setPressPic(":/image/icon/press/more_press.svg");
    m_voiceTimeLabel = new QLabel();
    m_voiceTimeLabel->setFixedSize(46, 20);
    m_voiceTimeLabel->setText(UiUtil::formatMillisecondToSecAndMil(m_note.voiceTime));

    m_hBoxLayout->addWidget(m_ctrlBtn);
    m_hBoxLayout->addWidget(m_voiceShape);
    m_hBoxLayout->addWidget(m_voiceTimeLabel);
    m_hBoxLayout->addWidget(m_menuBtn);

    m_hBoxLayout->addWidget(m_menuBtn);


}

void VoiceNoteItem::initConnection()
{

}
