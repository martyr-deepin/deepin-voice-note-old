#include "sliderhandle.h"
#include <QPainter>




SliderHandle::SliderHandle(QString imgpath, QWidget *parent) : DLabel(parent)
{
    setFixedSize(50, 141);
    m_imgpath = imgpath;
    m_timelabel = new DLabel(this);
    m_timelabel->setFixedSize(QSize(30,18));
    m_timelabel->move(10,12);
    //m_timelabel->move(10,50);

    QPalette pal;
    pal.setColor(QPalette::WindowText,QColor(Qt::white));
    //pal.setColor(QPalette::WindowText,QColor(QRgb(0xFFFFFF)));
    m_timelabel->setAutoFillBackground(true);
    m_timelabel->setPalette(pal);
    m_timelabel->setAlignment(Qt::AlignCenter);
    QFont labelFont;
    labelFont.setFamily("SourceHanSansSC");
    labelFont.setPixelSize(12);
    m_timelabel->setFont(labelFont);
}

void SliderHandle::setTime(QString time)
{
    m_timelabel->setText(time);
}

//void SliderHandle::paintEvent(QPaintEvent *event)
//{
////    QPixmap pix(m_imgpath);
////    QPainter painter(this);

////    painter.setRenderHints(QPainter::HighQualityAntialiasing |
////                            QPainter::SmoothPixmapTransform |
////                            QPainter::Antialiasing);
////    painter.drawPixmap(rect(), pix);
//}
