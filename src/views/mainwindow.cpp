#include "leftview.h"
#include "mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>
#include <DTitlebar>
#include <DMenu>
#include <uiutil.h>
#include "intancer.h"
#include <DApplicationHelper>

MyMainWindow::MyMainWindow()
{
    initUI();
    initConnection();
//    qDebug()<<"1111111111111111111111"<<UiUtil::canMicrophoneInput();
}

void MyMainWindow::initUI() {
    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    //setWindowRadius(20);
    setMinimumSize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    m_SearchDialog = UiUtil::createChooseDialog(QString(""), QString(tr("录音中进行搜索会中断录音，是否要继续？")), nullptr, QString(tr("否")), QString(tr("是")));
    initTitleBar();
    initCentralWidget();
}


void MyMainWindow::initConnection()
{
    //QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_mainPage, SIGNAL(textEditClicked(NOTE)), this, SLOT(showNoteDetail(NOTE)));
    QObject::connect(m_mainPage, SIGNAL(clearSearch()), this, SLOT(clearSearchLine()));
    QObject::connect(m_mainPage, SIGNAL(sig_research()), this, SLOT(tryToSearch()));
    connect(m_mainPage,SIGNAL(sigAllFolderDeleted()),this,SLOT(onAllFolderDeleted()));

    QObject::connect(m_returnBtn, SIGNAL(clicked()), this, SLOT(showListPage()));
    //connect(m_searchEdit, &DSearchEdit::returnPressed, this, &MyMainWindow::handleSearchKey);
    connect(m_searchEdit, &DSearchEdit::textChanged, this, &MyMainWindow::tryToSearch);
    connect(m_SearchDialog, &DDialog::buttonClicked, this, &MyMainWindow::handleDelDialogClicked);
    connect(m_SearchDialog, &DDialog::closed, this, &MyMainWindow::handleCloseDialogClicked);
    connect(m_InitEmptyPage,SIGNAL(sigAddFolderByInitPage()),this,SLOT(onAddFolderByInitPage()));



//    QObject::connect(m_returnBtn, &DImageButton::clicked, this, &MyMainWindow::showListPage);

}

void MyMainWindow::initTitleFrame()
{
    QIcon icon = QIcon::fromTheme("deepin-voice-note");
    m_logo = new QLabel();
    m_logo->setObjectName("LogoButton");
    m_logo->setFixedSize(QSize(32, 32));
    m_logo->setPixmap(icon.pixmap(QSize(32, 32)));


//    m_returnBtn = new DImageButton();
//    m_returnBtn->setFixedSize(QSize(24, 24));
//    m_returnBtn->setNormalPic(":/image/icon/normal/back_normal.svg");
//    m_returnBtn->setHoverPic(":/image/add_hover.svg");
//    m_returnBtn->setPressPic(":/image/icon/press/back_press.svg");
//    QString returnIcon = "";
//    QString text = "<";
//    m_returnBtn = new DIconButton(returnIcon, text);
    m_returnBtn = new DIconButton(this);
    m_returnBtn->setFixedSize(QSize(36,36));
    m_returnBtn->setIcon(QIcon(":/image/icon/normal/back_normal.svg"));
    m_returnBtn->setIconSize(QSize(27,27));
    m_returnBtn->setVisible(false);
    m_replaceForReturn = new DWidget;
    m_replaceForReturn->setFixedSize(QSize(36, 36));
    m_replaceForReturn->setVisible(true);

    m_searchEdit = new DSearchEdit();
    QSizePolicy sp = m_searchEdit->sizePolicy();
    sp.setHorizontalStretch(1);
    m_searchEdit->setSizePolicy(sp);

    m_titleFrame = new QFrame;
    m_titleFrame->setObjectName("TitleBar");

    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setMargin(0);
    titleLayout->setSpacing(0);
    titleLayout->addSpacing(2);
    titleLayout->addWidget(m_logo);
    titleLayout->addSpacing(12);
    titleLayout->addWidget(m_returnBtn);
    titleLayout->addWidget(m_replaceForReturn);
    titleLayout->addSpacing(145);
    titleLayout->addWidget(m_searchEdit);
    titleLayout->addSpacing(34);
    //titleLayout->setSpacing(52);
    titleLayout->setContentsMargins(0, 0, 0, 0);

    QSizePolicy spLogo= m_logo->sizePolicy();
    spLogo.setHorizontalStretch(1);
    m_logo->setSizePolicy(spLogo);
    m_titleFrame->setLayout(titleLayout);
    m_titleFrame->setFixedHeight(TITLE_FIXED_HEIGHT);

    this->titlebar()->setCustomWidget(m_titleFrame, false);

}

void MyMainWindow::initCentralWidget()
{
    initStackedWidget();

    m_centralWidget = new QFrame(this);
    m_centralWidget->setObjectName("CentralWidget");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_stackedWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    m_centralWidget->setLayout(mainLayout);
    setCentralWidget(m_centralWidget);
}

