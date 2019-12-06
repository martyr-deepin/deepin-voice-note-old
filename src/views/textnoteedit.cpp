#include "textnoteedit.h"
#include "intancer.h"
#include <QMouseEvent>

#include <QDebug>
#include <uiutil.h>

#include <DMenu>//3699
#include <QTextBlock>

TextNoteEdit::TextNoteEdit(NOTE textNote, QWidget *parent, NoteController *noteCtr) : QTextEdit(parent)
{
    qDebug() << "TextNoteEdit::TextNoteEdit()";

    if (nullptr == noteCtr)
    {
        m_noteCtr = new NoteController();
    }
    else
    {
        m_noteCtr = noteCtr;
    }
    m_textNote = textNote;

    qDebug() << "this->m_textNote.contentText: " << this->m_textNote.contentText;

    this->setPlainText(m_textNote.contentText);//liuyang 3550 3547 3528
    this->setLineHeight(24);

    initConnection();

//    QTextEdit *tmp = new QTextEdit(this);
//    tmp->setFixedSize(QSize(200,200));
//    tmp->move(200,0);
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

    this->setLineHeight(24);
}

TextNoteEdit::~TextNoteEdit()
{

}

QString TextNoteEdit::getText()
{
    QString tmp = this->toPlainText();
    return tmp;
}

void TextNoteEdit::setHtml(const QString &text)
{
    qDebug() << "TextNoteEdit::setHtml()";
    qDebug() << "text: " << text;

    int lastTextCursorPosition = this->textCursor().position();
    qDebug() << "lastTextCursorPosition: " << lastTextCursorPosition;

    DTextEdit::setHtml(text);

    QTextCursor textCursor = this->textCursor();
    textCursor.setPosition(lastTextCursorPosition);
    this->setTextCursor(textCursor);

    qDebug() << "this->toPlainText(): " << this->toPlainText();
    qDebug() << "this->textCursor().position(): " << this->textCursor().position();
}

void TextNoteEdit::setPlainText(const QString &text)
{
    qDebug() << "TextNoteEdit::setPlainText()";
    qDebug() << "text: " << text;

    int lastTextCursorPosition = this->textCursor().position();
    qDebug() << "lastTextCursorPosition: " << lastTextCursorPosition;

    DTextEdit::setPlainText(text);

    QTextCursor textCursor = this->textCursor();
    textCursor.setPosition(lastTextCursorPosition);
    this->setTextCursor(textCursor);

    qDebug() << "this->toPlainText(): " << this->toPlainText();
    qDebug() << "this->textCursor().position(): " << this->textCursor().position();
}

void TextNoteEdit::setText(const QString &text)
{
    qDebug() << "TextNoteEdit::setText()";
    qDebug() << "text: " << text;

    int lastTextCursorPosition = this->textCursor().position();
    qDebug() << "lastTextCursorPosition: " << lastTextCursorPosition;

    DTextEdit::setText(text);

    QTextCursor textCursor = this->textCursor();
    textCursor.setPosition(lastTextCursorPosition);
    this->setTextCursor(textCursor);

    qDebug() << "this->toPlainText(): " << this->toPlainText();
    qDebug() << "this->textCursor().position(): " << this->textCursor().position();
}

void TextNoteEdit::setTextNote(NOTE textNote, QString searchKey)
{
    qDebug() << "TextNoteEdit::setTextNote()";

    m_searchKey = searchKey;
    m_textNote = textNote;

    QString html = UiUtil::getHtmlText(m_textNote.contentText, 12, searchKey, BLUE);
    qDebug() << "html: " << html;

    this->setHtml(html);
    this->setLineHeight(24);
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
    qDebug() << "TextNoteEdit::focusInEvent()";
    qDebug() << "this->toPlainText(): " << this->toPlainText();

    Intancer::get_Intancer()->setWantScrollRightListFlag(false);

    qDebug() << "this->textCursor().position() before setText: " << this->textCursor().position();

    qDebug() << "this->toPlainText(): " << this->toPlainText();

    qDebug() << "this->textCursor().position() before setPlainText: " << this->textCursor().position();
    this->setPlainText(this->toPlainText());
    qDebug() << "this->textCursor().position() after setPlainText: " << this->textCursor().position();

    this->setLineHeight(24);

    DTextEdit::focusInEvent(e); //Add bug 2587

    emit SigTextEditGetFocus();
}

void TextNoteEdit::focusOutEvent(QFocusEvent *e)
{  
    qDebug()<< "TextNoteEdit::focusOutEvent()";
    qDebug()<< "this->toPlainText(): " << this->toPlainText();

    //3699
    if(menuOut)
    {
        return;
    }
    //3699
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

    QString searchKeywords = Intancer::get_Intancer()->getSearchKeywords();
    qDebug() << "searchKeywords: " << searchKeywords;

    QString html = UiUtil::getHtmlText(this->toPlainText(),  12, searchKeywords, BLUE);
    qDebug() << "html: " << html;

    qDebug() << "this->textCursor().position() before setHtml: " << this->textCursor().position();
    this->setHtml(html);
    qDebug() << "this->textCursor().position() after setHtml: " << this->textCursor().position();

    qDebug() << "this->setHtml() done";
    qDebug() << "this->toPlainText(): " << this->toPlainText();

    this->setLineHeight(24);

    DTextEdit::focusOutEvent(e);

    emit SigTextEditOutFocus();  //Add bug 2587
}

