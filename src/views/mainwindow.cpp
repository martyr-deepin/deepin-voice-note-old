#include "leftview.h"
#include "mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>
#include <DTitlebar>
#include <DMenu>
#include <uiutil.h>
#include "intancer.h"
#include <DApplicationHelper>
//start add by yuanshuai 20191120 2841
#include <DMessageManager>
#include <DFloatingMessage>
//end

MyMainWindow::MyMainWindow()
{
    m_quit = false; //Add bug3470
    //qDebug()<<"2222222222222222222"<<UiUtil::canMicrophoneInput();
    initUI();
    initConnection();
}

void MyMainWindow::initUI() {

    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    //setWindowRadius(20);
    setMinimumSize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    m_SearchDialog = UiUtil::createChooseDialog(QString(""), QString(tr("Searching in the recording interrupts the recording. Do you want to continue?")), nullptr, QString(tr("No")), QString(tr("Yes")));
//    m_SearchDialog = UiUtil::createChooseDialog(QString(""), QString(tr("录音中进行搜索会中断录音，是否要继续？")), nullptr, QString(tr("否")), QString(tr("是")));
    m_exitDialog = UiUtil::createChooseDialog(QString(""), QString(tr("Currently recording, is the recording terminated?")), nullptr, QString(tr("Cancel")), QString(tr("Stop")));
    //m_exitDialog = UiUtil::createChooseDialog(QString(""), QString(tr("当前正在录⾳中，是否终⽌录⾳？")), nullptr, QString(tr("取消")), QString(tr("终止")));
    initTitleBar();
    initCentralWidget();
}


void MyMainWindow::initConnection()
{
    //QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_mainPage, SIGNAL(textEditClicked(NOTE)), this, SLOT(showNoteDetail(NOTE)));
    QObject::connect(m_mainPage, SIGNAL(clearSearch()), this, SLOT(clearSearchLine()));
    QObject::connect(m_mainPage, SIGNAL(sig_research()), this, SLOT(tryToSearch()));
    QObject::connect(m_mainPage, SIGNAL(sigNoSearchResult()), this, SLOT(OnNoSearchResult()));

    connect(m_mainPage,SIGNAL(sigAllFolderDeleted()),this,SLOT(onAllFolderDeleted()));

    QObject::connect(m_returnBtn, SIGNAL(clicked()), this, SLOT(showListPage()));
    //connect(m_searchEdit, &DSearchEdit::returnPressed, this, &MyMainWindow::handleSearchKey);
    //connect(m_searchEdit, &DSearchEdit::returnPressed, this, &MyMainWindow::tryToSearch);
    connect(m_searchEdit, &DSearchEdit::textChanged, this, &MyMainWindow::tryToSearch);
    connect(m_SearchDialog, &DDialog::buttonClicked, this, &MyMainWindow::handleSearchDialogClicked);
    connect(m_SearchDialog, &DDialog::closed, this, &MyMainWindow::handleCloseSearchDialog);
    connect(m_InitEmptyPage,SIGNAL(sigAddFolderByInitPage()),this,SLOT(onAddFolderByInitPage()));

    connect(m_exitDialog, &DDialog::buttonClicked, this, &MyMainWindow::handleCloseExitDialogClicked);
    connect(m_exitDialog, &DDialog::closed, this, &MyMainWindow::handleCloseExitDialog);

    connect(m_mainPage, SIGNAL(stopRecoiding()), this, SLOT(stopRecoidingFunc()));  //Add bug3470
    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &MyMainWindow::changeTheme);
    connect(DApplicationHelper::instance(), &DApplicationHelper::newProcessInstance, this, &MyMainWindow::restoreminwindow);
//    QObject::connect(m_returnBtn, &DImageButton::clicked, this, &MyMainWindow::showListPage);
    //start add by yuanshuai 20191120 2841
    connect(m_mainPage,SIGNAL(sigMpCheckFile()),this,SLOT(checkFileExist()));
    //end
}

