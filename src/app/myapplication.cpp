#include "myapplication.h"
#include <QDebug>
MyApplication::MyApplication(int &argc, char **argv) : DApplication(argc,  argv)
{

}

void MyApplication::handleQuitAction()
{
    qDebug()<<"handleQuitAction";

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
