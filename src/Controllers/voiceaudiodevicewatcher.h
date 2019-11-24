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
    void OnCardsChanged(const QString & value);
    void OnDefaultSinkChanged(const QDBusObjectPath & value);
    void OnDefaultSourceChanged(const QDBusObjectPath & value);
    void OnMaxUIVolumeChanged(double  value);
    void OnSinkInputsChanged(const QList<QDBusObjectPath> &value);
    void OnSinksChanged(const QList<QDBusObjectPath> & value);
    void OnSourcesChanged(const QList<QDBusObjectPath> & value);

    void OnActivePortChanged(AudioPort  value);
    void OnBalanceChanged(double  value);
    void OnBaseVolumeChanged(double  value);
    void OnCardChanged(uint  value);
    void OnDescriptionChanged(const QString & value);
    void OnFadeChanged(double  value);
    void OnMuteChanged(bool  value);
    void OnNameChanged(const QString & value);
    void OnPortsChanged(AudioPortList  value);
    void OnSupportBalanceChanged(bool  value);
    void OnSupportFadeChanged(bool  value);
    void OnVolumeChanged(double value);

private:
    com::deepin::daemon::Audio *m_audioInterface;
    com::deepin::daemon::audio::Source *m_defaultSourceInterface;

};

#endif // VOICEAUDIODEVICEWATCHER_H
