#include "leftfolderlist.h"
#include "intancer.h"
#include "noteoper.h"   //Add bug2963

#include <QFrame>
#include <QDebug>
#include <DPalette>
#include <DApplicationHelper>
//#include <DStyledItemDelegate>

LeftFolderList::LeftFolderList(FolderController *folderCtr)
{
    this->m_folderCtr = folderCtr;
    initUI();
    initConnection();
    //setFocusPolicy(Qt::NoFocus);
    setSpacing(5);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setResizeMode(QListWidget::Adjust);
    setViewMode(QListView::ListMode);
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
    m_boader->setVisible(false);

    m_delConfirmDialog = UiUtil::createChooseDialog(QString(""), QString(tr("您确定要删除记事本吗？")), nullptr, QString(tr("取消")), QString(tr("删除")));

    m_delNoPromisDialog = UiUtil::createConfirmDialog(QString(""), QString(tr("录音中禁止删除记事本")), nullptr);

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
    item->setSizeHint(QSize(230,64));
    item->setData(Qt::UserRole, 10);

    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr, searchKey);
    connect(this, SIGNAL(sigBoardPress()), folderItem, SLOT(tryToFouceout()));

    this->addItem(item);
    this->setItemWidget(item, folderItem);

}

void LeftFolderList::insertWidgetItemToTop(FOLDER folder, QString searchKey)
{
    QListWidgetItem *item=new QListWidgetItem();
    item->setSizeHint(QSize(230,64));
    item->setData(Qt::UserRole, 10);

    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr, searchKey);
    connect(this, SIGNAL(sigBoardPress()), folderItem, SLOT(tryToFouceout()));

    int count = this->count();
    this->insertItem(0,item);
    this->setItemWidget(item, folderItem);
}

void LeftFolderList::handleCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous)
    {

    }
}

void LeftFolderList::mousePressEvent(QMouseEvent *event)
{
    if(Intancer::get_Intancer()->getTryToDelEmptyTextNote())
    {
        return;
    }
    //要继续保留QListWidget原有的点击事件.
    DListWidget::mousePressEvent(event);
    //确保右键点击，然后跳出菜单.
    if ((event->button() == Qt::RightButton) && (this->count() > 0))
    {
        m_contextMenu->exec(event->globalPos());
    }
}

bool LeftFolderList::eventFilter(QObject *o, QEvent *e)
{
    switch (e->type())
    {
        case QEvent::MouseButtonPress:
            emit sigBoardPress();
            qDebug()<<"LeftFolderList::MouseButtonPress";
        break;
    }
    return DListWidget::eventFilter(o,e);
}

void LeftFolderList::handleDelDialogClicked(int index, const QString &text)
{
    if (index == 1){
        FolerWidgetItem *itemDel = (FolerWidgetItem *)this->itemWidget(this->currentItem());

        if(!Intancer::get_Intancer()->getRecodingFlag())
        {
            if (m_folderCtr->deleteFolder(itemDel->m_folder.id))
            {
                QListWidgetItem * item = this->takeItem(this->currentRow());
                delete item;
                emit itemClicked(this->currentItem());

                if(this->count() == 0)
                {
                    //emit sigAllFolderDeleted(); //Del bug3136
                    //Add start bug3136
                    if (m_folderCtr->getFolderList().size() ==0)
                    {
                         emit sigAllFolderDeleted();
                    }
                    else
                    {
                         emit sigNoResult();
                    }
                    //Add end bug3163
                }
                //Add start bug2963
                //删除当前folde的所以对应文件级数据库的记录
                QList<NOTE> listNote = NoteOper::getNoteListByFolderId(itemDel->m_folder.id);
                for (int i=0; i<listNote.size();++i)
                {
                     if (!NoteOper::deleteNote(listNote.at(i)))
                     {
                         qDebug() << "error: delete note error";
                     }
                }
                //Add end bug2963
                //FolerWidgetItem *currItem = (FolerWidgetItem *)this->itemWidget(this->currentItem());
            }
            else {
                qDebug() << "error: delete item error";
            }
        }
        else
        {
            m_delNoPromisDialog->show();
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
    emit itemClicked(this->currentItem());
    item->changeToEditMode();
}


