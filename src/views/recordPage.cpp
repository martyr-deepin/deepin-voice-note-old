
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
#include <DApplicationHelper>
#include <QAudioDeviceInfo>

#include <uiutil.h>
//#include <QTimer>

#include "dimagebutton.h"
#include "recordPage.h"
#include "intancer.h"
//#include "utils.h"
//#include "waveform.h"

DWIDGET_USE_NAMESPACE

RecordPage::RecordPage(DWidget *parent) : DFloatingWidget(parent)
{
    this->workController = WorkerController::getInstance();
    m_audioRecorder = nullptr;
    initUI();
    initConnection();
    installEventFilter(this);  // add event filter
}

void RecordPage::getAudioStates(QMultimedia::AvailabilityStatus &audiostatus)
{
    audiostatus = m_audioStatus;
}

void RecordPage::initUI()
{
    //this->setBackgroundRole();
    //this->setAutoFillBackground(true);

//    this->setBlurRectXRadius(8);
//    this->setBlurRectYRadius(8);
//    this->setFixedHeight(64);

    m_hBoxLayout = new QHBoxLayout(this);
    m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_hBoxLayout->setObjectName("horizontalLayout");

    m_recordingButton = new RecordingButton();
    m_recordingButton->setFixedSize(QSize(60,60));


    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        m_finishButton = new MyRecodeButtons(
                    ":/image/icon/normal/finish_normal.svg",
                    ":/image/icon/press/finish_press.svg",
                    ":/image/icon/hover/finish_hover.svg",
                    "",
                    ":/image/icon/focus/finish_focus.svg",
                    QSize(60,60),
                    this);
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        m_finishButton = new MyRecodeButtons(
                    ":/image/icon_dark/normal/finish_normal_dark.svg",
                    ":/image/icon_dark/press/finish_press_dark.svg",
                    ":/image/icon_dark/hover/finish_hover_dark.svg",
                    "",
                    ":/image/icon_dark/focus/finish_focus_dark.svg",
                    QSize(60,60),
                    this);
    }
//    m_finishButton = new DFloatingButton(this);
//    m_finishButton->setFixedSize(QSize(45, 45));
//    m_finishButton->setIcon(QIcon(":/image/icon/normal/finish_normal.svg"));
//    m_finishButton->setIconSize(QSize(28,28));
//    DPalette pa = DApplicationHelper::instance()->palette(m_finishButton);
//    pa.setBrush(DPalette::Highlight, QColor(0x00FD5E5E));
//    m_finishButton->setPalette(pa);
//    m_finishButton = new DImageButton(
//        ":/image/icon/normal/finish_normal.svg",
//        ":/image/icon/hover/finish_hover.svg",
//        ":/image/icon/press/finish_press.svg"
//    );


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

    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &RecordPage::changeTheme);
}
void RecordPage::initConnection()
{
    connect(this->workController, &WorkerController::audioRecorderCreated, this, &RecordPage::onAudioRecorderCreated);
    this->workController->createAudioRecorder();
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
    m_recordingButton->handleResume();
    stopRecord();


//    buttonAreaWidget->setLayout(shrankAnimationButtonLayout);
//    shrankAnimationButton->startAnimation();
}

void RecordPage::startRecord()
{
    QString fileName = generateRecordingFilename();
    recordPath = UiUtil::getRecordingVoiceFullPath(fileName);

    //Patch for fixed record format ******BEGIN******
    //Todo:
    //    Find the mp3 codec and container if exist.
    {
        QStringList supportCodecList = m_audioRecorder->supportedAudioCodecs();
        QStringList supportContainer = m_audioRecorder->supportedContainers();

        QString codec;
        QString audioContainer;
        for (auto it : supportCodecList) {
            if (it.contains("audio/mpeg")) {
                codec = it;
                break;
            }
        }

        for (auto it: supportContainer) {
            if(it.contains("audio/mpeg")) {
                audioContainer = it;
                break;
            }
        }

        qDebug() << "startRecord: codec->" <<  codec << " container:" << audioContainer;

        QAudioEncoderSettings audioSettings;
        audioSettings.setCodec(codec);
        audioSettings.setQuality(QMultimedia::HighQuality);
        audioSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding);

        m_audioRecorder->setEncodingSettings(audioSettings, QVideoEncoderSettings(), audioContainer);
    }
    //Patch for fixed record format ******END  ******

    m_audioRecorder->setOutputLocation(recordPath);
    m_waveform->clearWave();
    //m_recordingTime = 0;
    m_recordTimeLabel->setText("00:00");
    //m_tickerTimer->start(200);

//    QDateTime currentTime = QDateTime::currentDateTime();
//    lastUpdateTime = currentTime;
    voiceInfo.voicePath = recordPath;
    voiceInfo.voiceLength = 0;
    m_audioRecorder->record();

    Intancer::get_Intancer()->setRecodingFlag(true);
}

