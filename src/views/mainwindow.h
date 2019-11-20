#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpage.h"
#include "textnoteedit.h"
#include "initemptypage.h"
#include "searchnonepage.h"
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

//主窗口，包含两层Page
class MyMainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MyMainWindow();

public slots:
    void showNoteDetail(NOTE note);
    void showListPage();
    void handleSearchKey();
    void tryToSearch();
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
    DDialog *m_SearchDialog;
    InitEmptyPage *m_InitEmptyPage;

    DDialog *m_exitDialog;
    bool m_quit;  //Add bug3470

    void initUI();
    void initConnection();

    void initTitleBar();
    void initTitleFrame();

    void initStackedWidget();
//    void initSplitter();

//    void initLeftView();

//    void initRightView();

    void initCentralWidget();
};

#endif // MAINWINDOW_H
