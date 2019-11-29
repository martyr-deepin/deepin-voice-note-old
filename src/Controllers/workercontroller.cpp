#include "workercontroller.h"
#include "worker.h"



Q_GLOBAL_STATIC(WorkerController, workerController)

WorkerController::WorkerController()
{
    worker = new Worker();
    worker->moveToThread(&workerThread);

    connect(this, &WorkerController::toCreateMediaPlayer, worker, &Worker::createMediaPlayer);
    connect(worker, &Worker::mediaPlayerCreated, this, &WorkerController::onMediaPlayerCreated);

    workerThread.start();
}

WorkerController::~WorkerController()
{

}

WorkerController* WorkerController::getInstance()
{
    qDebug() << "WorkerController::instance()";

    return workerController();
}

void WorkerController::createMediaPlayer()
{
    qDebug() << "WorkerController::createMediaPlayer()";

    if (this->mediaPlayer) {
        emit this->mediaPlayerCreated(this->mediaPlayer);

        return;
    }

    emit this->toCreateMediaPlayer();
}

void WorkerController::onMediaPlayerCreated(QMediaPlayer* mediaPlayer)
{
    qDebug() << "WorkerController::onMediaPlayerCreated()";

    if (!this->mediaPlayer) {
        this->mediaPlayer = mediaPlayer;
    }
    else {
        mediaPlayer->deleteLater();
    }

    emit this->mediaPlayerCreated(this->mediaPlayer);
}
