#ifndef TEXTNOTEEDIT_H
#define TEXTNOTEEDIT_H
#include <DTextEdit>
//#include <dtextedit.h>
#include <notecontroller.h>
#include <QObject>
#include <QTextEdit>
DWIDGET_USE_NAMESPACE

class TextNoteEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextNoteEdit(NOTE textNote, QWidget *parent = nullptr, NoteController *noteCtr = nullptr);
    TextNoteEdit(QWidget *parent = nullptr, NoteController *noteCtr = nullptr);
    ~TextNoteEdit();

    void setTextNote(NOTE textNote, QString searchKey);
    void searchText(QString searchKey);
signals:
    void clicked();

public slots:
    void updateNote();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    NOTE m_textNote;
    NoteController *m_noteCtr;

    void initConnection();

};

#endif // TEXTNOTEEDIT_H
