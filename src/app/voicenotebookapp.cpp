#include "voicenotebookapp.h"
#include "intancer.h"
#include "theadmngintancer.h"
#include <DApplication>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DLog>

#include <src/database/databaseoper.h>
#include <src/database/folderoper.h>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE


VoiceNotebookApp::VoiceNotebookApp(MyApplication &a)
{
    m_app = &a;
    Intancer::get_Intancer()->setApp(m_app);
    initApp();
}

VoiceNotebookApp::~VoiceNotebookApp()
{
    if (nullptr != m_mainWindow) {
            delete m_mainWindow;
            m_mainWindow = nullptr;
        }
    Intancer::get_Intancer()->destroyIntance();
    //TheadMngIntancer::get_Intancer()->destroyIntance();
}

//initI18n();
//    setOrganizationName("deepin");
//    setApplicationName("deepin-image-viewer");
//    setApplicationDisplayName(tr("Deepin Image Viewer"));

////    setApplicationVersion(DApplication::buildVersion("1.3"));
//    setApplicationVersion(DApplication::buildVersion("20190828"));
//    installEventFilter(new GlobalEventFilter());


//    initChildren();

void VoiceNotebookApp::initApp()
{
    m_app->setAttribute(Qt::AA_UseHighDpiPixmaps);
    //m_app->setTheme("light");
    m_app->loadTranslator(QList<QLocale>() << QLocale::system());
    //m_app->loadTranslator();
    m_app->setOrganizationName("deepin");
    m_app->setApplicationName("deepin-voice-note");


    m_app->setApplicationVersion(DApplication::buildVersion("20191108"));
    //installEventFilter(new GlobalEventFilter());
    //app.setApplicationVersion(DApplication::buildVersion("0816"));
    //m_app->setProductIcon(QIcon(":/images/logo.svg"));
    QIcon icon = QIcon::fromTheme("deepin-voice-note");
    m_app->setProductIcon(icon);
    //m_app->setProductName("Voice note Application");


    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();

    //save theme
    DApplicationSettings saveTheme;
    initMainWindow();
    //DatabaseOper *test = DatabaseOper::getInstance();
    //FolderOper *test1 = new FolderOper();
//    FOLDER folder1;
//    folder1.imgPath = "/mnt/hgfs/D/test/img/test.png";
//    folder1.folderName = "測試文件夾";
//    folder1.createTime = QDateTime::currentDateTime();
//    //test1->addFolder(folder1);
//    FolderOper::addFolder(folder1);
    initConnection();
    m_app->exec();
}

void VoiceNotebookApp::initMainWindow()
{
    m_mainWindow = new MyMainWindow();
    //mainWindow->setMinimumSize(500, 500);
    m_mainWindow->show();

    Dtk::Widget::moveToCenter(m_mainWindow);
}
void VoiceNotebookApp::initController()
{

}
void VoiceNotebookApp::initConnection()
{
    QObject::connect(m_app, &MyApplication::sigShowRecordDialog, m_mainWindow, &MyMainWindow::onShowRecordDialog);
    QObject::connect(m_app, &MyApplication::sigShowVoiceToTextDialog, m_mainWindow, &MyMainWindow::onShowVoiceToTextDialog);
}

//int VoiceNotebookApp::exec()
//{
//    return 1;
//    //return a->exec();
//}
