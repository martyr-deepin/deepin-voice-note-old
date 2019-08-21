#include "leftview.h"
#include "mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>

MyMainWindow::MyMainWindow()
{
    initUI();
    initConnection();
}

void MyMainWindow::initUI() {
    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    setWindowRadius(20);
    setMinimumSize(650, 420);
    initTitleBar();
    initCentralWidget();

}

void MyMainWindow::initConnection()
{
    QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    //QObject::connect(m_leftView, LeftView::selFolderIdChg, m_rightView, &RightView::handleSelFolderChg);
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
    QSizePolicy sp = m_rightView->sizePolicy();

    //NOTE(zccrs): 保证窗口宽度改变时只会调整right view的宽度，侧边栏保持不变
    //             QSplitter是使用QLayout的策略对widgets进行布局，所以此处
    //             设置size policy可以生效
    sp.setHorizontalStretch(1);
    m_rightView->setSizePolicy(sp);
    m_rightView->setObjectName("rightView");
    m_rightView->handleSelFolderChg(((LeftView*)m_leftView)->getCurrSelectFolderId());
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
