#include "voicenoteitem.h"
#include "uiutil.h"
#include <DLabel>
#include <QGraphicsOpacityEffect>
#include <DApplicationHelper>

VoiceNoteItem::VoiceNoteItem(NOTE note, NoteController *noteCtr):m_note(note), m_noteCtr(noteCtr)
{
    initUI();
    initConnection();
}

VoiceNoteItem::~VoiceNoteItem()
{

}

void VoiceNoteItem::init()
{
    if(nullptr != m_timeLabel)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText,QColor(00,26,46));
        m_timeLabel->setPalette(pe);

        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        m_timeLabel->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.5);
    }
}

bool VoiceNoteItem::getwaveformPoint(QRect &rect)
{
    bool ret = false;
    if(nullptr != m_waveform)
    {
        rect = m_waveform->geometry();
        ret = true;
    }
    return ret;
}

int VoiceNoteItem::getNoteID()
{
    return m_note.id;
}

NOTE_TYPE VoiceNoteItem::getType()
{
    return m_note.noteType;
}

void VoiceNoteItem::clearWaveformContent()
{
    m_waveform->clearWave();
    m_waveform->emptyWave();
}

void VoiceNoteItem::onlySetResumeNoSig()
{
    m_playingButton->onlySetResumeForButton();
}

void VoiceNoteItem::setPlayDiseable()
{
    m_playingButton->setPlayDiseable();
}


void VoiceNoteItem::initUI()
{
    this->setFixedHeight(VOICENOTE_HEIGHT);
    this->setBlurEnabled(false);

    m_timeLabel = new DLabel();

    m_bgWidget = new DBlurEffectWidget();
    m_bgWidget->setFixedHeight(68);
    m_itemLayout = new QVBoxLayout();
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    m_itemLayout->addSpacing(6);
    m_itemLayout->addWidget(m_timeLabel);
    m_itemLayout->addSpacing(2);
    m_itemLayout->addWidget(m_bgWidget);
    m_itemLayout->addSpacing(6);
    m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);
    this->setLayout(m_itemLayout);
    QSizePolicy sp = m_bgWidget->sizePolicy();
    sp.setHorizontalStretch(1);
    m_bgWidget->setSizePolicy(sp);

    m_timeLabel->setObjectName("timeLabel");

    QFont timeLabelFont;
    timeLabelFont.setFamily("PingFangSC-Regular");
    timeLabelFont.setPointSize(8);
    m_timeLabel->setFont(timeLabelFont);
    m_timeLabel->setText("   " + UiUtil::convertDateTime(m_note.createTime));
    m_timeLabel->setFixedHeight(16);

    //m_bgWidget->setGeometry(QRect(0, 40, this->width(), 91));
    m_bgWidget->setObjectName("widget");
    m_bgWidget->setBlurRectXRadius(8);
    m_bgWidget->setBlurRectYRadius(8);

    QPalette pb;
    pb.setColor(QPalette::Background,QColor(00,00,00));
    m_bgWidget->setPalette(pb);
    m_bgWidget->setMaskAlpha(14);

    m_hBoxLayout = new QHBoxLayout(m_bgWidget);
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");

//    m_ctrlBtn = new DImageButton(m_bgWidget);
//    m_ctrlBtn->setFixedSize(QSize(40, 40));
//    m_ctrlBtn->setNormalPic(":/image/icon/normal/play_normal.svg");
//    m_ctrlBtn->setHoverPic(":/m_waveformimage/icon/hover/play_hover.svg");
//    m_ctrlBtn->setPressPic(":/image/icon/press/play_press.svg");

    m_playingButton = new PlayingButton();
    m_playingButton->setFixedSize(QSize(45, 45));
    m_waveform = new Waveform();
    m_waveform->setCurrDisplayType(WHOLE);
    m_waveform->setWholeSampleList(UiUtil::convertStringToFloatList(m_note.voiceSampleData));
    m_waveform->setFixedHeight(33);
    //m_voiceShape = new QWidget();
    QSizePolicy spShape = m_waveform->sizePolicy();
    spShape.setHorizontalStretch(1);
    m_waveform->setSizePolicy(spShape);


    m_menuBtn = new MenuButton(m_bgWidget);
    //m_menuBtn->setFlat(true);
    //m_menuBtn = new DImageButton(m_bgWidget);
    m_menuBtn->setFixedSize(QSize(40, 40));
    m_menuBtn->setIcon(QIcon(":/image/icon/normal/more_normal.svg"));
    m_menuBtn->setIconSize(QSize(20,20));
    DPalette pa = DApplicationHelper::instance()->palette(m_menuBtn);
    pa.setBrush(DPalette::Highlight, pa.color(DPalette::Base));
    m_menuBtn->setPalette(pa);
    //m_menuBtn->setBtnPalette();
//    m_menuBtn->setNormalPic(":/image/icon/normal/more_normal.svg");
//    m_menuBtn->setHoverPic(":/image/icon/hover/more_hover.svg");
//    m_menuBtn->setPressPic(":/image/icon/press/more_press.svg");
    m_voiceTimeLabel = new QLabel();
    m_voiceTimeLabel->setFixedSize(46, 20);
    QPalette pe;
    pe.setColor(QPalette::WindowText,QColor(00,26,46));
    m_voiceTimeLabel->setPalette(pe);
    QFont font;
    font.setFamily("Avenir-Book");
    font.setPixelSize(15);
    m_voiceTimeLabel->setFont(font);
    m_voiceTimeLabel->setText(UiUtil::formatMillisecondToSecAndMil(m_note.voiceTime));

    m_hBoxLayout->addSpacing(6);
    m_hBoxLayout->addWidget(m_playingButton);
    m_hBoxLayout->addWidget(m_waveform);
    m_hBoxLayout->addSpacing(20);
    m_hBoxLayout->addWidget(m_voiceTimeLabel);
    m_hBoxLayout->addSpacing(10);
    m_hBoxLayout->addWidget(m_menuBtn);
    m_hBoxLayout->addSpacing(6);

    //m_hBoxLayout->addWidget(m_menuBtn);


}

void VoiceNoteItem::initConnection()
{
    connect(m_menuBtn, &QAbstractButton::pressed, this, &VoiceNoteItem::sig_menuBtnPressed);
    connect(m_menuBtn, &QAbstractButton::pressed, this, &VoiceNoteItem::handleMenuBtnClicked);
    connect(m_menuBtn, &QAbstractButton::released, this, &VoiceNoteItem::sig_menuBtnReleased);

    //connect(m_menuBtn, &DImageButton::clicked, this, &VoiceNoteItem::handleMenuBtnClicked);
    connect(m_playingButton, SIGNAL(pause()), this, SIGNAL(pausePlayingSignal()));
    connect(m_playingButton, SIGNAL(resume()), this, SLOT(handleResumePlaying()));

    connect(m_menuBtn, SIGNAL(pressed()), this, SIGNAL(buttonClicled()));
    connect(m_playingButton, SIGNAL(resume()), this, SIGNAL(buttonClicled()));
    connect(m_playingButton, SIGNAL(pause()), this, SIGNAL(buttonClicled()));


}

void VoiceNoteItem::handleMenuBtnClicked()
{
    QPoint pGlobal = m_menuBtn->mapToGlobal(QPoint(0,0));
    QPoint arrowPoint(pGlobal.x() + m_menuBtn->width() / 2, pGlobal.y() +m_menuBtn->height());
    QPoint pParent = m_menuBtn->mapTo(this, QPoint(0,0));
    emit menuBtnClicked(arrowPoint, pParent, this, m_note);
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
