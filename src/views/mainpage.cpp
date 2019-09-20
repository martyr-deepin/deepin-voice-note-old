#include "mainpage.h"
#include "leftview.h"

#include <QFrame>
#include <QVBoxLayout>


MainPage::MainPage()
{
    initUI();
    initConnection();
}

MainPage::~MainPage()
{

}


void MainPage::initUI() {
    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    //setWindowRadius(20);
    setMinimumSize(650, 420);
    initSplitter();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_splitter);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);

}

void MainPage::initConnection()
{
    QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_leftView, SIGNAL(searchNote(int, QString)), m_rightView, SLOT(handleSearchNote(int, QString)));
    QObject::connect(m_leftView, SIGNAL(clearNoteListSignal()), m_rightView, SLOT(handleClearNote()));
    QObject::connect(m_rightView, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
    //QObject::connect(m_leftView, LeftView::selFolderIdChg, m_rightView, &RightView::handleSelFolderChg);
}

void MainPage::initSplitter(){
    initLeftView();
    initRightView();

    m_splitter = new DFMSplitter(Qt::Horizontal, this);
    m_splitter->addWidget(m_leftView);
    m_splitter->addWidget(m_rightView);
    m_splitter->setChildrenCollapsible(false);
    qDebug() << "main page, leftview width:" << m_leftView->width() << ", right view width: " << m_rightView->width();
}

void MainPage::initLeftView(){
    m_leftView = new LeftView();



}

void MainPage::initRightView(){
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

//void MainPage::initCentralWidget()
//{

//}

void MainPage::initTitleBar(){

}

void MainPage::updateNoteList()
{
    m_rightView->updateNoteList();
}

void MainPage::searchFolder(QString searchKey)
{
    ((LeftView*)m_leftView)->searchFolder(searchKey);
}
