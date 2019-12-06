#ifndef FOLERWIDGETITEM_H
#define FOLERWIDGETITEM_H

#include <QLabel>
#include <QWidget>
#include <QDateTime>
#include <foldercontroller.h>
#include "consts.h"
#include <DLineEdit>
#include <QStackedWidget>
#include <DStackedWidget>
#include <DBlurEffectWidget>
#include <DLabel>
#include <DFrame>
#include "folderimage.h"
#include "renameedit.h"

DWIDGET_USE_NAMESPACE

//#define FOLDER_MAX_WIDTH 160
//#define FOLDER_MAX_WIDTH 100
#define FOLDER_MAX_WIDTH 110

//左侧item项
class FolerWidgetItem : public DWidget
//class FolerWidgetItem : public DBlurEffectWidget
//class FolerWidgetItem : public QWidget
{
    Q_OBJECT
public:
    //FolerWidgetItem();
    FolerWidgetItem(FOLDER m_folder, FolderController *m_folderCtr, QString searchKey);
    ~FolerWidgetItem();
    RenameEdit *m_lineEdit;
    DFrame *m_BackGround;
    DFrame *m_BackGroundHoverd;
//    DBlurEffectWidget *m_BackBorad;
    //QLabel *m_imageLabel;
    DLabel *m_nameLabel;
    DLabel *m_createTimeLabel;
    FOLDER m_folder;
    FolderImage *m_FolderImage;
    QString m_BakLineContent;
    QString m_BakDefaultName;
    bool m_clicked;

    void changeToEditMode();
    void changeToClickMode();
    void changeToUnClickMode();
    void Init();
    void copy(FolerWidgetItem *pSourceFolder);
    QString getSearchText();
    void updateTimeLable(const QDateTime &time);//liuyang 3550 3547 3528
    void setLabelText(const QString text);

public slots:
    void cancleRename();
    void checkNameValid();
    void checkNameLenth();
    void tryToFouceout();
    void changeTheme();

    //liuyang 3794
protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    //liuyang 3794

private:


    FolderController *m_folderCtr;
    QString m_searchKey;
    QStackedWidget *m_stackedWidget;

    void initConnection();
    //QPixmap getPixmap(QSize size, QString imgPath);
    QString getCreateTimeLabel(QDateTime createTime);


    void setItemBackground(QString imgPath);
    void setNormalBackground();


};

#endif // FOLERWIDGETITEM_H
