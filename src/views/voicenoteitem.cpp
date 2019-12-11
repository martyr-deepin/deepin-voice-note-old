#include "voicenoteitem.h"
#include "uiutil.h"
#include <DLabel>
#include <QGraphicsOpacityEffect>
#include <DApplicationHelper>
#include <QAction>
#include <DFontSizeManager>

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

int VoiceNoteItem::getRecodeTime()
{
    return m_note.voiceTime;
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

QRect VoiceNoteItem::getWaveRect()
{
    return m_waveform->geometry();
}

//Add start bug 2587
void VoiceNoteItem::VoicePlayOrPause()
{
    m_playingButton->VoicePlayOrPause();
}
//Add end bug 2587

void VoiceNoteItem::setPlayDisable()
{
    m_playingButton->setPlayDisable();
}

void VoiceNoteItem::setPlayEnable()
{
    m_playingButton->setPlayEnable();
}

void VoiceNoteItem::changeTheme()
{
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    //pb.setBrush(DPalette::Base, pb.color(DPalette::FrameBorder));
    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
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
    }
}

void VoiceNoteItem::onToDetalVoicePage()
{
    QString contant = m_textEdit->getText();
    emit sigToDetalVoicePage(contant);
}

//void VoiceNoteItem::onDetailButtonChanged(const bool isVisible)
//{

//    this->m_detailBtn->setVisible(isVisible);
//}

void VoiceNoteItem::onTextHeightChanged(int height)
{
    qDebug() << "VoiceNoteItem::onTextHeightChanged():"<<height;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceNoteItem::onTextHeightChanged():"), QString::number(height,10));
    int newHeight = 0;
    if(VOICE_TO_TEXT_MAX_HEIGHT < height)
    {
        newHeight = VOICE_TO_TEXT_MAX_HEIGHT - 7;
        m_detailBtn->setVisible(true);
    }
    else
    {
        newHeight = height + 5;
        m_detailBtn->setVisible(false);
    }
    //m_bgWidgetBydetailBtn->show();
    m_bgWidgetBytext->setFixedHeight(newHeight);
    m_bgWidgetBydetailBtn->setFixedHeight(newHeight);
    m_detailBtn->move(6,m_bgWidgetBydetailBtn->height() - m_detailBtn->height() - 13);
    //qDebug()<<"m_bgWidgetBydetailBtn->height:"<<m_bgWidgetBydetailBtn->height();
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_bgWidgetBydetailBtn->height:"), QString::number(m_bgWidgetBydetailBtn->height(),10));
    emit sigTextHeightChanged(newHeight,m_note.id);
}
//Add s 20191111
void VoiceNoteItem::setTextEditVal(QString txt)
{
    m_textEdit->setTextAndLineheight(txt);
}

void VoiceNoteItem::setTextEditAlignment(Qt::Alignment a)
{
    m_textEdit->setAlignment(a);
}
//Add e 20191111s
//3152 liuyang
void VoiceNoteItem::leaveEvent(QEvent *event)
{
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    //pb.setBrush(DPalette::Base, pb.color(DPalette::FrameBorder));
    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_bgWidget->setPalette(pb);
    return QWidget::leaveEvent(event);
}

void VoiceNoteItem::enterEvent(QEvent *event)
{
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    pb.setBrush(DPalette::Base, pb.color(DPalette::Light));
    m_bgWidget->setPalette(pb);
    return QWidget::enterEvent(event);
}
//3152 liuyang

void VoiceNoteItem::initUI()
{
    //Add e 20191111
    this->setFixedHeight(VOICENOTE_HEIGHT);



    m_bgWidget = new DFrame(this);
    DPalette pb = DApplicationHelper::instance()->palette(m_bgWidget);
    //pb.setBrush(DPalette::Base, pb.color(DPalette::FrameBorder));
    pb.setBrush(DPalette::Base, pb.color(DPalette::ItemBackground));
    m_bgWidget->setPalette(pb);
    //m_bgWidget->setFixedHeight(68);
    //m_bgWidget->setFixedHeight(173);
    m_timeLabel = new DLabel();
    m_itemLayout = new QVBoxLayout();
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    m_itemLayout->addSpacing(6);
    m_itemLayout->addWidget(m_timeLabel);
    m_itemLayout->addSpacing(2);
    m_itemLayout->addWidget(m_bgWidget);
    //m_itemLayout->addSpacing(6);   //Del 20191111
    m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);
    this->setLayout(m_itemLayout);
    QSizePolicy sp = m_bgWidget->sizePolicy();
    sp.setHorizontalStretch(1);
    m_bgWidget->setSizePolicy(sp);

    m_timeLabel->setObjectName("timeLabel");

    DFontSizeManager::instance()->bind(m_timeLabel,DFontSizeManager::T9);
    m_timeLabel->setText("   " + UiUtil::convertDateTime(m_note.createTime));
    m_timeLabel->setFixedHeight(16);

    m_bgWidget->setObjectName("widget");

    //playWidget
    m_bgWidgetByplay = new DWidget();
    m_bgWidgetByplay->setFixedHeight(68);

    //textWidget
    m_bgWidgetBytext = new DWidget();
    m_bgWidgetBytext->setFixedHeight(0);
