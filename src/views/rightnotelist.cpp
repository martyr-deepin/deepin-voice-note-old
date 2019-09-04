#include "rightnotelist.h"
#include "textnoteitem.h"
#include "voicenoteitem.h"
#include <QDebug>
#include <uiutil.h>

RightNoteList::RightNoteList(NoteController *noteController) : m_currPlayingItem(nullptr)
{
    initUI();
    initConnection();
}

RightNoteList::~RightNoteList()
{

}

void RightNoteList::initUI()
{
    m_contextMenu = new QMenu;
    m_saveAsAction = new QAction(tr(NOTE_MENU_SAVE_AS_TXT),this);
    m_delAction = new QAction(tr(FOLDER_MENU_DELETE),this);
    m_contextMenu->addAction(m_saveAsAction);
    m_contextMenu->addAction(m_delAction);
    m_arrowMenu = new DArrowRectangle(DArrowRectangle::ArrowTop, DArrowRectangle::FloatWindow);
    m_arrowMenu->setHeight(200);
    m_arrowMenu->setWidth(200);

    m_arrowMenu->setContent(m_contextMenu);
    m_arrowMenu->setBorderColor(QColor::fromRgb(255, 0, 0));

    m_delConfirmDialog = UiUtil::createDialog(QString(""), QString(tr("您确定要删除这条记事项吗？")), nullptr);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    audioPlayer = new QMediaPlayer(this);
    connect(audioPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(handlePlayingStateChanged(QMediaPlayer::State)));


}
void RightNoteList::initConnection()
{
    connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
    connect(m_saveAsAction, SIGNAL(triggered(bool)), this, SLOT(handleSaveAsItem(bool)));
    connect(m_delConfirmDialog, &DDialog::buttonClicked, this, &RightNoteList::handleDelDialogClicked);
}

//void LeftFolderList::addWidgetItem(FOLDER folder) {
//    QListWidgetItem *item=new QListWidgetItem(this);
//    item->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
//    item->setSizeHint(QSize(200,60));
//    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr);
//    this->setItemWidget(item, folderItem);
//}

void RightNoteList::addWidgetItem(NOTE note)
{


    if(note.noteType == NOTE_TYPE::TEXT)
    {
        TextNoteItem *textItem = new TextNoteItem(note, m_noteController);
        connect(textItem, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(menuBtnClicked(QPoint, QPoint, QWidget *, NOTE)), this, SLOT(handleMenuBtnClicked(QPoint, QPoint, QWidget *, NOTE)));
        QListWidgetItem *item=new QListWidgetItem(this);
        qDebug() << "text item height: " << textItem->height();
        item->setSizeHint(QSize(this->width(),140));
        this->setItemWidget(item, textItem);

    }
    else if(note.noteType == NOTE_TYPE::VOICE){
        VoiceNoteItem *voiceItem = new VoiceNoteItem(note, m_noteController);        
        connect(voiceItem, SIGNAL(menuBtnClicked(QPoint, QPoint, QWidget *, NOTE)), this, SLOT(handleMenuBtnClicked(QPoint, QPoint, QWidget *, NOTE)));        
        connect(voiceItem, SIGNAL(pausePlayingSignal()), this, SLOT(pause()));
        connect(voiceItem, SIGNAL(resumePlayingSignal(VoiceNoteItem *, QString)), this, SLOT(play(VoiceNoteItem *, QString)));
        QListWidgetItem *item=new QListWidgetItem(this);
        item->setSizeHint(QSize(this->width(),140));
        this->setItemWidget(item, voiceItem);
    }
}

void RightNoteList::handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note)
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

//    this->removeItemWidget(widgetItem);
//    delete widgetItem;
//    qDebug() << "handleMenuBtnClicked: x:" << itemGlobalPoint.x() << "handleMenuBtnClicked: y: " << itemGlobalPoint.y();

}


void RightNoteList::handleDelItem(bool)
{
    m_delConfirmDialog->show();

    m_arrowMenu->hide();
//    return;
}
void RightNoteList::handleSaveAsItem(bool)
{

    m_arrowMenu->hide();
}

void RightNoteList::handleDelDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        if (m_noteController->deleteNote(m_currSelNote.id))
        {

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
        audioPlayer->stop();
        m_currPlayingItem->handleStopPlay();
        m_currPlayingItem = nullptr;
    }
}

void RightNoteList::play(VoiceNoteItem * voiceNoteItem, QString filepath)
{
    if (filepath != getPlayingFilepath()) {
        audioPlayer->stop();
        if (nullptr != m_currPlayingItem)
        {
            m_currPlayingItem->handleStopPlay();
        }
    }
    m_currPlayingItem = voiceNoteItem;
    //waveform->show();

    audioPlayer->setMedia(QUrl::fromLocalFile(filepath));
    audioPlayer->play();
}

void RightNoteList::pause()
{
    audioPlayer->pause();
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
        m_currPlayingItem->handleStopPlay();
        m_currPlayingItem = nullptr;
    }
}

