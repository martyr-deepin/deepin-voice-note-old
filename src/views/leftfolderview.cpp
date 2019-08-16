#include "leftfolderview.h"

#include <QFrame>

LeftFolderView::LeftFolderView(FolderController *folderCtr)
{
    this->folderCtr = folderCtr;
    initUI();
    initConnection();
}

void LeftFolderView::initUI()
{


//    FOLDER folder1;
//    folder1.imgPath = "/mnt/hgfs/D/test/img/test.png";
//    folder1.folderName = "測試文件夾";
//    folder1.createTime = QDateTime();

//    FOLDER folder2;
//    folder2.imgPath = "/mnt/hgfs/D/test/img/test.png";
//    folder2.folderName = "測試文件夾2";
//    folder2.createTime = QDateTime();

//    addWidgetItem(folder1);
//    addWidgetItem(folder2);

}

void LeftFolderView::initConnection()
{
    connect(this, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(handleCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));
}

void LeftFolderView::addWidgetItem(FOLDER folder) {
    QListWidgetItem *item=new QListWidgetItem(this);
    item->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
    item->setSizeHint(QSize(200,60));
    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, folderCtr);
    this->setItemWidget(item, folderItem);
}

void LeftFolderView::handleCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous)
    {
        //previous->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
    }
    //current->setBackground(QBrush(QPixmap(":/image/add_press.svg")));
    //current->setForeground(QBrush(QPixmap(":/image/add_press.svg")));
}
