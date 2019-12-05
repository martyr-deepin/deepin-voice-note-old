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
//Add start bug 2587
#include <QShortcut>
#include <QJsonArray>
#include <QJsonDocument>
//Add end bug 2587
MyMainWindow::MyMainWindow()
{
    Intancer::get_Intancer()->setVoiceToTextFlag(false);
    //asrStateFlg = 0; //Add 20191111
    m_quit = false; //Add bug3470
    m_VoiceMemoAction = false; //Add createVoiceMemo 新建语音备忘录对应
    initUI();
    setTitlebarShadowEnabled(false);//liuyang 3799
}

void MyMainWindow::initUI() {

    resize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    //setWindowRadius(20);
    setMinimumSize(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
    m_SearchDialog = UiUtil::createChooseDialog(QString(""), QString(tr("Searching in the recording interrupts the recording. Do you want to continue?")), nullptr, QString(tr("No")), QString(tr("Yes")));
//    m_SearchDialog = UiUtil::createChooseDialog(QString(""), QString(tr("录音中进行搜索会中断录音，是否要继续？")), nullptr, QString(tr("否")), QString(tr("是")));
    m_exitDialog = UiUtil::createChooseDialog(QString(""), QString(tr("Currently recording, is the recording terminated?")), nullptr, QString(tr("Cancel")), QString(tr("Stop")));
    //m_exitDialog = UiUtil::createChooseDialog(QString(""), QString(tr("当前正在录⾳中，是否终⽌录⾳？")), nullptr, QString(tr("取消")), QString(tr("终止")));

    m_asrCloseConfirmDialog = UiUtil::createChooseDialog(QString(""), QString(tr("Converting a voice note now. Do you want to stop it?")), nullptr, QString(tr("Cancel")), QString(tr("Confirm")));  //Add 20191111
        //m_asrCloseConfirmDialog = UiUtil::createChooseDialog(QString(""), QString(tr("当前有语音笔记正在转写中，是否确定关闭？")), nullptr, QString(tr("取消")), QString(tr("确定")));   //Add 20191111
    initTitleBar();

    QTimer::singleShot(0, this, &MyMainWindow::initTheRest);
}


void MyMainWindow::initConnection()
{
    //QObject::connect(m_leftView, SIGNAL(selFolderIdChg(int)), m_rightView, SLOT(handleSelFolderChg(int)));
    QObject::connect(m_mainPage, SIGNAL(textEditClicked(NOTE)), this, SLOT(showNoteDetail(NOTE)));
    QObject::connect(m_mainPage, SIGNAL(clearSearch()), this, SLOT(clearSearchLine()));
    QObject::connect(m_mainPage, SIGNAL(sig_research()), this, SLOT(On_RetryToSearch()));
    QObject::connect(m_mainPage, SIGNAL(sigNoSearchResult()), this, SLOT(OnNoSearchResult()));

    connect(m_mainPage,SIGNAL(sigAllFolderDeleted()),this,SLOT(onAllFolderDeleted()));

    QObject::connect(m_returnBtn, SIGNAL(clicked()), this, SLOT(showListPage()));
    //connect(m_searchEdit, &DSearchEdit::returnPressed, this, &MyMainWindow::handleSearchKey);
    //connect(m_searchEdit, &DSearchEdit::returnPressed, this, &MyMainWindow::tryToSearch);
    connect(m_searchEdit, &DSearchEdit::textChanged, this, &MyMainWindow::tryToSearch);

    connect(m_searchEdit, &DSearchEdit::textChanged, Intancer::get_Intancer(), &Intancer::setSearchKeywords);

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
    QObject::connect(m_mainPage, SIGNAL(asrStart()), this, SLOT(asrStart()));    //Add 20191111
    QObject::connect(m_mainPage, SIGNAL(asrEnd()), this, SLOT(asrEnd()));   //Add 20191111
    connect(m_asrCloseConfirmDialog, &DDialog::buttonClicked, this, &MyMainWindow::asrDialogClicked); //Add 20191111

    connect(m_mainPage,SIGNAL(sigToDetalVoicePage(QString)),this,SLOT(OnToDetalVoicePage(QString)));
    connect(m_mainPage,SIGNAL(sigShowVoiceDeviceError()),this,SLOT(showNoVoiceDeviceDialog()));
    connect(m_mainPage, SIGNAL(sigRecordVoiceCouldUse()), this, SLOT(OnRecordVoiceCouldUse())); //Add createVoiceMemo 新建语音备忘录对应
}

void MyMainWindow::initTitleFrame()
{
    //chengjinwei 2019 11 29 bug3800    
     titlebar()->setIcon(QIcon::fromTheme("deepin-voice-note"));
//    QIcon icon = QIcon::fromTheme("deepin-voice-note");
//    m_logo = new QLabel(this);
//    m_logo->setObjectName("LogoButton");
//    m_logo->setFixedSize(QSize(32, 32));
//    m_logo->setPixmap(icon.pixmap(QSize(32, 32)));
//    m_logo->move(9,10);
    //chengjinwei 2019 11 29 bug3800


    //m_returnBtn = new DIconButton(this);
     m_returnBtn = new DIconButton(DStyle::SP_ArrowLeave,this);
    m_returnBtn->setFixedSize(QSize(36,36));

//    m_returnBtn->setIcon(QIcon(UiUtil::renderSVG(":/image/icon/normal/back_normal.svg", QSize(27,27),qApp)));
//    m_returnBtn->setIconSize(QSize(27,27));
    m_returnBtn->setVisible(false);

    //chengjinwei 2019 11 29 bug3800
    //m_returnBtn->move(m_logo->x() + m_logo->width() + 15,8);
    this->titlebar()->addWidget(m_returnBtn,Qt::AlignLeft);
    //chengjinwei 2019 11 29 bug3800

//    m_replaceForReturn = new DWidget;
//    m_replaceForReturn->setFixedSize(QSize(36, 36));
//    m_replaceForReturn->setVisible(true);

    m_searchEdit = new DSearchEdit();
    m_searchEdit->setFixedWidth(350);
//    QSizePolicy sp = m_searchEdit->sizePolicy();
//    sp.setHorizontalStretch(1);
//    m_searchEdit->setSizePolicy(sp);

//    m_titleFrame = new QFrame;
//    m_titleFrame->setObjectName("TitleBar");

//    QHBoxLayout *titleLayout = new QHBoxLayout;
//    titleLayout->addSpacing(230);   //liuyang 3793
//    titleLayout->addWidget(m_searchEdit);
//    titleLayout->addSpacing(34);
//    titleLayout->setContentsMargins(0, 0, 0, 0);

//    m_titleFrame->setLayout(titleLayout);
//    m_titleFrame->setFixedHeight(TITLE_FIXED_HEIGHT);
//    m_titleFrame->setFocusPolicy(Qt::ClickFocus);

    this->titlebar()->addWidget(m_searchEdit,Qt::AlignCenter);
    //this->titlebar()->setCustomWidget(m_titleFrame, false);

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

//Add start bug 2587
void MyMainWindow::initShortcutkeys()
{

    auto openkey = new QShortcut(QKeySequence(Qt::Key_Slash + Qt::CTRL + Qt::SHIFT), this);
    openkey->setContext(Qt::ApplicationShortcut);
    connect(openkey, &QShortcut::activated, this, &MyMainWindow::previewShortcut);

    auto openkey2 = new QShortcut(QKeySequence(Qt::Key_N + Qt::ControlModifier), this);
    openkey2->setContext(Qt::ApplicationShortcut);
    connect(openkey2, &QShortcut::activated, this, &MyMainWindow::newNoteShortcut);

    auto openkey3 = new QShortcut(QKeySequence(Qt::Key_F + Qt::ControlModifier), this);
    openkey3->setContext(Qt::ApplicationShortcut);
    connect(openkey3, &QShortcut::activated, this, &MyMainWindow::searchShortcut);

    auto openkey4 = new QShortcut(QKeySequence(Qt::Key_F2), this);
    openkey4->setContext(Qt::ApplicationShortcut);
    connect(openkey4, &QShortcut::activated, this, &MyMainWindow::reNameNoteShortcut);

    //Edit start 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)
//    auto openkey5 = new QShortcut(QKeySequence(Qt::Key_D + Qt::ControlModifier), this);
    auto openkey5 = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    //Edit end 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)
    openkey5->setContext(Qt::ApplicationShortcut);
    connect(openkey5, &QShortcut::activated, this, &MyMainWindow::deleteNoteShortcut);

    auto openkey6 = new QShortcut(QKeySequence(Qt::Key_Space), this);
    openkey6->setContext(Qt::ApplicationShortcut);
    connect(openkey6, &QShortcut::activated, this, &MyMainWindow::VoiceNotesPlayShortcut);
}

void MyMainWindow::initTheRest()
{
    initCentralWidget();

    initShortcutkeys(); //Add bug 2587

    initConnection();
}

//QJsonObject MyMainWindow::creatShorcutJson()
//{
//    //start notify by yuanshuai bug shortcut
//    QJsonObject shortcut1;
//    //shortcut1.insert("name", tr("帮助"));
//    shortcut1.insert("name", tr("Help"));
//    shortcut1.insert("value", "F1");

//    QJsonObject shortcut2;
//    //shortcut2.insert("name", tr("搜索"));
//    shortcut2.insert("name", tr("Search"));
//    shortcut2.insert("value", "Ctrl+F");

//    QJsonObject shortcut3;
//    //shortcut3.insert("name", tr("显示快捷键预览"));
//    shortcut3.insert("name", tr("Display shortcuts"));
//    shortcut3.insert("value", "Ctrl+Shift+?");

//    QJsonObject shortcut4;
//    //shortcut4.insert("name", tr("新建记事本"));
//    shortcut4.insert("name", tr("New notebook"));
//    shortcut4.insert("value", "Ctrl+N");

//    QJsonObject shortcut5;
////    shortcut5.insert("name", tr("删除记事本/删除记事项"));
//    shortcut5.insert("name", tr("Delete notebook/note"));
//    //Edit start 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)
////    shortcut5.insert("value", "Ctrl+D");
//    shortcut5.insert("value", "Delete");
//   //Edit start 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)

//    QJsonObject shortcut6;
////    shortcut6.insert("name", tr("重命名记事本"));
//    shortcut6.insert("name", tr("Rename notebook"));
//    shortcut6.insert("value", "F2");

//    QJsonObject shortcut7;
////    shortcut7.insert("name", tr("播放/暂停"));
//    shortcut7.insert("name", tr("Play/Pause"));
//    shortcut7.insert("value", "Space");

//    QJsonObject shortcut8;
////    shortcut8.insert("name", tr("全选"));
//    shortcut8.insert("name", tr("Select all"));
//    shortcut8.insert("value", "Ctrl+A");

//    QJsonObject shortcut9;
////    shortcut9.insert("name", tr("复制"));
//    shortcut9.insert("name", tr("Copy"));
//    shortcut9.insert("value", "Ctrl+C");

//    QJsonObject shortcut10;
////    shortcut10.insert("name", tr("剪切"));
//    shortcut10.insert("name", tr("Cut"));
//    shortcut10.insert("value", "Ctrl+X");

//    QJsonObject shortcut11;
////    shortcut11.insert("name", tr("粘贴"));
//    shortcut11.insert("name", tr("Paste"));
//    shortcut11.insert("value", "Ctrl+V");

//    QJsonObject shortcut12;
////    shortcut12.insert("name", tr("删除"));
//    shortcut12.insert("name", tr("Delete"));
//    shortcut12.insert("value", "Delete");

//    QJsonArray shortcutArray;
//    shortcutArray.append(shortcut1);
//    shortcutArray.append(shortcut2);
//    shortcutArray.append(shortcut3);
//    shortcutArray.append(shortcut4);
//    shortcutArray.append(shortcut5);
//    shortcutArray.append(shortcut6);
//    shortcutArray.append(shortcut7);
//    shortcutArray.append(shortcut8);
//    shortcutArray.append(shortcut9);
//    shortcutArray.append(shortcut10);
//    shortcutArray.append(shortcut11);
//    shortcutArray.append(shortcut12);

//    QJsonObject shortcut_group;
////    shortcut_group.insert("groupName", "快捷键");
//    shortcut_group.insert("groupName", tr("hot key"));
//    shortcut_group.insert("groupItems", shortcutArray);

//    QJsonArray shortcutArrayall;
//    shortcutArrayall.append(shortcut_group);

//    QJsonObject main_shortcut;
//    main_shortcut.insert("shortcut", shortcutArrayall);

//    return main_shortcut;
//}
QJsonObject MyMainWindow::creatShorcutJson()
{


    QJsonObject shortcut1;
    //shortcut3.insert("name", tr("帮助"));
    shortcut1.insert("name", tr("Help"));
    shortcut1.insert("value", "F1");

//    QJsonObject shortcut2;
//    //shortcut4.insert("name", tr("搜索"));
//    shortcut2.insert("name", tr("Search"));
//    shortcut2.insert("value", "Ctrl+F");

    QJsonObject shortcut3;
    //shortcut5.insert("name", tr("显示快捷键预览"));
    shortcut3.insert("name", tr("Display shortcuts"));
    shortcut3.insert("value", "Ctrl+Shift+?");

    QJsonObject shortcut4;
    //shortcut6.insert("name", tr("新建记事本"));
    shortcut4.insert("name", tr("New notebook"));
    shortcut4.insert("value", "Ctrl+N");

    QJsonObject shortcut5;
//    shortcut7.insert("name", tr("删除记事本/删除记事项"));
    shortcut5.insert("name", tr("Delete notebook/note"));
    //Edit start 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)
//    shortcut7.insert("value", "Ctrl+D");
    shortcut5.insert("value", "Delete");
   //Edit start 2587再对应 (文本编辑时，删除键快捷无效.另外【CTRL+D】=>【DEL】)

    QJsonObject shortcut6;
//    shortcut8.insert("name", tr("重命名记事本"));
    shortcut6.insert("name", tr("Rename notebook"));
    shortcut6.insert("value", "F2");

    QJsonObject shortcut7;
//    shortcut9.insert("name", tr("播放/暂停"));
    shortcut7.insert("name", tr("Play/Pause"));
    shortcut7.insert("value", "Space");

        QJsonObject shortcut8;
    //    shortcut8.insert("name", tr("全选"));
        shortcut8.insert("name", tr("Select all"));
        shortcut8.insert("value", "Ctrl+A");

        QJsonObject shortcut9;
    //    shortcut9.insert("name", tr("复制"));
        shortcut9.insert("name", tr("Copy"));
        shortcut9.insert("value", "Ctrl+C");

        QJsonObject shortcut10;
    //    shortcut10.insert("name", tr("剪切"));
        shortcut10.insert("name", tr("Cut"));
        shortcut10.insert("value", "Ctrl+X");

        QJsonObject shortcut11;
    //    shortcut11.insert("name", tr("粘贴"));
        shortcut11.insert("name", tr("Paste"));
        shortcut11.insert("value", "Ctrl+V");

        QJsonObject shortcut12;
    //    shortcut12.insert("name", tr("删除"));
        shortcut12.insert("name", tr("TextDelete"));
        shortcut12.insert("value", "Delete");

    QJsonArray shortcutArray1;
    shortcutArray1.append(shortcut4);
    shortcutArray1.append(shortcut5);
    shortcutArray1.append(shortcut6);

    QJsonArray shortcutArray2;
    shortcutArray2.append(shortcut7);
    shortcutArray2.append(shortcut8);
    shortcutArray2.append(shortcut9);
    shortcutArray2.append(shortcut10);
    shortcutArray2.append(shortcut11);
    shortcutArray2.append(shortcut12);

    QJsonArray shortcutArray3;
    shortcutArray3.append(shortcut1);
    //shortcutArray.append(shortcut2);
    shortcutArray3.append(shortcut3);




//    QJsonObject shortcut_group;
////    shortcut_group.insert("groupName", "快捷键");
//    shortcut_group.insert("groupName", tr("hot key"));
//    shortcut_group.insert("groupItems", shortcutArray);

    QJsonObject shortcut_group1;
//    shortcut_group1.insert("groupName", "记事本");
    shortcut_group1.insert("groupName", tr("Notebooks"));
    shortcut_group1.insert("groupItems", shortcutArray1);

    QJsonObject shortcut_group2;
//    shortcut_group.insert("groupName", "记事项");
    shortcut_group2.insert("groupName", tr("Notes"));
    shortcut_group2.insert("groupItems", shortcutArray2);

    QJsonObject shortcut_group3;
//    shortcut_group.insert("groupName", "设置");
    shortcut_group3.insert("groupName", tr("Settings"));
    shortcut_group3.insert("groupItems", shortcutArray3);

    QJsonArray shortcutArrayall;
    shortcutArrayall.append(shortcut_group1);
    shortcutArrayall.append(shortcut_group2);
    shortcutArrayall.append(shortcut_group3);

    QJsonObject main_shortcut;
    main_shortcut.insert("shortcut", shortcutArrayall);

    return main_shortcut;
}

//Add end bug 2587

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

    m_VoiceToNotePage = new VoiceToNotePage(this);
    m_stackedWidget->addWidget(m_VoiceToNotePage);
}

void MyMainWindow::showNoteDetail(NOTE note)
{
    //start add by yuanshuai 20191204 bug 4121
    m_bakForSearchStr = m_searchEdit->text();
    //end

    m_textNoteEdit->setTextNote(note, m_searchEdit->text());
    m_detailPage->setFocus();
    //m_textNoteEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

    m_DetalTextBak = m_textNoteEdit->getText();
    m_stackedWidget->setCurrentIndex(1);
    m_returnBtn->setVisible(true);
    //m_replaceForReturn->setVisible(false);
    //start add by yuanshuai 20191128 bug 3731
    Intancer::get_Intancer()->setEndRecordFlag(false);
    //end
}

void MyMainWindow::showListPage()
{

    //start notify by yuanshuai 20191128 bug 3731
    //if(!m_searchEdit->text().isEmpty())
    if((!m_searchEdit->text().isEmpty())&&(Intancer::get_Intancer()->getEndRecordFlag()))
    {
        bool hasNoFolder = false;
        m_mainPage->searchFolder(m_searchEdit->text(),hasNoFolder);
//        if(ret)
//        {
//            m_stackedWidget->setCurrentIndex(0);
//        }
    }
    //end
    m_mainPage->updateFromDetal(m_textNoteEdit->getID());
    m_stackedWidget->setCurrentIndex(0);
    m_searchEdit->setEnabled(true); //Add  bug3136
    m_mainPage->setFocus();
    m_returnBtn->setVisible(false);
    //m_replaceForReturn->setVisible(true);

    //start add by yuanshuai 20191204 bug 4121
    int ret = QString::compare(m_bakForSearchStr, m_searchEdit->text());
    if(ret != 0)
    {
        handleSearchKey();
    }
    //end

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
        //start add by yuanshuai 20191203 bug 4114 bug 4121 bug 4130
        if(!(1 == m_stackedWidget->currentIndex() || 4 == m_stackedWidget->currentIndex()))
        {
            m_stackedWidget->setCurrentIndex(0);
        }
        //end
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
    }
    else
    {
        m_textNoteEdit->searchText(searchKey);
    }


}
void MyMainWindow::On_RetryToSearch()
{
    tryToSearch(Intancer::get_Intancer()->getSearchKeywords());
}

