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

    //QObject::connect(m_leftView, SIGNAL(noResult()), m_rightView, SLOT(onShowNoResult()));
    QObject::connect(m_leftView, SIGNAL(noResult()), this, SIGNAL(sigNoSearchResult()));
    QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_leftView, SIGNAL(searchNote(int, QString)), m_rightView, SLOT(handleSearchNote(int, QString)));
    QObject::connect(m_leftView, SIGNAL(clearNoteListSignal()), m_rightView, SLOT(handleClearNote()));
    QObject::connect(m_leftView, SIGNAL(sigAllFolderDeleted()), m_rightView, SLOT(OnAllFolderGone()));
    QObject::connect(m_leftView, SIGNAL(sigAllFolderDeleted()), this, SIGNAL(sigAllFolderDeleted()));
    QObject::connect(m_rightView, SIGNAL(startRecoding()), m_leftView, SLOT(onStartRecoding()));   //Edit 3884
    QObject::connect(m_rightView, SIGNAL(stopRecoiding()), m_leftView, SLOT(onStopRecoding()));    //Edit 3884
    QObject::connect(m_rightView, SIGNAL(startRecoding()), m_leftView, SLOT(viewDisabled()));
    //QObject::connect(m_rightView, SIGNAL(asrStart()), m_leftView, SLOT(viewDisabled()));
    //QObject::connect(m_rightView, SIGNAL(stopRecoiding()), m_leftView, SLOT(viewEnabled()));
    QObject::connect(m_rightView, SIGNAL(stopRecoiding()), this, SIGNAL(stopRecoiding()));  //Add bug3470
    //QObject::connect(m_leftView, SIGNAL(sigAddFolder()), m_rightView, SLOT(OnAddAFolder()));
    QObject::connect(m_leftView, SIGNAL(sigAddFolder()), this, SLOT(onAddFolder()));
    QObject::connect(m_rightView, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
    QObject::connect(m_rightView, SIGNAL(sigBoardPress()), m_leftView, SIGNAL(sigBoardPress()));
    QObject::connect(m_rightView, SIGNAL(sig_research()), this, SIGNAL(sig_research()));
    QObject::connect(m_rightView, SIGNAL(sigChangeCurFolderToTop(int)), m_leftView, SLOT(OnChangeCurFolderToTop(int)));

    //start add by yuanshuai 20191121
    QObject::connect(m_rightView, SIGNAL(sigRvCheckFile()), this, SIGNAL(sigMpCheckFile()));
    //end
    QObject::connect(m_rightView, SIGNAL(sigToDetalVoicePage(QString)), this, SIGNAL(sigToDetalVoicePage(QString)));

    //QObject::connect(m_leftView, LeftView::selFolderIdChg, m_rightView, &RightView::handleSelFolderChg);
    QObject::connect(m_rightView, SIGNAL(asrStart()), m_leftView, SLOT(onStartAsr()));    //Add 20191111 Edit 3884
    QObject::connect(m_rightView, SIGNAL(asrEnd()), m_leftView, SLOT(onEndAsr()));   //Add 20191111 Edit 3884
    QObject::connect(m_rightView, SIGNAL(asrStart()), this, SIGNAL(asrStart()));    //Add 20191111
    QObject::connect(m_rightView, SIGNAL(asrEnd()), this, SIGNAL(asrEnd()));   //Add 20191111
    QObject::connect(m_rightView, SIGNAL(sigShowVoiceDeviceError()), this, SIGNAL(sigShowVoiceDeviceError()));


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
    m_rightView->initTxtFilesForDir();
    m_rightView->handleSelFolderChg(((LeftView*)m_leftView)->getCurrSelectFolderId());
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
}

void MainPage::initTitleBar(){

}

void MainPage::updateNoteList()
{
    m_rightView->updateNoteList();
}

bool MainPage::searchFolder(QString searchKey, bool &hasNoFolder)
{
    bool result = false;
    if (this->m_rightView->m_noteListWidget->isLoadedAudioPlayer) {
        m_rightView->stopAllPlayback();
    }

    m_rightView->cancleRecord();
    result = ((LeftView*)m_leftView)->searchFolder(searchKey,hasNoFolder);
    return result;
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

void MainPage::checkAndDeleteEmptyTextNoteFromDatabase()
{
    m_rightView->checkAndDeleteEmptyTextNoteFromDatabase();
}

int MainPage::getFolderCount()
{
    return m_rightView->getFolderCount();
}

void MainPage::trueAddFolder()
{
    m_leftView->addFolder();
}

void MainPage::saveRecorde()
{
    m_rightView->OnlySaveRecord();
}

void MainPage::ChangeCurFolderToTop(int folderID)
{
    m_leftView->OnChangeCurFolderToTop(folderID);
}

int MainPage::getAllFolderListNumFromDatabase()
{
    return m_leftView->getAllFolderListNum();
}

//Add start bug 2587
void MainPage::addFolder()
{
    m_leftView->addFolder();
}
void MainPage::reNameFolder()
{
    m_leftView->reNameFolder();
}
void MainPage::deleteFolder()
{
    m_leftView->deleteFolder();
}
void MainPage::VoicePlayOrPause()
{
    m_rightView->VoicePlayOrPause();
}
bool MainPage::shortcutsDeleteByRightlist()
{
    return m_rightView->shortcutsDelete();
}
//Add end bug 2587

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
