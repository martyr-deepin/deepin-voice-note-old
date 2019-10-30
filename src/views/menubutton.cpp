#include "menubutton.h"
#include <DStyleOptionButton>
#include <DApplicationHelper>

DWIDGET_USE_NAMESPACE

MenuButton::MenuButton(QWidget *parent) : DFloatingButton(parent)
{

}

void MenuButton::setBtnPalette()
{
    DStyleOptionButton *pop = new DStyleOptionButton();
    DPalette pa;
    DApplicationHelper::instance()->palette(this);
    pa.setBrush(DPalette::Highlight, pa.color(DPalette::Base));
    pop->palette = pa;
    this->initStyleOption(pop);
}