void RecordPage::changeTheme()
{
    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        if(nullptr != m_finishButton)
        {
            m_finishButton->setPicChange(
                        ":/image/icon/normal/finish_normal.svg",
                        ":/image/icon/press/finish_press.svg",
                        ":/image/icon/hover/finish_hover.svg",
                        "",
                        ":/image/icon/focus/finish_focus.svg"
                        );
        }

    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        if(nullptr != m_finishButton)
        {
            m_finishButton->setPicChange(
                    ":/image/icon_dark/normal/finish_normal_dark.svg",
                    ":/image/icon_dark/press/finish_press_dark.svg",
                    ":/image/icon_dark/hover/finish_hover_dark.svg",
                    "",
                    ":/image/icon_dark/focus/finish_focus_dark.svg"
                    );
        }

    }
}

void RecordPage::onAudioRecorderCreated(QAudioRecorder* audioRecorder)
{
    //qDebug() << "RecordPage::onAudioRecorderCreated()";
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("RecordPage::onAudioRecorderCreated():"), QString("RecordPage::onAudioRecorderCreated():"));

    this->m_audioRecorder = audioRecorder;
    //qDebug() << "m_audioRecorder->supportedAudioCodecs(): " << m_audioRecorder->supportedAudioCodecs();
    //UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_audioRecorder->supportedAudioCodecs():"), qdPath.path());
    //qDebug() << "m_audioRecorder->supportedContainers(): " << m_audioRecorder->supportedContainers();
    //UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("m_audioRecorder->supportedContainers():"), qdPath.path());

    QAudioEncoderSettings audioSettings;
    audioSettings.setQuality(QMultimedia::HighQuality);

#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    m_audioRecorder->setAudioSettings(audioSettings);

//    m_audioRecorder->setContainerFormat("audio/x-wav");
//    m_audioRecorder->setContainerFormat("audio/x-amr-nb-sh");
//    m_audioRecorder->setContainerFormat("audio/mpeg, mpegversion=(int)1");
//    m_audioRecorder->setContainerFormat("audio/mp3");
#else
    audioSettings.setCodec("audio/PCM");
    m_audioRecorder->setAudioSettings(audioSettings);
    m_audioRecorder->setContainerFormat("wav");
#endif

    audioProbe = new QAudioProbe(this);
    if (audioProbe->setSource(m_audioRecorder)) {
        connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(renderLevel(QAudioBuffer)));
    }

    connect(m_finishButton, SIGNAL(clicked()), this, SLOT(handleClickFinishButton()));
    connect(m_recordingButton, SIGNAL(pause()), this, SLOT(pauseRecord()));
    connect(m_recordingButton, SIGNAL(resume()), this, SLOT(resumeRecord()));
    connect(m_finishButton, SIGNAL(clicked()), this, SIGNAL(buttonClicled()));
    connect(m_recordingButton, SIGNAL(pause()), this, SIGNAL(buttonClicled()));
    connect(m_recordingButton, SIGNAL(resume()), this, SIGNAL(buttonClicled()));
}

void RecordPage::stopRecord()
{
    m_audioRecorder->stop();
    voiceInfo.voiceSampleData = UiUtil::convertFloatListToString(m_waveform->getWholeSampleList());
    recordPath.clear();
    emit finishRecord(voiceInfo);
    Intancer::get_Intancer()->setRecodingFlag(false);
}

void RecordPage::exitRecord()
{
    if(nullptr == m_audioRecorder)
    {
        return;
    }

    m_recordingButton->onlyhandleResume();
    m_audioRecorder->stop();
    //start notify by yuanshuai 20191128 bug 3807
//    recordPath.clear();
//    QFile(getRecordingFilepath()).remove();
    QFile(getRecordingFilepath()).remove();
    recordPath.clear();
    //end
    emit cancelRecord();
    Intancer::get_Intancer()->setRecodingFlag(false);
}

void RecordPage::pauseRecord()
{
    m_audioRecorder->pause();
}

void RecordPage::resumeRecord()
{
    m_audioRecorder->record();
}

QString RecordPage::generateRecordingFilename()
{
    return QString("%1 (%2).mp3").arg("New voice note").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    //return QString("%1 (%2).mp3").arg(tr("New voice note")).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    //return QDir(UiUtil::getRecordingSaveDirectory()).filePath(QString("%1 (%2).wav").arg(tr("New recording")).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
    //return QDir(UiUtil::getRecordingSaveDirectory()).filePath(QString("%1 (%2).mp3").arg(tr("New recording")).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
}

QString RecordPage::getRecordingFilepath()
{
    return recordPath;
}

void RecordPage::renderLevel(const QAudioBuffer &buffer)
{
    voiceInfo.voiceLength = static_cast<int>(buffer.startTime() / 1000);
    QString strTime = UiUtil::formatMillisecond(voiceInfo.voiceLength);
    if(m_recordTimeLabel->text() != strTime)
    {
        m_recordTimeLabel->setText(strTime);
    }
    QVector<qreal> levels = Waveform::getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i) {
        m_waveform->updateWave(levels.at(i));
    }
    if(voiceInfo.voiceLength >= 3600000)
    {
        handleClickFinishButton();
    }
}
