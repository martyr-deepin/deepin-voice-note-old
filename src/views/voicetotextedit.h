#ifndef VOICETOTEXTEDIT_H
#define VOICETOTEXTEDIT_H
#include <DTextEdit>
#include <QObject>
#include <QTextEdit>
DWIDGET_USE_NAMESPACE

class VoiceToTextEdit : public DTextEdit
{
    Q_OBJECT
public:
    explicit VoiceToTextEdit(QWidget *parent = nullptr);
    QString getText();
    void setTextAndLineheight(QString str);
signals:
    void sigTextHeightChanged(int newHeight);

public slots:
    void textAreaChanged(); //Add 20191111

private:
    void initConnection();
    void setLineHeight(int value);
};

#endif // VOICETOTEXTEDIT_H
