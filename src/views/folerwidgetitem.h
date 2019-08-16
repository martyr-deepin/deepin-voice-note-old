#ifndef FOLERWIDGETITEM_H
#define FOLERWIDGETITEM_H

#include <QLabel>
#include <QWidget>
#include <QDateTime>
#include "consts.h"
#include <DLineEdit>

DWIDGET_USE_NAMESPACE



class FolerWidgetItem : public QWidget
{
    Q_OBJECT
public:
    //FolerWidgetItem();
    FolerWidgetItem(FOLDER folder);
    ~FolerWidgetItem();
    DLineEdit *lineEdit;
    QLabel *imageLabel;
    QLabel *nameLabel;
    QLabel *createTimeLabel;

    void changeToEditMode();

public slots:
    void checkNameValid();
private:

    FOLDER folder;


    void initUI();
    void initConnection();
    QPixmap getPixmap(QSize size, QString imgPath);
    QString getCreateTimeLabel(QDateTime createTime);


    void setItemBackground(QString imgPath);
    void setNormalBackground();


};

#endif // FOLERWIDGETITEM_H
