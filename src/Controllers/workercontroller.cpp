#include "workercontroller.h"
#include "worker.h"

#include "uiutil.h"



Q_GLOBAL_STATIC(WorkerController, workerController)

WorkerController::WorkerController()
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::WorkerController()"));

//    worker = new Worker();
//    worker->moveToThread(&workerThread);

//    connect(this, &WorkerController::toCreateMediaPlayer, worker, &Worker::createMediaPlayer);
//    connect(worker, &Worker::mediaPlayerCreated, this, &WorkerController::onMediaPlayerCreated);

//    connect(this, &WorkerController::toCreateAudioRecorder, worker, &Worker::createAudioRecorder);
//    connect(worker, &Worker::audioRecorderCreated, this, &WorkerController::onAudioRecorderCreated);

//    workerThread.start();

    QMediaPlayer *mediaPlayer = new QMediaPlayer(this);
    QAudioRecorder *audioRecorder = new QAudioRecorder(this);

    onMediaPlayerCreated(mediaPlayer);
    onAudioRecorderCreated(audioRecorder);
}

WorkerController::~WorkerController()
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::~WorkerController()"));
    this->workerThread.quit();
    this->workerThread.wait();
}

WorkerController* WorkerController::getInstance()
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::instance()"));
    return workerController();
}

void WorkerController::createMediaPlayer()
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::createMediaPlayer()"));
    if (this->mediaPlayer) {
        emit this->mediaPlayerCreated(this->mediaPlayer);

        return;
    }

    emit this->toCreateMediaPlayer();
}

void WorkerController::createAudioRecorder()
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::createAudioRecorder()"));
    if (this->audioRecorder) {
        emit this->audioRecorderCreated(this->audioRecorder);

        return;
    }

    emit this->toCreateAudioRecorder();
}

void WorkerController::onMediaPlayerCreated(QMediaPlayer* mediaPlayer)
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::onMediaPlayerCreated()"));
    if (!this->mediaPlayer) {
        this->mediaPlayer = mediaPlayer;
    }
    else {
        mediaPlayer->deleteLater();
    }

    emit this->mediaPlayerCreated(this->mediaPlayer);
    this->updateRecordAvailability();
}

void WorkerController::onAudioRecorderCreated(QAudioRecorder* audioRecorder)
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::onAudioRecorderCreated()"));
    if (!this->audioRecorder) {
        this->audioRecorder = audioRecorder;
    }
    else {
        audioRecorder->deleteLater();
    }

    emit this->audioRecorderCreated(this->audioRecorder);
    this->updateRecordAvailability();
}

void WorkerController::updateRecordAvailability()
{
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::updateRecordAvailability()"));
    bool isAvailable = false;

    if (this->mediaPlayer && this->audioRecorder) {
        isAvailable = true;
    }

    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("isAvailable:"), QString::number(isAvailable));
    emit recordAvailability(isAvailable);
}