void MyMainWindow::tryToSearch(QString search)
{
    //qDebug()<<"search:"<<search;

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

void MyMainWindow::handleSearchDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        //start add by yuanshuai 20191128 bug 3731
        Intancer::get_Intancer()->setEndRecordFlag(true);
        //end
        handleSearchKey();
    }
    else
    {
        //start add by yuanshuai 20191128 bug 3731
        Intancer::get_Intancer()->setEndRecordFlag(false);
        //end
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
    //m_stackedWidget->setCurrentIndex(0);
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
void MyMainWindow::showNoVoiceDeviceDialog()
{
    DFloatingMessage *pDFloatingMessage = new DFloatingMessage(DFloatingMessage::MessageType::ResidentType,this);
    pDFloatingMessage->setMessage(QString(tr("Your audio recording device does not work.")));
    //pDFloatingMessage->setMessage(QString(tr("您的录音设备异常，无法录制语音。")));
    pDFloatingMessage->setIcon(QIcon(UiUtil::renderSVG(":/image/icon/normal/warning .svg", QSize(32,32),qApp)));
    DMessageManager::instance()->sendMessage(this,pDFloatingMessage);
}
//Add start bug 2587
void MyMainWindow::previewShortcut()
{
    QRect rect = window()->geometry();
    QPoint pos(rect.x() + rect.width()/2, rect.y() + rect.height()/2);
    QStringList shortcutString;
    QJsonObject json = creatShorcutJson();

    QString param1 = "-j=" + QString(QJsonDocument(json).toJson());
    QString param2 = "-p=" + QString::number(pos.x()) + "," + QString::number(pos.y());
    shortcutString << param1 << param2;

    QProcess* shortcutViewProcess = new QProcess();
    shortcutViewProcess->startDetached("deepin-shortcut-viewer", shortcutString);

    connect(shortcutViewProcess, SIGNAL(finished(int)),
    shortcutViewProcess, SLOT(deleteLater()));
}
void MyMainWindow::newNoteShortcut()
{
    //start add by yuanshuai 20191128 bug 3855
    if(!Intancer::get_Intancer()->getRecodingFlag())
    {
        //2587
        if(2 == m_stackedWidget->currentIndex())
        {
            m_InitEmptyPage->sigAddFolderByInitPage();
        }
        else
        {
            m_mainPage->addFolder();
        }
        //2587
    }
}
void MyMainWindow::searchShortcut()
{
    m_searchEdit->lineEdit()->setFocus();
}
void MyMainWindow::reNameNoteShortcut()
{
    m_mainPage->reNameFolder();
}
void MyMainWindow::deleteNoteShortcut()
{
    if (m_mainPage->shortcutsDeleteByRightlist())
    {
        return;
    }
    m_mainPage->deleteFolder();
}
void MyMainWindow::VoiceNotesPlayShortcut()
{
    m_mainPage->VoicePlayOrPause();
}
//Add end bug 2587
//Add s 20191111
void MyMainWindow::asrStart()
{
    //start add by yuanshuai 20191128 bug 3859
    m_searchEdit->setEnabled(false);
    //end
    Intancer::get_Intancer()->setVoiceToTextFlag(true);
    //asrStateFlg = 1;
}
void MyMainWindow::asrEnd()
{
    //start add by yuanshuai 20191128 bug 3859
    m_searchEdit->setEnabled(true);
    //end
    Intancer::get_Intancer()->setVoiceToTextFlag(false);
    //asrStateFlg = 0;
}
void MyMainWindow::asrDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
//        m_mainPage->checkAndDeleteEmptyTextNoteFromDatabase();
//        DMainWindow::closeEvent(m_eventSave);
        qApp->quit();
    }
}
//Add e 20191111

