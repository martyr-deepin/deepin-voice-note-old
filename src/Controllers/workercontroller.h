#ifndef WORKERCONTROLLER_H
#define WORKERCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QMediaPlayer>
#include <worker.h>


class WorkerController : public QObject
{
    Q_OBJECT
    QThread workerThread;

public:
    WorkerController();
    ~WorkerController();
    static WorkerController* getInstance();

    void createMediaPlayer();
    void createAudioRecorder();

public slots:
    void onMediaPlayerCreated(QMediaPlayer* mediaPlayer);
    void onAudioRecorderCreated(QAudioRecorder* audioRecorder);

signals:
    void toCreateMediaPlayer();
    void mediaPlayerCreated(QMediaPlayer* mediaPlayer);
    void toCreateAudioRecorder();
    void audioRecorderCreated(QAudioRecorder* audioRecorder);

private:
    Worker *worker = nullptr;

    QMediaPlayer *mediaPlayer = nullptr;
    QAudioRecorder *audioRecorder = nullptr;

    bool isMediaplayedCreated = false;
    bool isAudioRecorderCreated = false;
};

#endif // WORKERCONTROLLER_H
