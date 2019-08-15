#include "leftview.h"

#include <QVBoxLayout>

LeftView::LeftView()
{
    initUI();
}

//void DFileManagerWindow::initRightView()
//{
//    D_D(DFileManagerWindow);

//    initTabBar();
//    initViewLayout();
//    d->rightView = new QFrame;

//    QSizePolicy sp = d->rightView->sizePolicy();

//    //NOTE(zccrs): 保证窗口宽度改变时只会调整right view的宽度，侧边栏保持不变
//    //             QSplitter是使用QLayout的策略对widgets进行布局，所以此处
//    //             设置size policy可以生效
//    sp.setHorizontalStretch(1);
//    d->rightView->setSizePolicy(sp);

//    this->initRenameBarState();

//    d->emptyTrashButton = new QPushButton{ this };
//    d->emptyTrashButton->setFixedHeight(25);
//    d->emptyTrashButton->hide();
//    d->emptyTrashButton->setContentsMargins(0, 0, 0, 0);
//    d->emptyTrashButton->setObjectName("EmptyTrashButton");

//    QHBoxLayout *tabBarLayout = new QHBoxLayout;
//    tabBarLayout->setMargin(0);
//    tabBarLayout->setSpacing(0);
//    tabBarLayout->addWidget(d->tabBar);
//    tabBarLayout->addWidget(d->newTabButton);

//    d->rightViewLayout = new QVBoxLayout;
//    d->rightViewLayout->addLayout(tabBarLayout);
//    d->rightViewLayout->addWidget(d->emptyTrashButton);
//    d->rightViewLayout->addLayout(d->viewStackLayout);
//    d->rightViewLayout->setSpacing(0);
//    d->rightViewLayout->setContentsMargins(0, 0, 0, 0);
//    d->rightView->setLayout(d->rightViewLayout);
//}

void LeftView::initUI()
{
    //this->setStyleSheet("background: blue");
    leftViewLayout = new QVBoxLayout;
    leftViewLayout->setContentsMargins(0, 0, 0, 0);

    leftFolderView = new LeftFolderView();
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