void MyMainWindow::initTitleFrame()
{
    QIcon icon = QIcon::fromTheme("deepin-voice-note");
    m_logo = new QLabel(this);
    m_logo->setObjectName("LogoButton");
    m_logo->setFixedSize(QSize(32, 32));
    m_logo->setPixmap(icon.pixmap(QSize(32, 32)));
    m_logo->move(9,10);

    m_returnBtn = new DIconButton(this);
    m_returnBtn->setFixedSize(QSize(36,36));

    //m_returnBtn->setIcon(QIcon(":/image/icon/normal/back_normal.svg"));
    m_returnBtn->setIcon(QIcon(UiUtil::renderSVG(":/image/icon/normal/back_normal.svg", QSize(27,27),qApp)));
    m_returnBtn->setIconSize(QSize(27,27));
    m_returnBtn->setVisible(false);
    m_returnBtn->move(m_logo->x() + m_logo->width() + 15,8);
//    m_replaceForReturn = new DWidget;
//    m_replaceForReturn->setFixedSize(QSize(36, 36));
//    m_replaceForReturn->setVisible(true);

    m_searchEdit = new DSearchEdit();
    m_searchEdit->setFixedWidth(350);
//    QSizePolicy sp = m_searchEdit->sizePolicy();
//    sp.setHorizontalStretch(1);
//    m_searchEdit->setSizePolicy(sp);

    m_titleFrame = new QFrame;
    m_titleFrame->setObjectName("TitleBar");

    QHBoxLayout *titleLayout = new QHBoxLayout;
//    titleLayout->setMargin(0);
//    titleLayout->setSpacing(0);
//    titleLayout->addSpacing(2);
//    titleLayout->addWidget(m_logo);
//    titleLayout->addSpacing(12);
//    titleLayout->addWidget(m_returnBtn);
//    titleLayout->addWidget(m_replaceForReturn);
    titleLayout->addSpacing(145);
    titleLayout->addWidget(m_searchEdit);
    titleLayout->addSpacing(34);
    //titleLayout->setSpacing(52);
    titleLayout->setContentsMargins(0, 0, 0, 0);

//    QSizePolicy spLogo= m_logo->sizePolicy();
//    spLogo.setHorizontalStretch(1);
//    m_logo->setSizePolicy(spLogo);
    m_titleFrame->setLayout(titleLayout);
    m_titleFrame->setFixedHeight(TITLE_FIXED_HEIGHT);
    m_titleFrame->setFocusPolicy(Qt::ClickFocus);

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


    m_detailPage = new DWidget(this);
    m_detailPageLayout = new QVBoxLayout();
    m_detailPage->setLayout(m_detailPageLayout);
    m_textNoteEdit = new TextNoteEdit();
    m_textNoteEdit->document()->setDocumentMargin(10.0);
    m_detailPageLayout->addWidget(m_textNoteEdit);
    m_stackedWidget->addWidget(m_detailPage);
    //m_stackedWidget->addWidget(m_textNoteEdit);
    m_textNoteEdit->setFrameShape(QListWidget::NoFrame);
    m_textNoteEdit->setAttribute(Qt::WA_TranslucentBackground, true);
    QPalette pl = m_textNoteEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(0,0,0,0)));
    m_textNoteEdit->setPalette(pl);

    DPalette pb = DApplicationHelper::instance()->palette(m_detailPage);
    pb.setBrush(DPalette::Background, pb.color(DPalette::Base));
    m_detailPage->setPalette(pb);


    m_InitEmptyPage = new  InitEmptyPage();
    m_stackedWidget->addWidget(m_InitEmptyPage);

    if(0 < m_mainPage->getFolderCount())
    {
        m_stackedWidget->setCurrentIndex(0);
        m_searchEdit->setEnabled(true); //Add  bug3136
    }
    else
    {
        m_stackedWidget->setCurrentIndex(2);
        m_searchEdit->setEnabled(false); //Add  bug3136
    }

    m_SearchNonePage = new SearchNonePage(this);
    m_stackedWidget->addWidget(m_SearchNonePage);
}

void MyMainWindow::showNoteDetail(NOTE note)
{
    m_textNoteEdit->setTextNote(note, m_searchEdit->text());
    m_textNoteEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

    m_DetalTextBak = m_textNoteEdit->getText();
    m_stackedWidget->setCurrentIndex(1);
    m_returnBtn->setVisible(true);
    //m_replaceForReturn->setVisible(false);
}

