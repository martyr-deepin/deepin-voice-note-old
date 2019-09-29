/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2018 Deepin, Inc.
 *               2011 ~ 2018 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QAudioEncoderSettings>
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QDate>
#include <QDebug>
#include <QWidget>
#include <QDir>
#include <QFont>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QStandardPaths>
#include <QTime>
#include <QUrl>
#include <QVBoxLayout>
#include <QApplication>
#include <DHiDPIHelper>
#include <uiutil.h>
//#include <QTimer>

#include "dimagebutton.h"
#include "recordPage.h"

//#include "utils.h"
//#include "waveform.h"

DWIDGET_USE_NAMESPACE

RecordPage::RecordPage(DWidget *parent) : DBlurEffectWidget(parent)
//RecordPage::RecordPage(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnection();
    installEventFilter(this);  // add event filter

    m_recordingTime = 0;

//    layout = new QVBoxLayout();
//    layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(layout);

//    titleLabel = new QLabel(tr("New recording"));
//    QFont titleFont;
//    titleFont.setPixelSize(26);
//    titleLabel->setFont(titleFont);
//    waveform = new Waveform(this);
//    QFont recordTimeFont;
//    recordTimeFont.setPixelSize(14);
//    recordTimeLabel = new QLabel("00:00");
//    recordTimeLabel->setFont(recordTimeFont);

//    buttonAreaWidget = new QWidget();
//    buttonAreaLayout = new QVBoxLayout();
//    buttonAreaLayout->setContentsMargins(0, 0, 0, 0);

//    buttonWidget = new QWidget();
//    buttonLayout = new QHBoxLayout(buttonWidget);
//    buttonLayout->setContentsMargins(0, 0, 0, 0);

//    expandAnimationButtonLayout = new QVBoxLayout();
//    expandAnimationButtonLayout->setContentsMargins(0, 0, 0, 0);

//    expandAnimationButton = new ExpandAnimationButton(this);
//    connect(expandAnimationButton, &ExpandAnimationButton::finish, this, &RecordPage::handleExpandAnimationFinish);

//    expandAnimationButtonLayout->addWidget(expandAnimationButton, 0, Qt::AlignHCenter);

//    shrankAnimationButtonLayout = new QVBoxLayout();
//    shrankAnimationButtonLayout->setContentsMargins(0, 0, 0, 0);

//    shrankAnimationButton = new ShrankAnimationButton();
//    connect(shrankAnimationButton, &ShrankAnimationButton::finish, this, &RecordPage::handleShrankAnimationFinish);

//    shrankAnimationButtonLayout->addWidget(shrankAnimationButton, 0, Qt::AlignHCenter);

//    recordingButton = new RecordingButton();

//    finishButton = new DImageButton(
//        Utils::getQrcPath("finish_normal.svg"),
//        Utils::getQrcPath("finish_hover.svg"),
//        Utils::getQrcPath("finish_press.svg")
//    );

    /*buttonLayout->addStretch();
    buttonLayout->addWidget(recordingButton, 0, Qt::AlignVCenter);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(finishButton, 0, Qt::AlignVCenter);
    buttonLayout->addStretch();

    buttonAreaLayout->addWidget(buttonWidget, 0, Qt::AlignHCenter);

    layout->addSpacing(36);
    layout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    layout->addStretch();
    layout->addWidget(waveform, 1, Qt::AlignHCenter);
    layout->addStretch();
    layout->addWidget(recordTimeLabel, 0, Qt::AlignHCenter);
    layout->addStretch();
    layout->addWidget(buttonAreaWidget);
    layout->addSpacing(30);   */  // NOTE: bottom buttons padding

    m_audioRecorder = new QAudioRecorder(this);
    qDebug() << "support codecs:" << m_audioRecorder->supportedAudioCodecs();
    qDebug() << "support containers:" << m_audioRecorder->supportedContainers();

    QAudioEncoderSettings audioSettings;
    audioSettings.setQuality(QMultimedia::HighQuality);

#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    m_audioRecorder->setAudioSettings(audioSettings);
    //m_audioRecorder->setContainerFormat("audio/x-wav");
    //m_audioRecorder->setContainerFormat("audio/x-amr-nb-sh");
    m_audioRecorder->setContainerFormat("audio/mpeg, mpegversion=(int)1");
    //m_audioRecorder->setContainerFormat("audio/mp3");
#else
    audioSettings.setCodec("audio/PCM");
    m_audioRecorder->setAudioSettings(audioSettings);
    m_audioRecorder->setContainerFormat("wav");
#endif

    audioProbe = new QAudioProbe(this);
    if (audioProbe->setSource(m_audioRecorder)) {
        connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(renderLevel(QAudioBuffer)));
    }

    m_tickerTimer = new QTimer(this);
    connect(m_tickerTimer, SIGNAL(timeout()), this, SLOT(renderRecordingTime()));


    //startRecord();

    connect(m_finishButton, SIGNAL(clicked()), this, SLOT(handleClickFinishButton()));
    connect(m_recordingButton, SIGNAL(pause()), this, SLOT(pauseRecord()));
    connect(m_recordingButton, SIGNAL(resume()), this, SLOT(resumeRecord()));

