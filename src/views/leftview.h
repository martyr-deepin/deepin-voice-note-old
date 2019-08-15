#ifndef LEFTVIEW_H
#define LEFTVIEW_H
#include "leftfolderview.h"

#include <DWidgetUtil>
#include <QFrame>
#include "dimagebutton.h"
DWIDGET_USE_NAMESPACE
#define LEFTVIEW_MAX_WIDTH 200
class LeftView : public QFrame
{
    Q_OBJECT
public:
    LeftView();

private:
    QLayout *leftViewLayout;
    //QListWidget *folderList;
    LeftFolderView *leftFolderView;
    DImageButton *addFolderBtn;

    void initUI();
};

#endif // LEFTVIEW_H
