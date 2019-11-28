#include "leftview.h"
#include "intancer.h"
#include <QThread>
#include <DPalette>
#include <folderoper.h>
#include <QTime>
#include <DApplicationHelper>
#include <QDebug>
#include <DStyledItemDelegate>

//#include <DStyledItemDelegate>
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

//Add start bug 2587

void LeftView::reNameFolder()
{
    m_leftFolderView-> handleRenameItem(true);
}
void LeftView::deleteFolder()
{
    m_leftFolderView->handleDelItem(true);
}
//Add end bug 2587

void LeftView::initUI()
{
    this->setFixedWidth(250);
    m_leftViewLayout = new QVBoxLayout;
    m_leftViewLayout->setContentsMargins(0, 0, 0, 0);

//    m_LeftListBoard = new DWidget(this);
//    m_LeftListBoard->resize(this->width(),this->height() - 150);
//    m_LeftListBoard->move(0,0);


    m_leftFolderView = new LeftFolderList(m_folderCtr);

    DStyledItemDelegate* itemDelegate = new DStyledItemDelegate(m_leftFolderView);
    itemDelegate->setBackgroundType(DStyledItemDelegate::NoBackground);
    m_leftFolderView->setItemDelegate(itemDelegate);

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


    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        m_addFolderBtn = new MyRecodeButtons(
                    ":/image/icon/normal/circlebutton_add 2.svg",
                    ":/image/icon/press/circlebutton_add_press.svg",
                    ":/image/icon/hover/circlebutton_add _hover.svg",
                    ":/image/icon/disabled/circlebutton_add_disabled.svg",
                    ":/image/icon/focus/circlebutton_add_focus.svg",
                    QSize(68,68),
                    this);
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        m_addFolderBtn = new MyRecodeButtons(
                    ":/image/icon_dark/normal/add_normal_dark.svg",
                    ":/image/icon_dark/press/add_press_dark.svg",
                    ":/image/icon_dark/hover/add _hover_dark.svg",
                    ":/image/icon_dark/disabled/add_disabled_dark.svg",
                    ":/image/icon_dark/focus/add_focus_dark.svg",
                    QSize(68,68),
                    this);
    }
    else {
        m_addFolderBtn = new MyRecodeButtons(
                    ":/image/icon/normal/circlebutton_add 2.svg",
                    ":/image/icon/press/circlebutton_add_press.svg",
                    ":/image/icon/hover/circlebutton_add _hover.svg",
                    ":/image/icon/disabled/circlebutton_add_disabled.svg",
                    ":/image/icon/focus/circlebutton_add_focus.svg",
                    QSize(68,68),
                    this);
    }

//    m_addFolderBtn->setFixedSize(QSize(58,58));

//    //m_addFolderBtn->setIcon(QIcon(":/image/icon/normal/circlebutton_add .svg"));
//    m_addFolderBtn->setIcon(QIcon(UiUtil::renderSVG(":/image/icon/normal/circlebutton_add .svg", QSize(34,34),qApp)));
//    m_addFolderBtn->setIconSize(QSize(34,34));


    //3799
//    DPalette pa = DApplicationHelper::instance()->palette(m_addFolderBtn);
//    pa.setBrush(DPalette::Highlight, pa.color(DPalette::DarkLively));

    DPalette pa = DApplicationHelper::instance()->palette(this);
    pa.setBrush(DPalette::Background, pa.color(DPalette::Base));
    this->setAutoFillBackground(true);
    this->setPalette(pa);
}

void LeftView::initController()
{
     m_folderCtr = new FolderController();
}
void LeftView::initConnection()
{
    connect(m_addFolderBtn, &DFloatingButton::clicked, this, &LeftView::addFolder);
    //connect(m_leftFolderView, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(handleSelFolderChg(QListWidgetItem *)));
    //connect(m_leftFolderView, SIGNAL(currentItemChanged(QListWidgetItem *)), this, SLOT(handleSelFolderChg(QListWidgetItem *)));
    connect(m_leftFolderView, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(itemSelectedChanged(QListWidgetItem *, QListWidgetItem *)));

    //connect(m_leftFolderView, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(handlePressFolderChg(QListWidgetItem *)));
    connect(m_leftFolderView, SIGNAL(sigAllFolderDeleted()), this, SIGNAL(sigAllFolderDeleted()));

    connect(this, SIGNAL(sigBoardPress()), m_leftFolderView, SIGNAL(sigBoardPress()));
    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &LeftView::changeTheme);

    connect(m_leftFolderView, SIGNAL(sigNoResult()), this, SLOT(onNoResult())); //Add bug3136
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

bool LeftView::searchFolder(QString searchKey, bool &hasNoFolder)
{
    bool hasResult = false;
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
        hasResult = true;
        hasNoFolder = false;
    }
    else
    {
        emit noResult();
        clearNoteList();
        hasNoFolder = true;
    }

    return hasResult;
}

void LeftView::selectTheFirstFolderByCode()
{
    if(m_leftFolderView->count() > 0)
    {
        QListWidgetItem *pItem = m_leftFolderView->item(0);
        handleSelFolderChg(pItem);
    }
}

