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
    this->setFrameShape(QListWidget::NoFrame);
    this->setSelectionRectVisible(false);
    //this->setFocusPolicy(Qt::NoFocus);
    //this->setFocus(Qt::NoFocusReason);
    //this->setAttribute(Qt::WA_MacShowFocusRect, 0);
    this->setFixedWidth(250);
    //this->move(-10,this->y());
    m_contextMenu = new DMenu;
    m_renameAction = new QAction(tr(FOLDER_MENU_RENAME),this);
    m_delAction = new QAction(tr(FOLDER_MENU_DELETE),this);
    m_contextMenu->addAction(m_renameAction);
    m_contextMenu->addAction(m_delAction);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_boader = new DBlurEffectWidget(this);
    m_boader->setMaskAlpha(255);
    m_boader->setFixedWidth(8);
    m_boader->setFixedHeight(1000);
    m_boader->move(0,0);

    m_delConfirmDialog = UiUtil::createChooseDialog(QString(""), QString(tr("您确定要删除记事本吗？")), nullptr, QString(tr("取消")), QString(tr("删除")));
}

void LeftFolderList::initConnection()
{
    connect(this, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(handleCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));
    connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
    connect(m_delConfirmDialog, &DDialog::buttonClicked, this, &LeftFolderList::handleDelDialogClicked);
    connect(m_renameAction, SIGNAL(triggered(bool)), this, SLOT(handleRenameItem(bool)));
}

void LeftFolderList::addWidgetItem(FOLDER folder, QString searchKey) {
    QListWidgetItem *item=new QListWidgetItem(this);

    //QListWidgetItem *item=new QListWidgetItem();
//    item->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
    //item->setSizeHint(QSize(230,64));
    item->setSizeHint(QSize(250,74));
    //item->setBackgroundColor(QColor(QRgb(0x00f5f5f5)));
//    DPalette palette;
//    palette.setColor(DPalette::Background, QColor(247, 247, 247));
//    item->setAutoFillBackground(true);
//    item->setPalette(palette);
    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr, searchKey);
    //item->setData(Qt::BackgroundRole,QBrush(QColor(QRgb(0x00000000))));

    this->addItem(item);
    this->setItemWidget(item, folderItem);
    //folderItem->Init();

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

void LeftFolderList::handleDelDialogClicked(int index, const QString &text)
{
    if (index == 1){
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
    }
    return;
}

void LeftFolderList::handleDelItem(bool checked)
{
    m_delConfirmDialog->show();
//    FolerWidgetItem *itemDel = (FolerWidgetItem *)this->itemWidget(this->currentItem());

//    if (m_folderCtr->deleteFolder(itemDel->m_folder.id))
//    {
//        QListWidgetItem * item = this->takeItem(this->currentRow());
//        delete item;
//        emit itemClicked(this->currentItem());
//        //FolerWidgetItem *currItem = (FolerWidgetItem *)this->itemWidget(this->currentItem());
//    }
//    else {
//        qDebug() << "error: delete item error";
//    }
//    return;
}

void LeftFolderList::handleRenameItem(bool checked)
{
    FolerWidgetItem *item = (FolerWidgetItem*)this->itemWidget(this->currentItem());
    qDebug()<<"curItemRow:"<<this->currentRow();
    item->changeToEditMode();
}


