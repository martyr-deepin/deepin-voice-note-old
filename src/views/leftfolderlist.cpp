#include "leftfolderlist.h"

#include <QFrame>
#include <QDebug>
#include <DPalette>

LeftFolderList::LeftFolderList(FolderController *folderCtr)
{
    this->m_folderCtr = folderCtr;
    initUI();
    initConnection();
}
LeftFolderList::~LeftFolderList()
{

}

void LeftFolderList::initUI()
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
    this->setFrameShape(QListWidget::NoFrame);
    this->setSelectionRectVisible(false);
    m_contextMenu = new QMenu;
    m_renameAction = new QAction(tr(FOLDER_MENU_RENAME),this);
    m_delAction = new QAction(tr(FOLDER_MENU_DELETE),this);
    m_contextMenu->addAction(m_renameAction);
    m_contextMenu->addAction(m_delAction);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void LeftFolderList::initConnection()
{
    connect(this, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(handleCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));
    connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
    connect(m_renameAction, SIGNAL(triggered(bool)), this, SLOT(handleRenameItem(bool)));
}

void LeftFolderList::addWidgetItem(FOLDER folder, QString searchKey) {
    QListWidgetItem *item=new QListWidgetItem(this);
//    item->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
    item->setSizeHint(QSize(230,64));
    item->setBackgroundColor(QColor(Qt::red));
//    DPalette palette;
//    palette.setColor(DPalette::Background, QColor(247, 247, 247));
//    item->setAutoFillBackground(true);
//    item->setPalette(palette);
    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr, searchKey);

    this->setItemWidget(item, folderItem);
//    QWidget *pNewWidget = new QWidget;
//    pNewWidget->setFixedSize(QSize(230,64));
//    this->setItemWidget(item, pNewWidget);

}

void LeftFolderList::handleCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous)
    {
        //previous->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
    }
    //current->setBackground(QBrush(QPixmap(":/image/add_press.svg")));
    //current->setForeground(QBrush(QPixmap(":/image/add_press.svg")));
}

void LeftFolderList::mousePressEvent(QMouseEvent *event)
{
    //要继续保留QListWidget原有的点击事件.
    DListWidget::mousePressEvent(event);
    //确保右键点击，然后跳出菜单.
    if ((event->button() == Qt::RightButton) && (this->count() > 0))
    {
        m_contextMenu->exec(event->globalPos());
    }

}

void LeftFolderList::handleDelItem(bool checked)
{
    FolerWidgetItem *itemDel = (FolerWidgetItem *)this->itemWidget(this->currentItem());

    if (m_folderCtr->deleteFolder(itemDel->m_folder.id))
    {

        QListWidgetItem * item = this->takeItem(this->currentRow());
        delete item;
        emit itemClicked(this->currentItem());
        //FolerWidgetItem *currItem = (FolerWidgetItem *)this->itemWidget(this->currentItem());
    }
    else {
        qDebug() << "error: delete item error";
    }
    return;
}

void LeftFolderList::handleRenameItem(bool checked)
{
    FolerWidgetItem *item = (FolerWidgetItem*)this->itemWidget(this->currentItem());
    item->changeToEditMode();
}