int LeftView::getAllFolderListNum()
{
    int num = m_folderCtr->getFolderList().count();
    return num;
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

void LeftView::sendSelectCurFolder()
{
    int curfolderID = getCurrSelectFolderId();
    emit selFolderIdChg(curfolderID);
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
//        for(int i = 0; i < count; i++)
//        {
//            QListWidgetItem *tmpItem = m_leftFolderView->item(i);
//            FolerWidgetItem *tmpfolderItem = (FolerWidgetItem*)(m_leftFolderView->itemWidget(tmpItem));
//            tmpfolderItem->changeToUnClickMode();
//        }

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

void LeftView::itemSelectedChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(nullptr != m_leftFolderView)
    {
        if((nullptr != current) && (nullptr != previous))
        {
            FolerWidgetItem* pCurFolder = (FolerWidgetItem*)m_leftFolderView->itemWidget(current);
            pCurFolder->changeToClickMode();

            FolerWidgetItem* pPrevious = (FolerWidgetItem*)m_leftFolderView->itemWidget(previous);
            pPrevious->changeToUnClickMode();
        }
        if(0 == Intancer::get_Intancer()->getMoveFolderFlag())
        {
            if(nullptr != current)
            {
                handleSelFolderChg(current);
            }
        }
        else
        {
            Intancer::get_Intancer()->CountMoveFolderCount();
        }
    }
}

void LeftView::viewDisabled()
{
    m_leftFolderView->setDisabled(true);
    m_addFolderBtn->setDisabled(true);
}

void LeftView::viewEnabled()
{
    m_leftFolderView->setDisabled(false);
    m_addFolderBtn->setDisabled(false);
}

void LeftView::changeTheme()
{
    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        if(nullptr != m_addFolderBtn)
        {
            m_addFolderBtn->setPicChange(
                        ":/image/icon/normal/circlebutton_add 2.svg",
                        ":/image/icon/press/circlebutton_add_press.svg",
                        ":/image/icon/hover/circlebutton_add _hover.svg",
                        ":/image/icon/disabled/circlebutton_add_disabled.svg",
                        ":/image/icon/focus/circlebutton_add_focus.svg"
                        );
        }

    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        if(nullptr != m_addFolderBtn)
        {
            m_addFolderBtn->setPicChange(
                        ":/image/icon_dark/normal/add_normal_dark.svg",
                        ":/image/icon_dark/press/add_press_dark.svg",
                        ":/image/icon_dark/hover/add _hover_dark.svg",
                        ":/image/icon_dark/disabled/add_disabled_dark.svg",
                        ":/image/icon_dark/focus/add_focus_dark.svg"
                    );
        }

    }
    //liuyang 3799
    DPalette pa = DApplicationHelper::instance()->palette(this);
    pa.setBrush(DPalette::Background, pa.color(DPalette::Base));
    this->setPalette(pa);
    //liuyang 3799
}

void LeftView::OnChangeCurFolderToTop(int folderID)
{

    QListWidgetItem* tmpItem = m_leftFolderView->item(0);
    FolerWidgetItem *ptmpWidget = (FolerWidgetItem *)m_leftFolderView->itemWidget(tmpItem);
    if(nullptr != ptmpWidget)
    {
        FOLDER newFolder; //liuyang 3550 3547 3528
        if(ptmpWidget->m_folder.id != folderID)
        {
            QListWidgetItem *preItem = m_leftFolderView->currentItem();
            FolerWidgetItem *pWidget = (FolerWidgetItem*)m_leftFolderView->itemWidget(preItem);


            //FOLDER newFolder; //liuyang 3550 3547 3528

            newFolder.id = pWidget->m_folder.id;
            newFolder.imgPath = pWidget->m_folder.imgPath;
            newFolder.folderName = pWidget->m_folder.folderName;
            newFolder.createTime = pWidget->m_folder.createTime;

            //liuyang 3550 3547 3528
            QDateTime curtime = QDateTime::currentDateTime();
            if(newFolder.createTime != curtime)
            {
               newFolder.createTime = curtime;
               m_folderCtr->updateFolderCreateTime(newFolder);
            }
            //liuyang 3550 3547 3528

            QString searchKey = pWidget->getSearchText();

            m_leftFolderView->insertWidgetItemToTop(newFolder, searchKey);

            Intancer::get_Intancer()->initMoveFolderCount();

            m_leftFolderView->takeItem(m_leftFolderView->currentRow());
            delete preItem;

            m_leftFolderView->setCurrentRow(0);
        }
        //liuyang 3550 3547 3528
        else
        {
            QDateTime curtime = QDateTime::currentDateTime();
            if(ptmpWidget->m_folder.createTime != curtime)
            {
                newFolder.id = ptmpWidget->m_folder.id;
                newFolder.imgPath = ptmpWidget->m_folder.imgPath;
                newFolder.folderName = ptmpWidget->m_folder.folderName;
                newFolder.createTime = curtime;
                m_folderCtr->updateFolderCreateTime(newFolder);
                ptmpWidget->updateTimeLable(curtime);
            }
        }
        //liuyang 3550 3547 3528
    }
}

//Add start bug3136
void LeftView::onNoResult()
{
    emit noResult();
    clearNoteList();
}
//Add end bug3136

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
    m_addFolderBtn->move((this->width() - m_addFolderBtn->width())/2,this->height() - m_addFolderBtn->height() - 12);
    //m_greyboard->setFixedSize(this->size());
}
