#include "rightview.h"
#include "textnoteitem.h"
#include "intancer.h"
#include "uiutil.h"
//#include <QVBoxLayout>
#include "consts.h"
#include <DArrowRectangle>
#include <DtkGuis>
#include <QPalette>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <DApplicationHelper>
#include <DFontSizeManager>
#include <QToolTip>

RightView::RightView()
{
    //m_pVoiceAudioDeviceWatcher = new VoiceAudioDeviceWatcher(this);
    m_currFolderId = -1;
    Intancer::get_Intancer()->initHeightForRight();
    initUI();
    initConnection();
    m_pVoiceVolumeWatcher = new voiceVolumeWatcher(this);

    m_pVoiceVolumeWatcher->start();
    connect(m_pVoiceVolumeWatcher, SIGNAL(sigRecodeState(bool)), this, SLOT(on_CheckRecodeCouldUse(bool)));

//    DTextEdit *pTextEdit = new DTextEdit(this);
//    pTextEdit->setFixedSize(QSize(100,100));
//    pTextEdit->move(0,0);
}

RightView::~RightView()
{
    m_pVoiceVolumeWatcher->stopWatch();
    QThread::currentThread()->msleep(500);
//    if(nullptr != m_pVoiceVolumethread)
//    {
//        m_pVoiceVolumethread->terminate();
//        //delete m_pVoiceVolumethread;

//    }
}

void RightView::initUI()
{


//    pa.setBrush(DPalette::Background, pa.color(DPalette::Base));

    initNoteList();
    this->resize(548,this->height());

    m_NoSearchResault = new DLabel(this);
    m_NoSearchResault->setText(QString(tr("无结果")));
//    QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T4);
//    m_NoSearchResault->setFont(labelFont);
    DFontSizeManager::instance()->bind(m_NoSearchResault,DFontSizeManager::T4);
//    QPalette pb = DApplicationHelper::instance()->palette(m_NoSearchResault);
//    pb.setBrush(DPalette::Text, pb.color(QPalette::));
//    m_NoSearchResault->setPalette(pb);
    m_NoSearchResault->setFixedSize(QSize(60,29));
    m_NoSearchResault->setAlignment(Qt::AlignCenter);
    m_NoSearchResault->move((this->width() - m_NoSearchResault->width())/2,(this->height() - m_NoSearchResault->height())/2);
    m_NoSearchResault->setVisible(false);

//    DSlider *pslider = new DSlider(Qt::Horizontal,this);
//    pslider->setGeometry(0, 0, 300, 50);


    //m_noticeNoAudioInputs = UiUtil::createConfirmDialog(QString(""), QString(tr("未检测到录音设备")), this);

}


