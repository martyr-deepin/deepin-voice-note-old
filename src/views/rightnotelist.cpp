#include "rightnotelist.h"
#include "textnoteitem.h"
#include "voicenoteitem.h"
#include <QDebug>
#include <uiutil.h>
#include <DFileDialog>
#include <DToast>
#include <DApplication>
#include <DMessageBox>
#include <QMessageBox>
#include <QScrollBar>

MMenu::MMenu(QWidget *parent)
{

}

MMenu::~MMenu()
{

}

void MMenu::leaveEvent(QEvent* event)
{
    emit sigMMenu();
    return QMenu::leaveEvent(event);
}



RightNoteList::RightNoteList(NoteController *noteController) : m_currPlayingItem(nullptr)
  , m_defaultTxtName("文本.TXT")
  , m_defaultTxtPath("/home/deepin/Desktop")
  , m_defaultAudioName("语音.MP3")
  , m_defaultAudioPath("/home/deepin/Desktop")
  , m_arrowButtonPressed(false)
  , m_actionHoverd(false)
{
    initUI();
    initConnection();
}

RightNoteList::~RightNoteList()
{

}

void RightNoteList::initUI()
{
    this->setFrameShape(QListWidget::NoFrame);
    this->resize(548,this->height());

    m_addTextBtn = nullptr;

    m_contextMenu = new MMenu;
    m_saveAsAction = new QAction(tr(NOTE_MENU_SAVE_AS_TXT),this);
    m_delAction = new QAction(tr(FOLDER_MENU_DELETE),this);
    m_contextMenu->addAction(m_saveAsAction);
    m_contextMenu->addAction(m_delAction);
    m_arrowMenu = new DArrowRectangle(DArrowRectangle::ArrowTop, DArrowRectangle::FloatWindow);
    m_arrowMenu->setHeight(200);
    m_arrowMenu->setWidth(200);

    m_arrowMenu->setContent(m_contextMenu);
    m_arrowMenu->setBorderColor(QColor::fromRgb(255, 0, 0));
    m_arrowMenu->hide();

    m_delConfirmDialog = UiUtil::createChooseDialog(QString(""), QString(tr("您确定要删除这条记事项吗？")), nullptr, QString(tr("取消")), QString(tr("删除")));
    m_saveFileEndDialog = UiUtil::createConfirmDialog(QString(""), QString(tr("")), this);
    m_fileExistsDialog = new FileExistsDialog();
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    audioPlayer = new QMediaPlayer(this);
    connect(audioPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(handlePlayingStateChanged(QMediaPlayer::State)));

    m_myslider = new MySlider(Qt::Horizontal, this);
    //m_myslider = new MyCustomSlider(Qt::Horizontal, this);

    //m_myslider->setFixedSize(350, 70);
    //m_myslider->setHandleType(MySlider::HandleType::SharpHandler);
    m_myslider->setPageStep(SLIDER_PAGE_STEP);
    m_myslider->setGeometry(0, 0, 350, m_myslider->m_defaultHeight);
    m_myslider->hide();


//    m_addTextBtn->setNormalPic(":/image/add_text_btn.png");
//    m_addTextBtn->setHoverPic(":/image/add_text_btn.png");
//    m_addTextBtn->setPressPic(":/image/add_text_btn_press.png");

    qApp->installEventFilter(this);
    //this->setStyleSheet("background: red");
}
void RightNoteList::initConnection()
{

    connect(m_contextMenu, SIGNAL(sigMMenu()), this, SLOT(OnLeaveContentMenu()));
    connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
    connect(m_delAction, SIGNAL(hovered()), this, SLOT(OnActionHoverd()));
    connect(m_saveAsAction, SIGNAL(triggered(bool)), this, SLOT(handleSaveAsItem(bool)));
    connect(m_saveAsAction, SIGNAL(hovered()), this, SLOT(OnActionHoverd()));
    connect(audioPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(handleAudioPositionChanged(qint64)));
    connect(m_delConfirmDialog, &DDialog::buttonClicked, this, &RightNoteList::handleDelDialogClicked);
    connect(m_myslider, SIGNAL(sliderReleased()), this, SLOT(handleSliderReleased()));
    //connect(m_fileExistsDialog, SIGNAL(saveFileEnd(bool)), this, SLOT(handleSaveFileEnd(bool)));
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(handleVScrollBarChanged(int)));
}

