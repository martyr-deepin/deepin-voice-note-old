#include "loadwidget.h"

#include <QVBoxLayout>

#include <DLabel>

#include <DWaterProgress>
#include <DFontSizeManager>

DWIDGET_USE_NAMESPACE

LoadWidget::LoadWidget(QWidget *parent) :
    DFrame(parent)
{

    m_water = new DWaterProgress(this);
    m_water->setValue(1);
    m_water->setTextVisible(true);
    m_water->setFixedSize(QSize(49,49));

    m_deleteText = QString(tr("Deleteing..."));
    m_switchText = QString(tr("Loading..."));

    m_Text = new DLabel(this);
    m_Text->setObjectName("LoadWidgetLabel");
    m_Text->setForegroundRole(DPalette::WindowText);
    DFontSizeManager::instance()->bind(m_Text,DFontSizeManager::T6);

    auto vbox = new QVBoxLayout;
    setLayout(vbox);

    vbox->addStretch();
    vbox->addWidget(m_water, 0, Qt::AlignCenter);
    vbox->setSpacing(0);
    vbox->addSpacing(7);
    vbox->addWidget(m_Text, 0, Qt::AlignCenter);
    vbox->addStretch();
}

void LoadWidget::setValue(int value)
{
    m_water->setValue(value);
}

void LoadWidget::hideWidget()
{
    m_Text->clear();
    m_water->setValue(0);
    this->hide();
    m_water->stop();
}

void LoadWidget::showType(LoadType type)
{
    if(DELETEING == type)
    {
        m_Text->setText(m_deleteText);
    }
    else if(LOADING == type)
    {
        m_Text->setText(m_switchText);
    }
    else
    {
        m_Text->clear();
    }
    //this->show();
    m_water->start();
}
