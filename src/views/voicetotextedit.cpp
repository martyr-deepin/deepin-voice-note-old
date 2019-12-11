#include "voicetotextedit.h"
#include "uiutil.h"
#include "intancer.h"

#include <QDebug>
VoiceToTextEdit::VoiceToTextEdit(QWidget *parent) : DTextEdit(parent)
{
    initConnection();
}

QString VoiceToTextEdit::getText()
{
    QString tmp = this->toPlainText();
    return tmp;
}

void VoiceToTextEdit::setTextAndLineheight(QString str)
{
    this->setText(str);
    //this->setText(UiUtil::getHtmlText(str, 12, "", BLUE));
    this->setLineHeight(24);
}

int VoiceToTextEdit::getLineHeight()
{
    int documentHeight = 0;
//    QTimer::singleShot(0, this, [=]{

//        documentHeight = static_cast<int>(this->document()->size().height());
//        qDebug()<<"documentHeight:"<<documentHeight;
//    });

//    documentHeight = static_cast<int>(this->document()->size().height());
//    qDebug()<<"documentHeight_2:"<<documentHeight;
    return documentHeight;
}

void VoiceToTextEdit::textAreaChanged()
{
        QTimer::singleShot(0, this, [=]{

            int documentHeight = static_cast<int>(this->document()->size().height());
            emit sigTextHeightChanged(documentHeight);
            qDebug()<<"documentHeight:"<<documentHeight;
        });
//    QTextDocument *document=qobject_cast<QTextDocument*>(sender());
//    if(document){
//        QTextEdit *editor=qobject_cast<QTextEdit*>(document->parent()->parent());
//        if (editor){
//            int newheight = document->size().rheight();
//                //qDebug()<<"newheight:"<<newheight;
//                UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("newheight:"), QString::number(newheight,10));
//                emit sigTextHeightChanged(newheight);
//        }
//    }
}

void VoiceToTextEdit::wheelEvent(QWheelEvent *e)
{
    //qDebug() << "VoiceToTextEdit::wheelEvent()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceToTextEdit::wheelEvent():"), QString("VoiceToTextEdit::wheelEvent():"));
    if(!Intancer::get_Intancer()->getWantScrollRightListFlag()) {
        DTextEdit::wheelEvent(e);
    }
}

void VoiceToTextEdit::focusInEvent(QFocusEvent *e)
{
    Intancer::get_Intancer()->setWantScrollRightListFlag(false);
    DTextEdit::focusInEvent(e);
}

void VoiceToTextEdit::focusOutEvent(QFocusEvent *e)
{
    Intancer::get_Intancer()->setWantScrollRightListFlag(true);
    DTextEdit::focusOutEvent(e);
}

void VoiceToTextEdit::resizeEvent(QResizeEvent * event)
{
    DTextEdit::resizeEvent(event);
    QTimer::singleShot(0, this, [=]{
        int documentHeight = static_cast<int>(this->document()->size().height());
        emit sigTextHeightChanged(documentHeight);
    });
}

//void VoiceToTextEdit::onTextChanged()
//{

//    QTimer::singleShot(0, this, [=]{

//        int textEditHeight = this->height();
//        int documentHeight = static_cast<int>(this->document()->size().height());

//        if (textEditHeight < documentHeight - 3) {
//            emit sigDetailButtonChanged(true);
//        }
//        else {
//            emit sigDetailButtonChanged(false);
//        }
//    });
//}

void VoiceToTextEdit::initConnection()
{

    connect(this->document(), &QTextDocument::modificationChanged, this, &VoiceToTextEdit::textAreaChanged);
}

void VoiceToTextEdit::setLineHeight(int value)
{
    QTextCursor textCursor = this->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(value, QTextBlockFormat::FixedHeight);//设置固定行高
    textCursor.setBlockFormat(textBlockFormat);
    this->setTextCursor(textCursor);
}

