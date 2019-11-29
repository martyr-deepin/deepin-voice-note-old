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

public slots:
    void onMediaPlayerCreated(QMediaPlayer* mediaPlayer);

signals:
    void toCreateMediaPlayer();
    void mediaPlayerCreated(QMediaPlayer* mediaPlayer);

private:
    Worker *worker = nullptr;

    QMediaPlayer* mediaPlayer;
};

#endif // WORKERCONTROLLER_H
