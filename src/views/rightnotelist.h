#ifndef RIGHTNOTELIST_H
#define RIGHTNOTELIST_H

#include "textnoteitem.h"
#include "voicenoteitem.h"

#include <QListWidget>
#include <notecontroller.h>
#include <consts.h>
#include <QObject>
#include <darrowrectangle.h>
#include <DDialog>
#include <QMediaPlayer>
//#include <DArrowRectangle>

DWIDGET_USE_NAMESPACE

class RightNoteList : public QListWidget
{
    Q_OBJECT
public:
    RightNoteList(NoteController *noteController);
    ~RightNoteList();
    void addWidgetItem(NOTE note);

signals:
    void textEditClicked(NOTE textNote);


public slots:
    void handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
    void handleDelItem(bool);
    void handleSaveAsItem(bool);
    void handleDelDialogClicked(int index, const QString &text);
    void handlePlayingStateChanged(QMediaPlayer::State state);
    void play(VoiceNoteItem * voiceNoteItem, QString filepath);
    void pause();
    void handleClickRecordButton();

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
    void initUI();
    void initConnection();


    QString getPlayingFilepath();
};

#endif // RIGHTNOTELIST_H
