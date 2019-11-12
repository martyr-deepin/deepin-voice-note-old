#ifndef VOICEAUDIODEVICEWATCHER_H
#define VOICEAUDIODEVICEWATCHER_H

#include <QObject>
#include <com_deepin_daemon_audio.h>
#include <com_deepin_daemon_audio_source.h>
class VoiceAudioDeviceWatcher : public QObject
{
    Q_OBJECT
public:
    explicit VoiceAudioDeviceWatcher(QObject *parent = nullptr);
    ~VoiceAudioDeviceWatcher();
//    QString createSession(QString ability);
//    void freeSession(QString ability);

signals:

public slots:
    void OnActivePortChanged(AudioPort audioPort);

private:
    com::deepin::daemon::Audio *m_audioDBus;
    QList<com::deepin::daemon::audio::Source *>m_SourcesInterfaceList;
    QList<AudioPort> m_AudioPortList;
    //0 for Unknown, 1 for Not Available, 2 for Available.
    //QString m_appId;
};

#endif // VOICEAUDIODEVICEWATCHER_H
