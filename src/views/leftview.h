#ifndef LEFTVIEW_H
#define LEFTVIEW_H
#include "leftfolderlist.h"

#include <DWidgetUtil>
#include <QFrame>
#include <foldercontroller.h>
//#include <DImageButton>
#include <dimagebutton.h>
//#include <DIconButton>
#include <QObject>
#include "consts.h"
#include <DtkGuis>
#include <QVBoxLayout>
#include <DBlurEffectWidget>
DWIDGET_USE_NAMESPACE
#define LEFTVIEW_MAX_WIDTH 250

//左侧View
class LeftView : public DBlurEffectWidget
//class LeftView : public QFrame
{
    Q_OBJECT
public:
    LeftView();
    ~LeftView();

    int getCurrSelectFolderId();
    void searchFolder(QString searchKey);
signals:
    void selFolderIdChg(int folderId);
    void searchNote(int folderId, QString searchKey);
    void noResult();
    void clearNoteListSignal();

public slots:
    void addFolder();
    void handleSelFolderChg(QListWidgetItem *item);
    void handlePressFolderChg(QListWidgetItem *item);

private:
    QVBoxLayout *m_leftViewLayout;
    //QListWidget *folderList;
    LeftFolderList *m_leftFolderView;
    DImageButton *m_addFolderBtn;

    FolderController *m_folderCtr;
    QString m_currSearchKey;

    void initUI();
    void initController();
    void initConnection();
    void updateFolderView();
    void clearNoteList();
};

#endif // LEFTVIEW_H
