#ifndef LEFTVIEW_H
#define LEFTVIEW_H
#include "leftfolderview.h"

#include <DWidgetUtil>
#include <QFrame>
#include <foldercontroller.h>
#include "dimagebutton.h"
DWIDGET_USE_NAMESPACE
#define LEFTVIEW_MAX_WIDTH 200
class LeftView : public QFrame
{
    Q_OBJECT
public:
    LeftView();
    ~LeftView();

private:
    QLayout *leftViewLayout;
    //QListWidget *folderList;
    LeftFolderView *leftFolderView;
    DImageButton *addFolderBtn;

    FolderController *folderCtr;

    void initUI();
    void initController();
    void initConnection();
};

#endif // LEFTVIEW_H