//void LeftFolderList::addWidgetItem(FOLDER folder) {
//    QListWidgetItem *item=new QListWidgetItem(this);
//    item->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
//    item->setSizeHint(QSize(200,60));
//    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr);
//    this->setItemWidget(item, folderItem);
//}

void RightNoteList::addWidgetItem(NOTE note, QString searchKey)
{
    if(note.noteType == NOTE_TYPE::TEXT)
    {
        TextNoteItem *textItem = new TextNoteItem(note, m_noteController, searchKey);
        connect(textItem, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(menuBtnClicked(QPoint, QPoint, QWidget *, NOTE)), this, SLOT(handleMenuBtnClicked(QPoint, QPoint, QWidget *, NOTE)));
        connect(textItem, SIGNAL(sig_menuBtnPressed()), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(sig_menuBtnReleased()), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(sig_TextEditNotEmpty()), this, SLOT(onAbleAddBtn()));

        QListWidgetItem *item=new QListWidgetItem();
        //QListWidgetItem *item=new QListWidgetItem(this);
        //qDebug() << "text item height: " << textItem->height();
        //item->setSizeHint(QSize(this->width(),92));
        //qDebug()<<"textItem width1:"<<textItem->width();
        item->setSizeHint(QSize(this->width(),123));  //orig
        //qDebug()<<"textItem width2:"<<textItem->width();
        this->insertItem(this->count() - 1,item);
        this->setItemWidget(item, textItem);
        textItem->init();
        //qDebug()<<"textItem width3:"<<textItem->width();
    }
    else if(note.noteType == NOTE_TYPE::VOICE){
        VoiceNoteItem *voiceItem = new VoiceNoteItem(note, m_noteController);
        connect(voiceItem, SIGNAL(menuBtnClicked(QPoint, QPoint, QWidget *, NOTE)), this, SLOT(handleMenuBtnClicked(QPoint, QPoint, QWidget *, NOTE)));
        connect(voiceItem, SIGNAL(pausePlayingSignal()), this, SLOT(pause()));
        connect(voiceItem, SIGNAL(resumePlayingSignal(VoiceNoteItem *, QString, QRect)), this, SLOT(play(VoiceNoteItem *, QString, QRect)));
        QListWidgetItem *item=new QListWidgetItem();
        item->setSizeHint(QSize(this->width(), 94));
        this->insertItem(this->count() - 1,item);
        this->setItemWidget(item, voiceItem);
        voiceItem->init();
    }
}

void RightNoteList::addAddTextBtn()
{
    if(nullptr == m_addTextBtn)
    {
        m_addTextBtn = new AddTextBtn();
        m_addTextBtn->init();
        connect(m_addTextBtn, SIGNAL(addTextItem()), this, SIGNAL(addTextItem()));
        connect(m_addTextBtn, SIGNAL(addTextItem()), this, SLOT(onDisableAddBtn()));
        QListWidgetItem *item=new QListWidgetItem();
        item->setSizeHint(QSize(this->width(),m_addTextBtn->height()));
        this->addItem(item);
        this->setItemWidget(item, m_addTextBtn);
    }
}

void RightNoteList::delAddTextBtn()
{
    if(nullptr != m_addTextBtn)
    {
        QListWidgetItem *item = takeItem(count() - 1);
        if(nullptr != item)
        {
            disconnect(m_addTextBtn, SIGNAL(addTextItem()), this, SIGNAL(addTextItem()));
            disconnect(m_addTextBtn, SIGNAL(addTextItem()), this, SLOT(onDisableAddBtn()));
            m_addTextBtn = (AddTextBtn*)itemWidget(item);
            delete m_addTextBtn;
            m_addTextBtn = nullptr;
        }
    }
}

bool RightNoteList::eventFilter(QObject *o, QEvent *e)
{
    switch (e->type())
    {
        case QEvent::MouseButtonRelease:
        if((!m_arrowButtonPressed)&&(!m_actionHoverd))
        {
            m_arrowMenu->hide();
            m_actionHoverd = false;
            //qDebug()<<"click filter";
        }
        qDebug()<<"click filter";
        break;
    }
    return DListWidget::eventFilter(o,e);
}

