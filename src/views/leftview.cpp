#include "leftview.h"

#include <QVBoxLayout>
#include <folderoper.h>

LeftView::LeftView()
{
    initController();
    initUI();
    initConnection();
}

LeftView::~LeftView()
{
    delete m_folderCtr;
}



void LeftView::initUI()
{
    //this->setStyleSheet("background: blue");
    m_leftViewLayout = new QVBoxLayout;
    m_leftViewLayout->setContentsMargins(0, 0, 0, 0);



    m_leftFolderView = new LeftFolderList(m_folderCtr);
    QList<FOLDER> folderList = m_folderCtr->getFolderList();
    for (int i = 0; i < folderList.size(); i++)
    {
        m_leftFolderView->addWidgetItem(folderList.at(i));
    }
    m_leftFolderView->setObjectName("LeftSideBar");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
    m_leftViewLayout->addWidget(m_leftFolderView);

    m_addFolderBtn = new DImageButton();
    m_addFolderBtn->setNormalPic(":/image/add_normal.svg");
    m_addFolderBtn->setHoverPic(":/image/add_hover.svg");
    m_addFolderBtn->setPressPic(":/image/add_press.svg");

    m_leftViewLayout->addWidget(m_addFolderBtn);
    QSizePolicy sp = m_leftFolderView->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    m_leftFolderView->setSizePolicy(sp);
    this->setLayout(m_leftViewLayout);
    this->setFixedWidth(LEFTVIEW_MAX_WIDTH);

}

void LeftView::initController()
{
     m_folderCtr = new FolderController();
}
void LeftView::initConnection()
{
    connect(m_addFolderBtn, &DImageButton::clicked, this, &LeftView::addFolder);

}

void LeftView::updateFolderView()
{
    m_leftFolderView->clear();
    QList<FOLDER> folderList = m_folderCtr->getFolderList();
    for (int i = 0; i < folderList.size(); i++)
    {
        m_leftFolderView->addWidgetItem(folderList.at(i));
    }
}

void LeftView::addFolder()
{
    //todo:獲取新文件夾的名字
    FOLDER newFolder;
    newFolder.imgPath = DEFAULT_FOLDER_IMG_PATH;
    newFolder.folderName = m_folderCtr->getNextFolderName();
    newFolder.createTime = QDateTime::currentDateTime();
    m_folderCtr->addFolder(newFolder);
    updateFolderView();
    FolerWidgetItem *item = (FolerWidgetItem*)(m_leftFolderView->itemWidget(m_leftFolderView->item(0)));
    item->changeToEditMode();
    m_leftFolderView->setCurrentRow(0);
}
