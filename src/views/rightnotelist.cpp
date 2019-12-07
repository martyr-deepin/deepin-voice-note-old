#include "rightnotelist.h"
#include "textnoteitem.h"
#include "voicenoteitem.h"
#include "intancer.h"
#include <QDebug>
#include <uiutil.h>
#include <DFileDialog>
#include <DToast>
#include <DApplication>
#include <DMessageBox>
#include <QMessageBox>
#include <QScrollBar>
#include <QStandardPaths>
#include <QFileInfo>
#include <DApplicationHelper>
#include <QPainter>
#include <QCursor>
#include <QShortcut>  //Add bug 2587
#include <workercontroller.h>



MMenu::MMenu(QWidget *parent)
{
    //this->setFixedSize(QSize(162,100));
}

MMenu::~MMenu()
{

}

void MMenu::leaveEvent(QEvent* event)
{
    emit sigMMenu();
    return QMenu::leaveEvent(event);
}
void MMenu::paintEvent(QPaintEvent *event)
{
    QMenu::paintEvent(event);
}


RightNoteList::RightNoteList(NoteController *noteController) : m_currPlayingItem(nullptr)
  , m_defaultTxtName("文本.TXT")
  //, m_defaultTxtPath("/home/deepin/Desktop")
  , m_defaultAudioName("语音.MP3")
  , m_defaultAudioPath("/home/deepin/Desktop")
  , m_arrowButtonPressed(false)
  , m_actionHoverd(false)
  , m_asrStatusFlg(false) //Add 20191111
  , m_textEditNewHeight(0) //Add 20191111
{
    duringTime = 0;
    m_Recodefinised = false;  //ynb 20191109
    m_IsSliderBarReleased = false; //ynb 20191109
    m_addTextBtn = nullptr;
    m_arrowMenu = nullptr;
    m_contextMenu = nullptr;
    m_saveAsAction = nullptr;
    m_delAction = nullptr;
    m_textClicked = false;
    m_textChanged = false;
    m_textGetFocus = false; //Add bug 2587
    m_voiceOperation = false; //Add bug 2587
    m_asrAction = nullptr;           //Add 20191111
    m_voiceNoteItem = nullptr;       //Add 20191111
    m_currSelItemByasr = nullptr;    //Add 20191111
    m_voiceNoteItemByasr = nullptr;    //Add 20191111
    m_asrNetWorkErrDialog = nullptr; //Add 20191111
    m_asrlimitErrDialog = nullptr;  //Add 20191111
    m_spaceItem = nullptr;
    m_defaultTxtPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    this->workController = WorkerController::getInstance();

    Intancer::get_Intancer()->clearHeightForRightList();
    initUI();
    initConnection();
}

RightNoteList::~RightNoteList()
{
    Intancer::get_Intancer()->clearHeightForRightList();
}

void RightNoteList::createDArrowMenu()
{
    if(nullptr == m_contextMenu && nullptr == m_saveAsAction && nullptr == m_delAction)
    //if(nullptr == m_arrowMenu && nullptr == m_contextMenu && nullptr == m_saveAsAction && nullptr == m_delAction)
    {
        m_contextMenu = new MMenu;
        m_saveAsAction = new QAction(tr("Save As TXT"),this);
        m_delAction = new QAction(tr("Delete"),this);
        m_asrAction = new QAction(tr("Voice to Text"),this);
        m_contextMenu->addAction(m_asrAction);  //Add 20191111
        m_contextMenu->addAction(m_saveAsAction);
        m_contextMenu->addAction(m_delAction);
        //m_contextMenu->setFixedSize(QSize(162,89));
        m_contextMenu->setVisible(false);

        connect(m_contextMenu, SIGNAL(sigMMenu()), this, SLOT(OnLeaveContentMenu()));
        connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
        connect(m_delAction, SIGNAL(hovered()), this, SLOT(OnActionHoverd()));
        connect(m_saveAsAction, SIGNAL(triggered(bool)), this, SLOT(handleSaveAsItem(bool)));
        connect(m_saveAsAction, SIGNAL(hovered()), this, SLOT(OnActionHoverd()));

        connect(m_asrAction, SIGNAL(triggered(bool)), this, SLOT(handleAsrAsItem())); //Add 20191111
        connect(m_asrAction, SIGNAL(hovered()), this, SLOT(OnActionHoverd())); //Add 20191111
    }
}

void RightNoteList::destroyDArrowMenu()
{
    if(nullptr != m_contextMenu && nullptr != m_saveAsAction && nullptr != m_delAction)
    //if(nullptr != m_arrowMenu && nullptr != m_contextMenu && nullptr != m_saveAsAction && nullptr != m_delAction)
    {
        disconnect(m_contextMenu, SIGNAL(sigMMenu()), this, SLOT(OnLeaveContentMenu()));
        disconnect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
        disconnect(m_delAction, SIGNAL(hovered()), this, SLOT(OnActionHoverd()));
        disconnect(m_saveAsAction, SIGNAL(triggered(bool)), this, SLOT(handleSaveAsItem(bool)));
        disconnect(m_saveAsAction, SIGNAL(hovered()), this, SLOT(OnActionHoverd()));

        delete m_saveAsAction;
        m_saveAsAction = nullptr;

        delete m_delAction;
        m_delAction = nullptr;

        delete m_contextMenu;
        m_contextMenu = nullptr;

//        delete m_arrowMenu;
//        m_arrowMenu = nullptr;
    }
}

void RightNoteList::showDArrowMenu(int x, int y, NOTE_TYPE type)
{
    if(nullptr != m_contextMenu && nullptr != m_saveAsAction && nullptr != m_delAction)
    //if(nullptr != m_arrowMenu && nullptr != m_contextMenu && nullptr != m_saveAsAction && nullptr != m_delAction)
    {
        //m_arrowMenu->setVisible(true);
        m_contextMenu->setVisible(true);
        if (type == NOTE_TYPE::TEXT)
        {
            m_contextMenu->removeAction(m_asrAction);   //Add 20191111
            m_saveAsAction->setText(QString(tr("Save As TXT")));
        }
        else
        {
            //Add s 20191111
            m_contextMenu->addAction(m_asrAction);
            m_contextMenu->addAction(m_saveAsAction);
            m_contextMenu->addAction(m_delAction);
            if (m_asrStatusFlg)
            {
                m_asrAction->setEnabled(false);
                //qDebug() << "srActionEnabled: false";
                UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("srActionEnabled: false"), QString("srActionEnabled: false"));
            }
            else
            {
                m_asrAction->setEnabled(true);
            }
            //Add e 20191111
            m_saveAsAction->setText(QString(tr("Save As MP3")));
            //m_contextMenu->setFixedSize(QSize(162,109)); //Add 20191111
        }
        m_contextMenu->move(x - m_contextMenu->width()/2,y);
        //m_arrowMenu->move(x,y);
    }
}

void RightNoteList::hideDArrowMenu()
{
    if(nullptr != m_contextMenu && nullptr != m_saveAsAction && nullptr != m_delAction)
    //if(nullptr != m_arrowMenu && nullptr != m_contextMenu && nullptr != m_saveAsAction && nullptr != m_delAction)
    {
        //m_arrowMenu->setVisible(false);
        m_contextMenu->setVisible(false);
        m_contextMenu->move(-500,-500);
        //m_arrowMenu->move(-500,-500);
    }
}