void RightView::initConnection()
{
    //&RightView::addTextNote
    connect(m_noteListWidget, SIGNAL(addTextItem()), this, SLOT(addTextNote()));
    connect(m_noteListWidget, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
    //connect(m_noteListWidget, SIGNAL(currentRowChanged(int)), this, SIGNAL(OnCurrentRowChanged(int)));
    connect(m_noteListWidget, SIGNAL(sigBoardPress()), this, SIGNAL(sigBoardPress()));
    connect(m_noteListWidget, SIGNAL(sig_TextEditNotEmpty(bool)), this, SLOT(onAbleAddBtn(bool)));
    connect(m_noteListWidget, SIGNAL(sig_TextEditEmpty()), this, SLOT(onDisableAddBtn()));
    connect(m_noteListWidget, SIGNAL(sig_research()), this, SIGNAL(sig_research()));
    connect(m_noteListWidget, SIGNAL(sig_checkCurPageVoiceForDelete()), this, SLOT(oncheckCurPageVoiceForDelete()));
    connect(m_noteListWidget, SIGNAL(sigChangeCurFolderToTop(int)), this, SIGNAL(sigChangeCurFolderToTop(int)));



    //connect(m_noteListWidget, SIGNAL(sigHideViewAddTextButton()), this, SLOT(onViewAddTextHide()));

    connect(m_addVoiceBtn, &DFloatingButton::clicked, this, &RightView::handleStartRecord);
    connect(m_addVoiceBtn, &DFloatingButton::clicked, this, &RightView::TryToDisEditAllText);
    connect(m_addVoiceBtn, SIGNAL(sigHoverd()), this, SLOT(ShowRecodeTip()));

    //connect(m_addVoiceBtn, &DFloatingButton::clicked, m_noteListWidget, &RightNoteList::handleClickRecordButton);
//    connect(m_addVoiceBtn, &DImageButton::clicked, this, &RightView::handleStartRecord);
//    connect(m_addVoiceBtn, &DImageButton::clicked, m_noteListWidget, &RightNoteList::handleClickRecordButton);
    connect(m_recordPage, &RecordPage::finishRecord, this, &RightView::handleStopRecord);
    connect(m_recordPage, &RecordPage::cancelRecord, this, &RightView::handlecancelRecord);
    connect(m_recordPage, &RecordPage::buttonClicled, this, &RightView::TryToDisEditAllText);

    connect(Intancer::get_Intancer(), SIGNAL(sigShowViewAddTextButton()), this, SLOT(onViewAddTextShow()));
    connect(Intancer::get_Intancer(), SIGNAL(sigHideViewAddTextButton()), this, SLOT(onViewAddTextHide()));
    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &RightView::changeTheme);
    connect(m_noteListWidget, &RightNoteList::positionByfinishRecord, this, &RightView::handleStopRecord2); //ynb 20191109

    connect(m_noteListWidget, SIGNAL(sig_CheckFileExist()), this, SIGNAL(sigRvCheckFile()));    //by yuanshuai 20191120 2841
}


void RightView::initNoteList()
{
    m_FolderController = new FolderController();
    m_noteController = new NoteController();
//    m_noteListPage = new QWidget();
//    m_noteListPage->resize(548,m_noteListPage->height());

//    DPalette pb = DApplicationHelper::instance()->palette(m_noteListPage);
//    pb.setBrush(DPalette::Base, pb.color(DPalette::Base));
//    m_noteListPage->setPalette(pb);

//    m_noteListLayout = new QVBoxLayout();
//    m_noteListLayout->setContentsMargins(0, 0, 0, 0);

    m_noteListWidget = new RightNoteList(m_noteController);

    //m_noteListWidget->setFocusPolicy(Qt::NoFocus);
    //m_noteListLayout->addWidget(m_noteListWidget);
    //m_noteListLayout->addSpacing(1);

    QSizePolicy sp = m_noteListWidget->sizePolicy();
    sp.setVerticalStretch(1);
    //sp.setVerticalPolicy(QSizePolicy::Expanding);
    m_noteListWidget->setSizePolicy(sp);
    //qDebug()<<"m_noteListWidget width1:"<<m_noteListWidget->width();
    //m_noteListPage->setLayout(m_noteListLayout);
    //qDebug()<<"m_noteListWidget width2:"<<m_noteListWidget->width();
    QVBoxLayout *rightViewLayout = new QVBoxLayout();
    rightViewLayout->setContentsMargins(0, 0, 0, 0);
    //rightViewLayout->addWidget(m_noteListPage);
    rightViewLayout->addWidget(m_noteListWidget);

    //Intancer::get_Intancer()->setViewHeightForRightList(m_noteListPage->height());
    Intancer::get_Intancer()->setViewHeightForRightList(m_noteListWidget->height());


    m_BottomBoard = new DWidget(this);
    m_BottomBoard->setFocusPolicy(Qt::ClickFocus);
    //m_BottomBoard->setFrameRounded(false);
    DPalette pa = DApplicationHelper::instance()->palette(m_BottomBoard);
    pa.setBrush(DPalette::Background, pa.color(DPalette::Base));
    m_BottomBoard->setAutoFillBackground(true);
    //pa.setBrush(DPalette::Base, QColor(0,0,0,0));

    //m_BottomBoard->setFixedHeight(150);
    m_BottomBoard->setFixedHeight(76);
    m_BottomBoard->setFixedWidth(this->width());
    m_BottomBoard->setPalette(pa);
    rightViewLayout->setSpacing(0);
    rightViewLayout->addWidget(m_BottomBoard);
    this->setLayout(rightViewLayout);

    initRecordStackedWidget();

    m_AddBtnBoard = new DWidget(this);
    m_AddBtnBoard->setFocusPolicy(Qt::ClickFocus);
    DPalette pc = DApplicationHelper::instance()->palette(m_AddBtnBoard);
    //pc.setBrush(DPalette::Base, pc.color(DPalette::Base));
    pc.setBrush(DPalette::Background, pc.color(DPalette::Base));
    m_AddBtnBoard->setAutoFillBackground(true);

    m_AddBtnBoard->setFixedHeight(75);
    m_AddBtnBoard->setFixedWidth(this->width() - 10);
    m_AddBtnBoard->setPalette(pc);
    m_AddBtnBoard->move(0,this->height());

    m_AddButtonLocked = new AddTextBtn(this);
    m_AddButtonLocked->init();
    //m_AddButtonLocked->setFixedWidth(548);
    m_AddButtonLocked->move(6,this->height() - 78);
    connect(m_AddButtonLocked, SIGNAL(addTextItem()), this, SLOT(addTextNote()));
    connect(m_AddButtonLocked, SIGNAL(addTextItem()), this, SLOT(onDisableAddBtn()));
    m_AddButtonLocked->setVisible(false);
    m_AddButtonLocked->setFocusPolicy(Qt::NoFocus);

}

