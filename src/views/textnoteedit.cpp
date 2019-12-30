#include "textnoteedit.h"
#include "intancer.h"
#include <QMouseEvent>

#include <QDebug>
#include <uiutil.h>

#include <DMenu>//3699
#include <QTextBlock>
#include <DApplicationHelper> //add 3976

bool TextNoteEdit::doesFocusInToChangePlainText = false;
bool TextNoteEdit::doesFocusOutToChangeHtml = true;

TextNoteEdit::TextNoteEdit(NOTE textNote, QWidget *parent, NoteController *noteCtr) : DTextEdit(parent)
{
    //qDebug() << "TextNoteEdit::TextNoteEdit()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteEdit::TextNoteEdit()"), QString("TextNoteEdit::TextNoteEdit()"));

    if (nullptr == noteCtr)
    {
        m_noteCtr = new NoteController();
    }
    else
    {
        m_noteCtr = noteCtr;
    }
    m_textNote = textNote;
    m_wantFlag = false;
    //m_BgTextEdit = nullptr;
    //qDebug() << "this->m_textNote.contentText: " << this->m_textNote.contentText;
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->m_textNote.contentText:"), this->m_textNote.contentText);
    //add start 3976
    m_brush = this->palette().text();
    //add end 3976

    this->setPlainText(m_textNote.contentText);//liuyang 3550 3547 3528
    this->setLineHeight(26);

    initConnection();

//    QTextEdit *tmp = new QTextEdit(this);
//    tmp->setFixedSize(QSize(200,200));
//    tmp->move(200,0);
}

TextNoteEdit::TextNoteEdit(QWidget *parent, NoteController *noteCtr) : DTextEdit(parent)
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

    this->setLineHeight(26);
}

TextNoteEdit::~TextNoteEdit()
{

}

//void TextNoteEdit::setBgTextEdit(BgTextEdit *p)
//{
//    m_BgTextEdit = p;
//}

QString TextNoteEdit::getText()
{
    QString tmp = this->toPlainText();
    return tmp;
}

void TextNoteEdit::setHtml(const QString &text)
{
    //qDebug() << "TextNoteEdit::setHtml()";
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("text:"), text);

    int lastTextCursorPosition = this->textCursor().position();
//    qDebug() << "lastTextCursorPosition: " << lastTextCursorPosition;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("lastTextCursorPosition:"), QString::number(lastTextCursorPosition,10));

    DTextEdit::setHtml(text);

    QTextCursor textCursor = this->textCursor();
    textCursor.setPosition(lastTextCursorPosition);
    this->setTextCursor(textCursor);

    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());
    //qDebug() << "this->textCursor().position(): " << this->textCursor().position();
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("lastTextCursorPosition:"), QString::number(lastTextCursorPosition,10));
    UiUtil::writeLog(0, __FILE__, __LINE__, Q_FUNC_INFO, QString("textNum:"), QString::number(this->toPlainText().length(),10));
}

void TextNoteEdit::setPlainText(const QString &text)
{
    //qDebug() << "TextNoteEdit::setPlainText()";
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("text:"), text);

    int lastTextCursorPosition = this->textCursor().position();
    //qDebug() << "lastTextCursorPosition: " << lastTextCursorPosition;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("lastTextCursorPosition:"), QString::number(lastTextCursorPosition,10));

    DTextEdit::setPlainText(text);

    QTextCursor textCursor = this->textCursor();
    textCursor.setPosition(lastTextCursorPosition);
    this->setTextCursor(textCursor);

    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());
    //qDebug() << "this->textCursor().position(): " << this->textCursor().position();
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->textCursor().position():"), QString::number(this->textCursor().position(),10));
}

void TextNoteEdit::setText(const QString &text)
{
    //qDebug() << "TextNoteEdit::setText()";
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("text:"), text);

    int lastTextCursorPosition = this->textCursor().position();
//    qDebug() << "lastTextCursorPosition: " << lastTextCursorPosition;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("lastTextCursorPosition:"), QString::number(lastTextCursorPosition,10));

    DTextEdit::setText(text);

    QTextCursor textCursor = this->textCursor();
    textCursor.setPosition(lastTextCursorPosition);
    this->setTextCursor(textCursor);
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());
    //qDebug() << "this->textCursor().position(): " << this->textCursor().position();
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->textCursor().position():"), QString::number(this->textCursor().position(),10));
}