void RightNoteList::handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note)
{
    if(m_arrowMenu->isHidden())
    {
        QPoint itemGlobalPoint = textNoteItem->mapTo(this, menuArrowPointToItem);
        m_currSelItem= this->itemAt(itemGlobalPoint);
        m_currSelNote = note;
        if (note.noteType == NOTE_TYPE::TEXT)
        {
            m_saveAsAction->setText(NOTE_MENU_SAVE_AS_TXT);
        }
        else {
            m_saveAsAction->setText(NOTE_MENU_SAVE_AS_MP3);
        }
        m_arrowMenu->show(menuArrowPointGlobal.x(), menuArrowPointGlobal.y());
    }
    else {
        m_arrowMenu->hide();
        m_actionHoverd = false;
    }

//    else
//    {
//        m_arrowMenu->hide();
//    }


//    this->removeItemWidget(widgetItem);
//    delete widgetItem;
//    qDebug() << "handleMenuBtnClicked: x:" << itemGlobalPoint.x() << "handleMenuBtnClicked: y: " << itemGlobalPoint.y();

}


void RightNoteList::handleDelItem(bool)
{
    m_delConfirmDialog->show();

    m_arrowMenu->hide();
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
}

void RightNoteList::handleVScrollBarChanged(int value)
{
    qDebug()<<"handleVScrollBarChanged:"<<value;
    if((nullptr != m_myslider)&&(nullptr != m_currPlayingItem))
    {
        if (!m_myslider->isHidden())
        {
            QRect rect;
            if(m_currPlayingItem->getwaveformPoint(rect))
            {
                QPoint waveformPoint = m_currPlayingItem->mapTo(this, QPoint(rect.x(), rect.y()));
                m_myslider->move(m_myslider->x(),waveformPoint.y() - 16);
            }
        }
    }
}

void RightNoteList::onDisableAddBtn()
{
    if(nullptr != m_addTextBtn)
    {
        m_addTextBtn->setDisableBtn(true);
    }
}

void RightNoteList::onAbleAddBtn()
{
    if(nullptr != m_addTextBtn)
    {
        m_addTextBtn->setDisableBtn(false);
    }
}

//dialog.setAcceptMode(DFileDialog::AcceptOpen);
//        dialog.setFileMode(DFileDialog::Directory);
//        dialog.setDirectory(m_pathstr);

//        const int mode = dialog.exec();

//        if (mode != QDialog::Accepted) {
//            return;
//        }

//        QList<QUrl> pathlist = dialog.selectedUrls();
//        QString curpath = pathlist.at(0).toLocalFile();
void RightNoteList::handleSaveAsItem(bool)
{
    m_arrowMenu->hide();
    m_actionHoverd = false;

    SAVE_INFO saveInfo;
    saveInfo.note = m_currSelNote;
    if (TEXT == m_currSelNote.noteType)
    {
        saveInfo.windowTitle = QString(tr("另存为TXT"));
        saveInfo.fileExtension = QString(".txt");
    }
    else
    {
        saveInfo.windowTitle = QString(tr("另存为MP3"));
        saveInfo.fileExtension = QString(".mp3");
    }
    showFileDialog(saveInfo);

}

void RightNoteList::showFileDialog(SAVE_INFO saveInfo)
{
    DFileDialog fileDialog(this);
    fileDialog.setWindowTitle(saveInfo.windowTitle);
    fileDialog.setDirectory(m_defaultTxtPath);
    fileDialog.setFileMode(DFileDialog::Directory);
    fileDialog.addLineEdit(tr("文件名"));
    fileDialog.setLabelText(DFileDialog::Accept, tr("保存"));
    //fileDialog->setFilter(QDir::filePath());
    if(fileDialog.exec() == QDialog::Accepted) {
        QString path = fileDialog.selectedFiles()[0];
        QString fileName = fileDialog.getLineEditValue(tr("文件名"));
        QString filePath = path + '/' + fileName;
        if (fileName.isEmpty())
        {
            DMessageBox::information(this, tr(""), tr("文件名不能为空"));

        }
        else if (!UiUtil::checkFileExtension(fileName, saveInfo.fileExtension))
        {
            DMessageBox::information(this, tr(""), tr("文件扩展名必须是") + saveInfo.fileExtension);
        }
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

void RightNoteList::handleDelDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        if (m_noteController->deleteNote(m_currSelNote.id))
        {
            audioPlayer->stop();
            this->removeItemWidget(m_currSelItem);
            delete m_currSelItem;
            m_currSelItem = nullptr;
        }
        else {
            qDebug() << "error: delete item error";
        }
    }

}

