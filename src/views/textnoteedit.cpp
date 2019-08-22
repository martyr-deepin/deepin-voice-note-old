#include "textnoteedit.h"

#include <QMouseEvent>

#include <QDebug>

TextNoteEdit::TextNoteEdit(NOTE textNote, QWidget *parent, NoteController *noteCtr) : QTextEdit(parent)
{
    if (nullptr == noteCtr)
    {
        m_noteCtr = new NoteController();
    }
    else
    {
        m_noteCtr = noteCtr;
    }
    m_textNote = textNote;
    initConnection();
}

TextNoteEdit::TextNoteEdit(QWidget *parent, NoteController *noteCtr) : QTextEdit(parent)
{
    if (nullptr == noteCtr)
    {
        m_noteCtr = new NoteController();
    }
    else
    {
        m_noteCtr = noteCtr;
    }

    initConnection();
}


TextNoteEdit::~TextNoteEdit()
{

}

void TextNoteEdit::setTextNote(NOTE textNote)
{
    m_textNote = textNote;
    this->setText(m_textNote.contentText);
}

void TextNoteEdit::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
//    qDebug() << "TextNoteEdit::mousePressEvent" << this->lines();

//    //确保右键点击，然后跳出菜单.
//    if ((event->button() == Qt::LeftButton) && (this->document()->rowCount() > 5))
//    {
//        emit clicked();
//    }
//    //要继续保留QListWidget原有的点击事件.
    QTextEdit::mousePressEvent(event);
}
void TextNoteEdit::initConnection()
{
    connect(this, &TextNoteEdit::textChanged, this, &TextNoteEdit::updateNote);

}

void TextNoteEdit::updateNote()
{

    NOTE note = m_textNote;
    note.contentText = this->toPlainText();
    if(!m_noteCtr->updateNote(note))
    {
        //todo：弹出popup，保存失败
        qDebug()<< "error: update text note fail!";
    }
    else
    {
        m_textNote.contentText = this->toPlainText();
    }
}
