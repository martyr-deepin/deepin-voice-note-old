#include "renameedit.h"
#include <QKeyEvent>
#include <QDebug>
#include <DPalette>
#include <DApplicationHelper>
#include <DStyleHelper>
#include <QStyleOption>

RenameEdit::RenameEdit(QWidget *parent) : DLineEdit(parent)
{
    m_isEdited = false;
    m_mouseIsIn = false;
}

void RenameEdit::setToEdited(bool flag)
{
    m_isEdited = flag;
}

void RenameEdit::tryToFouceout()
{
    if(m_isEdited && !m_mouseIsIn)
    {
        emit editingFinished();
    }
}

void RenameEdit::leaveEvent(QEvent *event)
{
    m_mouseIsIn = false;
    return QWidget::leaveEvent(event);
}

void RenameEdit::enterEvent(QEvent *event)
{
    m_mouseIsIn = true;
    return QWidget::enterEvent(event);
}

void RenameEdit::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            m_isEdited = false;
            emit editingFinished();
        break;
    }
    return QWidget::keyPressEvent(event);
}

//void RenameEdit::paintEvent(QPaintEvent *event)
//{
////    QPalette pl = this->palette();
////    pl.setColor(QPalette::Background,QColor(00,129,255));
////    pl.setBrush(QPalette::Background,QBrush(QColor(0,0,0,254)));
////    this->setPalette(pl);
////    QPalette pli = this->lineEdit()->palette();
////    pli.setColor(QPalette::Background,QColor(00,129,255));
////    pli.setBrush(QPalette::Background,QBrush(QColor(0,0,0,254)));
////    this->lineEdit()->setPalette(pli);

////    QPainter painter(this);
////    DPalette pa = DApplicationHelper::instance()->palette(this);
////                DStyleHelper styleHelper;
////                //QColor fillColor = styleHelper.getColor(static_cast<const QStyleOption *>(&option), pa, DPalette::ItemBackground);
////                QColor fillColor(00,129,255);
////                painter.setBrush(QBrush(fillColor));
////                painter.fillRect(this->rect(),fillColor);

//    return QWidget::paintEvent(event);
//}
