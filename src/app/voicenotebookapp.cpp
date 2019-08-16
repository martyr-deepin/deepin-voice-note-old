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
    app = &a;
    initApp();
}

VoiceNotebookApp::~VoiceNotebookApp()
{
//    if (NULL != mainWindow) {
//        delete mainWindow;
//        mainWindow = NULL;
//    }
}

void VoiceNotebookApp::initApp()
{
    app->setAttribute(Qt::AA_UseHighDpiPixmaps);
    app->setTheme("light");
    app->setOrganizationName("deepin");
    app->setApplicationName("dtk application");
    app->setApplicationVersion("1.0");
    app->setProductIcon(QIcon(":/images/logo.svg"));
    app->setProductName("Dtk Application");
    app->setApplicationDescription("This is a dtk template application.");
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

    app->exec();



}

void VoiceNotebookApp::initMainWindow()
{
    mainWindow = new MyMainWindow();
    //mainWindow->setMinimumSize(500, 500);
    mainWindow->show();

    Dtk::Widget::moveToCenter(mainWindow);
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
