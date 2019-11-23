#include "textnoteedit.h"
#include "intancer.h"
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
    this->setText(m_textNote.contentText);//liuyang 3550 3547 3528
    initConnection();

//    QTextEdit *tmp = new QTextEdit(this);
//    tmp->setFixedSize(QSize(200,200));
//    tmp->move(200,0);

    setLineHeight(24);
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
    setLineHeight(24);
}


TextNoteEdit::~TextNoteEdit()
{

}

QString TextNoteEdit::getText()
{
    QString tmp = this->toPlainText();
    return tmp;
}

void TextNoteEdit::setTextNote(NOTE textNote, QString searchKey)
{
    m_searchKey = searchKey;
    m_textNote = textNote;
    this->setText(UiUtil::getHtmlText(m_textNote.contentText, 12, searchKey, BLUE));
    //this->setHtml(UiUtil::getHtmlText(m_textNote.contentText, 12, searchKey, BLUE));
    setLineHeight(24);
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

void TextNoteEdit::focusInEvent(QFocusEvent *e)
{
    Intancer::get_Intancer()->setWantScrollRightListFlag(false);
    qDebug()<<"TextNoteEdit::focusInEvent";

    DTextEdit::focusInEvent(e);//Add bug 2587
    emit SigTextEditGetFocus();
}

void TextNoteEdit::focusOutEvent(QFocusEvent *e)
{
    Intancer::get_Intancer()->setWantScrollRightListFlag(true);
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

    qDebug()<<"TextNoteEdit::focusOutEvent";
    DTextEdit::focusOutEvent(e);
    emit SigTextEditOutFocus();  //Add bug 2587
}

void TextNoteEdit::wheelEvent(QWheelEvent *e)
{
    qDebug()<<"RightNoteList::wheelEvent";

    if(!Intancer::get_Intancer()->getWantScrollRightListFlag())
    {
        DTextEdit::wheelEvent(e);
    }
}

void TextNoteEdit::initConnection()
{
    connect(this, &TextNoteEdit::textChanged, this, &TextNoteEdit::updateNote);
    connect(this->document(),SIGNAL(contentsChanged()),this,SLOT(textAreaChanged())); //Add 20191111
}

void TextNoteEdit::updateNote()
{
    //liuyang 3550 3547 3528
    QString preContent = this->toPlainText();
    if(preContent == m_textNote.contentText)
    {
        return;
    }
    //liuyang 3550 3547 3528
    qDebug() << "TextNoteEdit::updateNote" << "start";
    if (this->isReadOnly())
    {
        qDebug() << "TextNoteEdit::updateNote" << "return";
        return;
    }
    qDebug() << "TextNoteEdit::updateNote" << "exec";
    NOTE note = m_textNote;



    //note.contentText = this->toPlainText();//liuyang 3550 3547 3528
    //liuyang 3550 3547 3528
    note.contentText = preContent;
    note.createTime = QDateTime::currentDateTime();
    //liuyang 3550 3547 3528

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
        //liuyang 3550 3547 3528
        m_textNote.createTime = note.createTime;
        //liuyang 3550 3547 3528
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
    this->setText(UiUtil::getHtmlText(this->toPlainText(), 12, searchKey, BLUE));
    //this->setHtml(UiUtil::getHtmlText(this->toPlainText(), 12, searchKey, BLUE));
    setLineHeight(24);
}

void TextNoteEdit::readFromDatabase()
{
    m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id);
    this->setText(m_textNote.contentText);
    setLineHeight(24);
}

QString TextNoteEdit::onlyreadFromDatabase()
{
    return m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id);
}

void TextNoteEdit::setLineHeight(int value)
{
    QTextCursor textCursor = this->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(value, QTextBlockFormat::FixedHeight);//设置固定行高
    textCursor.setBlockFormat(textBlockFormat);
    this->setTextCursor(textCursor);
}

int TextNoteEdit::getLineHeight()
{
    int height = 0;
    QTextDocument *document=qobject_cast<QTextDocument*>(sender());
    //document->adjustSize();
    if(document){
        QTextEdit *editor=qobject_cast<QTextEdit*>(document->parent()->parent());
        if (editor){
            //int newheight = document->size().rheight()+10;
            height = document->size().rheight();
        }
    }
    return height;
}

//liuyang 3550 3547 3528
QDateTime TextNoteEdit::getUpdateTime()
{
    return m_textNote.createTime;
}
//liuyang 3550 3547 3528
