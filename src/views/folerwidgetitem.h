#ifndef FOLERWIDGETITEM_H
#define FOLERWIDGETITEM_H

#include <QLabel>
#include <QWidget>
#include <QDateTime>
#include <foldercontroller.h>
#include "consts.h"
#include <DLineEdit>
#include <QStackedWidget>
#include <DBlurEffectWidget>

DWIDGET_USE_NAMESPACE

//#define FOLDER_MAX_WIDTH 160
//#define FOLDER_MAX_WIDTH 100
#define FOLDER_MAX_WIDTH 110

//左侧item项
class FolerWidgetItem : public QWidget
{
    Q_OBJECT
public:
    //FolerWidgetItem();
    FolerWidgetItem(FOLDER m_folder, FolderController *m_folderCtr, QString searchKey);
    ~FolerWidgetItem();
    DLineEdit *m_lineEdit;
    DBlurEffectWidget *m_BackGround;
    QLabel *m_imageLabel;
    QLabel *m_nameLabel;
    QLabel *m_createTimeLabel;
    FOLDER m_folder;

    void changeToEditMode();
    void changeToClickMode();
    void changeToUnClickMode();

public slots:
    void checkNameValid();
private:


    FolderController *m_folderCtr;
    QString m_searchKey;
    QStackedWidget * m_stackedWidget;


    void initUI();
    void initConnection();
    //QPixmap getPixmap(QSize size, QString imgPath);
    QString getCreateTimeLabel(QDateTime createTime);


    void setItemBackground(QString imgPath);
    void setNormalBackground();


};

#endif // FOLERWIDGETITEM_H