void RightNoteList::initUI()
{
    this->setFrameShape(QListWidget::NoFrame);
    this->resize(548,this->height());

    m_addTextBtn = nullptr;

    createDArrowMenu();

    m_delConfirmDialog = UiUtil::createChooseDialog(QString(""), QString(tr("Are you sure you want to delete this note?")), nullptr, QString(tr("Cancel")), QString(tr("Delete")));
    //m_delConfirmDialog = UiUtil::createChooseDialog(QString(""), QString(tr("您确定要删除这条记事项吗？")), nullptr, QString(tr("取消")), QString(tr("删除")));
    m_saveFileEndDialog = UiUtil::createConfirmDialog(QString(""), QString(tr("")), this);
    //by yuanshuai 20191120 2841
    //m_noticeNotExistDialog = UiUtil::createConfirmDialog(QString(""), QString(tr("该语音记事项已删除")), this);
    //end
    m_asrlimitErrDialog = UiUtil::createConfirmDialog(QString(""), QString(tr("Cannot convert this voice note, as notes over 20 minutes are not supported at present.")), this);  //Add 20191111
    //m_asrlimitErrDialog = UiUtil::createConfirmDialog(QString(""), QString(tr("无法转写此条语音笔记，暂仅支持20分钟内的语音笔记。")), this);  //Add 20191111
    m_fileExistsDialog = new FileExistsDialog();
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_myslider = new MySlider(Qt::Horizontal, this);
    //m_TestSlider = new DSlider(Qt::Horizontal, this);
    //m_TestSlider->setVisible(false);
    //m_myslider = new MyCustomSlider(Qt::Horizontal, this);

    //m_myslider->setFixedSize(350, 70);
    //m_myslider->setHandleType(MySlider::HandleType::SharpHandler);
    m_myslider->setPageStep(SLIDER_PAGE_STEP);
    m_myslider->setGeometry(0, 0, 350, m_myslider->m_defaultHeight);
    m_myslider->hide();

    DPushButton *button = new DPushButton(QString(tr("Try Again"))); //Add 20191111
    //DPushButton *button = new DPushButton(QStringLiteral("重新转写")); //Add 20191111
    m_asrOtherErrDMessage = UiUtil::createAsrErrorDF(this,button);  //Add 20191111
    connect(button, SIGNAL(clicked()), this, SLOT(asrOtherErrBtnClick()));  //Add 20191111

    DPushButton *button2 = new DPushButton(QString(tr("Try Again"))); //Add 20191111
    //DPushButton *button2 = new DPushButton(QStringLiteral("重新转写")); //Add 20191111
    m_asrNetWorkErrDialog = UiUtil::createAsrNetWorkErrDialog(this,button2);  //Add 20191111
    connect(button2, SIGNAL(clicked()), this, SLOT(asrOtherErrBtnClick()));  //Add 20191111

    this->verticalScrollBar()->setSingleStep(10);//2260
    qApp->installEventFilter(this);

}
void RightNoteList::initConnection()
{
    connect(this->workController, &WorkerController::mediaPlayerCreated, this, &RightNoteList::onMediaPlayerCreated);
    this->workController->createMediaPlayer();

    connect(m_delConfirmDialog, &DDialog::buttonClicked, this, &RightNoteList::handleDelDialogClicked);
    connect(m_delConfirmDialog, &DDialog::closed, this, &RightNoteList::handleCloseDialogClicked);
    //start notify by yuanshuai 20191119
    //connect(m_noticeNotExistDialog, &DDialog::buttonClicked, this, &RightNoteList::sig_checkCurPageVoiceForDelete);
    //connect(m_noticeNotExistDialog, &DDialog::closed, this, &RightNoteList::sig_checkCurPageVoiceForDelete);
    //end
    connect(m_myslider, SIGNAL(sliderPressed()), this, SLOT(handleSliderPressed()));  //ynb 20191109
    connect(m_myslider, SIGNAL(sliderReleased()), this, SLOT(handleSliderReleased()));
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(handleVScrollBarChanged(int)));
    connect(&m_AiServiceController, SIGNAL(AsrResultReq(AsrResult)),this,SLOT(AsrResultResp(AsrResult))); //Add 20191111
}

//3550-3547-3528
void RightNoteList::addWidgetItem(bool isAddByButton, NOTE note, QString searchKey, int textEditCursorPos)
{
    if(note.noteType == NOTE_TYPE::TEXT)
    {
        TextNoteItem *textItem = new TextNoteItem(isAddByButton, note, m_noteController, searchKey);

        //qDebug() << "textItem->m_textEdit->toPlainText(): " << textItem->m_textEdit->toPlainText();
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("textItem->m_textEdit->toPlainText():"), textItem->m_textEdit->toPlainText());

        connect(textItem, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(textEditTrueClicked(NOTE)), this, SLOT(onCheckEditState(NOTE)));
        connect(textItem, SIGNAL(textEditClicked(NOTE)), this, SLOT(onCheckEditState(NOTE)));
        connect(textItem, SIGNAL(menuBtnClicked(QPoint, QPoint, QWidget *, NOTE)), this, SLOT(handleMenuBtnClicked(QPoint, QPoint, QWidget *, NOTE)));
        connect(textItem, SIGNAL(sig_menuBtnPressed()), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(sig_menuBtnReleased()), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(sig_menuBtnPressed()), this, SLOT(handleMenuBtnPressed()));
        connect(textItem, SIGNAL(sig_menuBtnReleased()), this, SLOT(handleMenuBtnReleased()));
        connect(textItem, SIGNAL(sig_TextEditNotEmpty(bool)), this, SLOT(onTextChangedFlagChange(bool)));
        connect(textItem, SIGNAL(sig_TextEditNotEmpty(bool)), this, SLOT(onAbleAddBtn(bool)));
        connect(textItem, SIGNAL(sig_TextEditNotEmpty(bool)), this, SIGNAL(sig_TextEditNotEmpty(bool)));
        connect(textItem, SIGNAL(sig_TextEditEmpty()), this, SLOT(onDisableAddBtn()));
        connect(textItem, SIGNAL(sig_TextEditEmpty()), this, SIGNAL(sig_TextEditEmpty()));
        connect(textItem, SIGNAL(sig_fouceOutAndEditEmpty(NOTE)), this, SLOT(onCallDelDialog(NOTE)));
        //connect(textItem, SIGNAL(sig_ItemTimeChanged(NOTE)), this, SLOT(onSortItemByTime(NOTE)));
        connect(textItem, SIGNAL(buttonClicled()), this, SLOT(onfouceOutAllTextItem()));
        //connect(this, SIGNAL(sigBoardPress()), textItem, SLOT(tryToFouceout()));

        connect(textItem, SIGNAL(SigTextEditGetFocus(NOTE)), this, SLOT(onTextEditGetFocus(NOTE))); //Add bug 2587
        connect(textItem, SIGNAL(SigTextEditOutFocus(NOTE)), this, SLOT(onTextEditOutFocus(NOTE))); //Add bug 2587

        //qDebug() << "textItem->m_textEdit->toPlainText(): " << textItem->m_textEdit->toPlainText();
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("textItem->m_textEdit->toPlainText():"), textItem->m_textEdit->toPlainText());

        QListWidgetItem *item=new QListWidgetItem();
        //QListWidgetItem *item=new QListWidgetItem(this);
        //item->setSizeHint(QSize(this->width(),92));
        //item->setSizeHint(QSize(this->width(),123));  //orig
        item->setSizeHint(QSize(this->width(),TEXTNOTE_HEIGHT));  //orig
        int count = this->count();
        this->insertItem(count - 1,item);
        this->setItemWidget(item, textItem);
        textItem->init();

        if(isAddByButton)
        {
            //textItem->changeToEditMode();
            textItem->changeToEditMode(textEditCursorPos);//3550-3547-3528
            adjustWidgetItemWidth();
        }

        //textItem->changeToEditMode();
    }
    else if(note.noteType == NOTE_TYPE::VOICE){
        VoiceNoteItem *voiceItem = new VoiceNoteItem(note, m_noteController);
        connect(voiceItem, SIGNAL(menuBtnClicked(QPoint, QPoint, QWidget *, NOTE)), this, SLOT(handleMenuBtnClicked(QPoint, QPoint, QWidget *, NOTE)));
        connect(voiceItem, SIGNAL(sig_menuBtnPressed()), this, SLOT(handleMenuBtnPressed()));
        connect(voiceItem, SIGNAL(sig_menuBtnReleased()), this, SLOT(handleMenuBtnReleased()));


        connect(voiceItem, SIGNAL(pausePlayingSignal()), this, SLOT(pause()));
        connect(voiceItem, SIGNAL(resumePlayingSignal(VoiceNoteItem *, QString, QRect, NOTE)), this, SLOT(play(VoiceNoteItem *, QString, QRect, NOTE))); //Edit  bug 2587
        //connect(voiceItem, SIGNAL(resumePlayingSignal(VoiceNoteItem *, QString, QRect)), this, SLOT(play(VoiceNoteItem *, QString, QRect)));
        connect(voiceItem, SIGNAL(buttonClicled()), this, SLOT(onfouceOutAllTextItem()));
        connect(voiceItem, SIGNAL(sigToDetalVoicePage(QString)), this, SIGNAL(sigToDetalVoicePage(QString)));

        connect(Intancer::get_Intancer(), &Intancer::sigDisAbleReplay, voiceItem, &VoiceNoteItem::setPlayDisable);
        connect(Intancer::get_Intancer(), &Intancer::sigEnAbleReplay, voiceItem, &VoiceNoteItem::setPlayEnable);

        connect(this, &RightNoteList::sig_EnablePlaybackButton, voiceItem, &VoiceNoteItem::setPlayEnable);

        if(this->isLoadedAudioPlayer) {
            voiceItem->setPlayEnable();
        }
        else {
            voiceItem->setPlayDisable();
        }

        QListWidgetItem *item=new QListWidgetItem();
        item->setSizeHint(QSize(this->width(), VOICENOTE_HEIGHT)); //Edit 20191111
//        item->setSizeHint(QSize(this->width(), 98)); //DEl ynbboy
        this->insertItem(this->count() - 1,item);
        this->setItemWidget(item, voiceItem);
        voiceItem->init();
        //DEl start ynbboy
//        //Add s 20191111
//        QString asrTxt = Intancer::get_Intancer()->getAsrTxt(note.folderId,note.id);
//        if (asrTxt !="")
//        {
//            voiceItem->setTextEditDisplay(true);
//            voiceItem->setTextEditVal(asrTxt);
//            item->setSizeHint(QSize(this->width(), VOICENOTE_HEIGHT + m_textEditNewHeight)); //ynbboy
//            voiceItem->setFixedHeight(VOICENOTE_HEIGHT + m_textEditNewHeight); //ynbboy
//            voiceItem->m_bgWidgetBytext->move(6,55); //ynbboy
//        }
//        //Add e 20191111
        //DEl end ynbboy
        if(isAddByButton)
        {
            adjustWidgetItemWidth();
        }
    }
}

