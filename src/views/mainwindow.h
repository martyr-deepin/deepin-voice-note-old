#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpage.h"
#include "textnoteedit.h"


#include <DMainWindow>
#include <QFrame>
#include <QObject>
#include <QVBoxLayout>
#include <QStackedWidget>
#define DEFAULT_WINDOWS_WIDTH 960
#define DEFAULT_WINDOWS_HEIGHT 540


DWIDGET_USE_NAMESPACE

class MyMainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MyMainWindow();

public slots:
    void showNoteDetail(NOTE note);

private:
     QFrame *m_centralWidget;
//     DFMSplitter *m_splitter;
//     QFrame *m_leftView;

//     RightView *m_rightView;
    MainPage * m_mainPage;
    QStackedWidget * m_stackedWidget;
    TextNoteEdit * m_textNoteEdit;
    QWidget *m_detailPage;
    QVBoxLayout *m_detailPageLayout;

    void initUI();
    void initConnection();

    void initTitleBar();

    void initStackedWidget();
//    void initSplitter();

//    void initLeftView();

//    void initRightView();

    void initCentralWidget();
};

#endif // MAINWINDOW_H
