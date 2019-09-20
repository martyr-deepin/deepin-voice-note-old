#ifndef RIGHTNOTELIST_H
#define RIGHTNOTELIST_H

#include "fileexistsdialog.h"
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

//右侧文字语音记录列表
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
    void handleSaveFileEnd(bool);

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
    FileExistsDialog *m_fileExistsDialog;
    DDialog *m_saveFileEndDialog;

    QString m_defaultTxtName;
    QString m_defaultTxtPath;
    QString m_defaultAudioName;
    QString m_defaultAudioPath;
    //MyCustomSlider *m_myslider;
    void initUI();
    void initConnection();
    void showFileDialog(SAVE_INFO saveInfo);


    QString getPlayingFilepath();
};

#endif // RIGHTNOTELIST_H
