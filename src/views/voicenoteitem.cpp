#include "voicenoteitem.h"
#include "uiutil.h"

VoiceNoteItem::VoiceNoteItem(NOTE note, NoteController *noteCtr):m_note(note), m_noteCtr(noteCtr)
{
    initUI();
    initConnection();
}

VoiceNoteItem::~VoiceNoteItem()
{

}

void VoiceNoteItem::initUI()
{

    this->setFixedHeight(94);
    m_timeLabel = new QLabel();
    m_timeLabel->setFixedHeight(30);

//    QSizePolicy sp = m_timeLabel->sizePolicy();
//    sp.setVerticalPolicy(QSizePolicy::Fixed);
//    m_timeLabel->setSizePolicy(sp);
    m_bgWidget = new QWidget();
//    QSizePolicy sp1 = m_bgWidget->sizePolicy();
//    sp.setVerticalPolicy(QSizePolicy::Fixed);
//    m_bgWidget->setSizePolicy(sp1);
    m_itemLayout = new QVBoxLayout();
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    m_itemLayout->addWidget(m_timeLabel);
    m_itemLayout->addWidget(m_bgWidget);
    m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);
    this->setLayout(m_itemLayout);
    QSizePolicy sp = m_bgWidget->sizePolicy();
    sp.setHorizontalStretch(1);
    m_bgWidget->setSizePolicy(sp);

    m_timeLabel->setGeometry(QRect(10, 10, 161, 16));
    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setText(UiUtil::convertNoteDate(m_note.createTime));
//    m_timeLabel->setText(m_note.createTime.toString());

    //m_bgWidget->setGeometry(QRect(0, 40, this->width(), 91));
    m_bgWidget->setObjectName("widget");
    QPalette p;
    //p.setBrush(m_BackGround->backgroundRole(),QBrush(QColor(255,245,245,100)));
    p.setBrush(m_bgWidget->backgroundRole(),QBrush(QColor(QRgb(0x00ffff00))));
    m_bgWidget->setAutoFillBackground(true);
    m_bgWidget->setPalette(p);

    m_timeLabel->setPalette(p);
    m_timeLabel->setAutoFillBackground(true);
    //m_bgWidget->setStyleSheet("background: #f2f2f2");

    m_hBoxLayout = new QHBoxLayout(m_bgWidget);
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");

//    m_ctrlBtn = new DImageButton(m_bgWidget);
//    m_ctrlBtn->setFixedSize(QSize(40, 40));
//    m_ctrlBtn->setNormalPic(":/image/icon/normal/play_normal.svg");
//    m_ctrlBtn->setHoverPic(":/m_waveformimage/icon/hover/play_hover.svg");
//    m_ctrlBtn->setPressPic(":/image/icon/press/play_press.svg");

    m_playingButton = new PlayingButton();
    m_playingButton->setFixedSize(QSize(60, 60));
    m_waveform = new Waveform();
    m_waveform->setCurrDisplayType(WHOLE);
    m_waveform->setWholeSampleList(UiUtil::convertStringToFloatList(m_note.voiceSampleData));
    m_waveform->setFixedHeight(33);
    //m_voiceShape = new QWidget();
    QSizePolicy spShape = m_waveform->sizePolicy();
    spShape.setHorizontalStretch(1);
    m_waveform->setSizePolicy(spShape);
    m_menuBtn = new DImageButton(m_bgWidget);
    m_menuBtn->setFixedSize(QSize(44, 44));
    m_menuBtn->setNormalPic(":/image/icon/normal/more_normal.svg");
    m_menuBtn->setHoverPic(":/image/icon/hover/more_hover.svg");
    m_menuBtn->setPressPic(":/image/icon/press/more_press.svg");
    m_voiceTimeLabel = new QLabel();
    m_voiceTimeLabel->setFixedSize(46, 20);
    m_voiceTimeLabel->setText(UiUtil::formatMillisecondToSecAndMil(m_note.voiceTime));

    m_hBoxLayout->addWidget(m_playingButton);
    m_hBoxLayout->addWidget(m_waveform);
    m_hBoxLayout->addSpacing(20);
    m_hBoxLayout->addWidget(m_voiceTimeLabel);
    m_hBoxLayout->addSpacing(10);
    m_hBoxLayout->addWidget(m_menuBtn);

    //m_hBoxLayout->addWidget(m_menuBtn);


}

void VoiceNoteItem::initConnection()
{
    connect(m_menuBtn, &DImageButton::clicked, this, &VoiceNoteItem::handleMenuBtnClicked);
    connect(m_playingButton, SIGNAL(pause()), this, SIGNAL(pausePlayingSignal()));
    connect(m_playingButton, SIGNAL(resume()), this, SLOT(handleResumePlaying()));

}

void VoiceNoteItem::handleMenuBtnClicked()
{
    QPoint pGlobal = m_menuBtn->mapToGlobal(QPoint(0,0));
    QPoint arrowPoint(pGlobal.x() + m_menuBtn->width() / 2, pGlobal.y() +m_menuBtn->height());
    QPoint pParent = m_menuBtn->mapTo(this, QPoint(0,0));
    emit menuBtnClicked(arrowPoint, pParent, this, m_note);
    //qDebug()<< "p.x: " << p.x() << ", p.y: " << p.y();
    //m_arrowMenu->show(p.x() + m_menuBtn->width() / 2, p.y() +m_menuBtn->height());
}

void VoiceNoteItem::handleStopPlay()
{
    m_playingButton->handleStop();
}

void VoiceNoteItem::handlePausePlay()
{
    m_playingButton->handlePause();
}

void VoiceNoteItem::handleResumePlaying()
{
//    QPoint itemPointToParent = this->mapToParent(QPoint(0,0));
//    QPoint waveformPointToParent(itemPointToParent.x() + m_waveform->x(), itemPointToParent.y());
    QRect waveformPoint = m_waveform->geometry();
    emit resumePlayingSignal(this, UiUtil::getRecordingVoiceFullPath(m_note.contentPath), waveformPoint);
}