void RightView::initRecordStackedWidget()
{
    m_recordStackedWidget = new QStackedWidget(this);
    //m_recordStackedWidget->setFixedSize(QSize(548,64));
    m_recordStackedWidget->setFixedSize(QSize(548,76));

    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        m_addVoiceBtn = new MyRecodeButtons(
                    ":/image/icon/normal/circlebutton_voice.svg",
                    ":/image/icon/press/circlebutton_voice_press.svg",
                    ":/image/icon/hover/circlebutton_voice_hover.svg",
                    ":/image/icon/disabled/circlebutton_voice_disabled.svg",
                    ":/image/icon/focus/circlebutton_voice_focus.svg",
                    QSize(68,68),
                    this);
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        m_addVoiceBtn = new MyRecodeButtons(
                    ":/image/icon_dark/normal/voice_normal_dark.svg",
                    ":/image/icon_dark/press/voice_press_dark.svg",
                    ":/image/icon_dark/hover/voice_hover_dark.svg",
                    ":/image/icon_dark/disabled/voice_disabled_dark.svg",
                    ":/image/icon_dark/focus/voice_focus_dark.svg",
                    QSize(68,68),
                    this);
    }
    else {
        m_addVoiceBtn = new MyRecodeButtons(
                    ":/image/icon/normal/circlebutton_voice.svg",
                    ":/image/icon/press/circlebutton_voice_press.svg",
                    ":/image/icon/hover/circlebutton_voice_hover.svg",
                    ":/image/icon/disabled/circlebutton_voice_disabled.svg",
                    ":/image/icon/focus/circlebutton_voice_focus.svg",
                    QSize(68,68),
                    this);
    }
    m_addVoiceBtn->DisableBtn();
//    m_addVoiceBtn = new DFloatingButton(this);
//    m_addVoiceBtn->setFixedSize(QSize(58,58));
//    m_addVoiceBtn->setIcon(QIcon(":/image/icon/normal/circlebutton_voice.svg"));
//    m_addVoiceBtn->setIconSize(QSize(34,34));

