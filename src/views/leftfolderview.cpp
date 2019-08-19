#include "leftfolderview.h"

#include <QFrame>
#include <QDebug>

LeftFolderView::LeftFolderView(FolderController *folderCtr)
{
    this->m_folderCtr = folderCtr;
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
    m_contextMenu = new QMenu;
    m_renameAction = new QAction(FOLDER_MENU_RENAME,this);
    m_delAction = new QAction(FOLDER_MENU_DELETE,this);
    m_contextMenu->addAction(m_renameAction);
    m_contextMenu->addAction(m_delAction);


}

void LeftFolderView::initConnection()
{
    connect(this, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(handleCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));
    connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
    connect(m_renameAction, SIGNAL(triggered(bool)), this, SLOT(handleRenameItem(bool)));
}

void LeftFolderView::addWidgetItem(FOLDER folder) {
    QListWidgetItem *item=new QListWidgetItem(this);
    item->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
    item->setSizeHint(QSize(200,60));
    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr);
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

void LeftFolderView::mousePressEvent(QMouseEvent *event)
{
    //要继续保留QListWidget原有的点击事件.
    QListWidget::mousePressEvent(event);
    //确保右键点击，然后跳出菜单.
    if ((event->button() == Qt::RightButton) && (this->count() > 0))
    {
        m_contextMenu->exec(event->globalPos());
    }

}

void LeftFolderView::handleDelItem(bool checked)
{
    FolerWidgetItem *itemDel = (FolerWidgetItem *)this->itemWidget(this->currentItem());

    if (m_folderCtr->deleteFolder(itemDel->m_folder.id))
    {

        QListWidgetItem * item = this->takeItem(this->currentRow());
        delete item;
    }
    else {
        qDebug() << "error: delete item error";
    }
    return;
}

void LeftFolderView::handleRenameItem(bool checked)
{
    FolerWidgetItem *item = (FolerWidgetItem*)this->itemWidget(this->currentItem());
    item->changeToEditMode();
}