//3699
void TextNoteEdit::contextMenuEvent(QContextMenuEvent *e)
{
    menuOut = true;

    DTextEdit::contextMenuEvent(e);

    menuOut = false;
}

//3699
void TextNoteEdit::wheelEvent(QWheelEvent *e)
{
    qDebug() << "TextNoteEdit::wheelEvent()";

    if(!Intancer::get_Intancer()->getWantScrollRightListFlag()) {
        DTextEdit::wheelEvent(e);
    }
}

void TextNoteEdit::keyReleaseEvent(QKeyEvent *e)
{
//    qDebug() << "TextNoteEdit::keyReleaseEvent()";

    if(!e->isAutoRepeat()) {
        this->updateNote();
    }

    DTextEdit::keyReleaseEvent(e);
}
//Add start 4166
void TextNoteEdit::insertFromMimeData(const QMimeData *source)
{
    DTextEdit::insertFromMimeData(source);
    this->updateNote();
}
//Add end 4166

void TextNoteEdit::resizeEvent(QResizeEvent * event)
{
    DTextEdit::resizeEvent(event);
    onTextChanged();
}

void TextNoteEdit::initConnection()
{
    connect(this->document(), &QTextDocument::modificationChanged, this, &TextNoteEdit::textAreaChanged); //Add 20191111
    connect(this, &TextNoteEdit::textChanged, this, &TextNoteEdit::onTextChanged);
}

void TextNoteEdit::updateNote()
{
    qDebug() << "TextNoteEdit::updateNote()";

    //3550-3547-3528 patch
//    //liuyang 3550 3547 3528
//    QString preContent = this->toPlainText();
//    if(preContent == m_textNote.contentText)
//    {
//        return;
//    }
//    //liuyang 3550 3547 3528

    if (this->isReadOnly()) {
        qDebug() << "TextNoteEdit::updateNote" << "return";
        return;
    }

    qDebug() << "TextNoteEdit::updateNote(): " << "executed";

    //3550-3547-3528 patch
    //liuyang 3550 3547 3528
    QString preContent = this->toPlainText();
    if (preContent == m_textNote.contentText) {
        return;
    }
    //liuyang 3550 3547 3528
    NOTE note = m_textNote;

    //note.contentText = this->toPlainText();//liuyang 3550 3547 3528
    //liuyang 3550 3547 3528
    note.contentText = preContent;
    note.createTime = QDateTime::currentDateTime();
    //liuyang 3550 3547 3528

    //==== start add 20191105  bug2162
    if (!UiUtil::autoAddEditTxt(note)) {
        qDebug() << "error: edit file error";
    }
    //==== end add 20191105  bug2162
    if(!m_noteCtr->updateNote(note)) {
        //todo：弹出popup，保存失败
        qDebug()<< "error: update text note fail!";
    }
    else {
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
    qDebug() << "TextNoteEdit::textAreaChanged()";
    qDebug() << "this->toPlainText(): " << this->toPlainText();

    QTextDocument *document=qobject_cast<QTextDocument*>(sender());
    //document->adjustSize();
    if(document){
        QTextEdit *editor=qobject_cast<QTextEdit*>(document->parent()->parent());
        if (editor){
            //int newheight = document->size().rheight()+10;
            int newheight = document->size().rheight();
            if (newheight != editor->height()){
                qDebug()<<"newheight:"<<newheight;
                //3550-3547-3528 patch

                //3550-3547-3528 patch
                emit sigTextHeightChanged(newheight);
               //editor->setFixedHeight(newheight);
            }
        }
    }
}
//Add e 20191111

void TextNoteEdit::onTextChanged()
{
//    qDebug() << "TextNoteEdit::onTextChanged()";

    QTimer::singleShot(0, this, [=]{
//        qDebug() << "QTimer::singleShot()";

        int textEditHeight = this->height();
        int documentHeight = static_cast<int>(this->document()->size().height());

//        qDebug() << "QTimer::singleShot() this->toPlainText(): " << this->toPlainText();
        qDebug() << "QTimer::singleShot() textEditHeight: " << textEditHeight;
        qDebug() << "QTimer::singleShot() documentHeight: " << documentHeight;

        if (textEditHeight < documentHeight - 3) {
            emit sigDetailButtonChanged(true);
        }
        else {
            emit sigDetailButtonChanged(false);
        }
    });
}

void TextNoteEdit::searchText(QString searchKey)
{
    m_searchKey = searchKey;

    QString html = UiUtil::getHtmlText(this->toPlainText(), 12, searchKey, BLUE);
    qDebug() << "html: " << html;

    this->setHtml(html);
    this->setLineHeight(24);
}

void TextNoteEdit::readFromDatabase()
{
    m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id);

    qDebug() << "this->m_textNote.contentText: " << this->m_textNote.contentText;

    this->setText(m_textNote.contentText);
    this->setLineHeight(24);
}

//QString TextNoteEdit::onlyreadFromDatabase()
QString TextNoteEdit::onlyreadFromDatabase(QDateTime *time)//liuyang 3547
{
    //return m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id);
    return m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id,time);//liuyang 3547
}

void TextNoteEdit::setLineHeight(int value)
{
    QTextDocument *textDocument = this->document();
    for (QTextBlock it = textDocument->begin(); it != textDocument->end(); it = it.next()) {
        QTextCursor textCursor(it);
        QTextBlockFormat textBlockFormat = it.blockFormat();
        textBlockFormat.setLineHeight(value, QTextBlockFormat::FixedHeight);
        textCursor.setBlockFormat(textBlockFormat);
    }
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