void MyMainWindow::initTitleBar()
{
    initTitleFrame();
}

void MyMainWindow::initStackedWidget()
{
//    m_stackedWidgetLayout = new QVBoxLayout();
//    this->setLayout(m_stackedWidgetLayout);
    m_stackedWidget = new QStackedWidget();
    //m_stackedWidgetLayout->addWidget(m_stackedWidget);
    //m_stackedWidget->setGeometry(QRect(10, 10, this->width(), this->height()));
    m_stackedWidget->setObjectName("stackedWidget");

    m_mainPage = new MainPage();
    m_stackedWidget->addWidget(m_mainPage);
    //m_stackedWidget->setCurrentIndex(0);


    m_detailPage = new DFrame();
    m_detailPageLayout = new QVBoxLayout();
    m_detailPage->setLayout(m_detailPageLayout);
    m_textNoteEdit = new TextNoteEdit();
    m_detailPageLayout->addWidget(m_textNoteEdit);
    m_stackedWidget->addWidget(m_detailPage);
    m_textNoteEdit->setFrameShape(QListWidget::NoFrame);
    m_textNoteEdit->setAttribute(Qt::WA_TranslucentBackground, true);

    DPalette pb = DApplicationHelper::instance()->palette(m_detailPage);
    //pb.setBrush(DPalette::Base, QColor(255,255,255,255));
    pb.setBrush(DPalette::Base, pb.color(DPalette::Base));
    m_detailPage->setPalette(pb);


    m_InitEmptyPage = new  InitEmptyPage();
    m_stackedWidget->addWidget(m_InitEmptyPage);

    if(0 < m_mainPage->getFolderCount())
    {
        m_stackedWidget->setCurrentIndex(0);
    }
    else
    {
        m_stackedWidget->setCurrentIndex(2);
    }
}

void MyMainWindow::showNoteDetail(NOTE note)
{
    m_textNoteEdit->setTextNote(note, m_searchEdit->text());
    m_textNoteEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

    m_stackedWidget->setCurrentIndex(1);
    m_returnBtn->setVisible(true);
    m_replaceForReturn->setVisible(false);
}

void MyMainWindow::showListPage()
{
    if(!m_searchEdit->text().isEmpty())
    {
        m_mainPage->searchFolder(m_searchEdit->text());
    }
    m_mainPage->updateFromDetal(m_textNoteEdit->getID());
    m_stackedWidget->setCurrentIndex(0);
    m_returnBtn->setVisible(false);
    m_replaceForReturn->setVisible(true);
}

void MyMainWindow::handleSearchKey()
{
    QString searchKey = m_searchEdit->text();

   if(!searchKey.isEmpty())
    {
        Intancer::get_Intancer()->setSearchingFlag(true);
    }
    else
    {
        Intancer::get_Intancer()->setSearchingFlag(false);
    }

    if (0 == m_stackedWidget->currentIndex())
    {
        Intancer::get_Intancer()->setRenameRepeatFlag(false);
        m_mainPage->searchFolder(searchKey);
    }
    else
    {
        m_textNoteEdit->searchText(searchKey);
    }
}

void MyMainWindow::tryToSearch()
{
    if(Intancer::get_Intancer()->getRecodingFlag())
    {
        m_SearchDialog->show();
        Intancer::get_Intancer()->setSearchingFlag(false);
    }
    else
    {
        handleSearchKey();
    }
}

void MyMainWindow::handleDelDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        handleSearchKey();
    }
    else
    {
        m_searchEdit->clear();
        Intancer::get_Intancer()->setSearchingFlag(false);
    }
}

void MyMainWindow::handleCloseDialogClicked()
{
    m_searchEdit->clear();
}

void MyMainWindow::clearSearchLine()
{
    m_searchEdit->clear();
}

void MyMainWindow::onAddFolderByInitPage()
{
    m_stackedWidget->setCurrentIndex(0);
    m_mainPage->trueAddFolder();
}

void MyMainWindow::onAllFolderDeleted()
{
    m_stackedWidget->setCurrentIndex(2);
}

void MyMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
        m_mainPage->cancleRecord();
        break;
    }
    return QWidget::keyPressEvent(event);
}

void MyMainWindow::changeEvent(QEvent * event)
{
    if(event->type()!=QEvent::WindowStateChange)
    {
        return;
    }

    if(this->windowState()==Qt::WindowMaximized || this->windowState()==Qt::WindowNoState)
    {
        //m_mainPage->selectCurFolder();
    }

}

void MyMainWindow::closeEvent(QCloseEvent* event)
{
    m_mainPage->checkAndDeleteEmptyTextNoteFromDatabase();
//    if(4 == m_pCenterWidget->currentIndex())
//    {
//        emit dApp->signalM->hideImageView();
//        //不关闭
//        event->ignore();
//    }
//    else {
//        //关闭
//        event->accept();
//    }
    DMainWindow::closeEvent(event);
}


