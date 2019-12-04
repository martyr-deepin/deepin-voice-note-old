#ifndef VOICENOTEBOOKAPP_H
#define VOICENOTEBOOKAPP_H

#include <src/views/mainwindow.h>

#include <DApplication>
#include "myapplication.h"

DWIDGET_USE_NAMESPACE

class VoiceNotebookApp
{
public:
    //VoiceNotebookApp(DApplication &a);
    VoiceNotebookApp(MyApplication &a, MyMainWindow *mainWindow); //Edit createVoiceMemo 新建语音备忘录对应
    ~VoiceNotebookApp();
    MyMainWindow *getMainWindowObject();  //Add createVoiceMemo 新建语音备忘录对应
    //int exec();


private:
    MyMainWindow *m_mainWindow;
    //DApplication *m_app;
    MyApplication *m_app;
    void initApp();
    void initMainWindow();
    void initController();
    void initConnection();

};

#endif // VOICENOTEBOOKAPP_H
