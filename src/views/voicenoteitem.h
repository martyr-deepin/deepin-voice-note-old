#ifndef VOICENOTEITEM_H
#define VOICENOTEITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <dimagebutton.h>
#include "consts.h"
#include "notecontroller.h"

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
    DImageButton *m_ctrlBtn;
    DImageButton *m_menuBtn;
    QLabel *m_voiceTimeLabel;
    QWidget *m_voiceShape;

signals:
    void menuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, QWidget *textNoteItem, NOTE note);
public slots:

private:
    NoteController *m_noteCtr;
    void initUI();
    void initConnection();
    void handleMenuBtnClicked();
};

#endif // VOICENOTEITEM_H