//    DPalette pb = DApplicationHelper::instance()->palette(m_addVoiceBtn);
//    pb.setBrush(DPalette::Highlight, QColor(0x00FD5E5E));
//    m_addVoiceBtn->setPalette(pb);

    m_recordPage = new RecordPage();
    DPalette palette = DApplicationHelper::instance()->palette(m_recordPage);
    palette.setBrush(DPalette::Background, palette.color(DPalette::Base));
    //palette.setColor(palette.Background, QColor(0, 0, 0));
    m_recordPage->setPalette(palette);
    m_recordStackedWidget->addWidget(m_addVoiceBtn);
    m_recordStackedWidget->addWidget(m_recordPage);
    m_recordStackedWidget->setCurrentIndex(0);
    m_recordStackedWidget->setFixedSize(QSize(m_addVoiceBtn->width(),m_recordStackedWidget->height()));
    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
    //m_recordStackedWidget->setFixedWidth(m_addVoiceBtn->width());
    //qDebug()<<"m_recordStackedWidget x y:"<<m_recordStackedWidget->x()<<" "<<m_recordStackedWidget->y();
    //m_recordStackedWidget->move(0,0);

//    qDebug()<<"RightView width:"<<this->width();
//    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,this->height() - 10 - m_recordStackedWidget->height());
//    m_recordStackedWidget->show();
    m_addVoiceBtn->setVisible(false);
}

void RightView::onShowNoResult()
{
    m_NoSearchResault->setVisible(true);
    m_AddButtonLocked->setVisible(false);
    m_AddBtnBoard->setVisible(false);
}

void RightView::handleSelFolderChg(int folderId)
{
    //stopAllNeedStop
    m_noteListWidget->stop();

    m_noteListWidget->delAllEmptyText();
    m_currFolderId = folderId;
    updateNoteList();
    if(-1 != folderId)
    {
        m_addVoiceBtn->setVisible(true);
    }
    else
    {
        m_addVoiceBtn->setVisible(false);
    }
}

void RightView::handleSearchNote(int folderId, QString searchKey)
{
    m_currFolderId = folderId;

    searchNoteList(searchKey);
    if(searchKey.isEmpty())
    {
        m_NoSearchResault->setVisible(false);
    }
    m_addVoiceBtn->setVisible(true);
}

//only for button add
void RightView::addTextNote()
{
    NOTE note;
    note.folderId = m_currFolderId;
    note.noteType = NOTE_TYPE::TEXT;
    note.createTime = QDateTime::currentDateTime();
    note.contentText = "";

    m_noteController->addNote(note);
    //==== start add 20191105  bug2162
    if (!UiUtil::autoAddEditTxt(note))
    {
        qDebug() << "error: add file error";
    }
    //==== end add 20191105  bug2162

    addNoteToNoteList(note);
    //updateNoteList();

//    TextNoteItem *item = (TextNoteItem*)(m_noteListWidget->itemWidget(m_noteListWidget->item(m_noteListWidget->count() - 1)));
//    item->changeToEditMode();

//    m_leftFolderView->setCurrentRow(0);


}

//only for button add
void RightView::addNoteToNoteList(NOTE note)
{
    m_NoSearchResault->setVisible(false);

    if(TEXT == note.noteType)
    {
        m_noteListWidget->fouceOutAllTextItem();
    }

    m_noteListWidget->addWidgetItem(true,note, "");
    if(VOICE == note.noteType)
    {
        Intancer::get_Intancer()->addHeightForRightList(VOICENOTE_HEIGHT);
    }
    else if(TEXT == note.noteType)
    {
        Intancer::get_Intancer()->addHeightForRightList(TEXTNOTE_HEIGHT);

    }
    qDebug()<<"rightlistheight:"<<m_noteListWidget->height();
    qDebug()<<"rightViewheight:"<<this->height();
    m_noteListWidget->scrollToBottom();
//    if(m_noteListWidget->verticalScrollBar()->isVisible())
//    {
//        onViewAddTextShow();
//    }
//    else
//    {
//        onViewAddTextHide();
//    }
   emit sigChangeCurFolderToTop(note.folderId);
}

