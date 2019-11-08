#include "sliderhandler.h"
#include "uiutil.h"
#include <DFontSizeManager>

SliderHandler::SliderHandler(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnection();
}

SliderHandler::~SliderHandler()
{

}


void SliderHandler::initUI()
{
    this->setFixedSize(38, 127);
    m_timeLabel = new QLabel(this);
    m_timeLabel->setGeometry(0, 0, 38, 27);
    //m_timeLabel->setFixedSize(38, 27);
    //m_timeLabel->setPixmap(UiUtil::getPixmap(m_timeLabel->size(), ":/image/time_label.png"));
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/image/time_label.png")));
    m_timeLabel->setAutoFillBackground(true);
    m_timeLabel->setPalette(pal);
    m_timeLabel->setAlignment(Qt::AlignHCenter| Qt::AlignTop);

    QFont labelFont = DFontSizeManager::instance()->get(DFontSizeManager::T8);
    m_timeLabel->setFont(labelFont);

    m_line = new QLabel(this);
    m_line->setGeometry(18, 28, 2, 64);
    //m_line->setFixedSize(2, 57);
    m_line->setPixmap(UiUtil::getPixmap(m_line->size(), ":/image/slider_handle_line.png"));
    m_handle = new QLabel(this);
    m_handle->setGeometry(4, 84, 30, 36);
    //m_handle->setFixedSize(30, 36);
    m_handle->setPixmap(UiUtil::getPixmap(m_handle->size(), ":/image/slider_handle.png"));

//    m_layout = new QVBoxLayout;
//    m_layout->setContentsMargins(0, 0, 0, 0);
//    m_layout->addWidget(m_timeLabel);
//    m_layout->addWidget(m_line);
//    m_layout->addWidget(m_handle);
//    this->setLayout(m_layout);
}

void SliderHandler::initConnection()
{

}