void RightNoteList::addSpaceItem()
{
    if(nullptr == m_spaceItem)
    {
        m_spaceItem = new DWidget();
        m_spaceItem->setFixedSize(QSize(10,30));
        QListWidgetItem *item=new QListWidgetItem();
        item->setSizeHint(QSize(m_spaceItem->size()));
        this->addItem(item);
        this->setItemWidget(item, m_spaceItem);
    }
}

void RightNoteList::delSpaceItem()
{
    if(nullptr != m_spaceItem)
    {
        QListWidgetItem *item = takeItem(count() - 1);
        if(nullptr != item)
        {
            m_spaceItem = (DWidget*)itemWidget(item);
            delete m_spaceItem;
            m_spaceItem = nullptr;
        }
    }
}

void RightNoteList::addAddTextBtn()
{
//    if(nullptr == m_addTextBtn)
//    {
//        m_addTextBtn = new AddTextBtn(this);
//        m_addTextBtn->init();
//        connect(m_addTextBtn, SIGNAL(addTextItem()), this, SIGNAL(addTextItem()));
//        connect(m_addTextBtn, SIGNAL(addTextItem()), this, SLOT(onDisableAddBtn()));
//        QListWidgetItem *item=new QListWidgetItem();
//        item->setSizeHint(QSize(this->width(),m_addTextBtn->height()));
//        this->addItem(item);
//        this->setItemWidget(item, m_addTextBtn);
//    }
}

void RightNoteList::delAddTextBtn()
{
//    if(nullptr != m_addTextBtn)
//    {
//        QListWidgetItem *item = takeItem(count() - 1);
//        if(nullptr != item)
//        {
//            disconnect(m_addTextBtn, SIGNAL(addTextItem()), this, SIGNAL(addTextItem()));
//            disconnect(m_addTextBtn, SIGNAL(addTextItem()), this, SLOT(onDisableAddBtn()));
//            m_addTextBtn = (AddTextBtn*)itemWidget(item);
//            delete m_addTextBtn;
//            m_addTextBtn = nullptr;
//        }
//    }
}

void RightNoteList::listAddTextShow()
{
//    if(nullptr != m_addTextBtn)
//    {
//        m_addTextBtn->setFixedHeight(ADDBUTTON_HEIGHT_HEIGHT);
//    }
}

void RightNoteList::listAddTextHide()
{
//    if(nullptr != m_addTextBtn)
//    {
//        m_addTextBtn->setFixedHeight(0);
//    }
}

void RightNoteList::fouceOutAllTextItem()
{
    int count = this->count();
    for(int i = 0; i < count - 1; i++)
    {
        TextNoteItem *pTextItem = (TextNoteItem *)this->itemWidget(this->item(i));
        if(TEXT == pTextItem->getType())
        {
            pTextItem->tryToFouceout();
        }
    }

//    if(m_textChanged && m_textClicked)
//    {
//        emit sigChangeCurFolderToTop();
//    }
//    m_textChanged = false;
//    m_textClicked = false;
}

void RightNoteList::delAllEmptyText()
{
    this->fouceOutAllTextItem();
//    for(int i = 0; i < this->count(); i++)
//    {

//    }
//m_noteController->deleteNote(m_currSelNote)
}

// start ynb 20191109
void RightNoteList::getDurtimgByRecodefinised(QString filepath)
{
    if(nullptr != audioPlayer)
    {
        m_Recodefinised = true;
        audioPlayer->setMedia(QUrl::fromLocalFile(filepath));
        //audioPlayer->setMedia(QUrl::fromLocalFile(""));
    }
}
// end ynb 20191109

//bool RightNoteList::eventFilter(QObject *o, QEvent *e)
//{
//    if(0 == o->objectName().compare(QString("QMainWindowClassWindow")))
//    {
//        switch (e->type())
//        {
//            case QEvent::MouseButtonRelease:
//            if((!m_arrowButtonPressed)&&(!m_actionHoverd))
//            {
//                hideDArrowMenu();
//                m_actionHoverd = false;
//            }
//            break;
//            case QEvent::MouseButtonPress:
//                emit sigBoardPress();
//            break;
//        }
//    }

//    return DListWidget::eventFilter(o,e);
//}

void RightNoteList::paintEvent(QPaintEvent *event)
{

}

void RightNoteList::resizeEvent(QResizeEvent * event)
{
    DListWidget::resizeEvent(event);
    adjustWidgetItemWidth();
    if(nullptr != m_currPlayingItem && nullptr != m_myslider)
    {
        QRect rect = m_currPlayingItem->getWaveRect();
        QPoint waveformPoint = m_currPlayingItem->mapTo(this, QPoint(rect.x(), rect.y()));
        m_myslider->setGeometry( waveformPoint.x() - m_myslider->getHandlerWidth() / 2, waveformPoint.y() - 27, rect.width() + m_myslider->getHandlerWidth(), m_myslider->m_defaultHeight);
        //m_TestSlider->setGeometry( waveformPoint.x(), waveformPoint.y() - 27, rect.width(), m_myslider->m_defaultHeight);
    }
    //2719 fix liuyang
    if(m_currClickTextNote.noteType == TEXT)
    {
        onCheckEditState(m_currClickTextNote);
    }
    //2719 fix liuyang
}

void RightNoteList::wheelEvent(QWheelEvent *e)
{
    //qDebug()<<"RightNoteList::wheelEvent";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("RightNoteList::wheelEvent"), QString("RightNoteList::wheelEvent"));
    if(Intancer::get_Intancer()->getWantScrollRightListFlag())
    {
        DListWidget::wheelEvent(e);
    }
}