//    QFileInfoList fileInfoList = Utils::getRecordingFileinfos();
//    if (fileInfoList.count() == 0) {
//        buttonAreaWidget->setLayout(buttonAreaLayout);

//        // Get keyboard focus.
//        setFocus();
//    } else {
//        buttonAreaWidget->setLayout(expandAnimationButtonLayout);
//        expandAnimationButton->startAnimation();
//    }
}

void RecordPage::initUI()
{
    //this->setBackgroundRole();
    //this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(palette.Background,QColor(255, 255, 255));
    //palette.setColor(palette.Background, QColor(0, 0, 0));
    this->setPalette(palette);
    this->setBlurRectXRadius(8);
    this->setBlurRectYRadius(8);

    m_hBoxLayout = new QHBoxLayout(this);
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");

    m_recordingButton = new RecordingButton();

    m_finishButton = new DImageButton(
        ":/image/icon/normal/finish_normal.svg",
        ":/image/icon/hover/finish_hover.svg",
        ":/image/icon/press/finish_press.svg"
    );


    m_waveform = new Waveform();
    m_waveform->setFixedHeight(50);
    m_waveform->setWavePosition(-1);
    QSizePolicy spShape = m_waveform->sizePolicy();
    spShape.setHorizontalStretch(1);
    m_waveform->setSizePolicy(spShape);

//    m_voiceTimeLabel = new QLabel();
//    m_voiceTimeLabel->setFixedSize(46, 20);
//    m_voiceTimeLabel->setText(m_note.createTime.toString());

    QFont recordTimeFont;
    recordTimeFont.setPixelSize(14);
    m_recordTimeLabel = new QLabel("00:00");
    m_recordTimeLabel->setFont(recordTimeFont);

    m_hBoxLayout->addWidget(m_recordingButton);
    m_hBoxLayout->addWidget(m_waveform);
    m_hBoxLayout->addWidget(m_recordTimeLabel);
    m_hBoxLayout->addWidget(m_finishButton);
}
void RecordPage::initConnection()
{

}

//void RecordPage::handleExpandAnimationFinish()
//{
//    Utils::removeChildren(buttonAreaWidget);

//    buttonAreaWidget->setLayout(buttonAreaLayout);

//    // Get keyboard focus.
//    setFocus();
//}

//void RecordPage::handleShrankAnimationFinish()
//{
//    emit finishRecord(getRecordingFilepath());
//}

void RecordPage::handleClickFinishButton()
{
    stopRecord();


//    buttonAreaWidget->setLayout(shrankAnimationButtonLayout);
//    shrankAnimationButton->startAnimation();
}

void RecordPage::renderRecordingTime()
{
    if (m_audioRecorder->state() != QMediaRecorder::StoppedState) {
        QString time = UiUtil::formatMillisecond(m_recordingTime);
        //QString time1 = "00:01";
        m_recordTimeLabel->setText(time);
    }
}

void RecordPage::startRecord()
{
    QString fileName = generateRecordingFilename();
    recordPath = UiUtil::getRecordingVoiceFullPath(fileName);
    m_audioRecorder->setOutputLocation(recordPath);
    m_waveform->clearWave();
    m_recordingTime = 0;
    m_tickerTimer->start(1000);

    QDateTime currentTime = QDateTime::currentDateTime();
    lastUpdateTime = currentTime;
    voiceInfo.voicePath = fileName;
    m_audioRecorder->record();
}

void RecordPage::stopRecord()
{
    m_audioRecorder->stop();
    m_tickerTimer->stop();
    m_recordTimeLabel->setText("00:00");
    voiceInfo.voiceLength = m_recordingTime;
    voiceInfo.voiceSampleData = UiUtil::convertFloatListToString(m_waveform->getWholeSampleList());
    emit finishRecord(voiceInfo);
}

void RecordPage::exitRecord()
{
    stopRecord();

    QFile(getRecordingFilepath()).remove();

    emit cancelRecord();
}

void RecordPage::pauseRecord()
{
    m_audioRecorder->pause();
}

void RecordPage::resumeRecord()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    lastUpdateTime = currentTime;

    m_audioRecorder->record();
}

QString RecordPage::generateRecordingFilename()
{
    return QString("%1 (%2).mp3").arg(tr("New voice note")).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    //return QDir(UiUtil::getRecordingSaveDirectory()).filePath(QString("%1 (%2).wav").arg(tr("New recording")).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
    //return QDir(UiUtil::getRecordingSaveDirectory()).filePath(QString("%1 (%2).mp3").arg(tr("New recording")).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
}

QString RecordPage::getRecordingFilepath()
{
    return recordPath;
}

void RecordPage::renderLevel(const QAudioBuffer &buffer)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    m_recordingTime += lastUpdateTime.msecsTo(currentTime);
    lastUpdateTime = currentTime;

    QVector<qreal> levels = Waveform::getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i) {
        m_waveform->updateWave(levels.at(i));
    }
}

bool RecordPage::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent == QKeySequence::Cancel) {
            exitRecord();
        }
    }

    return false;
}
