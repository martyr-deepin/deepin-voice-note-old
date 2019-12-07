#include "workercontroller.h"
#include "worker.h"

#include "uiutil.h"



Q_GLOBAL_STATIC(WorkerController, workerController)

WorkerController::WorkerController()
{
    //qDebug() << "WorkerController::WorkerController()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::WorkerController():"), QString("WorkerController::WorkerController():"));

    worker = new Worker();
    worker->moveToThread(&workerThread);

    connect(this, &WorkerController::toCreateMediaPlayer, worker, &Worker::createMediaPlayer);
    connect(worker, &Worker::mediaPlayerCreated, this, &WorkerController::onMediaPlayerCreated);

    connect(this, &WorkerController::toCreateAudioRecorder, worker, &Worker::createAudioRecorder);
    connect(worker, &Worker::audioRecorderCreated, this, &WorkerController::onAudioRecorderCreated);

    workerThread.start();
}

WorkerController::~WorkerController()
{
    //qDebug() << "WorkerController::~WorkerController()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::~WorkerController():"), QString("WorkerController::~WorkerController():"));
    this->workerThread.quit();
    this->workerThread.wait();
}

WorkerController* WorkerController::getInstance()
{
    //qDebug() << "WorkerController::instance()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::instance():"), QString("WorkerController::instance():"));
    return workerController();
}

void WorkerController::createMediaPlayer()
{
    //qDebug() << "WorkerController::createMediaPlayer()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::createMediaPlayer():"), QString("WorkerController::createMediaPlayer():"));
    if (this->mediaPlayer) {
        emit this->mediaPlayerCreated(this->mediaPlayer);

        return;
    }

    emit this->toCreateMediaPlayer();
}

void WorkerController::createAudioRecorder()
{
    //qDebug() << "WorkerController::createAudioRecorder()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::createAudioRecorder():"), QString("WorkerController::createAudioRecorder():"));
    if (this->audioRecorder) {
        emit this->audioRecorderCreated(this->audioRecorder);

        return;
    }

    emit this->toCreateAudioRecorder();
}

void WorkerController::onMediaPlayerCreated(QMediaPlayer* mediaPlayer)
{
    //qDebug() << "WorkerController::onMediaPlayerCreated()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::onMediaPlayerCreated():"), QString("WorkerController::onMediaPlayerCreated():"));
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
    //qDebug() << "WorkerController::onAudioRecorderCreated()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::onAudioRecorderCreated():"), QString("WorkerController::onAudioRecorderCreated():"));
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
    //qDebug() << "WorkerController::updateRecordAvailability()";
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("WorkerController::updateRecordAvailability():"), QString("WorkerController::updateRecordAvailability():"));
    bool isAvailable = false;

    if (this->mediaPlayer && this->audioRecorder) {
        isAvailable = true;
    }

    //qDebug() << "isAvailable: " << isAvailable;
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("isAvailable:"), QString::number(isAvailable));
    emit recordAvailability(isAvailable);
}
