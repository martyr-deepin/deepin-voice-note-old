#ifndef VOICENOTEITEM_H
#define VOICENOTEITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <dimagebutton.h>
#include "consts.h"
#include "notecontroller.h"
#include "playingbutton.h"
#include "waveform.h"

DWIDGET_USE_NAMESPACE
class VoiceNoteItem : public QWidget
{
    Q_OBJECT
public:
    VoiceNoteItem(NOTE note, NoteController *noteCtr);
    ~VoiceNoteItem();

    NOTE m_note;

    QLabel *m_timeLabel;
    QWidget *m_bgWidget;
    QLayout *m_itemLayout;
    QHBoxLayout *m_hBoxLayout;
    //DImageButton *m_ctrlBtn;
    DImageButton *m_menuBtn;
    QLabel *m_voiceTimeLabel;
    //QWidget *m_voiceShape;
    Waveform *m_waveform;

signals:
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void resumePlayingSignal(VoiceNoteItem * voiceNoteItem, QString filePath);
    void pausePlayingSignal();
public slots:
    void handleStopPlay();
    void handleResumePlaying();
    //void handle

private:
    NoteController *m_noteCtr;
    PlayingButton *m_playingButton;
    void initUI();
    void initConnection();
    void handleMenuBtnClicked();
};

#endif // VOICENOTEITEM_H