void RightView::updateNoteList()
{
    //qDebug()<<"before clear m_noteListWidget width:"<<m_noteListWidget->width();
    //onViewAddTextHide();
    Intancer::get_Intancer()->clearHeightForRightList();
    m_noteListWidget->delAddTextBtn();
    m_noteListWidget->clear();
    //qDebug()<<"after clear m_noteListWidget width:"<<m_noteListWidget->width();
    if (m_currFolderId > 0)
    {
        m_noteListWidget->addAddTextBtn();
        Intancer::get_Intancer()->addHeightForRightList(ADDBUTTON_HEIGHT_HEIGHT);
        m_noteController->checkCleanDataBaseForVoiceByForderId(m_currFolderId);
        QList<NOTE> noteList = m_noteController->getNoteListByFolderId(m_currFolderId);
        if(noteList.size() > 0)
        {
            //m_NoSearchResault->setVisible(false);
        }
        else
        {
            //m_NoSearchResault->setVisible(true);
        }


        for (int i = 0; i < noteList.size(); i++)
        {
            m_noteListWidget->addWidgetItem(false, noteList.at(i), "");

            if(VOICE == noteList.at(i).noteType)
            {
                Intancer::get_Intancer()->addHeightForRightList(VOICENOTE_HEIGHT);
            }
            else if(TEXT == noteList.at(i).noteType)
            {
                Intancer::get_Intancer()->addHeightForRightList(TEXTNOTE_HEIGHT);
            }
        }

        m_noteListWidget->setCurrentRow(noteList.size());
        //m_noteListWidget->scrollToBottom();
    }

//    if(m_noteListWidget->verticalScrollBar()->isVisible())
//    {
//        if(!Intancer::get_Intancer()->getViewAddTextButtonShowFlag())
//        {
//            onViewAddTextShow();
//        }
//    }
}

void RightView::searchNoteList(QString searchKey)
{
    //onViewAddTextHide();
    Intancer::get_Intancer()->clearHeightForRightList();
    m_noteListWidget->delAddTextBtn();
    m_noteListWidget->clear();
    if (m_currFolderId > 0)
    {
        QList<NOTE> noteList;
        if (searchKey.isEmpty())
        {
            noteList = m_noteController->getNoteListByFolderId(m_currFolderId);
        }
        else
        {
            noteList = m_noteController->searchNote(m_currFolderId, searchKey);
        }

        m_noteListWidget->addAddTextBtn();
        if(0 == noteList.size())
        {
            onShowNoResult();
        }
        else {
            m_NoSearchResault->setVisible(false);
        }
        for (int i = 0; i < noteList.size(); i++)
        {
            m_noteListWidget->addWidgetItem(false, noteList.at(i), searchKey);
            if(VOICE == noteList.at(i).noteType)
            {
                Intancer::get_Intancer()->addHeightForRightList(VOICENOTE_HEIGHT);
            }
            else if(TEXT == noteList.at(i).noteType)
            {
                Intancer::get_Intancer()->addHeightForRightList(TEXTNOTE_HEIGHT);
            }
        }
        m_noteListWidget->scrollToBottom();
    }
}

void RightView::updateFromDetal(int ID)
{
    for(int i = 0; i < m_noteListWidget->count(); i++)
    {
        QListWidgetItem* pitem = m_noteListWidget->item(i);
        TextNoteItem* pWidget = (TextNoteItem*)m_noteListWidget->itemWidget(pitem);
        if(ID == pWidget->getId())
        {
            pWidget->readFromDatabase();
            break;
        }
    }
}

void RightView::stopAllPlayback()
{
    m_noteListWidget->stop();
}

void RightView::cancleRecord()
{
    m_recordPage->exitRecord();
    emit stopRecoiding();
}

void RightView::checkAndDeleteEmptyTextNoteFromDatabase()
{
    m_noteListWidget->delAllEmptyText();
}

int RightView::getFolderCount()
{
    return m_noteListWidget->count();
}

void RightView::initTxtFilesForDir()
{
    if((nullptr != m_FolderController) && (nullptr != m_noteController))
    {
        QList<FOLDER> folderlist = m_FolderController->getFolderList();
        for(int i = 0; i < folderlist.count(); i++)
        {
            QList<NOTE> noteList = m_noteController->getNoteListByFolderId(folderlist.at(i).id);
            for(int j = 0; j < noteList.count(); j++)
            {
                if(noteList.at(j).noteType == TEXT)
                {
                    UiUtil::autoAddEditTxt(noteList.at(j));
                }
            }
        }
    }
}

