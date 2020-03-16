#ifndef VOICEVOLUMEWATCHER_H
#define VOICEVOLUMEWATCHER_H

#include <QObject>
#include <QThread>

#define INPUT_DEVICE_CONF "/etc/deepin-voice-note/deepin-voice-note.conf"

class voiceVolumeWatcher : public QThread
{
    Q_OBJECT
public:
    explicit voiceVolumeWatcher(QObject *parent = nullptr);
    ~voiceVolumeWatcher();
    void stopWatch();
    //void setIsRecoding(bool value);
    void run();
    int getCouldUse();

signals:
    void sigRecodeState(int couldUse);


private:
    bool m_loopwatch;
    //bool m_isRecoding;
    int m_coulduse;
    int m_failedCount;
    bool m_bCheckInputDevice {true};

    bool checkInputDevice();
};


#endif // VOICEVOLUMEWATCHER_H
