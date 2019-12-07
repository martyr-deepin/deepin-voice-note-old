#include "voiceaudiodevicewatcher.h"

#include "uiutil.h"

VoiceAudioDeviceWatcher::VoiceAudioDeviceWatcher(QObject *parent) : QObject(parent)
{

    m_audioInterface = new com::deepin::daemon::Audio(
                com::deepin::daemon::Audio::staticInterfaceName(),
                "/com/deepin/daemon/Audio",
                QDBusConnection::sessionBus(),
                this);

    connect(m_audioInterface,SIGNAL(SinkInputsChanged(const QList<QDBusObjectPath> &)),this,SLOT(OnSinkInputsChanged(const QList<QDBusObjectPath> &)));
    connect(m_audioInterface,SIGNAL(CardsChanged(const QString &)),this,SLOT(OnCardsChanged(const QString &)));
    connect(m_audioInterface,SIGNAL(DefaultSinkChanged(const QDBusObjectPath &)),this,SLOT(OnDefaultSinkChanged(const QDBusObjectPath &)));
    connect(m_audioInterface,SIGNAL(DefaultSourceChanged(const QDBusObjectPath &)),this,SLOT(OnDefaultSourceChanged(const QDBusObjectPath &)));
    connect(m_audioInterface,SIGNAL(MaxUIVolumeChanged(double)),this,SLOT(OnMaxUIVolumeChanged(double)));
    connect(m_audioInterface,SIGNAL(SinksChanged(const QList<QDBusObjectPath> &)),this,SLOT(OnSinksChanged(const QList<QDBusObjectPath> &)));
    connect(m_audioInterface,SIGNAL(SourcesChanged(const QList<QDBusObjectPath> &)),this,SLOT(OnSourcesChanged(const QList<QDBusObjectPath> &)));

    m_defaultSourceInterface = new com::deepin::daemon::audio::Source (
                com::deepin::daemon::audio::Source::staticInterfaceName(),
                //"com.deepin.daemon.Audio.Source",
                m_audioInterface->defaultSource().path(),
                QDBusConnection::sessionBus(),
                this );

    connect(m_defaultSourceInterface,SIGNAL(ActivePortChanged(AudioPort)),this,SLOT(OnActivePortChanged(AudioPort)));
    connect(m_defaultSourceInterface,SIGNAL(BalanceChanged(double)),this,SLOT(OnBalanceChanged(double)));
    connect(m_defaultSourceInterface,SIGNAL(aseVolumeChanged(double)),this,SLOT(OnaseVolumeChanged(double)));
    connect(m_defaultSourceInterface,SIGNAL(CardChanged(uint)),this,SLOT(OnCardChanged(uint)));
    connect(m_defaultSourceInterface,SIGNAL(DescriptionChanged(QString &)),this,SLOT(OnDescriptionChanged(QString &)));
    connect(m_defaultSourceInterface,SIGNAL(FadeChanged(double)),this,SLOT(OnFadeChanged(double)));
    connect(m_defaultSourceInterface,SIGNAL(MuteChanged(bool)),this,SLOT(OnMuteChanged(bool)));
    connect(m_defaultSourceInterface,SIGNAL(NameChanged(QString &)),this,SLOT(OnNameChanged(QString &)));
    connect(m_defaultSourceInterface,SIGNAL(PortsChanged(AudioPortList)),this,SLOT(OnPortsChanged(AudioPortList)));
    connect(m_defaultSourceInterface,SIGNAL(SupportBalanceChanged(bool)),this,SLOT(OnSupportBalanceChanged(bool)));
    connect(m_defaultSourceInterface,SIGNAL(SupportFadeChanged(bool)),this,SLOT(OnSupportFadeChanged(bool)));
    connect(m_defaultSourceInterface,SIGNAL(VolumeChanged(double)),this,SLOT(OnVolumeChanged(double)));







    QDBusObjectPath defaultSource = m_audioInterface->defaultSource();
    //qDebug()<<"defaultSource:"<<defaultSource.path();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("defaultSource:"), defaultSource.path());

    QList<QDBusObjectPath> sourceslist = m_audioInterface->sources();
    QString namedefault = m_defaultSourceInterface->activePort().name;
    //qDebug()<<"Volume:"<<m_defaultSourceInterface->volume();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("ObjectPath:"), QString::number(m_defaultSourceInterface->volume(),10,4));
//    for(int i = 0 ; i < sourceslist.count(); i++)
//    {
//        if(!sourceslist.at(i).path().isEmpty())
//        {
//            com::deepin::daemon::audio::Source *pInterface = new com::deepin::daemon::audio::Source (
//                        "com.deepin.daemon.Audio",
//                        sourceslist.at(i).path(),
//                        QDBusConnection::sessionBus(),
//                        this );
//            if(nullptr != pInterface)
//            {
//                m_SourcesInterfaceList.append(pInterface);
//                QString name = pInterface->activePort().name;
//                AudioPort AudioPort = pInterface->activePort();
//                m_AudioPortList.append(AudioPort);
//                connect(pInterface,SIGNAL(ActivePortChanged(AudioPort)),this,SLOT(OnActivePortChanged(AudioPort)));
//            }
//        }
//    }
}

VoiceAudioDeviceWatcher::~VoiceAudioDeviceWatcher()
{

}

