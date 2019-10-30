#include "mainpage.h"
#include "leftview.h"

#include <QFrame>
#include <QVBoxLayout>
#include <DApplicationHelper>


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
    //QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));

    QObject::connect(m_leftView, SIGNAL(noResult()), m_rightView, SLOT(onShowNoResult()));
    QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_leftView, SIGNAL(searchNote(int, QString)), m_rightView, SLOT(handleSearchNote(int, QString)));
    QObject::connect(m_leftView, SIGNAL(clearNoteListSignal()), m_rightView, SLOT(handleClearNote()));
    QObject::connect(m_leftView, SIGNAL(sigAllFolderDeleted()), m_rightView, SLOT(OnAllFolderGone()));
    QObject::connect(m_rightView, SIGNAL(startRecoding()), m_leftView, SLOT(viewDisabled()));
    QObject::connect(m_rightView, SIGNAL(stopRecoiding()), m_leftView, SLOT(viewEnabled()));
    //QObject::connect(m_leftView, SIGNAL(sigAddFolder()), m_rightView, SLOT(OnAddAFolder()));
    QObject::connect(m_leftView, SIGNAL(sigAddFolder()), this, SLOT(onAddFolder()));
    QObject::connect(m_rightView, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
    QObject::connect(m_rightView, SIGNAL(sigBoardPress()), m_leftView, SIGNAL(sigBoardPress()));


    //QObject::connect(m_leftView, LeftView::selFolderIdChg, m_rightView, &RightView::handleSelFolderChg);
}

void MainPage::initSplitter(){
    initLeftView();
    initRightView();

    m_splitter = new DFMSplitter(Qt::Horizontal,this);
    m_splitter->addWidget(m_leftView);
    DWidget *pLine = new DWidget(this);
    pLine->setFixedWidth(2);
    m_splitter->addWidget(pLine);
    m_splitter->addWidget(m_rightView);
    m_splitter->setChildrenCollapsible(false);
    //m_splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //QSplitterHandle *handle = m_splitter->handle(1);
//    DPalette pa = DApplicationHelper::instance()->palette(handle);
//    //pa.setBrush(DPalette::AlternateBase, pa.brush(DPalette::AlternateBase));
//    pa.setBrush(DPalette::AlternateBase, QBrush(QColor(255,0,0,254)));
//    handle->setPalette(pa);
//    handle->setFixedWidth(100);
    qDebug() << "main page, leftview width:" << m_leftView->width() << ", right view width: " << m_rightView->width();
    //m_leftView->selectTheFirstFolderByCode();


//    pList = new DListWidget(this);
//    //pList->setFixedSize(QSize(500,500));
//    pList->move(0,0);

//    pList->addItem(QString("1"));
//    count = 0;
//    pList->setFixedWidth(200);

//    QSizePolicy sp = pList->sizePolicy();
//    sp.setVerticalStretch(1);
//    //sp.setVerticalPolicy(QSizePolicy::Expanding);
//    pList->setSizePolicy(sp);

//    QVBoxLayout *pnoteListLayout = new QVBoxLayout();
//    pnoteListLayout->setContentsMargins(0, 0, 0, 0);
//    pnoteListLayout->addWidget(pList);

//    QWidget *pnoteListPage = new QWidget();
//    pnoteListPage->resize(100,pnoteListPage->height());
//    pnoteListPage->setLayout(pnoteListLayout);

//    QVBoxLayout *rightViewLayout = new QVBoxLayout();
//    rightViewLayout->setContentsMargins(0, 0, 0, 0);
//    rightViewLayout->addWidget(pnoteListPage);



//    QFrame *pView = new QFrame();
//    pView->resize(100,pView->height());
//    pView->setLayout(rightViewLayout);


//    m_splitter->addWidget(pView);
//    DPushButton *pBtn = new DPushButton(this);
//    pBtn->setFixedSize(QSize(100,50));
//    pBtn->move(600,0);

//    connect(pBtn,SIGNAL(clicked()),this,SLOT(addItemTest()));
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
    m_rightView->stopAllPlayback();
    m_rightView->cancleRecord();
    ((LeftView*)m_leftView)->searchFolder(searchKey);
}

void MainPage::updateFromDetal(int id)
{
    m_rightView->updateFromDetal(id);
}

void MainPage::cancleRecord()
{
    m_rightView->cancleRecord();
}

void MainPage::selectCurFolder()
{
    m_leftView->sendSelectCurFolder();
}

void MainPage::onAddFolder()
{
    emit clearSearch();
    m_rightView->OnAddAFolder();
}

//void MainPage::addItemTest()
//{
//    count++;
//    pList->addItem(QString::number(count));
//}