void RightView::OnlySaveRecord()
{
    m_recordPage->stopRecord();
}

void RightView::handleStartRecord()
{
    //QList<QAudioDeviceInfo>  list = QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioInput);

    QMultimedia::AvailabilityStatus audioinputs;
    m_recordPage->getAudioStates(audioinputs);
//    if(QMultimedia::AvailabilityStatus::Available == audioinputs)
//    {
        m_noteListWidget->handleClickRecordButton();
        m_recordStackedWidget->setCurrentIndex(1);
        m_recordStackedWidget->setFixedSize(QSize(548,m_recordStackedWidget->height()));
        m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
        //m_recordStackedWidget->move(0,this->height() - m_recordStackedWidget->height());
        m_recordPage->startRecord();

        emit startRecoding();
//    }
//    else
//    {
//        m_noticeNoAudioInputs->show();
//    }
}

void RightView::TryToDisEditAllText()
{
    m_noteListWidget->fouceOutAllTextItem();
}

//typedef struct
//{
//    int id;
//    NOTE_TYPE noteType;
//    QString contentText;
//    QString contentPath;
//    int voiceTime;
//    int folderId;
//    QDateTime createTime;
//}NOTE;

//typedef struct
//{
//    QString voicePath;
//    int voiceLength;
//}VOICE_INFO;
void RightView::handleStopRecord(VOICE_INFO voiceInfo)
{
//    NOTE voiceNote;
//    voiceNote.noteType = NOTE_TYPE::VOICE;
//    voiceNote.contentPath = voiceInfo.voicePath;
//    voiceNote.voiceTime = voiceInfo.voiceLength;
//    voiceNote.voiceSampleData = voiceInfo.voiceSampleData;
//    voiceNote.folderId = m_currFolderId;
//    voiceNote.createTime = QDateTime::currentDateTime();
//    if (!m_noteController->addNote(voiceNote))
//    {
//        qDebug() << "handleStopRecord： add voice note error！";
//    }
//    m_recordStackedWidget->setCurrentIndex(0);
//    m_recordStackedWidget->setFixedSize(QSize(m_addVoiceBtn->width(),m_recordStackedWidget->height()));
//    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
//    addNoteToNoteList(voiceNote);
//    emit stopRecoiding();
//    //updateNoteList();

    m_voiceinfo = voiceInfo;                                             //ynb 20191109
    m_noteListWidget->getDurtimgByRecodefinised(voiceInfo.voicePath);    //ynb 20191109
}


void RightView::handlecancelRecord()
{
    m_recordStackedWidget->setCurrentIndex(0);
    m_recordStackedWidget->setFixedSize(QSize(m_addVoiceBtn->width(),m_recordStackedWidget->height()));
    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
    emit stopRecoiding();
}

void RightView::handleClearNote()
{
    //onViewAddTextHide();
    Intancer::get_Intancer()->clearHeightForRightList();
    m_noteListWidget->delAddTextBtn();
    m_noteListWidget->clear();
    m_currFolderId = -1;
    m_addVoiceBtn->setVisible(false);
}

void RightView::OnCurrentRowChanged(int curRow)
{
    qDebug()<<"curRow:"<<curRow;
    m_noteListWidget->setCurrentRow(1);
}

void RightView::OnAllFolderGone()
{
    //cancleRecord();
    handleClearNote();
    m_recordStackedWidget->setVisible(false);
    m_AddButtonLocked->setVisible(false);
    m_AddBtnBoard->setVisible(false);
}

void RightView::OnAddAFolder()
{
    m_recordStackedWidget->setVisible(true);
    m_NoSearchResault->setVisible(false);
}

void RightView::onDisableAddBtn()
{
    if(nullptr != m_AddButtonLocked)
    {
        m_AddButtonLocked->setDisableBtn(true);
    }
}

void RightView::onAbleAddBtn(bool changed)
{
    if(nullptr != m_AddButtonLocked)
    {
        m_AddButtonLocked->setDisableBtn(false);
    }
}

