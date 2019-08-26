#ifndef LEFTVIEW_H
#define LEFTVIEW_H
#include "leftfolderlist.h"

#include <DWidgetUtil>
#include <QFrame>
#include <foldercontroller.h>
//#include <DImageButton>
#include <dimagebutton.h>
#include <QObject>
#include "consts.h"
DWIDGET_USE_NAMESPACE
#define LEFTVIEW_MAX_WIDTH 200
class LeftView : public QFrame
{
    Q_OBJECT
public:
    LeftView();
    ~LeftView();

    int getCurrSelectFolderId();
signals:
    void selFolderIdChg(int folderId);

public slots:
    void addFolder();
    void handleSelFolderChg(QListWidgetItem *item);

private:
    QLayout *m_leftViewLayout;
    //QListWidget *folderList;
    LeftFolderList *m_leftFolderView;
    DImageButton *m_addFolderBtn;

    FolderController *m_folderCtr;

    void initUI();
    void initController();
    void initConnection();
    void updateFolderView();
};

#endif // LEFTVIEW_H
