#ifndef FOLDERIMAGE_H
#define FOLDERIMAGE_H

#include <DWidget>

DWIDGET_USE_NAMESPACE
class FolderImage : public DWidget
{
    Q_OBJECT
public:
    explicit FolderImage(QWidget *parent = nullptr);
    void loadPic(QString imagePath);
signals:

public slots:
protected:
    void paintEvent(QPaintEvent *event);
private:
    DLabel *m_imageLabel;
    QString m_PicPath;
};

#endif // FOLDERIMAGE_H
