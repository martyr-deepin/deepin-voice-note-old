#include "leftview.h"
#include "mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>
#include <DTitlebar>
#include <uiutil.h>


MyMainWindow::MyMainWindow()
{
    initUI();
    initConnection();
}

void MyMainWindow::initUI() {
    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    //setWindowRadius(20);
    setMinimumSize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    initTitleBar();
    initCentralWidget();

}


void MyMainWindow::initConnection()
{
    //QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_mainPage, SIGNAL(textEditClicked(NOTE)), this, SLOT(showNoteDetail(NOTE)));
    QObject::connect(m_returnBtn, SIGNAL(clicked()), this, SLOT(showListPage()));
    connect(m_searchEdit, &DSearchEdit::returnPressed, this, &MyMainWindow::handleSearchKey);

//    QObject::connect(m_returnBtn, &DImageButton::clicked, this, &MyMainWindow::showListPage);

}

void MyMainWindow::initTitleFrame()
{
    m_logo = new QLabel();
    m_logo->setObjectName("LogoButton");
    m_logo->setFixedSize(QSize(32, 32));
    m_logo->setPixmap(UiUtil::getPixmap(m_logo->size(), ":/image/voice_note_logo.svg"));

    m_returnBtn = new DImageButton();
    m_returnBtn->setFixedSize(QSize(24, 24));
    m_returnBtn->setNormalPic(":/image/icon/normal/back_normal.svg");
    //m_returnBtn->setHoverPic(":/image/add_hover.svg");
    m_returnBtn->setPressPic(":/image/icon/press/back_press.svg");
//    QString returnIcon = "";
//    QString text = "<";
//    m_returnBtn = new DIconButton(returnIcon, text);
    m_returnBtn->setVisible(false);

    m_searchEdit = new DSearchEdit();
    QSizePolicy sp = m_searchEdit->sizePolicy();
    sp.setHorizontalStretch(1);
    m_searchEdit->setSizePolicy(sp);

    m_titleFrame = new QFrame;
    m_titleFrame->setObjectName("TitleBar");
    //m_titleFrame->setStyleSheet("background: blue");
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setMargin(0);
    titleLayout->setSpacing(0);
    titleLayout->addSpacing(12);
    titleLayout->addWidget(m_logo);
    titleLayout->addSpacing(12);
    titleLayout->addWidget(m_returnBtn);
    titleLayout->addSpacing(12);
    titleLayout->addWidget(m_searchEdit);
    titleLayout->setSpacing(0);
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
    //m_stackedWidget->setStyleSheet("background: blue");
    //m_stackedWidget->setGeometry(QRect(10, 10, this->width(), this->height()));
    m_stackedWidget->setObjectName("stackedWidget");

    m_mainPage = new MainPage();
    m_stackedWidget->addWidget(m_mainPage);
    m_stackedWidget->setCurrentIndex(0);


    m_detailPage = new QWidget();
    m_detailPageLayout = new QVBoxLayout();
    m_detailPage->setLayout(m_detailPageLayout);
    m_textNoteEdit = new TextNoteEdit();
    m_detailPageLayout->addWidget(m_textNoteEdit);
    m_stackedWidget->addWidget(m_detailPage);

//    m_plainTextEdit = new QPlainTextEdit(m_detailPage);
//    //    self.detailPage = QtWidgets.QWidget()
//    //    self.detailPage.setObjectName("detailPage")
//    //    self.plainTextEdit = QtWidgets.QPlainTextEdit(self.detailPage)
//    //    self.plainTextEdit.setGeometry(QtCore.QRect(10, 40, 1071, 821))
//    //    self.plainTextEdit.setObjectName("plainTextEdit")
//    m_stackedWidget->addWidget(m_detailPage);
}

void MyMainWindow::showNoteDetail(NOTE note)
{
    m_textNoteEdit->setTextNote(note, m_searchEdit->text());
    m_stackedWidget->setCurrentIndex(1);
    m_returnBtn->setVisible(true);
}

void MyMainWindow::showListPage()
{
    if (m_searchEdit->text().isEmpty())
    {
        m_mainPage->updateNoteList();
    }
    else
    {
        m_mainPage->searchFolder(m_searchEdit->text());
    }
    m_stackedWidget->setCurrentIndex(0);
    m_returnBtn->setVisible(false);
}

void MyMainWindow::handleSearchKey()
{
    QString searchKey = m_searchEdit->text();
    if (0 == m_stackedWidget->currentIndex())
    {
        m_mainPage->searchFolder(searchKey);
    }
    else
    {
        m_textNoteEdit->searchText(searchKey);
    }
}