void RightNoteList::handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note)
{
    bool flag = Intancer::get_Intancer()->getTryToDelEmptyTextNote();
    //if(nullptr == m_arrowMenu)
    if(!flag)
    {
        if(!m_contextMenu->isVisible())
        //if(!m_arrowMenu->isVisible())
        {
            QPoint itemGlobalPoint = textNoteItem->mapTo(this, menuArrowPointToItem);
            m_currSelItem= this->itemAt(itemGlobalPoint);
            m_currSelNote = note;

            //如果音频文件不存在
            if(VOICE == note.noteType)
            {
                if(!UiUtil::checkFileExist(note.contentPath))
                {
                    if(nullptr != m_contextMenu)
                    {
                        m_saveAsAction->setDisabled(true);
                    }
                }
                else {
                    m_saveAsAction->setDisabled(false);
                }
            }
            else {
                m_saveAsAction->setDisabled(false);
            }

            // Zhangya 2019.11.23 bug fix 3085
            VoiceNoteItem* Voiceitem = qobject_cast<VoiceNoteItem*>(textNoteItem);
//            if(Voiceitem)
//            {
//                QPoint pGlobal = Voiceitem->m_menuBtn->mapToGlobal(QPoint(0,0));
//                QPoint arrowPoint(pGlobal.x() + Voiceitem->m_menuBtn->width() / 2, pGlobal.y() +Voiceitem->m_menuBtn->height());
//                menuArrowPointGlobal = arrowPoint;
//                QCursor::setPos(menuArrowPointGlobal);
//                Voiceitem->m_menuBtn->setBtnToNormal();
//            }

//            TextNoteItem* itemText = qobject_cast<TextNoteItem*>(textNoteItem);
//            if(itemText)
//            {
//                QPoint pGlobal = itemText->m_menuBtn->mapToGlobal(QPoint(0,0));
//                QPoint arrowPoint(pGlobal.x() + itemText->m_menuBtn->width() / 2, pGlobal.y() +itemText->m_menuBtn->height());
//                menuArrowPointGlobal = arrowPoint;
//                QCursor::setPos(menuArrowPointGlobal);
//                itemText->m_menuBtn->setBtnToNormal();
//            }
            // Zhangya 2019.11.23 bug fix 3085
            showDArrowMenu(menuArrowPointGlobal.x(), menuArrowPointGlobal.y(),note.noteType);
            //qDebug()<<"handleMenuBtnClicked show";
            UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("handleMenuBtnClicked show"), QString("handleMenuBtnClicked show"));
        }
        else {
            hideDArrowMenu();
    //        m_arrowMenu->setVisible(false);
    //        m_contextMenu->setVisible(false);
            m_actionHoverd = false;
            //qDebug()<<"handleMenuBtnClicked hide";
            UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("handleMenuBtnClicked hide"), QString("handleMenuBtnClicked hide"));
        }
    }

}


void RightNoteList::handleDelItem(bool)
{
    m_delConfirmDialog->show();
    hideDArrowMenu();
//    m_arrowMenu->setVisible(false);
//    m_contextMenu->setVisible(false);
    m_actionHoverd = false;
//    return;
}

void RightNoteList::OnActionHoverd()
{
    m_actionHoverd = true;
}

void RightNoteList::OnLeaveContentMenu()
{
    m_actionHoverd = false;
    //handleVScrollBarChanged(-1);
}

void RightNoteList::handleVScrollBarChanged(int value)
{
    if((nullptr != m_myslider)&&(nullptr != m_currPlayingItem))
    {
        if (!m_myslider->isHidden())
        {
            QRect rect;
            if(m_currPlayingItem->getwaveformPoint(rect))
            {
                QPoint waveformPoint = m_currPlayingItem->mapTo(this, QPoint(rect.x(), rect.y()));
                //qDebug()<<"waveformPoint.y():"<<waveformPoint.y();
                UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("waveformPoint.y():"), QString::number(waveformPoint.y(),10));
                m_myslider->move(m_myslider->x(),waveformPoint.y() - 27);
            }
        }
    }

//    QWidget* ptmpWidget = this->itemWidget(this->item(this->count() -  1));
//    if(ptmpWidget != nullptr)
//    {
//        if(value == 0)
//        {
//            adjustWidgetItemWidth();
//        }
//        else
//        {
//            ptmpWidget->setFixedSize(QSize(this->width() + 5,ptmpWidget->height()));
//        }
//    }
}

void RightNoteList::onDisableAddBtn()
{
//    if(nullptr != m_addTextBtn)
//    {
//        m_addTextBtn->setDisableBtn(true);
//    }
}

void RightNoteList::onAbleAddBtn(bool changed)
{
//    if(nullptr != m_addTextBtn)
//    {
//        m_addTextBtn->setDisableBtn(false);
//    }
}

void RightNoteList::onTextChangedFlagChange(bool changed)
{
//    qDebug() << "changed: " << changed;
//    qDebug() << "this->count(): " << this->count();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("changed:"), QString::number(changed));
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->count():"), QString::number(this->count(),10));

//    if(m_textClicked)
//    {
//        m_textChanged = changed;
//        //emit sigChangeCurFolderToTop();
//    }

    //liuyang 3550 3547 3528
    if(changed)
    {
       if(this->count() > 2)
       {
           TextNoteItem *senderWidget = static_cast<TextNoteItem *>(sender());
           TextNoteItem *pLasteWidget = static_cast<TextNoteItem *>(this->itemWidget(this->item(this->count() - 2)));
           if(pLasteWidget != senderWidget)
           {
               NOTE note = senderWidget->getTextNote();
               int cursorPos = senderWidget->getTextEditCursorPos();//3550-3547-3528
               QListWidgetItem *senderItem = getListItemById(note.id);
               this->removeItemWidget(senderItem);
               delete senderItem;
               senderItem = nullptr;

               addWidgetItem(true, note, Intancer::get_Intancer()->getSearchKeywords(), cursorPos); //3550-3547-3528
               this->scrollToBottom();
           }
       }
       emit sigChangeCurFolderToTop(m_currSelNote.folderId);
    }
    //liuyang 3550 3547 3528
}

void RightNoteList::onCallDelDialog(NOTE textNote)
{
    m_currSelNote = textNote;
    m_currSelItem = getListItemById(textNote.id);

    if(nullptr != m_currSelItem)
    {
        //m_delConfirmDialog->show();
        Intancer::get_Intancer()->setTryToDelEmptyTextNote(true);

        handleDelDialogClicked(1,"");
    }
}

void RightNoteList::onCheckEditState(NOTE note)
{
    int count = this->count();
    for(int i = 0; i < count - 1; i++)
    {
        TextNoteItem *pTextItem = (TextNoteItem *)this->itemWidget(this->item(i));
        if((note.id != pTextItem->getId()) && (note.noteType == pTextItem->getType()))
        {
            pTextItem->tryToFouceout();
        }
    }

    m_currClickTextNote = note; //2719 fix liuyang
//    m_textClicked = true;
//    if(m_textChanged && m_textClicked)
//    {

        //emit sigChangeCurFolderToTop(m_currClickTextNote.folderId);//liuyang 3550 3547 3528

//    }
//    m_textChanged = false;
//    //m_textClicked = false;
}

void RightNoteList::onfouceOutAllTextItem()
{
    this->fouceOutAllTextItem();
}

//s ynbboy 20191109
void RightNoteList::getduration(qint64 position)
{
    if(m_Recodefinised)
    {
       m_Recodefinised = false;
       duringTime = position;
       emit positionByfinishRecord(position);
    }
}
//e ynbboy 20191109

void RightNoteList::OnlyTryToFouceOutEveryText()
{
    int count = this->count();
    for(int i = 0; i < count - 1; i++)
    {
        TextNoteItem *pTextItem = (TextNoteItem *)this->itemWidget(this->item(i));
        if(TEXT == pTextItem->getType())
        {
            pTextItem->tryToFouceout();
        }
    }
}

//Add start bug 2587
bool RightNoteList::shortcutsDelete()
{
    //按选中的item进行删除处理，暂时不对应。
    //        bool IsSelItemExist = false;
    //        for(int i =0; i <this->count()-1;++i)
    //        {
    //            if (this->item(i)->isSelected())
    //            {
    //                m_currSelItem = this->item(i);
    //                IsSelItemExist = true;
    //                break;
    //            }
    //        }
    //        if (IsSelItemExist == true)
    //        {
    //             m_delConfirmDialog->show();
    //        }
    bool ret = false;
    //qDebug()<<"m_textGetFocus:"<< m_textGetFocus;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_textGetFocus:"), QString::number(m_textGetFocus));
    m_currSelItem = getListItemById(m_currSelNote.id);
    if (m_currSelNote.noteType == NOTE_TYPE::TEXT)
    {
        if (m_textGetFocus)
        {
            //Del start 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)
//            TextNoteItem *item = (TextNoteItem*)this->itemWidget(m_currSelItem);
//            QString txt = item->m_textEdit->getText();
//            if (txt!="")
//            {
//                m_textGetFocus = false;
//                m_delConfirmDialog->show();
//            }
            //Del end 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)
            ret = true;
        }
    }
    else
    {
        if (m_voiceOperation)
        {
            m_voiceOperation =false;
            m_delConfirmDialog->show();
            ret = true;
        }

    }
    return ret;
}
void RightNoteList::VoicePlayOrPause()
{
   if (m_currPlayingItem != nullptr)
   {
        m_currPlayingItem->VoicePlayOrPause();
   }
}
void RightNoteList::onTextEditGetFocus(NOTE note)
{
        m_currSelNote = note;
        m_textGetFocus = true;
}
void RightNoteList::onTextEditOutFocus(NOTE note)
{
        m_currSelNote = note;
        m_textGetFocus = false;
}
//Add end bug 2587

