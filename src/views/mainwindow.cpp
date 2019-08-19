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

    m_splitter = new DFMSplitter(Qt::Horizontal, this);
    m_splitter->addWidget(m_leftView);
    m_splitter->addWidget(m_rightView);
    m_splitter->setChildrenCollapsible(false);
}

void MyMainWindow::initLeftView(){
    m_leftView = new LeftView();



}

void MyMainWindow::initRightView(){
    m_rightView = new RightView();
    m_rightView->setObjectName("rightView");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
}

void MyMainWindow::initCentralWidget()
{
    initSplitter();

    m_centralWidget = new QFrame(this);
    m_centralWidget->setObjectName("CentralWidget");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_splitter);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    m_centralWidget->setLayout(mainLayout);
    setCentralWidget(m_centralWidget);
}

void MyMainWindow::initTitleBar(){

}
