#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpage.h"
#include "textnoteedit.h"
#include "initemptypage.h"
#include "searchnonepage.h"
#include "voicetonotepage.h"
#include <DMainWindow>
#include <QFrame>
#include <QObject>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <DSearchEdit>
#include <DIconButton>

#define DEFAULT_WINDOWS_WIDTH 820
#define DEFAULT_WINDOWS_HEIGHT 634
#define TITLE_FIXED_HEIGHT 50


DWIDGET_USE_NAMESPACE

enum STATIC_PAGE {
    MAIN_PAGE = 0,
    DETAL_PAGE =1,
    INIT_PAGE =2,
    NOSEARCH_PAGE =3,
    VOICE_PAGE =4,
};

//主窗口，包含两层Page
class MyMainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MyMainWindow();
    void CreateVoiceMemo(); //Add createVoiceMemo 新建语音备忘录对应
public slots:
    void showNoteDetail(NOTE note);
    void showListPage();
    void handleSearchKey();
    void On_RetryToSearch();
    void tryToSearch(QString search);
    void handleSearchDialogClicked(int index, const QString &text);
    void handleCloseSearchDialog();
    void clearSearchLine();
    void onAddFolderByInitPage();
    void onAllFolderDeleted();
    void handleCloseExitDialog();
    void handleCloseExitDialogClicked(int index, const QString &text);
    void changeTheme();
    void OnNoSearchResult();
    void stopRecoidingFunc(); //Add bug3470
    void restoreminwindow();
    //by yuanshuai 20191120 2841
    void checkFileExist();
    //Add start bug 2587
    void showNoVoiceDeviceDialog();
    void previewShortcut();
    void searchShortcut();
    void newNoteShortcut();
    void deleteNoteShortcut();
    void reNameNoteShortcut();
    void VoiceNotesPlayShortcut();
    //Add end bug 2587
    //end
    void asrStart(); //Add 20191111
    void asrEnd(); //Add 20191111
    void asrDialogClicked(int index, const QString &text); //Add 20191111
    void OnToDetalVoicePage(QString contant);
    void onShowRecordDialog();
    void onShowVoiceToTextDialog();
    void OnRecordVoiceCouldUse(); //Add createVoiceMemo 新建语音备忘录对应
protected:
    void keyPressEvent(QKeyEvent *event);
    void changeEvent(QEvent * event);
    void closeEvent(QCloseEvent* event);
private:
     QFrame *m_centralWidget;
//     DFMSplitter *m_splitter;
//     QFrame *m_leftView;

//     RightView *m_rightView;
    MainPage * m_mainPage;
    SearchNonePage *m_SearchNonePage;
    QStackedWidget * m_stackedWidget;
    TextNoteEdit * m_textNoteEdit;
    QString m_DetalTextBak;
    DWidget *m_detailPage;
    QVBoxLayout *m_detailPageLayout;
    QLabel *m_logo;
    DIconButton *m_returnBtn;
    //DImageButton *m_returnBtn;
    DWidget *m_replaceForReturn;
    //DIconButton *m_returnBtn;
    QFrame *m_titleFrame;
    DSearchEdit *m_searchEdit;
    QString m_bakForSearchStr;
    DDialog *m_SearchDialog;
    InitEmptyPage *m_InitEmptyPage;
    VoiceToNotePage *m_VoiceToNotePage;
    DDialog *m_exitDialog;
    bool m_quit;  //Add bug3470
    DDialog *m_asrCloseConfirmDialog;   //Add 20191111
    int asrStateFlg;  //0:未转写  1：转写中   Add 20191111
    QCloseEvent* m_eventSave;  //Add 20191111
    void initUI();
    void initConnection();

    void initTitleBar();
    void initTitleFrame();

    void initStackedWidget();
//    void initSplitter();

//    void initLeftView();

//    void initRightView();

    void initCentralWidget();
    //Add start bug 2587
    void initShortcutkeys();
    void initTheRest();
    void switchPage(STATIC_PAGE pageID);
    QJsonObject creatShorcutJson();
    //Add end bug 2587
    bool m_VoiceMemoAction;  //true: 创建语音备忘录指令有 false 创建语音备忘录指令无  Add createVoiceMemo 新建语音备忘录对应
    STATIC_PAGE m_showPageID;
};

#endif // MAINWINDOW_H