//    m_bgWidgetBytext->raise();
//    DPalette pb2 = DApplicationHelper::instance()->palette(m_bgWidget);
//    pb2.setBrush(DPalette::Base, pb2.color(DPalette::TextWarning));

    m_ayoutBybgWidget = new QVBoxLayout(m_bgWidget);
    m_ayoutBybgWidget->setContentsMargins(0, 0, 0, 0);

    m_hBoxLayout = new QHBoxLayout(m_bgWidgetByplay);
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");


    m_playingButton = new PlayingButton(this);
    m_playingButton->setFixedSize(QSize(60, 60));
    m_waveform = new Waveform();
    m_waveform->setCurrDisplayType(WHOLE);
    m_waveform->setWholeSampleList(UiUtil::convertStringToFloatList(m_note.voiceSampleData));
    m_waveform->setFixedHeight(33);
    QSizePolicy spShape = m_waveform->sizePolicy();
    spShape.setHorizontalStretch(1);
    m_waveform->setSizePolicy(spShape);


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
                    m_bgWidget);
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
                    m_bgWidget);
    }

    m_voiceTimeLabel = new DLabel();
    m_voiceTimeLabel->setFixedSize(66, 30);//bug 3359
    m_voiceTimeLabel->setAlignment(Qt::AlignCenter);//bug 3359
    QPalette pe;
    pe.setColor(QPalette::WindowText,QColor(00,26,46));
    m_voiceTimeLabel->setPalette(pe);

    DFontSizeManager::instance()->bind(m_voiceTimeLabel,DFontSizeManager::T6);
    m_voiceTimeLabel->setText(UiUtil::formatMillisecondToSecAndMil(m_note.voiceTime));

    m_hBoxLayout->addSpacing(6);
    m_hBoxLayout->addWidget(m_playingButton);
    m_hBoxLayout->addSpacing(12);
    m_hBoxLayout->addWidget(m_waveform);
    m_hBoxLayout->addSpacing(20);
    m_hBoxLayout->addWidget(m_voiceTimeLabel);
    m_hBoxLayout->addSpacing(6);
    m_hBoxLayout->addWidget(m_menuBtn);
    m_hBoxLayout->addSpacing(6);

    m_hBoxLayoutBytext = new QHBoxLayout(m_bgWidgetBytext);
    m_hBoxLayoutBytext->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayoutBytext->setObjectName("horizontalLayout");

    //m_textEdit = new TextNoteEdit(m_bgWidgetBytext,m_noteCtr);
    m_textEdit = new VoiceToTextEdit(m_bgWidgetBytext);

    DFontSizeManager::instance()->bind(m_textEdit,DFontSizeManager::T8);
    //m_textEdit->document()->setDocumentMargin(6);
    m_textEdit->document()->setDocumentMargin(2);

    DStyle::setFocusRectVisible(m_textEdit,false);
    DPalette pl = DApplicationHelper::instance()->palette(m_textEdit);
    pl.setBrush(DPalette::Button, QColor(0,0,0,0));
    m_textEdit->setPalette(pl);
    //zhangya 3846
    //m_textEdit->setTextColor(pb.color(DPalette::LightLively));
    QColor hightTextColor = pb.highlight().color();
    hightTextColor.setAlpha(hightTextColor.alpha() + 20);
    m_textEdit->setTextColor(hightTextColor);
    //zhangya 3846
    m_textEdit->setFrameShape(QFrame::NoFrame);
    m_textEdit->setReadOnly(true);
    //m_textEdit->hide();
    m_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //todo  右边的button没有加
    //Add start ynbboy

    m_bgWidgetBydetailBtn = new DWidget(m_bgWidgetBytext);
    m_bgWidgetBydetailBtn->setFixedWidth(48);
    m_bgWidgetBydetailBtn->setFixedHeight(0);
    //m_bgWidgetBydetailBtn->setFixedSize(QSize(48,m_bgWidgetBytext->height()));
    if(themeType == DGuiApplicationHelper::LightType)
    {
        m_detailBtn = new MyRecodeButtons(
                    ":/image/icon/normal/detail-normal.svg",
                    ":/image/icon/press/detail-press.svg",
                    ":/image/icon/hover/detail-hover.svg",
                    "",
                    "",
                    QSize(44,44),
                    m_bgWidgetBydetailBtn
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
                    m_bgWidgetBydetailBtn
                );
    }

    m_detailBtn->setVisible(false);
    m_detailBtn->move(6,m_bgWidgetBydetailBtn->height());


    m_hBoxLayoutBytext->addSpacing(3);
    m_hBoxLayoutBytext->addWidget(m_textEdit);
    m_hBoxLayoutBytext->addSpacing(5);
    m_hBoxLayoutBytext->addWidget(m_bgWidgetBydetailBtn);
    m_hBoxLayoutBytext->addSpacing(8);

    m_ayoutBybgWidget->addWidget(m_bgWidgetByplay);
    m_ayoutBybgWidget->setSpacing(0);
    //m_ayoutBybgWidget->addSpacing(0); //ynbboy
    m_ayoutBybgWidget->addWidget(m_bgWidgetBytext);
    m_bgWidgetBytext->setVisible(false);
    //m_bgWidgetBydetailBtn->hide();
    //Add end ynbboy
    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &VoiceNoteItem::changeTheme);
    //Add e 20191111
}

