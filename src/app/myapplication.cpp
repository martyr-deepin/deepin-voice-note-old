#include "myapplication.h"
#include <QDebug>

#include "uiutil.h"

MyApplication::MyApplication(int &argc, char **argv) : DApplication(argc,  argv)
{

}

void MyApplication::handleQuitAction()
{
    //qDebug()<<"handleQuitAction";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("handleQuitAction:"), QString("handleQuitAction:"));

    if(Intancer::get_Intancer()->getVoiceToTextFlag())
    {
        emit sigShowVoiceToTextDialog();
    }
    else
    {
        if(Intancer::get_Intancer()->getRecodingFlag())
        {
            emit sigShowRecordDialog();
        }
        else
        {
            DApplication::handleQuitAction();
        }
    }
}
