#include <QThread>
#include "voicevolumewatcher.h"
#include "uiutil.h"

voiceVolumeWatcher::voiceVolumeWatcher(QObject *parent) : QThread(parent)
{
    m_loopwatch = true;
    //m_isRecoding = false;
    m_coulduse = false;
    m_failedCount = 0;
}

voiceVolumeWatcher::~voiceVolumeWatcher()
{

}

//停止log循环读取
void voiceVolumeWatcher::stopWatch()
{
    m_loopwatch = false;
}

//void voiceVolumeWatcher::setIsRecoding(bool value)
//{
//    m_isRecoding = value;
//}

void voiceVolumeWatcher::run()
{
    m_loopwatch = true;
    while(m_loopwatch)
    {
        QThread::currentThread()->msleep(200);
        //log缓存被更新并且仍进行loop循环
        //if(!m_isRecoding && m_loopwatch)
        //{
            bool couldUse = false;
            couldUse = UiUtil::canMicrophoneInput();
            //couldUse = true;
            if(!couldUse)
            {
                m_failedCount++;
            }
            else
            {
                m_failedCount = 0;
            }

            if(couldUse != m_coulduse)
            {
                if(!couldUse)//failded
                {
                    if(5 <= m_failedCount)//real failed
                    {
                        //发送log信息到UI
                        m_coulduse = couldUse;
                        emit sigRecodeState(couldUse);
                    }
                }
                else
                {
                    //发送log信息到UI
                    m_coulduse = couldUse;
                    emit sigRecodeState(couldUse);
                }
            }
        //}
    }
}

bool voiceVolumeWatcher::getCouldUse()
{
    return m_coulduse;
}