void RightNoteList::onMediaPlayerCreated(QMediaPlayer* mediaPlayer)
{
    //qDebug() << "RightNoteList::onMediaPlayerCreated()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("RightNoteList::onMediaPlayerCreated():"), QString("RightNoteList::onMediaPlayerCreated():"));

    this->audioPlayer = mediaPlayer;

    this->audioPlayer->setNotifyInterval(200);
    this->isLoadedAudioPlayer = true;

    //connect(audioPlayer, &QMediaPlayer::stateChanged, this, &RightNoteList::handlePlayingStateChanged);
    connect(audioPlayer, &QMediaPlayer::positionChanged, this, &RightNoteList::handleAudioPositionChanged);
    connect(audioPlayer, &QMediaPlayer::durationChanged, this, &RightNoteList::getduration);

    emit sig_EnablePlaybackButton();
}

void RightNoteList::handleSaveAsItem(bool)
{
    hideDArrowMenu();
//    m_arrowMenu->setVisible(false);
//    m_contextMenu->setVisible(false);
    m_actionHoverd = false;

    SAVE_INFO saveInfo;
    saveInfo.note = m_currSelNote;
    if (TEXT == m_currSelNote.noteType)
    {
        saveInfo.windowTitle = QString(tr("Save as TXT"));
        //saveInfo.windowTitle = QString(tr("另存为TXT"));
        saveInfo.fileExtension = QString(".txt");
    }
    else
    {
        saveInfo.windowTitle = QString(tr("Save as MP3"));
        //saveInfo.windowTitle = QString(tr("另存为MP3"));
        saveInfo.fileExtension = QString(".mp3");
    }
    showFileDialog(saveInfo);

}
// Add s 20191111
void RightNoteList::TextHeightChanged(int newHeight)
{
    m_textEditNewHeight = newHeight;
}
void RightNoteList::asrOtherErrBtnClick()
{
    m_asrNetWorkErrDialog->hide();
    m_asrOtherErrDMessage->hide();
    //    handleAsrAsItem(); //Del 4297
        AsrStart(1); //Add 4297
}
//Add start 4297
void RightNoteList::handleAsrAsItem()
{
    AsrStart(0);
}
void RightNoteList::setAsrErrDialogHide()
{
    m_asrNetWorkErrDialog->hide();
    m_asrOtherErrDMessage->hide();
}
//Add end 4297
//void RightNoteList::handleAsrAsItem() //Del 4297
void RightNoteList::AsrStart(int type)  //Add 4297
{
    if (&m_AiServiceController != nullptr)
    {
        //Add start 4297
        if (type == 1)
        {
            m_currSelItem = m_currSelItembyReasr;
            m_currSelNote = m_currSelNoteByReasr;
        }
        //Add end 4297
        //转写限制
        if(m_currSelNote.voiceTime > ASR_LIMIT_MILLISECOND)
        {
            m_asrlimitErrDialog->show();
        }
        else
        {
            //获取当前voiceNoteItem
            m_voiceNoteItem = (VoiceNoteItem *)this->itemWidget(m_currSelItem);

            //保存当前要转写的Item
            m_currSelItemByasr =  m_currSelItem;
            m_voiceNoteItemByasr = m_voiceNoteItem;
            m_currSelNoteByasr  = m_currSelNote;  //Add 3878
            connect(m_voiceNoteItem ,SIGNAL(sigTextHeightChanged(int)),this,SLOT(TextHeightChanged(int))); //Add 20191111

            //设定选中的菜单按钮不可用
            m_voiceNoteItem->setMenuBtnEnabled(false);
            //转写状态:设定为开始
            m_asrStatusFlg = true;
            //转写开始文字edit显示
            m_voiceNoteItem->setTextEditDisplay(true);
            m_voiceNoteItem->setTextEditVal(tr("Converting voice to text"));  //ynbboy
            //start add by yuanshuai 20191128 bug 3876
            //m_voiceNoteItem->setTextEditAlignment(Qt::AlignCenter);
            m_voiceNoteItem->setDocmentAligment(QTextOption(Qt::AlignHCenter));
            //end
            //m_voiceNoteItem->setTextEditVal(tr("正在转为文字..."));  //ynbboy

            m_currSelItem->setSizeHint(QSize(this->width(),VOICENOTE_HEIGHT + m_textEditNewHeight));  //orig
            m_voiceNoteItem->setFixedHeight(VOICENOTE_HEIGHT + m_textEditNewHeight);
            Intancer::get_Intancer()->delHeightForRightList(VOICENOTE_HEIGHT);
            m_tmpHeightForVoiceToText = VOICENOTE_HEIGHT + m_textEditNewHeight;
            Intancer::get_Intancer()->addHeightForRightList(m_tmpHeightForVoiceToText);
           // m_voiceNoteItemByasr->m_bgWidgetBytext->move(6,55); //ynbboy
            m_voiceNoteItemByasr->m_bgWidgetBydetailBtn->hide(); //ynbboy
            m_voiceNoteItemByasr->m_bgWidgetBytext->setVisible(true);
            //通知mainPage转写开始  mainPage里设置leftView不可用

            if(nullptr != m_currPlayingItem)
            {
                int playRow = 0;
                getRowByID(m_currPlayingItem->getNoteID(),VOICE,playRow);

                int voiceToTextRow = 0;
                getRowByID(m_voiceNoteItemByasr->getNoteID(),VOICE,voiceToTextRow);

                if(voiceToTextRow < playRow)
                {
                    int movement = m_tmpHeightForVoiceToText - VOICENOTE_HEIGHT;
                    changeSliderPosByHand(-movement);
                }
            }

            emit asrStart();
            //转写接口调用
            //Edit start 3878
//            m_AiServiceController.startAsr(m_currSelNote.contentPath,m_currSelNote.voiceTime,"","");
            m_AiServiceController.startAsr(m_currSelNoteByasr.contentPath,m_currSelNoteByasr.voiceTime,"","");
            //Edit end 3878
        }
    }
}
void RightNoteList::AsrResultResp(AsrResult clsResult)
{
//    qDebug() << "code:" << clsResult.code;
//    qDebug() << "descInfo:" <<clsResult.descInfo;
//    qDebug() << "failType:" <<clsResult.failType;
//    qDebug() << "status:" <<clsResult.status;
//    qDebug() << "txt:" <<clsResult.txt;
//    qDebug() << "ErrorMsg:" <<clsResult.ErrorMsg;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("code:"), clsResult.code);
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("descInfo:"), clsResult.descInfo);
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("failType:"), clsResult.failType);
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("status:"), clsResult.status);
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("txt:"), clsResult.txt);
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("ErrorMsg:"), clsResult.ErrorMsg);
    //设定选中的菜单按钮可用
    m_voiceNoteItemByasr->setMenuBtnEnabled(true);
    //转写状态:设定为结束
    m_asrStatusFlg = false;

    //转写开始文字edit隐藏
