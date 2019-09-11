#ifndef RIGHTNOTELIST_H
#define RIGHTNOTELIST_H

#include "myslider.h"
#include "textnoteitem.h"
#include "voicenoteitem.h"

#include <DListWidget>
#include <notecontroller.h>
#include <consts.h>
#include <QObject>
#include <darrowrectangle.h>
#include <DDialog>
#include <QMediaPlayer>
//#include <DArrowRectangle>

DWIDGET_USE_NAMESPACE

#define SLIDER_PAGE_STEP 4

class RightNoteList : public DListWidget
{
    Q_OBJECT
public:
    RightNoteList(NoteController *noteController);
    ~RightNoteList();
    void addWidgetItem(NOTE note, QString searchKey);

signals:
    void textEditClicked(NOTE textNote);


public slots:
    void handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void handleDelItem(bool);
    void handleSaveAsItem(bool);
    void handleDelDialogClicked(int index, const QString &text);
    void handlePlayingStateChanged(QMediaPlayer::State state);
    void play(VoiceNoteItem * voiceNoteItem, QString filepath, QRect waveformPos);
    void pause();
    void handleClickRecordButton();
    void handleAudioPositionChanged(qint64 position);
    void handleSliderReleased();

private:
    QMenu *m_contextMenu;
    QAction *m_saveAsAction;
    QAction *m_delAction;
    NoteController *m_noteController;
    DArrowRectangle *m_arrowMenu;
    QListWidgetItem *m_currSelItem;
    NOTE m_currSelNote;
    DDialog *m_delConfirmDialog;
    VoiceNoteItem *m_currPlayingItem;
    QMediaPlayer *audioPlayer;
    MySlider *m_myslider;

    //MyCustomSlider *m_myslider;
    void initUI();
    void initConnection();


    QString getPlayingFilepath();
};

#endif // RIGHTNOTELIST_H
