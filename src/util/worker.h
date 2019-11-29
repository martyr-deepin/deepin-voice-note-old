#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioRecorder>
#include <QThread>



class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();
    ~Worker();

    void createMediaPlayer();
    void createAudioRecorder();

signals:
    void mediaPlayerCreated(QMediaPlayer *mediaplayer);
    void audioRecorderCreated(QAudioRecorder *audioRecorder);
};

#endif // WORKER_H