//    m_voiceNoteItem->setLineEditDisplay(false);
    if (clsResult.code == "000000" && clsResult.status == "4")
    //if ((clsResult.code == "000000" && clsResult.status == "4"))
    {
        //转写结束文字edit显示
//        m_voiceNoteItem->setTextEditDisplay(true);
        //转写文字设定
        //clsResult.txt = "字edit显示转写结转写结束文字edit显示转写结结转写结束文字edit结转写结束文字edit结转写结束文字显示转写结结转写结束文字edit结转写结束文显示转写结结转写结束文字edit结转写结束文显示转写结结转写结束文字edit结转写结束文显示转写结结转写结束文字edit结转写结束文显示转写结结转写结束文字edit结转写结束文显示转写结结转写结束文字edit结转写结束文edit";
        m_voiceNoteItemByasr->setTextEditVal(clsResult.txt);
        m_voiceNoteItem->setTextEditAlignment(Qt::AlignLeft);
        m_voiceNoteItem->setDocmentAligment(QTextOption(Qt::AlignLeft));
        m_currSelItemByasr->setSizeHint(QSize(this->width(),VOICENOTE_HEIGHT + m_textEditNewHeight + 5)); //ynbboy
        m_voiceNoteItemByasr->setFixedHeight(VOICENOTE_HEIGHT + m_textEditNewHeight + 5); //ynbboy
        Intancer::get_Intancer()->delHeightForRightList(m_tmpHeightForVoiceToText);
        Intancer::get_Intancer()->addHeightForRightList(VOICENOTE_HEIGHT + m_textEditNewHeight + 5);
        //m_voiceNoteItemByasr->m_bgWidgetBytext->setFixedHeight(m_textEditNewHeight);
//        m_voiceNoteItemByasr->m_bgWidgetBytext->move(6,55); //ynbboy
        m_voiceNoteItemByasr->m_bgWidgetBydetailBtn->show(); //ynbboy
        m_voiceNoteItemByasr->m_bgWidgetBytext->setVisible(true);
        //Edit start 3878
//        Intancer::get_Intancer()->setAsrTxt(m_currSelNote.folderId,m_currSelNote.id,clsResult.txt);
        Intancer::get_Intancer()->setAsrTxt(m_currSelNoteByasr.folderId,m_currSelNoteByasr.id,clsResult.txt);
        //Edit end 3878

        if(nullptr != m_currPlayingItem)
        {
            int playRow = 0;
            getRowByID(m_currPlayingItem->getNoteID(),VOICE,playRow);

            int voiceToTextRow = 0;
            getRowByID(m_voiceNoteItemByasr->getNoteID(),VOICE,voiceToTextRow);

            if(voiceToTextRow < playRow)
            {
                int movement = VOICENOTE_HEIGHT + m_textEditNewHeight + 5 - m_tmpHeightForVoiceToText;
                changeSliderPosByHand(-movement);
            }
        }


        int count = this->count();
        int transrow = row(m_currSelItemByasr);
        if(transrow == count - 2)
        {
            this->scrollToBottom();
        }

    }
    else
    {
        m_voiceNoteItemByasr->m_bgWidgetBytext->setVisible(false);
        m_voiceNoteItem->setTextEditDisplay(false);
        m_voiceNoteItem->setTextEditVal("");
        m_currSelItemByasr->setSizeHint(QSize(this->width(),VOICENOTE_HEIGHT));
        m_voiceNoteItemByasr->setFixedHeight(VOICENOTE_HEIGHT);
        Intancer::get_Intancer()->delHeightForRightList(m_tmpHeightForVoiceToText);
        Intancer::get_Intancer()->addHeightForRightList(VOICENOTE_HEIGHT);
        if (clsResult.code == "900003")
        {
            //网络异常
            m_asrNetWorkErrDialog->show();
        }
        else
        {
            //其他异常
            m_asrOtherErrDMessage->show();
        }
        //Add start 4297
        m_currSelItembyReasr = m_currSelItemByasr;
        m_currSelNoteByReasr = m_currSelNoteByasr;
        //Add end 4297
    }


    //通知mainPage转写结束  mainPage里设置leftView可用
    emit asrEnd();
}
// Add e 20191111
void RightNoteList::showFileDialog(SAVE_INFO saveInfo)
{
    DFileDialog fileDialog(this);
        fileDialog.setWindowTitle(saveInfo.windowTitle);
        fileDialog.setDirectory(m_defaultTxtPath);
        fileDialog.setFileMode(DFileDialog::Directory);
        fileDialog.setAcceptMode(DFileDialog::AcceptSave);

        QDir dir(m_defaultTxtPath);
        QStringList files;
        QString newName;
        if (TEXT == m_currSelNote.noteType) {
            fileDialog.setDefaultSuffix("txt");
            fileDialog.setNameFilter("TXT(*.txt)");
            //fileDialog.setNameFilter(tr("TXT(*.txt)"));
            scanData(dir,".txt", files, tr("TextNote"));
            getNewName(newName,files);
            fileDialog.selectFile(tr("TextNote") + newName);
            //fileDialog.selectFile(tr("Note") + newName);
            //fileDialog.selectFile("记事本" + newName);
        }else {
            fileDialog.setDefaultSuffix("mp3");
            fileDialog.setNameFilter("MP3(*.mp3)");
            //fileDialog.setNameFilter(tr("MP3(*.mp3)"));
            scanData(dir,".mp3", files, tr("VoiceNote"));
            getNewName(newName,files);
            fileDialog.selectFile(tr("VoiceNote") + newName);
            //fileDialog.selectFile("记事本" + newName);
        }

    //fileDialog->setFilter(QDir::filePath());
    if(fileDialog.exec() == QDialog::Accepted) {
        QString path = fileDialog.selectedFiles()[0];
//        QString fileName = fileDialog.getLineEditValue(tr("文件名"));
        QString fileName = QFileInfo(path).fileName();
//        QString filePath = path + '/' + fileName;
        QString filePath = path;
        if (fileName.isEmpty())
        {
            DMessageBox::information(this, tr(""), tr("File name cannot be empty"));
            //DMessageBox::information(this, tr(""), tr("文件名不能为空"));

        }
//        else if (!UiUtil::checkFileExtension(fileName, saveInfo.fileExtension))
//        {
//            DMessageBox::information(this, tr(""), tr("文件扩展名必须是") + saveInfo.fileExtension);
//        }
        else if(UiUtil::checkFileExist(filePath))
        {
            m_fileExistsDialog->setSavePath(filePath);
            m_fileExistsDialog->setNote(m_currSelNote);
            m_fileExistsDialog->show();
            //DDialog *fileExistDialog = UiUtil::createDialog(QString(""), QString(tr("文件名已存在，是否覆盖？")), nullptr, QString(tr("是")), QString(tr("否")));;
        }
        else
        {
            bool result = false;
            //filePath.append(saveInfo.fileExtension);
            if (VOICE == m_currSelNote.noteType)
            {
                result = UiUtil::saveMP3(UiUtil::getRecordingVoiceFullPath(m_currSelNote.contentPath), filePath);
            }
            else
            {
                result = UiUtil::saveTxt(filePath, m_currSelNote.contentText);
            }
            //handleSaveFileEnd(result);
        }

    } else {
       //QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
}

void RightNoteList::scanData(const QDir &fromDir, const QString &filter, QStringList &files, QString compareText)
{
    QFileInfoList fileInfoList = fromDir.entryInfoList(QDir::Files);
    //QFileInfoList fileInfoList = fromDir.entryInfoList();
    files.clear();
    for(int i = 0; i < fileInfoList.count(); i++)
    {
        if(fileInfoList.at(i).fileName().endsWith(filter))
        {
            QString filename = fileInfoList.at(i).fileName();
            filename = filename.remove(filename.count() - filter.count(),filter.count());
            if(filename.count() > 4)
            {
                QString prefilename = filename;
                QString tmpfilename = filename.remove(4,filename.count() - 4);
                //if(0 == tmpfilename.compare("记事本"))
                if(0 == tmpfilename.compare(compareText))
                {
                    prefilename = prefilename.remove(0,4);
                    files.append(prefilename);
                }
            }
        }
    }
}

void RightNoteList::getNewName(QString &outName, QStringList files)
{
    int newName = 0;
    bool find = false;
    while(!find)
    {
        newName++;
        outName = QString::number(newName);
        bool hassame = false;
        for(int i = 0; i < files.count(); i++)
        {
            if(0 == files.at(i).compare(outName))
            {
                hassame = true;
                break;
            }
        }

        if(!hassame)
        {
            find = true;
        }
    }
}

QListWidgetItem *RightNoteList::getListItemById(int id)
{
    QListWidgetItem * tmpItem = nullptr;
    for(int i = 0; i < this->count(); i++)
    {
        tmpItem = this->item(i);
        TextNoteItem* pTextNoteItem = (TextNoteItem*)this->itemWidget(tmpItem);
        if(id == pTextNoteItem->getId())
        {
            break;
        }
    }
    return tmpItem;
}

void RightNoteList::handleDelDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        //==== start add 20191105  bug2162
//        NOTE_TYPE delType2 = m_currSelNote.noteType;
//        if(TEXT == delType2)
//        {
//            if (!UiUtil::autoDeleteTxt(m_currSelNote))
//            {
//            }
//        }

        //==== start add 20191105  bug2162
        if (m_noteController->deleteNote(m_currSelNote))
        {
            bool move = false;
            int moveMovment = 0;
            if(nullptr != m_currPlayingItem)
            {

                int delRow = -1;
                NOTE_TYPE delType = m_currSelNote.noteType;
                getRowByID(m_currSelNote.id,delType,delRow);
                int playRow = -1;
                NOTE_TYPE playType = VOICE;
                getRowByID(m_currPlayingItem->getNoteID(),playType,playRow);

                if(m_currPlayingItem->getNoteID() == m_currSelNote.id)
                {
                    m_currPlayingItem = nullptr;
                    audioPlayer->stop();
                    DotheStopThePlayVoiceItem();
                }

                if(delRow < playRow)
                {
                    move = true;
                    moveMovment = this->itemWidget(m_currSelItem)->height();
                    //qDebug()<<"moveMovment: "<<moveMovment;
                    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("moveMovment:"), QString::number(moveMovment,10));
                }

            }

            this->removeItemWidget(m_currSelItem);
            delete m_currSelItem;
            m_currSelItem = nullptr;

            //m_addTextBtn->setDisableBtn(false);
            emit sig_TextEditNotEmpty(false);

            if(move)
            {
                changeSliderPosByHand(moveMovment);
            }

            if(VOICE == m_currSelNote.noteType)
            {
                //Add start 4297
                if (m_currSelNote.id == m_currSelNoteByReasr.id)
                {
                    setAsrErrDialogHide();
                }
                //Add end 4297
                Intancer::get_Intancer()->delHeightForRightList(VOICENOTE_HEIGHT);
            }
            else if(TEXT == m_currSelNote.noteType)
            {
                Intancer::get_Intancer()->delHeightForRightList(TEXTNOTE_HEIGHT);
            }

            //删除成功并且处于搜索状态下的话，再次出发搜索
            if(Intancer::get_Intancer()->getSearchingFlag())
            {
                int count = this->count();
                if(count <= 1)//3133
                {
                    emit sig_research();
                }
            }

            emit sigChangeCurFolderToTop(m_currSelNote.folderId);

        }
        else {
            //qDebug() << "error: delete item error";
            UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("error: delete item error"), QString("error: delete item error"));
        }
    }
    else {
        NOTE_TYPE delType = m_currSelNote.noteType;
        if(TEXT == delType)
        {
            TextNoteItem *pPreDelItem = (TextNoteItem*)this->itemWidget(m_currSelItem);
            pPreDelItem->changeToEditMode();
        }
    }
    Intancer::get_Intancer()->setTryToDelEmptyTextNote(false);
    Intancer::get_Intancer()->setWantScrollRightListFlag(true);
    //handleVScrollBarChanged(-1);
}

