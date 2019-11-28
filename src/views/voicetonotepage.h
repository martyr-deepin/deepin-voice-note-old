#ifndef VOICETONOTEPAGE_H
#define VOICETONOTEPAGE_H

#include <DWidget>
#include <QVBoxLayout>
#include <DPalette>
#include <DFrame>
#include "textnoteedit.h"

DWIDGET_USE_NAMESPACE
class VoiceToNotePage : public DWidget
{
    Q_OBJECT
public:
    explicit VoiceToNotePage(QWidget *parent = nullptr);
    void ToDetalVoicePage(QString contant);

signals:

public slots:


private:
    QVBoxLayout *m_detailPageLayout;
    TextNoteEdit *m_textNoteEdit;
};

#endif // VOICETONOTEPAGE_H
