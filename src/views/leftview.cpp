#include "leftview.h"
#include "intancer.h"
#include <DPalette>
#include <folderoper.h>
#include <QTime>
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
    this->setFixedWidth(250);
    //this->setStyleSheet("background: red");
    m_leftViewLayout = new QVBoxLayout;
    m_leftViewLayout->setContentsMargins(0, 0, 0, 0);


    m_leftFolderView = new LeftFolderList(m_folderCtr);
    //m_leftFolderView->setFocusPolicy(Qt::NoFocus);//会隐去DListWidget的选择背景样式，但是由于失去焦点无法通过键盘上下滚动list。
    QList<FOLDER> folderList = m_folderCtr->getFolderList();
    for (int i = 0; i < folderList.size(); i++)
    {
        m_leftFolderView->addWidgetItem(folderList.at(i), "");
    }

    m_leftFolderView->setObjectName("LeftSideBar");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
    m_leftViewLayout->addSpacing(5);
    m_leftViewLayout->addWidget(m_leftFolderView);


    //m_leftViewLayout->addWidget(m_addFolderBtn);
    //m_leftViewLayout->addSpacing(9);

    QSizePolicy sp = m_leftFolderView->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    m_leftFolderView->setSizePolicy(sp);
    this->setLayout(m_leftViewLayout);
    this->setFixedWidth(LEFTVIEW_MAX_WIDTH);

    if (m_leftFolderView->count() > 0)
    {
        m_leftFolderView->setCurrentRow(0);
        handleSelFolderChg(m_leftFolderView->currentItem());
    }

    m_addFolderBtn = new DFloatingButton(this);
    m_addFolderBtn->setFixedSize(QSize(58,58));
    m_addFolderBtn->setIcon(QIcon(":/image/icon/normal/circlebutton_add 2.svg"));
    m_addFolderBtn->setIconSize(QSize(58,58));

//    m_addFolderBtn->setIcon(QIcon(":/image/icon/normal/circlebutton_add.svg"));
//    m_addFolderBtn->setNormalPic(":/image/icon/normal/circlebutton_add 2.svg");
//    m_addFolderBtn->setHoverPic(":/image/icon/hover/circlebutton_add _hover.svg");
//    m_addFolderBtn->setPressPic(":/image/icon/press/circlebutton_add_press.svg");
    //

//    DPalette palette;

//    palette.setColor(DPalette::Background, QColor(255, 255, 255));

//    this->setAutoFillBackground(true);
//    this->setPalette(palette);

}

void LeftView::initController()
{
     m_folderCtr = new FolderController();
}
void LeftView::initConnection()
{
    connect(m_addFolderBtn, &DFloatingButton::clicked, this, &LeftView::addFolder);
    connect(m_leftFolderView, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(handleSelFolderChg(QListWidgetItem *)));
    //connect(m_leftFolderView, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(handlePressFolderChg(QListWidgetItem *)));
    connect(m_leftFolderView, SIGNAL(sigAllFolderDeleted()), this, SIGNAL(sigAllFolderDeleted()));

    connect(this, SIGNAL(sigBoardPress()), m_leftFolderView, SIGNAL(sigBoardPress()));

}

void LeftView::updateFolderView()
{
    m_leftFolderView->clear();
    QList<FOLDER> folderList = m_folderCtr->getFolderList();

    for (int i = 0; i < folderList.size(); i++)
    {
        m_leftFolderView->addWidgetItem(folderList.at(i), "");
    }
    if (m_leftFolderView->count() > 0)
    {
        m_leftFolderView->setCurrentRow(0);
        handleSelFolderChg(m_leftFolderView->currentItem());
    }
    else
    {
        clearNoteList();
    }
}

