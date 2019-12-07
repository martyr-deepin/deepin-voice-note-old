#include "worker.h"

#include "uiutil.h"

Worker::Worker()
{
    //qDebug() << "Worker::Worker()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("Worker::Worker():"), QString("Worker::Worker():"));
}

Worker::~Worker()
{
    //qDebug() << "Worker::~Worker()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("Worker::~Worker():"), QString("Worker::~Worker():"));
}

void Worker::createMediaPlayer()
{
    //qDebug() << "Worker::createMediaPlayer()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("Worker::createMediaPlayer():"), QString("Worker::createMediaPlayer():"));

    QMediaPlayer *mediaPlayer = new QMediaPlayer();

    emit this->mediaPlayerCreated(mediaPlayer);
}

void Worker::createAudioRecorder()
{
    //qDebug() << "Worker::createAudioRecorder()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("Worker::createAudioRecorder():"), QString("Worker::createAudioRecorder():"));

    QAudioRecorder *audioRecorder = new QAudioRecorder();

    emit this->audioRecorderCreated(audioRecorder);
}

