#include "leftview.h"

#include <DPalette>
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
        m_leftFolderView->addWidgetItem(folderList.at(i), "");
    }

    m_leftFolderView->setObjectName("LeftSideBar");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
    m_leftViewLayout->addWidget(m_leftFolderView);

    m_addFolderBtn = new DImageButton();
    m_addFolderBtn->setNormalPic(":/image/icon/normal/circlebutton_add.svg");
    m_addFolderBtn->setHoverPic(":/image/icon/hover/circlebutton_add _hover.svg");
    m_addFolderBtn->setPressPic(":/image/icon/press/circlebutton_add_press.svg");

    m_leftViewLayout->addWidget(m_addFolderBtn);
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

    DPalette palette;

    palette.setColor(DPalette::Background, QColor(255, 255, 255));

    this->setAutoFillBackground(true);
    this->setPalette(palette);



}

void LeftView::initController()
{
     m_folderCtr = new FolderController();
}
void LeftView::initConnection()
{
    connect(m_addFolderBtn, &DImageButton::clicked, this, &LeftView::addFolder);
    connect(m_leftFolderView, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(handleSelFolderChg(QListWidgetItem *)));

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
    QList<FOLDER> folderList = m_folderCtr-> searchFolder(searchKey);
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
    }
    else
    {
        clearNoteList();
    }
}

void LeftView::addFolder()
{
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
    FolerWidgetItem *folderItem = (FolerWidgetItem*)(m_leftFolderView->itemWidget(item));
    int folderId = folderItem->m_folder.id;
    if (m_currSearchKey.isEmpty())
    {
        emit selFolderIdChg(folderId);
    }
    else
    {
        emit searchNote(folderId, m_currSearchKey);
    }

}

void LeftView::clearNoteList()
{
    emit clearNoteListSignal();
}
