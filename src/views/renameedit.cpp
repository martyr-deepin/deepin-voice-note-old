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
