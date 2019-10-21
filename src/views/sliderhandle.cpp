#include "sliderhandle.h"
#include <QPainter>

SliderHandle::SliderHandle(QString imgpath, QWidget *parent) : DLabel(parent)
{
    m_imgpath = imgpath;
//    m_timelabel = new DLabel(this);
//    m_timelabel->setFixedSize();
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
