#ifndef VOICENOTEITEM_H
#define VOICENOTEITEM_H

#include <QHBoxLayout>
#include <DLabel>
#include <QWidget>
#include <DBlurEffectWidget>
#include <dimagebutton.h>
#include "consts.h"
#include "notecontroller.h"
#include "playingbutton.h"
#include "waveform.h"

DWIDGET_USE_NAMESPACE
//右侧语音记录Item
class VoiceNoteItem : public DBlurEffectWidget
{
    Q_OBJECT
public:
    VoiceNoteItem(NOTE note, NoteController *noteCtr);
    ~VoiceNoteItem();
    void init();
    bool getwaveformPoint(QRect &rect);
    int getNoteID();
    NOTE m_note;

    DLabel *m_timeLabel;
    DBlurEffectWidget *m_bgWidget;
    QVBoxLayout *m_itemLayout;
    QHBoxLayout *m_hBoxLayout;
    //DImageButton *m_ctrlBtn;
    DImageButton *m_menuBtn;
    QLabel *m_voiceTimeLabel;
    //QWidget *m_voiceShape;
    Waveform *m_waveform;

signals:
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void resumePlayingSignal(VoiceNoteItem * voiceNoteItem, QString filePath, QRect waveformRect);
    void pausePlayingSignal();

public slots:
    void handleStopPlay();
    void handlePausePlay();
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
