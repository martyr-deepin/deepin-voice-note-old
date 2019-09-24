#include "voicenotebookapp.h"

#include <DApplication>
#include <DWidgetUtil>
#include <DLog>

#include <src/database/databaseoper.h>
#include <src/database/folderoper.h>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE


VoiceNotebookApp::VoiceNotebookApp(DApplication &a)
{
    m_app = &a;
    initApp();
}

VoiceNotebookApp::~VoiceNotebookApp()
{
//    if (NULL != mainWindow) {
//        delete mainWindow;
//        mainWindow = NULL;
//    }
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
    m_app->setOrganizationName("deepin");
    m_app->setApplicationName("voice note");
    m_app->setApplicationVersion(DApplication::buildVersion("20190925"));
    //installEventFilter(new GlobalEventFilter());
    //app.setApplicationVersion(DApplication::buildVersion("0816"));
    m_app->setProductIcon(QIcon(":/images/logo.svg"));
    m_app->setProductName("Voice note Application");
    m_app->setApplicationDescription("This is a dtk voice notebook application.");
    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();

    initMainWindow();
    //DatabaseOper *test = DatabaseOper::getInstance();
    //FolderOper *test1 = new FolderOper();
//    FOLDER folder1;
//    folder1.imgPath = "/mnt/hgfs/D/test/img/test.png";
//    folder1.folderName = "測試文件夾";
//    folder1.createTime = QDateTime::currentDateTime();
//    //test1->addFolder(folder1);
//    FolderOper::addFolder(folder1);

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

}

//int VoiceNotebookApp::exec()
//{
//    return 1;
//    //return a->exec();
//}