void VoiceAudioDeviceWatcher::OnCardsChanged(const QString & value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnCardsChanged:"<<value;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnCardsChanged:"), value);
}

void VoiceAudioDeviceWatcher::OnDefaultSinkChanged(const QDBusObjectPath & value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnDefaultSinkChanged:"<<value.path();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnDefaultSinkChanged:"), value.path());
}

void VoiceAudioDeviceWatcher::OnDefaultSourceChanged(const QDBusObjectPath & value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnDefaultSourceChanged:"<<value.path();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnDefaultSourceChanged:"), value.path());
}

void VoiceAudioDeviceWatcher::OnMaxUIVolumeChanged(double  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnMaxUIVolumeChanged:"<<value;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnMaxUIVolumeChanged:"), QString::number(value,10,4));
}


void VoiceAudioDeviceWatcher::OnSinkInputsChanged(const QList<QDBusObjectPath> &value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnSinkInputsChanged:"<<value.count();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnSinkInputsChanged:"), QString::number(value.count(),10));
    for(int i = 0; i < value.count(); i++)
    {
        //qDebug()<<"row:"<<i<<"path:"<<value.at(i).path();
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("row:"), QString::number(i,10));
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("path:"), value.at(i).path());
    }
}

void VoiceAudioDeviceWatcher::OnSinksChanged(const QList<QDBusObjectPath> & value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnSinksChanged:"<<value.count();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnSinksChanged:"), QString::number(value.count(),10));
    for(int i = 0; i < value.count(); i++)
    {
        //qDebug()<<"row:"<<i<<"path:"<<value.at(i).path();
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("row:"), QString::number(i,10));
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("path:"), value.at(i).path());
    }
}

void VoiceAudioDeviceWatcher::OnSourcesChanged(const QList<QDBusObjectPath> & value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnSourcesChanged:"<<value.count();
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnSourcesChanged:"), QString::number(value.count(),10));
    for(int i = 0; i < value.count(); i++)
    {
        //qDebug()<<"row:"<<i<<"path:"<<value.at(i).path();
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("row:"), QString::number(i,10));
        UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("path:"), value.at(i).path());
    }
}

void VoiceAudioDeviceWatcher::OnActivePortChanged(AudioPort  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnActivePortChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnActivePortChanged:"), QString("VoiceAudioDeviceWatcher::OnActivePortChanged:"));
}

void VoiceAudioDeviceWatcher::OnBalanceChanged(double  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnBalanceChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnBalanceChanged:"), QString("VoiceAudioDeviceWatcher::OnBalanceChanged:"));
}

void VoiceAudioDeviceWatcher::OnBaseVolumeChanged(double  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnBaseVolumeChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnBaseVolumeChanged:"), QString("VoiceAudioDeviceWatcher::OnBaseVolumeChanged:"));
}

void VoiceAudioDeviceWatcher::OnCardChanged(uint  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnCardChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnCardChanged:"), QString("VoiceAudioDeviceWatcher::OnCardChanged:"));
}

void VoiceAudioDeviceWatcher::OnDescriptionChanged(const QString & value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnDescriptionChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnDescriptionChanged:"), QString("VoiceAudioDeviceWatcher::OnDescriptionChanged:"));
}
void VoiceAudioDeviceWatcher::OnFadeChanged(double  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnFadeChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnFadeChanged:"), QString("VoiceAudioDeviceWatcher::OnFadeChanged:"));
}

void VoiceAudioDeviceWatcher::OnMuteChanged(bool  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnMuteChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnMuteChanged:"), QString("VoiceAudioDeviceWatcher::OnMuteChanged:"));
}

void VoiceAudioDeviceWatcher::OnNameChanged(const QString & value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnNameChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnNameChanged:"), QString("VoiceAudioDeviceWatcher::OnNameChanged:"));
}

void VoiceAudioDeviceWatcher::OnPortsChanged(AudioPortList  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnPortsChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnPortsChanged:"), QString("VoiceAudioDeviceWatcher::OnPortsChanged:"));
}

void VoiceAudioDeviceWatcher::OnSupportBalanceChanged(bool  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnSupportBalanceChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnSupportBalanceChanged:"), QString("VoiceAudioDeviceWatcher::OnSupportBalanceChanged:"));
}

void VoiceAudioDeviceWatcher::OnSupportFadeChanged(bool  value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnSupportFadeChanged:";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnSupportFadeChanged:"), QString("VoiceAudioDeviceWatcher::OnSupportFadeChanged:"));
}

void VoiceAudioDeviceWatcher::OnVolumeChanged(double value)
{
    //qDebug()<<"VoiceAudioDeviceWatcher::OnVolumeChanged:"<<value;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("VoiceAudioDeviceWatcher::OnVolumeChanged:"), QString("VoiceAudioDeviceWatcher::OnVolumeChanged:"));
}

//void VoiceAudioDeviceWatcher::OnActivePortChanged(AudioPort audioPort)
//{
//    // 0 for Unknown, 1 for Not Available, 2 for Available.
//    uchar availability ;
//    for(int i = 0; i < m_AudioPortList.count(); i++)
//    {
//        if(0 == m_AudioPortList.at(i).name.compare(audioPort.name))
//        {
//            m_AudioPortList.replace(i,audioPort);
//        }
//    }
//}
