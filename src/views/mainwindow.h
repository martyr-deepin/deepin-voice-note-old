#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dfmsplitter.h"
#include "leftfolderview.h"
#include "rightview.h"

#include <DMainWindow>
#include <QFrame>

#define DEFAULT_WINDOWS_WIDTH 960
#define DEFAULT_WINDOWS_HEIGHT 540


DWIDGET_USE_NAMESPACE

class MyMainWindow : public DMainWindow
{
    //Q_OBJECT
public:
    MyMainWindow();

private:
     QFrame *m_centralWidget;
     DFMSplitter *m_splitter;
     QFrame *m_leftView;

     RightView *m_rightView;

    void initUI();

    void initTitleBar();

    void initSplitter();

    void initLeftView();

    void initRightView();

    void initCentralWidget();
};

#endif // MAINWINDOW_H