void LeftView::searchFolder(QString searchKey)
{
    m_currSearchKey = searchKey;
    m_leftFolderView->clear();
    QList<FOLDER> folderList = m_folderCtr->searchFolder(searchKey);
    for (int i = 0; i < folderList.size(); i++)
    {
        m_leftFolderView->addWidgetItem(folderList.at(i), searchKey);
    }

    if (m_leftFolderView->count() > 0)
    {
        m_leftFolderView->setCurrentRow(0);
        FolerWidgetItem *folderItem = (FolerWidgetItem*)(m_leftFolderView->itemWidget(m_leftFolderView->currentItem()));
        int folderId = folderItem->m_folder.id;
        emit searchNote(folderId, searchKey);
        folderItem->changeToClickMode();
    }
    else
    {
        emit noResult();
        clearNoteList();
    }
}

void LeftView::selectTheFirstFolderByCode()
{
    if(m_leftFolderView->count() > 0)
    {
        QListWidgetItem *pItem = m_leftFolderView->item(0);
        handleSelFolderChg(pItem);
    }
}

void LeftView::addFolder()
{
    FOLDER newFolder;
    newFolder.imgPath = UiUtil::getDefaultAvatarByRand();
    newFolder.folderName = m_folderCtr->getNextFolderName();
    newFolder.createTime = QDateTime::currentDateTime();

    m_folderCtr->addFolder(newFolder);
    updateFolderView();
    FolerWidgetItem *item = (FolerWidgetItem*)(m_leftFolderView->itemWidget(m_leftFolderView->item(0)));
    item->changeToEditMode();
    m_leftFolderView->setCurrentRow(0);

    emit sigAddFolder();
}

int LeftView::getCurrSelectFolderId()
{
    if (m_leftFolderView->count() > 0) {
        FolerWidgetItem *item = (FolerWidgetItem*)(m_leftFolderView->itemWidget(m_leftFolderView->currentItem()));
        return item->m_folder.id;
    }
    else
    {
        return -1;
    }
}

void LeftView::handleSelFolderChg(QListWidgetItem *item)
{
    int folderId = -1;
    if(Intancer::get_Intancer()->getTryToDelEmptyTextNote())
    {
        return;
    }

    if(!Intancer::get_Intancer()->getRenameRepeatFlag())
    {
        int count = m_leftFolderView->count();
        for(int i = 0; i < count; i++)
        {
            QListWidgetItem *tmpItem = m_leftFolderView->item(i);
            FolerWidgetItem *tmpfolderItem = (FolerWidgetItem*)(m_leftFolderView->itemWidget(tmpItem));
            tmpfolderItem->changeToUnClickMode();
        }

        if (nullptr != item)
        {
            FolerWidgetItem *folderItem = (FolerWidgetItem*)(m_leftFolderView->itemWidget(item));
            folderId = folderItem->m_folder.id;
            folderItem->changeToClickMode();
        }
        else
        {
            emit selFolderIdChg(folderId);
            return;
        }

        if (m_currSearchKey.isEmpty())
        {
            emit selFolderIdChg(folderId);
        }
        else
        {
            emit searchNote(folderId, m_currSearchKey);
        }
    }
}

//void LeftView::handlePressFolderChg(QListWidgetItem *item)
//{
////    int count = m_leftFolderView->count();
////    for(int i = 0; i < count; i++)
////    {
////        QListWidgetItem *tmpItem = m_leftFolderView->item(i);
////        FolerWidgetItem *tmpfolderItem = (FolerWidgetItem*)(m_leftFolderView->itemWidget(tmpItem));
////        tmpfolderItem->changeToUnClickMode();
////    }

////    if (nullptr != item)
////    {
////        FolerWidgetItem *folderItem = (FolerWidgetItem*)(m_leftFolderView->itemWidget(item));
////        folderItem->changeToClickMode();
////    }
//}

void LeftView::clearNoteList()
{
    emit clearNoteListSignal();
}

void LeftView::resizeEvent(QResizeEvent * event)
{
    m_addFolderBtn->move((this->width() - m_addFolderBtn->width())/2,this->height() - m_addFolderBtn->height() - 18);
}
