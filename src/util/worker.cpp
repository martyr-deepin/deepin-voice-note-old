#include "worker.h"



Worker::Worker()
{
    qDebug() << "Worker::Worker()";
}

Worker::~Worker()
{
    qDebug() << "Worker::~Worker()";
}

void Worker::createMediaPlayer()
{
    qDebug() << "Worker::createMediaPlayer()";

    QMediaPlayer *mediaPlayer = new QMediaPlayer();

    emit this->mediaPlayerCreated(mediaPlayer);
}

void Worker::createAudioRecorder()
{
    qDebug() << "Worker::createAudioRecorder()";

    QAudioRecorder *audioRecorder = new QAudioRecorder();

    emit this->audioRecorderCreated(audioRecorder);
}