void VoiceNoteItem::initConnection()
{
    connect(m_menuBtn, &QAbstractButton::pressed, this, &VoiceNoteItem::sig_menuBtnPressed);
    connect(m_menuBtn, &MyRecodeButtons::sigReleased, this, &VoiceNoteItem::handleMenuBtnClicked);
    connect(m_menuBtn, &MyRecodeButtons::sigReleased, this, &VoiceNoteItem::sig_menuBtnReleased);
    connect(m_menuBtn, SIGNAL(pressed()), this, SIGNAL(buttonClicled()));

    connect(m_detailBtn, SIGNAL(clicked()), this, SLOT(onToDetalVoicePage()));


    connect(m_playingButton, SIGNAL(pause()), this, SIGNAL(pausePlayingSignal()));
    connect(m_playingButton, SIGNAL(pause()), this, SIGNAL(buttonClicled()));
    connect(m_playingButton, SIGNAL(resume()), this, SLOT(handleResumePlaying()));
    connect(m_playingButton, SIGNAL(resume()), this, SIGNAL(buttonClicled()));

    connect(m_textEdit ,SIGNAL(sigTextHeightChanged(int)),this,SLOT(onTextHeightChanged(int))); //Add 20191111
    //connect(m_textEdit, &TextNoteEdit::sigDetailButtonChanged, this, &VoiceNoteItem::onDetailButtonChanged);
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
    emit resumePlayingSignal(this, UiUtil::getRecordingVoiceFullPath(m_note.contentPath), waveformPoint, m_note);  //Edit bug 2587
    //emit resumePlayingSignal(this, UiUtil::getRecordingVoiceFullPath(m_note.contentPath), waveformPoint);
}
//Add s 20191111
void VoiceNoteItem::setMenuBtnEnabled(bool enabled)
{
    if(enabled)
    {
        m_menuBtn->EnAbleBtn();
    }
    else
    {
        m_menuBtn->DisableBtn();
    }
}
//void VoiceNoteItem::setLineEditDisplay(bool disp)
//{
//    if (disp)
//    {
//         m_bgWidgetBytext->show();
//    }
//    else
//    {
//         m_bgWidgetBytext->hide();
//    }
//}
void VoiceNoteItem::setTextEditDisplay(bool disp)
{
    if (disp)
    {
         m_textEdit->show();
    }
    else {
         m_textEdit->hide();
    }
}
//Add e 20191111
//start add by yuanshuai 20191128 bug 3876
void VoiceNoteItem::setDocmentAligment(QTextOption op)
{
    m_textEdit->document()->setDefaultTextOption(op);
}
//end

int VoiceNoteItem::getLineHeight()
{
    if(nullptr != m_textEdit)
    {
        m_textEdit->getLineHeight();
    }
}