void RightNoteList::handleCloseDialogClicked()
{
    NOTE_TYPE delType = m_currSelNote.noteType;
    if(TEXT == delType)
    {
        TextNoteItem *pPreDelItem = (TextNoteItem*)this->itemWidget(m_currSelItem);
        pPreDelItem->changeToEditMode();
    }
    Intancer::get_Intancer()->setTryToDelEmptyTextNote(false);
}

void RightNoteList::handleClickRecordButton()
{
    // Must stop player before new record.
    if (QMediaPlayer::StoppedState !=audioPlayer->state())
    {
        //m_currPlayingItem->handleStopPlay();
        audioPlayer->stop();
        DotheStopThePlayVoiceItem();
        //audioPlayer->setMedia(QUrl::fromLocalFile("default"));//clear path
        //m_currPlayingItem = nullptr;
    }
}

void RightNoteList::play(VoiceNoteItem * voiceNoteItem, QString filepath, QRect waveformPos, NOTE note)  //Edit bug 2587
//void RightNoteList::play(VoiceNoteItem * voiceNoteItem, QString filepath, QRect waveformPos)
{
    m_currSelNote = note;  //Add bug 2587
    m_voiceOperation = true;  //Add bug 2587
    if (filepath != getPlayingFilepath()) {
        audioPlayer->stop();
        DotheStopThePlayVoiceItem();

        m_currPlayingItem = voiceNoteItem;


        if(!UiUtil::checkFileExist(filepath))
        {
            m_myslider->hide();
            m_currPlayingItem->onlySetResumeNoSig();
            m_currPlayingItem->setPlayDisable();
            m_currPlayingItem->clearWaveformContent();
            //by yuanshuai 20191120 2841
            //m_noticeNotExistDialog->show();
            emit sig_checkCurPageVoiceForDelete();
            emit sig_CheckFileExist();
            //end

            m_currPlayingItem = nullptr; //4303 yuanshuai
            return;
        }
        audioPlayer->setMedia(QUrl::fromLocalFile(filepath));
    }
    else {
        m_currPlayingItem = voiceNoteItem;
        if(!UiUtil::checkFileExist(filepath))
        {
            //by yuanshuai 20191120 2841
            //m_noticeNotExistDialog->show();
            emit sig_checkCurPageVoiceForDelete();
            emit sig_CheckFileExist();
            //end
            m_myslider->hide();
            m_currPlayingItem = nullptr; //4303 yuanshuai
            return;
        }

    }

    connect(m_myslider,SIGNAL(sigSliderPos(int)),m_currPlayingItem->m_waveform,SLOT(OnSetWavePos(int)));

    //waveform->show();


    audioPlayer->play();
    if (m_myslider->isHidden())
    {
        QPoint waveformPoint = voiceNoteItem->mapTo(this, QPoint(waveformPos.x(), waveformPos.y()));
        //QPoint x = voiceNoteItem->mapTo(this, QPoint(waveformPos.x(), waveformPos.y()));
//        // - m_myslider->m_handleTextHeight
        m_myslider->setTimeText(QString("00:00"));
        //m_myslider->setTimeText(QString(tr("00:00")));
        m_myslider->setGeometry( waveformPoint.x() - m_myslider->getHandlerWidth() / 2, waveformPoint.y() - 27, waveformPos.width() + m_myslider->getHandlerWidth(), m_myslider->m_defaultHeight);
        m_myslider->showSlider();
        curWaveformPosWidth = waveformPos.width() + m_myslider->getHandlerWidth();
        int sliderwidth = m_myslider->width() - m_myslider->getSliderHandlerWidth();
        //m_myslider->setRange(0, waveformPos.width());
        int duringtime = m_currPlayingItem->getRecodeTime();
        int maxtime = duringtime/1000;
        if(0 == maxtime)
        {
            maxtime = 1;
        }
        m_myslider->setRange(0, maxtime);
        m_myslider->setSliderPostion(0); //ynb 20191109
        m_myslider->show();

        //m_TestSlider->setGeometry( waveformPoint.x(), waveformPoint.y() - 27, waveformPos.width(), m_myslider->m_defaultHeight);
    }
}

void RightNoteList::pause()
{
    m_voiceOperation = true;  //Add bug 2587
    audioPlayer->pause();
}

void RightNoteList::stop()
{
    audioPlayer->stop();
    DotheStopThePlayVoiceItem();
}

QString RightNoteList::getPlayingFilepath()
{
    if (audioPlayer->isAudioAvailable()) {
        return audioPlayer->media().resources().first().url().path();
    } else {
        return "";
    }
}

void RightNoteList::changeSliderPosByHand(int moveMovment)
{
    if(nullptr != m_myslider)
    {
        if (!m_myslider->isHidden())
        {
            //qDebug()<<"before move slider y:"<<m_myslider->y();
            UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("before move slider y:"), QString::number(m_myslider->y(),10));
            m_myslider->move(m_myslider->x(), m_myslider->y() - moveMovment);
            //qDebug()<<"after move slider y:"<<m_myslider->y();
            UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("after move slider y:"), QString::number(m_myslider->y(),10));
            if(this->verticalScrollBar()->isVisible())
            {
                int value = this->verticalScrollBar()->value();
                this->verticalScrollBar()->setValue(value - 1);
            }
        }
    }
}