void RightNoteList::handleClickRecordButton()
{
    // Must stop player before new record.
    if (QMediaPlayer::StoppedState !=audioPlayer->state())
    {
        //m_currPlayingItem->handleStopPlay();
        audioPlayer->stop();
        //audioPlayer->setMedia(QUrl::fromLocalFile("default"));//clear path
        //m_currPlayingItem = nullptr;
    }
}

void RightNoteList::play(VoiceNoteItem * voiceNoteItem, QString filepath, QRect waveformPos)
{
    if (filepath != getPlayingFilepath()) {
        audioPlayer->stop();
//        if (nullptr != m_currPlayingItem)
//        {
//            m_currPlayingItem->handleStopPlay();
//        }
        m_currPlayingItem = voiceNoteItem;
        audioPlayer->setMedia(QUrl::fromLocalFile(filepath));
    }
    else {
        m_currPlayingItem = voiceNoteItem;
    }

    //waveform->show();


    audioPlayer->play();
    if (m_myslider->isHidden())
    {
        QPoint waveformPoint = voiceNoteItem->mapTo(this, QPoint(waveformPos.x(), waveformPos.y()));
        //QPoint x = voiceNoteItem->mapTo(this, QPoint(waveformPos.x(), waveformPos.y()));
        qDebug() << "width: " << waveformPos.width() << "height: " << m_myslider->y();
        // - m_myslider->m_handleTextHeight
        m_myslider->setGeometry( waveformPoint.x() - m_myslider->getHandlerWidth() / 2, waveformPoint.y() - 16, waveformPos.width() + m_myslider->getHandlerWidth(), m_myslider->m_defaultHeight);
        m_myslider->setRange(0, waveformPos.width());
        m_myslider->show();
    }
}

void RightNoteList::pause()
{
    audioPlayer->pause();
}

void RightNoteList::stop()
{
    audioPlayer->stop();
}

//void RightNoteList::resume()
//{
//    audioPlayer->play();
//}

//void RightNoteList::stop(QString filepath)
//{
//    if (filepath == getPlayingFilepath()) {
//        audioPlayer->stop();
//    }
//}

//void RightNoteList::stopPlayer()
//{
//    audioPlayer->stop();
//}

QString RightNoteList::getPlayingFilepath()
{
    if (audioPlayer->isAudioAvailable()) {
        return audioPlayer->media().resources().first().url().path();
    } else {
        return "";
    }
}

void RightNoteList::handlePlayingStateChanged(QMediaPlayer::State state)
{
    if (QMediaPlayer::StoppedState == state)
    {
        m_currPlayingItem->m_waveform->setWavePosition(0);
        m_currPlayingItem->handleStopPlay();
        m_currPlayingItem = nullptr;
        m_myslider->hide();
    }
}


void RightNoteList::handleAudioPositionChanged(qint64 position)
{
//    if(0 != position)
//    {

//    }
    int audioLength = m_currPlayingItem->m_note.voiceTime;
    int sliderPos = 0;
    if (audioLength > 0)
    {
        sliderPos = position * ( m_myslider->width()) / audioLength;
    }

    qDebug() << "handleAudioPositionChanged:" << position;
    qDebug() << "sliderPos:" <<sliderPos;
    m_currPlayingItem->m_waveform->setWavePosition(sliderPos);
    m_myslider->setTimeText(UiUtil::formatMillisecond(position));
    m_myslider->setSliderPostion(sliderPos);
}

void RightNoteList::handleSliderReleased()
{
    int audioPos = m_myslider->sliderPosition() * m_currPlayingItem->m_note.voiceTime / (m_myslider->width() - m_myslider->getHandlerWidth());
    qDebug() << "audioPos:" << audioPos << ",m_myslider->sliderPosition(): " << m_myslider->sliderPosition() << ",m_currPlayingItem->m_note.voiceTime: " << m_currPlayingItem->m_note.voiceTime << ",m_myslider->width(): " << m_myslider->width() - m_myslider->getHandlerWidth();

    audioPlayer->setPosition(audioPos);
}

void RightNoteList::handleSaveFileEnd(bool result)
{
    QString title;

    if (result)
    {
        title = tr("保存文件成功!");
    }
    else
    {
        title = tr("保存文件失败!");
    }
    m_saveFileEndDialog->setTitle(title);
    m_saveFileEndDialog->show();
    //UiUtil::createConfirmDialog(QString(""), title, this);
}

void RightNoteList::handleMenuBtnPressed()
{
    m_arrowButtonPressed = true;
}

void RightNoteList::handleMenuBtnReleased()
{
    m_arrowButtonPressed = false;
}
