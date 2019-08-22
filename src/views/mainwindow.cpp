#include "leftview.h"
#include "mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>

MyMainWindow::MyMainWindow()
{
    initUI();
    initConnection();
}

void MyMainWindow::initUI() {
    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    setWindowRadius(20);
    setMinimumSize(650, 420);
    initTitleBar();
    initCentralWidget();

}

void MyMainWindow::initConnection()
{
    //QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_mainPage, SIGNAL(textEditClicked(NOTE)), this, SLOT(showNoteDetail(NOTE)));
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

void MyMainWindow::initTitleBar(){

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
    m_textNoteEdit->setTextNote(note);
    m_stackedWidget->setCurrentIndex(1);
}


