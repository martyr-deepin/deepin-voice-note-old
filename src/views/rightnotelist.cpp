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
    this->setFrameShape(QListWidget::NoFrame);
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

    m_myslider = new MySlider(Qt::Horizontal, this);
    //m_myslider = new MyCustomSlider(Qt::Horizontal, this);

    //m_myslider->setFixedSize(350, 70);
    //m_myslider->setHandleType(MySlider::HandleType::SharpHandler);
    m_myslider->setPageStep(SLIDER_PAGE_STEP);
    m_myslider->setGeometry(0, 0, 350, 121);
    m_myslider->hide();

}
void RightNoteList::initConnection()
{
    connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
    connect(m_saveAsAction, SIGNAL(triggered(bool)), this, SLOT(handleSaveAsItem(bool)));
    connect(audioPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(handleAudioPositionChanged(qint64)));
    connect(m_delConfirmDialog, &DDialog::buttonClicked, this, &RightNoteList::handleDelDialogClicked);
    connect(m_myslider, SIGNAL(sliderReleased()), this, SLOT(handleSliderReleased()));
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
        connect(voiceItem, SIGNAL(resumePlayingSignal(VoiceNoteItem *, QString, QRect)), this, SLOT(play(VoiceNoteItem *, QString, QRect)));
        QListWidgetItem *item=new QListWidgetItem(this);
        item->setSizeHint(QSize(this->width(),64));
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

void RightNoteList::play(VoiceNoteItem * voiceNoteItem, QString filepath, QRect waveformPos)
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
    if (m_myslider->isHidden())
    {
        QPoint waveformPoint = voiceNoteItem->mapTo(this, QPoint(waveformPos.x(), waveformPos.y()));
        //QPoint x = voiceNoteItem->mapTo(this, QPoint(waveformPos.x(), waveformPos.y()));
        qDebug() << "width: " << waveformPos.width() << "height: " << m_myslider->y();
        m_myslider->setGeometry( waveformPoint.x() - m_myslider->getHandlerWidth() / 2, waveformPoint.y(), waveformPos.width() + m_myslider->getHandlerWidth(), m_myslider->m_defaultHeight);
        m_myslider->setRange(0, waveformPos.width());
        m_myslider->show();
    }
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
        m_currPlayingItem->m_waveform->setWavePosition(0);
        m_currPlayingItem->handleStopPlay();
        m_currPlayingItem = nullptr;
        m_myslider->hide();
    }
}


void RightNoteList::handleAudioPositionChanged(qint64 position)
{
    int audioLength = m_currPlayingItem->m_note.voiceTime;
    int sliderPos = 0;
    if (audioLength > 0)
    {
        sliderPos = position * ( m_myslider->width()) / audioLength;
    }

    qDebug() << "handleAudioPositionChanged:" << position;
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
