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
#include <DLabel>
#include "folderimage.h"

DWIDGET_USE_NAMESPACE

//#define FOLDER_MAX_WIDTH 160
//#define FOLDER_MAX_WIDTH 100
#define FOLDER_MAX_WIDTH 110

//左侧item项
class FolerWidgetItem : public DBlurEffectWidget
//class FolerWidgetItem : public QWidget
{
    Q_OBJECT
public:
    //FolerWidgetItem();
    FolerWidgetItem(FOLDER m_folder, FolderController *m_folderCtr, QString searchKey);
    ~FolerWidgetItem();
    DLineEdit *m_lineEdit;
    DBlurEffectWidget *m_BackGround;
    DBlurEffectWidget *m_BackBorad;
    //QLabel *m_imageLabel;
    DLabel *m_nameLabel;
    QLabel *m_createTimeLabel;
    FOLDER m_folder;
    FolderImage *m_FolderImage;
    QString m_BakLineContent;
    QString m_BakDefaultName;

    void changeToEditMode();
    void changeToClickMode();
    void changeToUnClickMode();
    void Init();

public slots:
    void checkNameValid();
    void checkNameLenth();
private:


    FolderController *m_folderCtr;
    QString m_searchKey;
    QStackedWidget * m_stackedWidget;

    void initConnection();
    //QPixmap getPixmap(QSize size, QString imgPath);
    QString getCreateTimeLabel(QDateTime createTime);


    void setItemBackground(QString imgPath);
    void setNormalBackground();


};

#endif // FOLERWIDGETITEM_H
