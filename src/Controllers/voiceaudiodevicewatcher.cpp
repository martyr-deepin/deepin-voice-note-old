#include "voiceaudiodevicewatcher.h"

VoiceAudioDeviceWatcher::VoiceAudioDeviceWatcher(QObject *parent) : QObject(parent)
{
    m_audioDBus = nullptr;
    m_audioDBus = new com::deepin::daemon::Audio("com.deepin.daemon.Audio","/com/deepin/daemon/Audio",QDBusConnection::sessionBus(),this);

    QList<QDBusObjectPath> sourceslist = m_audioDBus->sources();
    QDBusObjectPath defaultSource = m_audioDBus->defaultSource();
    qDebug()<<"defaultSource:"<<defaultSource.path();

    com::deepin::daemon::audio::Source *pInterfaceDefault = new com::deepin::daemon::audio::Source (
                "com.deepin.daemon.Audio.Source",
                defaultSource.path(),
                QDBusConnection::sessionBus(),
                this );
    QString namedefault = pInterfaceDefault->activePort().name;

    for(int i = 0 ; i < sourceslist.count(); i++)
    {
        qDebug()<<"sources:"<<sourceslist.at(i).path();
        if(!sourceslist.at(i).path().isEmpty())
        {
            com::deepin::daemon::audio::Source *pInterface = new com::deepin::daemon::audio::Source (
                        "com.deepin.daemon.Audio",
                        sourceslist.at(i).path(),
                        QDBusConnection::sessionBus(),
                        this );
            if(nullptr != pInterface)
            {
                m_SourcesInterfaceList.append(pInterface);
                QString name = pInterface->activePort().name;
                qDebug()<<"name:"<<name;
                AudioPort AudioPort = pInterface->activePort();
                m_AudioPortList.append(AudioPort);
                connect(pInterface,SIGNAL(ActivePortChanged(AudioPort)),this,SLOT(OnActivePortChanged(AudioPort)));
            }
        }
    }
}

VoiceAudioDeviceWatcher::~VoiceAudioDeviceWatcher()
{

}

void VoiceAudioDeviceWatcher::OnActivePortChanged(AudioPort audioPort)
{
    // 0 for Unknown, 1 for Not Available, 2 for Available.
    uchar availability ;
    for(int i = 0; i < m_AudioPortList.count(); i++)
    {
        if(0 == m_AudioPortList.at(i).name.compare(audioPort.name))
        {
            m_AudioPortList.replace(i,audioPort);
        }
    }
}
