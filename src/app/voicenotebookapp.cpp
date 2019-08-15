#include "voicenotebookapp.h"

#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE


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

    initMainWindow();

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
