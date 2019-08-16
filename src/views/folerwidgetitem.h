#ifndef FOLERWIDGETITEM_H
#define FOLERWIDGETITEM_H

#include <QLabel>
#include <QWidget>
#include <QDateTime>
#include "consts.h"



class FolerWidgetItem : public QWidget
{
public:
    //FolerWidgetItem();
    FolerWidgetItem(FOLDER folder);
    ~FolerWidgetItem();
private:

    FOLDER folder;
    QLabel *imageLabel;
    QLabel *nameLabel;
    QLabel *createTimeLabel;

    void initUI();
    QPixmap getPixmap(QSize size, QString imgPath);
    QString getCreateTimeLabel(QDateTime createTime);


    void setItemBackground(QString imgPath);
    void setNormalBackground();


};

#endif // FOLERWIDGETITEM_H
