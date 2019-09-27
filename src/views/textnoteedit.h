#ifndef TEXTNOTEEDIT_H
#define TEXTNOTEEDIT_H
#include <DTextEdit>
//#include <dtextedit.h>
#include <notecontroller.h>
#include <QObject>
#include <QTextEdit>
DWIDGET_USE_NAMESPACE

//文字编辑框(Detal和非Deltal都在使用)
class TextNoteEdit : public DTextEdit
//class TextNoteEdit : public QTextEdit
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
    void focusOutSignal();

public slots:
    void updateNote();

protected:
    void mousePressEvent(QMouseEvent *event);
    void focusOutEvent(QFocusEvent *e);

private:
    NOTE m_textNote;
    NoteController *m_noteCtr;
    QString m_searchKey;

    void initConnection();

};

#endif // TEXTNOTEEDIT_H