void MyMainWindow::OnToDetalVoicePage(QString contant)
{
    m_VoiceToNotePage->ToDetalVoicePage(contant);
    m_stackedWidget->setCurrentIndex(VOICE_PAGE);
    m_returnBtn->setVisible(true);
}

void MyMainWindow::onShowRecordDialog()
{
    if(nullptr != m_exitDialog)
    {
        m_exitDialog->show();
    }
}

void MyMainWindow::onShowVoiceToTextDialog()
{
    if(nullptr != m_asrCloseConfirmDialog)
    {
        m_asrCloseConfirmDialog->show();
    }
}

void MyMainWindow::closeEvent(QCloseEvent* event)
{
    m_mainPage->checkAndDeleteEmptyTextNoteFromDatabase();
    //Add s 20191111
    if(Intancer::get_Intancer()->getVoiceToTextFlag())
    //if (asrStateFlg)
    {
         m_eventSave = event;
         event->ignore();
         m_asrCloseConfirmDialog->show();
         return;
    }
    else
    {
        if(Intancer::get_Intancer()->getRecodingFlag())
        {
            event->ignore();
            m_exitDialog->show();
            return;
        }
        else
        {
            event->accept();
        }
    }
    //Add e 20191111

    //DMainWindow::closeEvent(event);
}

//Add start createVoiceMemo 新建语音备忘录对应
void MyMainWindow::CreateVoiceMemo()
{
    m_VoiceMemoAction = true;
    if (Intancer::get_Intancer()->getRecodingFlag() == false)
    {
        if(0 >= m_mainPage->getFolderCount())
        {
            onAddFolderByInitPage();
        }

        if (m_mainPage->isAddVoiceBtnEnabled())
        {
            this->setDisabled(false);
            m_mainPage->startRecording();
            m_VoiceMemoAction =false;
        }
        else
        {
            this->setDisabled(true);
        }
    }

}
void MyMainWindow::OnRecordVoiceCouldUse()
{
    if (m_VoiceMemoAction)
    {
        this->setDisabled(false);
        m_mainPage->startRecording();
        m_VoiceMemoAction = false;
    }

}
//Add end createVoiceMemo 新建语音备忘录对应
