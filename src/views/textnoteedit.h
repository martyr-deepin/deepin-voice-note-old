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

    QString getText();
    void setHtml(const QString &text);
    void setPlainText(const QString &text);
    void setText(const QString &text);
    void setTextNote(NOTE textNote, QString searchKey);
    int getID();
    int getFolderID();
    void searchText(QString searchKey);
    void readFromDatabase();
    //QString onlyreadFromDatabase();
    QString onlyreadFromDatabase(QDateTime *time = nullptr);// liuyang 3547
    void setLineHeight(int value);
    int getLineHeight();
    QDateTime getUpdateTime(); //liuyang 3550 3547 3528
signals:
    void clicked();
    void focusOutSignal();
    void sigTextChanged(QString str);
    void sigTextHeightChanged(int newHeight); //Add 20191111
    void sigDelMyself();
    void SigTextEditGetFocus();  //Add bug 2587
    void SigTextEditOutFocus();  //Add bug 2587
    void sigDetailButtonChanged(const bool isVisible);

public slots:
    void updateNote();
    void textAreaChanged(); //Add 20191111
    void onTextChanged();


protected:
    void mousePressEvent(QMouseEvent *event)override;
    void focusInEvent(QFocusEvent *e)override;
    void focusOutEvent(QFocusEvent *e)override;
    void contextMenuEvent(QContextMenuEvent *e) override;//3699
    void wheelEvent(QWheelEvent *e)override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void insertFromMimeData(const QMimeData *source) override; //Add 4166
    void resizeEvent(QResizeEvent * event) override;

private:
    static bool doesFocusInToChangePlainText;
    static bool doesFocusOutToChangeHtml;
    NOTE m_textNote;
    NoteController *m_noteCtr;
    QString m_searchKey;
    bool menuOut = false;//3699
    void initConnection();

};

#endif // TEXTNOTEEDIT_H
