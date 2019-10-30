#include "addfolderbutton.h"
#include <DStyleOptionButton>
#include <DApplicationHelper>
#include <QDebug>
DWIDGET_USE_NAMESPACE

AddFolderButton::AddFolderButton(QWidget *parent) : DFloatingButton(parent)
{

}

void AddFolderButton::initStyleOption(DStyleOptionButton *option) const
{
    DFloatingButton::initStyleOption(option);
//    DPalette pa;
//    DApplicationHelper::instance()->palette(this);
//    pa.setBrush(DPalette::Highlight, pa.color(DPalette::TextWarning));
//    option->palette = pa;
}

