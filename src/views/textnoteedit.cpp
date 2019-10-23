#include "textnoteedit.h"

#include <QMouseEvent>

#include <QDebug>
#include <uiutil.h>

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

void TextNoteEdit::setTextNote(NOTE textNote, QString searchKey)
{
    m_searchKey = searchKey;
    m_textNote = textNote;
    this->setHtml(UiUtil::getHtmlText(m_textNote.contentText, 12, searchKey, BLUE));
}

int TextNoteEdit::getID()
{
    return m_textNote.id;
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
    //要继续保留QListWidget原有的点击事件.
    QTextEdit::mousePressEvent(event);
}

void TextNoteEdit::focusOutEvent(QFocusEvent *e)
{
    if (this->isReadOnly())
    {
        return;
    }
    qDebug()<<"--------------------------------edit focusOutEvent";
    emit focusOutSignal();
}
void TextNoteEdit::initConnection()
{
    connect(this, &TextNoteEdit::textChanged, this, &TextNoteEdit::updateNote);
}

void TextNoteEdit::updateNote()
{
    qDebug() << "TextNoteEdit::updateNote" << "start";
    if (this->isReadOnly())
    {
        qDebug() << "TextNoteEdit::updateNote" << "return";
        return;
    }
    qDebug() << "TextNoteEdit::updateNote" << "exec";
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

void TextNoteEdit::searchText(QString searchKey)
{
    m_searchKey = searchKey;
    this->setHtml(UiUtil::getHtmlText(this->toPlainText(), 12, searchKey, BLUE));
}

void TextNoteEdit::readFromDatabase()
{
    m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id);
    this->setText(m_textNote.contentText);
}