bool RightNoteList::getRowByID(int id, NOTE_TYPE type,  int &row)
{
    bool ret = false;

    int count = this->count();
    for(int i = 0; i < count - 1; i++)
    {
        QListWidgetItem* ptmp = this->item(i);

        if(VOICE == type)
        {
            VoiceNoteItem* pWidget = (VoiceNoteItem*)this->itemWidget(ptmp);
            if(pWidget->getNoteID() == id)
            {
                ret = true;
                row = i;
                break;
            }
        }
        else if(TEXT == type)
        {
            TextNoteItem* pWidget = (TextNoteItem*)this->itemWidget(ptmp);
            if(pWidget->getId() == id)
            {
                ret = true;
                row = i;
                break;
            }
        }
        else
        {
            break;
        }
    }

    return ret;
}

void RightNoteList::DotheStopThePlayVoiceItem()
{
    if(nullptr != m_currPlayingItem)
    {
        disconnect(m_myslider,SIGNAL(sigSliderPos(int)),m_currPlayingItem->m_waveform,SLOT(OnSetWavePos(int)));
        m_currPlayingItem->m_waveform->setWavePosition(-1);
        m_currPlayingItem->onlySetResumeNoSig();
        m_currPlayingItem = nullptr;
    }
    m_myslider->hide();
}

//void RightNoteList::handlePlayingStateChanged(QMediaPlayer::State state)
//{
//    if (QMediaPlayer::StoppedState == state)
//    {
//        if(nullptr != m_currPlayingItem)
//        {
//            disconnect(m_myslider,SIGNAL(sigSliderPos(int)),m_currPlayingItem->m_waveform,SLOT(OnSetWavePos(int)));
//            m_currPlayingItem->m_waveform->setWavePosition(-1);
//            m_currPlayingItem->handleStopPlay();
//            m_currPlayingItem = nullptr;
//        }

//        m_myslider->hide();
//    }
//}


void RightNoteList::handleAudioPositionChanged(qint64 position)
{
//    if(nullptr != m_currPlayingItem)
//    {
//        //int audioLength = audioPlayer->duration();
//        int audioLength = m_currPlayingItem->m_note.voiceTime;
//        int sliderPos = 0;
//        if (audioLength > 0)
//        {
//            sliderPos = position * ( m_myslider->width()) / audioLength;
//        }
//        m_currPlayingItem->m_waveform->setWavePosition(sliderPos);
//        //QTime curTime(0,0,0);
//        QTime curTime(0, position / 60000, qRound((position % 60000) / 1000.0));
//        //QTime curTime(0, position / 60000, (position % 60000) / 1000.0);
//        QString curTimeStr = curTime.toString(tr("mm:ss"));
//        m_myslider->setTimeText(curTimeStr);
//        //m_myslider->setTimeText(UiUtil::formatMillisecond(position));
//        m_myslider->setSliderPostion(sliderPos);

//    }
    //s ynbboy 20191109
    if(nullptr != m_currPlayingItem)
    {
        //qDebug()<<"position:"<<position;
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("position:"), QString::number(position,10));
        if (0 == position)
        {
            QTime curTime(0, 0, 0);
            QString curTimeStr = curTime.toString("mm:ss");
            //QString curTimeStr = curTime.toString(tr("mm:ss"));
            m_myslider->setTimeText(curTimeStr);
        }

       int s = int((position) / 1000.0);

       if (position == 0 || m_IsSliderBarReleased)
       {
          seconds = s + 1 ;
          m_IsSliderBarReleased = false;
       }

       int audioLength = int(audioPlayer->duration());
       int maxTime = audioLength/1000;
//       qDebug()<<"s:"<<s;
//       qDebug()<<"audioLength:"<<audioLength;
//       qDebug()<<"maxTime:"<<maxTime;
       UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("s:"), QString::number(s,10));
       UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("audioLength:"), QString::number(audioLength,10));
       UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("maxTime:"), QString::number(maxTime,10));
       if ((s == seconds) || ((audioLength - position) < 1000 && position == audioLength))
       {
//            int sliderPos = 0;
//            int stepLenth = 0;
//            if (audioLength > 0)
//            {
//                long lwidth = m_myslider->width() - m_myslider->getSliderHandlerWidth();
//                double aa =  double((float)position/audioLength);
//                sliderPos = int(aa * lwidth + 0.5);
//            }
            QTime curTime(0, 0, 0);
            curTime = curTime.addSecs(seconds);
            QString curTimeStr;
            if(curTime.hour())
            {
                curTimeStr = "60:00";
            }
            else
            {
                curTimeStr = curTime.toString("mm:ss");
                //curTimeStr = curTime.toString(tr("mm:ss"));
            }

            //m_myslider->setTimeText(curTimeStr); liuyang 3561
            m_myslider->setSliderPostion(s);
            m_myslider->setTimeText(curTimeStr); //liuyang 3561
//            int sliderPos = m_myslider->gethandlePos();
//            m_currPlayingItem->m_waveform->setWavePosition(sliderPos);
            //m_myslider->setSliderPostion(sliderPos);

//            qDebug() << "handleAudioPositionChanged:" << position;
//            qDebug()<<"seconds:"<<seconds;
//            qDebug()<<"curTime:"<<curTime;
            UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("handleAudioPositionChanged:"), QString::number(position,10));
            UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("seconds:"), QString::number(seconds,10));
            UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("curTime:"), curTime.toString());

            seconds++;
       }

       if((audioLength <= position) && (audioLength != 0) && (position != 0))
       {
           //update UI to stop curplay UI.
           DotheStopThePlayVoiceItem();
       }
    }
    //e ynbboy 20191109
}

void RightNoteList::handleSliderReleased()
{
    m_IsSliderBarReleased = true; //ynb 20191109
    if(nullptr != m_currPlayingItem)
    {
        int sliderpos = m_myslider->sliderPosition();
//        int voiceTime = m_currPlayingItem->m_note.voiceTime;
//        int lenth = m_myslider->width() - m_myslider->getHandlerWidth();
//        int audioPos = sliderpos * voiceTime / lenth;

        //audioPlayer->setPosition(sliderpos);
        qint64 audioPos = sliderpos * 1000;
        //audioPos = 3000000;
        //qDebug()<<"audioPos:"<<audioPos;
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("audioPos:"), QString::number(audioPos,10));
        audioPlayer->setPosition(audioPos);
    }
}

void RightNoteList::handleSliderPressed()
{
//    int audioPos = m_myslider->sliderPosition() * m_currPlayingItem->m_note.voiceTime / (m_myslider->width() - m_myslider->getHandlerWidth());

//    audioPlayer->setPosition(audioPos);
}

void RightNoteList::handleSliderMove(int value)
{
//    int audioPos = m_myslider->sliderPosition() * m_currPlayingItem->m_note.voiceTime / (m_myslider->width() - m_myslider->getHandlerWidth());

//    audioPlayer->setPosition(audioPos);
}

void RightNoteList::handleSaveFileEnd(bool result)
{
    QString title;

    if (result)
    {
        title = tr("Save file successfully!");
        //title = tr("保存文件成功!");
    }
    else
    {
        title = tr("Saving file failed!");
        //title = tr("保存文件失败!");
    }
    m_saveFileEndDialog->setTitle(title);
    m_saveFileEndDialog->show();
    //UiUtil::createConfirmDialog(QString(""), title, this);
}

void RightNoteList::handleMenuBtnPressed()
{
    //Add start bug 2587
    if (m_currSelNote.noteType == VOICE)
    {
        m_voiceOperation = true;
    }
    else
    {
        m_textGetFocus = true;
    }
    //Add end bug 2587
    m_arrowButtonPressed = true;
}

void RightNoteList::handleMenuBtnReleased()
{
    m_arrowButtonPressed = false;
}
void RightNoteList::adjustWidgetItemWidth()
{
    QListWidgetItem *ptmp = nullptr;
    for(int i = 0; i < this->count() - 1; i++)
    {
        ptmp = this->item(i);

        QWidget* ptmpWidget = this->itemWidget(ptmp);
        int listWidth = this->width();
        //int newWidth = this->width() - 23;
        int newWidth = this->width() - 18;
        ptmpWidget->setFixedSize(QSize(newWidth,ptmpWidget->height()));

        if(i != this->count() - 1)
        {
            this->item(i)->setSizeHint(QSize(listWidth,ptmpWidget->height()));
        }
    }
}