void RightView::onViewAddTextShow()
{
    if((nullptr != m_AddButtonLocked) && (nullptr != m_noteListWidget))
    {
        m_AddButtonLocked->setVisible(true);
        m_AddBtnBoard->setVisible(true);
        //m_AddButtonLocked->setVisible(false);
        m_noteListWidget->listAddTextHide();
    }
}

void RightView::onViewAddTextHide()
{
    if((nullptr != m_AddButtonLocked) && (nullptr != m_noteListWidget))
    {
        m_AddButtonLocked->setVisible(false);
        m_AddBtnBoard->setVisible(false);
        m_noteListWidget->listAddTextShow();
    }
}

void RightView::changeTheme()
{
    DPalette pa = DApplicationHelper::instance()->palette(m_BottomBoard);
    pa.setBrush(DPalette::Background, pa.color(DPalette::Base));
    //m_BottomBoard->setAutoFillBackground(true);
    m_BottomBoard->setPalette(pa);

    DPalette palette = DApplicationHelper::instance()->palette(m_recordPage);
    palette.setBrush(DPalette::Background, palette.color(DPalette::Base));
    //palette.setColor(palette.Background, QColor(0, 0, 0));
    m_recordPage->setPalette(palette);

    DPalette pc = DApplicationHelper::instance()->palette(m_AddBtnBoard);
    pc.setBrush(DPalette::Background, pc.color(DPalette::Base));
    m_AddBtnBoard->setPalette(pc);

    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();

    if(themeType == DGuiApplicationHelper::LightType)
    {
        if(nullptr != m_addVoiceBtn)
        {
            m_addVoiceBtn->setPicChange(
                    ":/image/icon/normal/circlebutton_voice.svg",
                    ":/image/icon/press/circlebutton_voice_press.svg",
                    ":/image/icon/hover/circlebutton_voice_hover.svg",
                    ":/image/icon/disabled/circlebutton_voice_disabled.svg",
                    ":/image/icon/focus/circlebutton_voice_focus.svg"
                        );
        }

    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        if(nullptr != m_addVoiceBtn)
        {
            m_addVoiceBtn->setPicChange(
                    ":/image/icon_dark/normal/voice_normal_dark.svg",
                    ":/image/icon_dark/press/voice_press_dark.svg",
                    ":/image/icon_dark/hover/voice_hover_dark.svg",
                    ":/image/icon_dark/disabled/voice_disabled_dark.svg",
                    ":/image/icon_dark/focus/voice_focus_dark.svg"
                    );
        }

    }

}

void RightView::oncheckCurPageVoiceForDelete()
{
    updateNoteList();
}

void RightView::on_CheckRecodeCouldUse(bool coulduse)
{
    if(coulduse)
    {
        //m_pVoiceVolumeWatcher->stopWatch();
        m_addVoiceBtn->EnAbleBtn();
    }
    else
    {
        m_addVoiceBtn->DisableBtn();
    }
}

void RightView::ShowRecodeTip()
{
//    DPalette pa = DApplicationHelper::instance()->palette(m_addVoiceBtn);
//    pa.setBrush(DPalette::ToolTipText, pa.color(DPalette::ToolTipText));

//    m_addVoiceBtn->setPalette(pa);
    m_addVoiceBtn->setToolTip(QString(tr("未检测到录音设备")));
//    QPoint pGlobal = m_addVoiceBtn->mapToGlobal(QPoint(0,0));
//    QToolTip::showText(QPoint(pGlobal.x() + m_addVoiceBtn->width() * 3/4,pGlobal.y() - 8), QString(tr("未检测到录音设备")));


//    m_pNotRecordToolTip = new DToolTip(QString(tr("未检测到录音设备")));
////    QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T8);
////    m_pNotRecordToolTip->setFont(labelFont);
//    DPalette pb = DApplicationHelper::instance()->palette(m_pNotRecordToolTip);
////    pb.setBrush(DPalette::Text, QColor(255,0,0,255));
////    pb.setBrush(DPalette::Text, pb.color(DPalette::ToolTipText));
////    pb.setBrush(DPalette::ToolTipText, QColor(255,0,0,255));
////    pb.setBrush(DPalette::ToolTipText, pb.color(DPalette::ToolTipText));
////    pb.setBrush(DPalette::ToolTipBase, pb.color(DPalette::ToolTipBase));
//    m_pNotRecordToolTip->setPalette(pb);
//    m_pNotRecordToolTip->show(QPoint(pGlobal.x() + m_addVoiceBtn->width() * 3/4,pGlobal.y() - 8),1500);

}

