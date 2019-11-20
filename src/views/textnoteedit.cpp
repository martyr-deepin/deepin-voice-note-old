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

QString TextNoteEdit::getText()
{
    return toPlainText();
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

int TextNoteEdit::getFolderID()
{
    return m_textNote.folderId;
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
    if(this->getText().isEmpty())
    {
        emit sigDelMyself();
    }
    //emit focusOutSignal();
    DTextEdit::focusOutEvent(e);
}
void TextNoteEdit::initConnection()
{
    connect(this, &TextNoteEdit::textChanged, this, &TextNoteEdit::updateNote);
    connect(this->document(),SIGNAL(contentsChanged()),this,SLOT(textAreaChanged())); //Add 20191111
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
    //==== start add 20191105  bug2162
    if (!UiUtil::autoAddEditTxt(note))
    {
        qDebug() << "error: edit file error";
    }
    //==== end add 20191105  bug2162
    if(!m_noteCtr->updateNote(note))
    {
        //todo：弹出popup，保存失败
        qDebug()<< "error: update text note fail!";
    }
    else
    {
        m_textNote.contentText = this->toPlainText();
        emit sigTextChanged(m_textNote.contentText);
    }
}

//Add s 20191111
void TextNoteEdit::textAreaChanged()
{
    QTextDocument *document=qobject_cast<QTextDocument*>(sender());
    //document->adjustSize();
    if(document){
        QTextEdit *editor=qobject_cast<QTextEdit*>(document->parent()->parent());
        if (editor){
            //int newheight = document->size().rheight()+10;
            int newheight = document->size().rheight();
            if (newheight != editor->height()){
                qDebug()<<"newheight:"<<newheight;
                emit sigTextHeightChanged(newheight);
               //editor->setFixedHeight(newheight);
            }
        }
    }
}
//Add e 20191111

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

QString TextNoteEdit::onlyreadFromDatabase()
{
    return m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id);
}

