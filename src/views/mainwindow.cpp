#include "leftview.h"
#include "mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>

MyMainWindow::MyMainWindow()
{
    initUI();
}

void MyMainWindow::initUI() {
    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    setMinimumSize(650, 420);
    initTitleBar();
    initCentralWidget();



}

void MyMainWindow::initSplitter(){
    initLeftView();
    initRightView();

    splitter = new DFMSplitter(Qt::Horizontal, this);
    splitter->addWidget(leftView);
    splitter->addWidget(rightView);
    splitter->setChildrenCollapsible(false);
}

void MyMainWindow::initLeftView(){
    leftView = new LeftView();



}

void MyMainWindow::initRightView(){
    rightView = new RightView();
    rightView->setObjectName("rightView");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
}

void MyMainWindow::initCentralWidget()
{
    initSplitter();

    centralWidget = new QFrame(this);
    centralWidget->setObjectName("CentralWidget");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MyMainWindow::initTitleBar(){

}
