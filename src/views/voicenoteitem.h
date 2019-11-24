#ifndef VOICENOTEITEM_H
#define VOICENOTEITEM_H

#include <QHBoxLayout>
#include <DLabel>
#include <QWidget>
#include <DBlurEffectWidget>
#include <DIconButton>
#include <DFloatingButton>
#include <dimagebutton.h>
#include "consts.h"
#include "notecontroller.h"
#include "playingbutton.h"
#include "waveform.h"
#include "menubutton.h"
#include <DFrame>

DWIDGET_USE_NAMESPACE
//右侧语音记录Item
class VoiceNoteItem : public QWidget
{
    Q_OBJECT
public:
    VoiceNoteItem(NOTE note, NoteController *noteCtr);
    ~VoiceNoteItem();
    void init();
    bool getwaveformPoint(QRect &rect);
    int getNoteID();
    int getRecodeTime();
    NOTE_TYPE getType();
    void clearWaveformContent();
    void onlySetResumeNoSig();
    QRect getWaveRect();
    void VoicePlayOrPause(); //Add bug 2587
    NOTE m_note;

    DLabel *m_timeLabel;
    DFrame *m_bgWidget;
    QVBoxLayout *m_itemLayout;
    QHBoxLayout *m_hBoxLayout;
    //DImageButton *m_ctrlBtn;
    MenuButton *m_menuBtn;
    //DIconButton *m_menuBtn;
    //DImageButton *m_menuBtn;
    DLabel *m_voiceTimeLabel;
    //QWidget *m_voiceShape;
    Waveform *m_waveform;

signals:
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void resumePlayingSignal(VoiceNoteItem * voiceNoteItem, QString filePath, QRect waveformRect, NOTE note); //Edit  bug 2587
    //void resumePlayingSignal(VoiceNoteItem * voiceNoteItem, QString filePath, QRect waveformRect);
    void pausePlayingSignal();
    void sig_menuBtnPressed();
    void sig_menuBtnReleased();
    void buttonClicled();

public slots:
    void handleStopPlay();
    void handlePausePlay();
    void handleResumePlaying();
    void setPlayDiseable();
    void setPlayEnable();
    void changeTheme();
    //void handle

private:
    NoteController *m_noteCtr;
    PlayingButton *m_playingButton;
    void initUI();
    void initConnection();
    void handleMenuBtnClicked();
};

#endif // VOICENOTEITEM_H
