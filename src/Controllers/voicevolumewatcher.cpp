#include <QThread>
#include "voicevolumewatcher.h"
#include "uiutil.h"

voiceVolumeWatcher::voiceVolumeWatcher(QObject *parent) : QThread(parent)
{
    m_loopwatch = true;
    //m_isRecoding = false;
    m_coulduse = 0;
    m_failedCount = 0;

    m_bCheckInputDevice = checkInputDevice();
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
            int couldUse = 0;
            //返回0：录音设备异常，返回1：录音设备正常，返回2：系统输入音量低于20%
            couldUse = UiUtil::canMicrophoneInput(m_bCheckInputDevice);
            //couldUse = true;
            if(couldUse == 0)
            {
                m_failedCount++;
            }
            else
            {
                m_failedCount = 0;
            }

            if(couldUse != m_coulduse)
            {
                if(couldUse == 0)//failded
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

int voiceVolumeWatcher::getCouldUse()
{
    return m_coulduse;
}

bool voiceVolumeWatcher::checkInputDevice()
{
    QFile file(INPUT_DEVICE_CONF);
    if (file.exists() == false) {
        return true;
    }

    QSettings settings(INPUT_DEVICE_CONF, QSettings::IniFormat);
    QString strCheInputDecValue;
    strCheInputDecValue = settings.value("Audio/CheckInputDevice").toString();
    if (strCheInputDecValue == "true") {
        m_bCheckInputDevice = true;
    } else {
        m_bCheckInputDevice = false;
    }

    return m_bCheckInputDevice;
}
