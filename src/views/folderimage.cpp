#include "folderimage.h"
#include "uiutil.h"
#include <QPainter>
#include <QDebug>

FolderImage::FolderImage(QWidget *parent) : DWidget(parent)
{
    this->setFixedSize(QSize(40,40));
}

void FolderImage::loadPic(QString imagePath)
{
    m_PicPath = imagePath;
    m_Picmap = UiUtil::renderSVG(m_PicPath, QSize(this->width(), this->height()),qApp);
    this->update();
}

void FolderImage::paintEvent(QPaintEvent *event)
{

    //QPixmap pix(m_PicPath);
    QPainter painter(this);

    painter.setRenderHints(QPainter::HighQualityAntialiasing |
                            QPainter::SmoothPixmapTransform |
                            QPainter::Antialiasing);


    QPainterPath bp1;
    bp1.addRoundedRect(rect(), rect().width()/2, rect().width()/2);
    painter.setClipPath(bp1);

    painter.drawPixmap(rect(), m_Picmap);
}