void TextNoteEdit::setTextNote(NOTE textNote, QString searchKey)
{
    //qDebug() << "TextNoteEdit::setTextNote()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteEdit::setTextNote()"), QString("TextNoteEdit::setTextNote()"));

    m_searchKey = searchKey;
    m_textNote = textNote;

    QString html = UiUtil::getHtmlText(m_textNote.contentText, 12, searchKey, BLUE);
    //qDebug() << "html: " << html;
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("html:"), html);

    this->setHtml(html);
    this->setLineHeight(26);
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
    //qDebug() << "TextNoteEdit::focusInEvent()";
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());
    Intancer::get_Intancer()->setWantScrollRightListFlag(false);

    if (this->doesFocusInToChangePlainText) {
        //qDebug() << "this->textCursor().position() before setText: " << this->textCursor().position();
        //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());

        //qDebug() << "this->textCursor().position() before setPlainText: " << this->textCursor().position();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->textCursor().position() before setPlainText:"), QString::number(this->textCursor().position(),10));
        this->setPlainText(this->toPlainText());
        //qDebug() << "this->textCursor().position() after setPlainText: " << this->textCursor().position();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->textCursor().position() after setPlainText:"), QString::number(this->textCursor().position(),10));

        this->setLineHeight(26);
    }

    //add start 3976
    QTextDocument *document = this->document();
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    color_format.setForeground(m_brush);

    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(Intancer::get_Intancer()->getSearchKeywords(), highlight_cursor, QTextDocument::FindCaseSensitively);
        //highlight_cursor = document->find(this->getText(), highlight_cursor, QTextDocument::FindCaseSensitively);
        if (!highlight_cursor.isNull()) {
            if(!found)
                found = true;
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //add end 3976

    DTextEdit::focusInEvent(e); //Add bug 2587
    emit SigTextEditGetFocus();
}

void TextNoteEdit::focusOutEvent(QFocusEvent *e)
{  
    //qDebug()<< "TextNoteEdit::focusOutEvent()";
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());
    this->moveCursor(QTextCursor::Start);
    //3699
    if(menuOut)
    {
        return;
    }
    //3699

    if(m_wantFlag)
    {
        return;
    }
    Intancer::get_Intancer()->setWantScrollRightListFlag(true);
//    if (this->isReadOnly())
//    {
//        return;
//    }
    //qDebug()<<"--------------------------------edit focusOutEvent";
    if(this->getText().isEmpty())
    {
        emit sigDelMyself();
    }
    //emit focusOutSignal();


   if (this->doesFocusOutToChangeHtml) {
        QString searchKeywords = Intancer::get_Intancer()->getSearchKeywords();
        //qDebug() << "searchKeywords: " << searchKeywords;
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("searchKeywords:"), searchKeywords);

        QString html = UiUtil::getHtmlText(this->toPlainText(),  12, searchKeywords, BLUE);
//        qDebug() << "html: " << html;

        //qDebug() << "this->textCursor().position() before setHtml: " << this->textCursor().position();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->textCursor().position() before setHtml:"), QString::number(this->textCursor().position(),10));
        this->setHtml(html);
        qDebug() << "this->textCursor().position() after setHtml: " << this->textCursor().position();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->textCursor().position() after setHtml:"), QString::number(this->textCursor().position(),10));

        //qDebug() << "this->setHtml() done";
        //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());

        this->setLineHeight(26);
    }
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
    //qDebug() << "TextNoteEdit::wheelEvent()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteEdit::wheelEvent()"), QString("TextNoteEdit::wheelEvent()"));

    if(!Intancer::get_Intancer()->getWantScrollRightListFlag()) {
        DTextEdit::wheelEvent(e);
    }
}

