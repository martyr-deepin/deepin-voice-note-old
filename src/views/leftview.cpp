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
    delete folderCtr;
}



void LeftView::initUI()
{
    //this->setStyleSheet("background: blue");
    leftViewLayout = new QVBoxLayout;
    leftViewLayout->setContentsMargins(0, 0, 0, 0);



    leftFolderView = new LeftFolderView(folderCtr);
    QList<FOLDER> folderList = folderCtr->getFolderList();
    for (int i = 0; i < folderList.size(); i++)
    {
        leftFolderView->addWidgetItem(folderList.at(i));
    }
    leftFolderView->setObjectName("LeftSideBar");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
    leftViewLayout->addWidget(leftFolderView);

    addFolderBtn = new DImageButton();
    addFolderBtn->setNormalPic(":/image/add_normal.svg");
    addFolderBtn->setHoverPic(":/image/add_hover.svg");
    addFolderBtn->setPressPic(":/image/add_press.svg");

    leftViewLayout->addWidget(addFolderBtn);
    QSizePolicy sp = leftFolderView->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    leftFolderView->setSizePolicy(sp);
    this->setLayout(leftViewLayout);
    this->setFixedWidth(LEFTVIEW_MAX_WIDTH);

}

void LeftView::initController()
{
     folderCtr = new FolderController();
}
void LeftView::initConnection()
{
    connect(addFolderBtn, &DImageButton::clicked, this, &LeftView::addFolder);

}

void LeftView::updateFolderView()
{
    leftFolderView->clear();
    QList<FOLDER> folderList = folderCtr->getFolderList();
    for (int i = 0; i < folderList.size(); i++)
    {
        leftFolderView->addWidgetItem(folderList.at(i));
    }
}

void LeftView::addFolder()
{
    //todo:獲取新文件夾的名字
    FOLDER newFolder;
    newFolder.imgPath = DEFAULT_FOLDER_IMG_PATH;
    newFolder.folderName = folderCtr->getNextFolderName();
    newFolder.createTime = QDateTime::currentDateTime();
    folderCtr->addFolder(newFolder);
    updateFolderView();
    FolerWidgetItem *item = (FolerWidgetItem*)(leftFolderView->itemWidget(leftFolderView->item(0)));
    item->changeToEditMode();
    leftFolderView->setCurrentRow(0);
}
