#include "searchnonepage.h"
#include <DFontSizeManager>
#include <DApplicationHelper>

SearchNonePage::SearchNonePage(QWidget *parent) : DFrame(parent)
{
    m_Text = new DLabel(this);
    m_Text->setText(QString(tr("无结果")));
//    QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T4);
//    m_Text->setFont(labelFont);
    DFontSizeManager::instance()->bind(m_Text,DFontSizeManager::T4);
    m_Text->setFixedSize(QSize(60,29));
    m_Text->setAlignment(Qt::AlignCenter);
    m_Text->move((this->width() - m_Text->width())/2,(this->height() - m_Text->height())/2);

    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &SearchNonePage::onChangeColor);
}

void SearchNonePage::resizeEvent(QResizeEvent * event)
{
    DFrame::resizeEvent(event);
    checkPos();
}

void SearchNonePage::onChangeColor()
{

}

void SearchNonePage::checkPos()
{
    m_Text->move((this->width() - m_Text->width())/2,(this->height() - m_Text->height())/2);
}