void MyMainWindow::showListPage()
{
    //bool ret = false;
    if(!m_searchEdit->text().isEmpty())
    {
        bool hasNoFolder = false;
        m_mainPage->searchFolder(m_searchEdit->text(),hasNoFolder);
//        if(ret)
//        {
//            m_stackedWidget->setCurrentIndex(0);
//        }
    }
    m_mainPage->updateFromDetal(m_textNoteEdit->getID());
    m_stackedWidget->setCurrentIndex(0);
    m_searchEdit->setEnabled(true); //Add  bug3136
    m_mainPage->setFocus();
    m_returnBtn->setVisible(false);
    //m_replaceForReturn->setVisible(true);

    if(m_DetalTextBak != m_textNoteEdit->getText())
    {
        m_mainPage->ChangeCurFolderToTop(m_textNoteEdit->getFolderID());
    }

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
        m_stackedWidget->setCurrentIndex(0);
        m_searchEdit->setEnabled(true); //Add  bug3136
    }

    bool ret = false;
    if (0 == m_stackedWidget->currentIndex() || 3 == m_stackedWidget->currentIndex())
    {
        Intancer::get_Intancer()->setRenameRepeatFlag(false);
        bool hasNoFolder = false;
        ret = m_mainPage->searchFolder(searchKey,hasNoFolder);
        if(ret)
        {
            m_stackedWidget->setCurrentIndex(0);
            m_searchEdit->setEnabled(true); //Add  bug3136
        }
//        else
//        {
////            if(hasNoFolder)
////            {
//                m_stackedWidget->setCurrentIndex(2);
////            }
//        }
    }
    else
    {
        m_textNoteEdit->searchText(searchKey);
    }


}

void MyMainWindow::tryToSearch()
{
//    if(0 < m_mainPage->getAllFolderListNumFromDatabase())
//    {
        if(Intancer::get_Intancer()->getRecodingFlag())
        {
            m_SearchDialog->show();
            Intancer::get_Intancer()->setSearchingFlag(false);
        }
        else
        {
            handleSearchKey();
        }
//    }
}

void MyMainWindow::handleSearchDialogClicked(int index, const QString &text)
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

void MyMainWindow::handleCloseSearchDialog()
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
    m_searchEdit->setEnabled(true); //Add  bug3136
    m_mainPage->trueAddFolder();
}

void MyMainWindow::onAllFolderDeleted()
{
    m_stackedWidget->setCurrentIndex(2);
    //m_searchEdit->clear(); //Add  bug3136
    m_searchEdit->setEnabled(false); //Add  bug3136
}

void MyMainWindow::handleCloseExitDialog()
{

}

void MyMainWindow::handleCloseExitDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        //保存录音
        m_mainPage->saveRecorde();
        m_quit = true;  //Del bug3470
        //qApp->quit(); //Del bug3470

    }
    else
    {
        //取消退出
    }
}

void MyMainWindow::changeTheme()
{
    DPalette pb = DApplicationHelper::instance()->palette(m_detailPage);
    pb.setBrush(DPalette::Background, pb.color(DPalette::Base));
    m_detailPage->setPalette(pb);
}

void MyMainWindow::OnNoSearchResult()
{
    m_stackedWidget->setCurrentIndex(3);
}

//Add start bug3470
void MyMainWindow::stopRecoidingFunc()
{
    if (m_quit)
    {
        qApp->quit();
    }
}
//Add end bug3470

void MyMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
        m_mainPage->cancleRecord();
        break;
        case Qt::Key_Space:
        m_mainPage->cancleRecord();
        break;
        case Qt::Key_Enter:
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
void MyMainWindow::restoreminwindow()
{
    Qt::WindowStates status = this->windowState();
    if(status == Qt::WindowMinimized)
    {
        this->setWindowState(Qt::WindowActive);
        this->activateWindow();
    }
}

//start add by yuanshuai 20191120 2841
void MyMainWindow::checkFileExist()
{
    DFloatingMessage *pDFloatingMessage = new DFloatingMessage(DFloatingMessage::MessageType::ResidentType,this);
    pDFloatingMessage->setMessage(QString(tr("The voice memo has been deleted")));
    //pDFloatingMessage->setMessage(QString(tr("该语音记事项已删除")));
    pDFloatingMessage->setIcon(QIcon(UiUtil::renderSVG(":/image/icon/normal/warning .svg", QSize(32,32),qApp)));
    DMessageManager::instance()->sendMessage(this,pDFloatingMessage);
}
//end

void MyMainWindow::closeEvent(QCloseEvent* event)
{
    m_mainPage->checkAndDeleteEmptyTextNoteFromDatabase();
    if(Intancer::get_Intancer()->getRecodingFlag())
    {
        event->ignore();
        m_exitDialog->show();
    }
    else
    {
        event->accept();
    }
    //DMainWindow::closeEvent(event);
}


