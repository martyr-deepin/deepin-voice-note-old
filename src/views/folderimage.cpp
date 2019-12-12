#include "folderimage.h"
#include "uiutil.h"
#include <QPainter>
#include <QDebug>

FolderImage::FolderImage(QWidget *parent) : DWidget(parent)
{
    this->setFixedSize(QSize(40,40));
    m_isGray = false;
}

void FolderImage::loadPic(QString imagePath)
{
    m_PicPath = imagePath;
    m_Picmap = UiUtil::renderSVG(m_PicPath, QSize(this->width(), this->height()),qApp);
    m_greyPicmap = greyPix(m_Picmap);
    this->update();
}

void FolderImage::setGray(bool isgray)
{
    m_isGray = isgray;
    this->update();
}

void FolderImage::paintEvent(QPaintEvent *event)
{

    //QPixmap pix(m_PicPath);
    QPainter painter(this);

//    painter.setRenderHints(QPainter::HighQualityAntialiasing |
//                            QPainter::SmoothPixmapTransform |
//                            QPainter::Antialiasing);


//    QPainterPath bp1;
//    bp1.addRoundedRect(rect(), rect().width()/2, rect().width()/2);
//    painter.setClipPath(bp1);


    if(m_isGray)
    {
        painter.drawPixmap(rect(), m_greyPicmap);
    }
    else
    {
        painter.drawPixmap(rect(), m_Picmap);
    }

    //painter.drawPixmap(rect(), m_Picmap);
}

QPixmap FolderImage::greyPix(QPixmap pix)
{
    QPixmap temp(pix.size());
    temp.fill(Qt::transparent);

    QPainter p1(&temp);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, pix);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(temp.rect(), QColor(0, 0, 0, 64));
    p1.end();

    return temp;
}