void TextNoteEdit::keyReleaseEvent(QKeyEvent *e)
{

    if(!e->isAutoRepeat()) {
        this->updateNote();
    }

    DTextEdit::keyReleaseEvent(e);
}
//Add start 4166
void TextNoteEdit::insertFromMimeData(const QMimeData *source)
{
    QMimeData newMimeData;
    newMimeData.setText(source->text());

    DTextEdit::insertFromMimeData(&newMimeData);

    this->setLineHeight(26);

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
    //qDebug() << "TextNoteEdit::updateNote()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteEdit::updateNote()"), QString("TextNoteEdit::updateNote()"));

    //3550-3547-3528 patch
//    //liuyang 3550 3547 3528
//    QString preContent = this->toPlainText();
//    if(preContent == m_textNote.contentText)
//    {
//        return;
//    }
//    //liuyang 3550 3547 3528

    if (this->isReadOnly()) {
        //qDebug() << "TextNoteEdit::updateNote" << "return";
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteEdit::updateNote return"), QString("TextNoteEdit::updateNote return"));
        return;
    }

    //qDebug() << "TextNoteEdit::updateNote(): " << "executed";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteEdit::updateNote() executed"), QString("TextNoteEdit::updateNote() executed"));

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

//    //==== start add 20191105  bug2162
//    if (!UiUtil::autoAddEditTxt(note)) {
//        //qDebug() << "error: edit file error";
//        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("error: edit file error"), QString("error: edit file error"));
//    }
//    //==== end add 20191105  bug2162
    if(!m_noteCtr->updateNote(note)) {
        //todo：弹出popup，保存失败
        //qDebug()<< "error: update text note fail!";
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("error: update text note fail!"), QString("error: update text note fail!"));
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
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("TextNoteEdit::textAreaChanged()"), QString("TextNoteEdit::textAreaChanged()"));
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());

    QTextDocument *document=qobject_cast<QTextDocument*>(sender());
    //document->adjustSize();
    if(document){
        QTextEdit *editor=qobject_cast<QTextEdit*>(document->parent()->parent());
        if (editor){
            //int newheight = document->size().rheight()+10;
            int newheight = document->size().rheight();
            if (newheight != editor->height()){
                //qDebug()<<"newheight:"<<newheight;
                UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("newheight:"), QString::number(newheight,10));
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

    QTimer::singleShot(0, this, [=]{

        int textEditHeight = this->height();
        int documentHeight = static_cast<int>(this->document()->size().height());

        //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->toPlainText():"), this->toPlainText());
//        qDebug() << "QTimer::singleShot() textEditHeight: " << textEditHeight;
//        qDebug() << "QTimer::singleShot() documentHeight: " << documentHeight;

        if (textEditHeight < documentHeight - 10) {
            emit sigDetailButtonChanged(true);
        }
        else {
            emit sigDetailButtonChanged(false);
        }
    });
    setDocRightMargin(m_docRightMargin);
}

//add start 3976
void TextNoteEdit::changeTheme()
{
    m_brush = this->palette().text();
}
//add end 3976

void TextNoteEdit::searchText(QString searchKey)
{
    m_searchKey = searchKey;

    QString html = UiUtil::getHtmlText(this->toPlainText(), 12, searchKey, BLUE);
    //qDebug() << "html: " << html;
    //UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("html:"), html);

    this->setHtml(html);
    this->setLineHeight(26);
}

void TextNoteEdit::readFromDatabase()
{
    m_textNote.contentText = m_noteCtr->getConttextByNoteID(m_textNote.folderId,m_textNote.id);

    //qDebug() << "this->m_textNote.contentText: " << this->m_textNote.contentText;
    //UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("this->m_textNote.contentText:"), this->m_textNote.contentText);

    this->setText(m_textNote.contentText);
    this->setLineHeight(26);
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

void TextNoteEdit::prepareTODelete()
{
    m_wantFlag = true;
}

void TextNoteEdit::setDocRightMargin(int margin)
{
    if(margin != 0)
    {
        m_docRightMargin = margin;
        QTextDocument *document = this->document();
        for (QTextBlock it = document->begin(); it != document->end(); it = it.next()) {
            QTextCursor textCursor(it);
            QTextBlockFormat textBlockFormat = it.blockFormat();
            int right = static_cast<int>(textBlockFormat.rightMargin());
            if(right != margin)
            {
                textBlockFormat.setRightMargin(margin);
                textCursor.setBlockFormat(textBlockFormat);
            }
        }
    }
}
