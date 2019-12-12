#ifndef FOLDERIMAGE_H
#define FOLDERIMAGE_H

#include <DWidget>
#include <DLabel>

DWIDGET_USE_NAMESPACE
class FolderImage : public DWidget
{
    Q_OBJECT
public:
    explicit FolderImage(QWidget *parent = nullptr);
    void loadPic(QString imagePath);
    void setGray(bool isgray);
signals:

public slots:
protected:
    void paintEvent(QPaintEvent *event);
private:
    QPixmap greyPix(QPixmap pix);

    DLabel *m_imageLabel;
    QString m_PicPath;
    QPixmap m_Picmap;
    QPixmap m_greyPicmap;

    bool m_isGray;
};

#endif // FOLDERIMAGE_H
