#ifndef TEXTNOTEITEM_H
#define TEXTNOTEITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <dimagebutton.h>
#include "consts.h"


DWIDGET_USE_NAMESPACE
class TextNoteItem : public QWidget
{
public:
    TextNoteItem(NOTE textNote);
    ~TextNoteItem();

    NOTE textNote;
    QLabel *m_timeLabel;
    QWidget *m_bgWidget;
    QHBoxLayout *m_hBoxLayout;
    QLabel *m_textLabel;
    DImageButton *m_menuBtn;



private:
    void initUI();
    void initConnection();
};

#endif // TEXTNOTEITEM_H
