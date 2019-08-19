#ifndef LEFTVIEW_H
#define LEFTVIEW_H
#include "leftfolderview.h"

#include <DWidgetUtil>
#include <QFrame>
#include <foldercontroller.h>
#include <dimagebutton.h>
#include "consts.h"
DWIDGET_USE_NAMESPACE
#define LEFTVIEW_MAX_WIDTH 200
class LeftView : public QFrame
{
    Q_OBJECT
public:
    LeftView();
    ~LeftView();

public slots:
    void addFolder();

private:
    QLayout *m_leftViewLayout;
    //QListWidget *folderList;
    LeftFolderView *m_leftFolderView;
    DImageButton *m_addFolderBtn;

    FolderController *m_folderCtr;

    void initUI();
    void initController();
    void initConnection();
    void updateFolderView();
};

#endif // LEFTVIEW_H
