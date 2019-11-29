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
#include <DFloatingButton>
#include "addfolderbutton.h"
#include "myrecodebuttons.h"

DWIDGET_USE_NAMESPACE
#define LEFTVIEW_MAX_WIDTH 250

//左侧View
//class LeftView : public DBlurEffectWidget
class LeftView : public DWidget //liuyang 3799
//class LeftView : public QFrame
{
    Q_OBJECT
public:
    LeftView();
    ~LeftView();

    void sendSelectCurFolder();
    int getCurrSelectFolderId();
    bool searchFolder(QString searchKey,bool &hasNoFolder);
    void selectTheFirstFolderByCode();
    int getAllFolderListNum();
    void reNameFolder(); //Add bug 2587
    void deleteFolder(); //Add bug 2587

signals:
    void selFolderIdChg(int folderId);
    void searchNote(int folderId, QString searchKey);
    void noResult();
    void clearNoteListSignal();
    void sigBoardPress();
    void sigAllFolderDeleted();
    void sigAddFolder();

protected:
    void resizeEvent(QResizeEvent * event);

public slots:
    void addFolder();
    void handleSelFolderChg(QListWidgetItem *item);
    void itemSelectedChanged(QListWidgetItem *current, QListWidgetItem *previous);
    //    void viewDisabled();  //Del 3884
    //    void viewEnabled();     //Del 3884
        void onStartRecoding(); //Add  3884
        void onStopRecoding();  //Add  3884
        void onStartAsr();  //Add  3884
        void onEndAsr();  //Add  3884
    void changeTheme();
    void OnChangeCurFolderToTop(int folderID);
    void onNoResult(); //Add bug3136
    //void handlePressFolderChg(QListWidgetItem *item);

private:
    QVBoxLayout *m_leftViewLayout;
    //QListWidget *folderList;
    LeftFolderList *m_leftFolderView;
    MyRecodeButtons *m_addFolderBtn;
    //AddFolderButton *m_addFolderBtn;
    //DWidget *m_LeftListBoard;

    FolderController *m_folderCtr;
    QString m_currSearchKey;
    DWidget *m_greyboard;

    int m_RecodingState; // 0:录音开始  1:录音结束   Add 3884
    int m_asrState;  // 0:转写开始  1:转写结束   Add 3884

    void initUI();
    void initController();
    void initConnection();
    void updateFolderView();
    void clearNoteList();
    void viewDisabled();  //Add 3884
    void viewEnabled();     //Add 3884
};

#endif // LEFTVIEW_H