// start ynb 20191109
void RightView::handleStopRecord2(qint64 position)
{
    NOTE voiceNote;
    int voiceLength = 0;
    voiceNote.noteType = NOTE_TYPE::VOICE;
    voiceNote.contentPath = m_voiceinfo.voicePath;
    //voiceNote.voiceTime = voiceInfo.voiceLength;
    voiceNote.voiceTime = int(position);
    voiceNote.voiceSampleData = m_voiceinfo.voiceSampleData;
    voiceNote.folderId = m_currFolderId;
    voiceNote.createTime = QDateTime::currentDateTime();
    if (!m_noteController->addNote(voiceNote))
    {
        qDebug() << "handleStopRecord： add voice note error！";
    }
    m_recordStackedWidget->setCurrentIndex(0);
    m_recordStackedWidget->setFixedSize(QSize(m_addVoiceBtn->width(),m_recordStackedWidget->height()));
    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
    addNoteToNoteList(voiceNote);
    emit stopRecoiding();
    //updateNoteList();
}
// end ynb 20191109

void RightView::resizeEvent(QResizeEvent * event)
{
    if(nullptr != m_recordStackedWidget)
    {
        qDebug()<<"RightView width:"<<this->width();
        qDebug()<<"m_recordStackedWidget width:"<<m_recordStackedWidget->width();
        m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,this->height() - m_recordStackedWidget->height() - 5);
        qDebug()<<"m_recordStackedWidget x y:"<<m_recordStackedWidget->x()<<" "<<m_recordStackedWidget->y();
        m_recordStackedWidget->show();


        m_AddButtonLocked->move(6,this->height() - 78 - m_AddButtonLocked->height());
        //m_AddButtonLocked->move((this->width() - m_AddButtonLocked->width())/2,this->height() - 78 - m_AddButtonLocked->height());

        m_AddButtonLocked->resize(this->width() - 15,m_AddButtonLocked->height());
        qDebug()<<"m_AddButtonLocked width:"<<m_AddButtonLocked->width();
        qDebug()<<"rightView width:"<<this->width();
        m_AddBtnBoard->setFixedWidth(this->width() - 10);
        m_AddBtnBoard->move(0,m_AddButtonLocked->y() + 11);
        m_BottomBoard->setFixedWidth(this->width());

        qDebug()<<"rightlistheight:"<<m_noteListWidget->height();
        qDebug()<<"rightViewheight:"<<this->height();

        //Intancer::get_Intancer()->setViewHeightForRightList(m_noteListPage->height());
        Intancer::get_Intancer()->setViewHeightForRightList(m_noteListWidget->height());

//        if(m_noteListWidget->verticalScrollBar()->isVisible())
//        {
//            if(!Intancer::get_Intancer()->getViewAddTextButtonShowFlag())
//            {
//                onViewAddTextShow();
//            }
//        }
//        else
//        {
//            if(Intancer::get_Intancer()->getViewAddTextButtonShowFlag())
//            {
//                onViewAddTextHide();
//            }
//        }
    }

    if(nullptr != m_NoSearchResault)
    {
        m_NoSearchResault->move((this->width() - m_NoSearchResault->width())/2,(this->height() - m_NoSearchResault->height())/2);
    }

    if(nullptr != m_noteListWidget)
    {
        m_noteListWidget->resize(this->width(),m_noteListWidget->height());
        qDebug()<<"RightView width:"<<this->width();
        qDebug()<<"m_noteListWidget width:"<<this->m_noteListWidget->width();
    }

}
