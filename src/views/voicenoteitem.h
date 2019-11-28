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
#include "myrecodebuttons.h"
#include <DFrame>
#include <DLineEdit>    //Add 20191111
#include "textnoteedit.h" //Add 20191111
#include "menubutton.h"  //ynbboy
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
    void setMenuBtnEnabled(bool enabled);  //Add 20191111
    void setTextEditVal(QString txt); //Add 20191111
    void setTextEditAlignment(Qt::Alignment a);

    void setLineEditDisplay(bool disp); //true: 显示 fasle:隐藏  Add 20191111
    void setTextEditDisplay(bool disp); //true: 显示 fasle:隐藏  Add 20191111
    NOTE m_note;

    DLabel *m_timeLabel;
    // DLabel *m_arsLabel;         //Add 20191111
    DFrame *m_bgWidget;
    DWidget *m_bgWidgetBytext;   //Add 20191111
    DWidget *m_bgWidgetByplay;   //Add 20191111
    DWidget *m_bgWidgetBydetailBtn; //ynbboy
    QVBoxLayout *m_itemLayout;
    QVBoxLayout *m_ayoutBybgWidget; //Add 20191111
    QHBoxLayout *m_hBoxLayout;
    QHBoxLayout *m_hBoxLayoutBytext; //Add 20191111
    //DImageButton *m_ctrlBtn;
    MyRecodeButtons *m_menuBtn;
    //DIconButton *m_menuBtn;
    //DImageButton *m_menuBtn;
    DLabel *m_voiceTimeLabel;
    //QWidget *m_voiceShape;
    Waveform *m_waveform;
    MenuButton *m_detailBtn;  //ynbboy
signals:
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void resumePlayingSignal(VoiceNoteItem * voiceNoteItem, QString filePath, QRect waveformRect, NOTE note); //Edit  bug 2587
    //void resumePlayingSignal(VoiceNoteItem * voiceNoteItem, QString filePath, QRect waveformRect);
    void pausePlayingSignal();
    void sig_menuBtnPressed();
    void sig_menuBtnReleased();
    void buttonClicled();
    void sigTextHeightChanged(int newHeight); //Add 20191111
    void sigToDetalVoicePage(QString contant);

public slots:
    void handleStopPlay();
    void handlePausePlay();
    void handleResumePlaying();
    void setPlayDisable();
    void setPlayEnable();
    void changeTheme();
    void onToDetalVoicePage();
    void onDetailButtonChanged(const bool isVisible);
    //void handle

    //3152 liuyang
protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    //3152 liuyang
private:
    NoteController *m_noteCtr;
    PlayingButton *m_playingButton;
    TextNoteEdit *m_textEdit;  //Add 20191111
    DLineEdit *m_LineEdit;  //Add 20191111
    void initUI();
    void initConnection();
    void handleMenuBtnClicked();
};

#endif // VOICENOTEITEM_H
