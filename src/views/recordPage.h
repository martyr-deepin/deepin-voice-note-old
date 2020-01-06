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

#ifndef RECORDPAGE_H
#define RECORDPAGE_H

#include <QAudioProbe>
#include <QAudioRecorder>
#include <QVBoxLayout>
#include <workercontroller.h>

//#include "dimagebutton.h"
#include <DImageButton>
//#include "expand_animation_button.h"
#include "recordingButton.h"
#include "waveform.h"
#include "myrecodebuttons.h"

#include <QDateTime>
#include <QTimer>
#include <DWidget>
#include "consts.h"
#include <DFloatingWidget>
#include <DFloatingButton>
#include <DBlurEffectWidget>

DWIDGET_USE_NAMESPACE

//录音按钮Page
class RecordPage : public DFloatingWidget
{
    Q_OBJECT
    
public:
    RecordPage(DWidget *parent = 0);
    void getAudioStates(QMultimedia::AvailabilityStatus &audioinputs);

    //QLabel *m_voiceTimeLabel;

    MyRecodeButtons *m_finishButton;
    //DFloatingButton *m_finishButton;
    //QVBoxLayout *layout;
    RecordingButton *m_recordingButton;
    
    QString generateRecordingFilename();
    QString getRecordingFilepath();
                                  
    
signals:
    void finishRecord(VOICE_INFO voiceInfo);
    void cancelRecord();
    void buttonClicled();
    
public slots:
    void exitRecord();
    void handleClickFinishButton();
//    void handleExpandAnimationFinish();
//    void handleShrankAnimationFinish();
    void pauseRecord();
    void renderLevel(const QAudioBuffer &buffer);
    void resumeRecord();
    void startRecord();
    void stopRecord();
    void changeTheme();
    void onAudioRecorderCreated(QAudioRecorder* audioRecorder);
    
private:
    //ExpandAnimationButton *expandAnimationButton;
    QHBoxLayout *m_hBoxLayout;
    QAudioProbe *audioProbe;
    QAudioRecorder *m_audioRecorder;
    QHBoxLayout *buttonLayout;
    QLabel *m_recordTimeLabel;
    //QLabel *titleLabel;
    QString recordPath;
    QVBoxLayout *expandAnimationButtonLayout;
    QVBoxLayout *shrankAnimationButtonLayout;
    QVBoxLayout *buttonAreaLayout;
    QWidget *buttonAreaWidget;
    QWidget *buttonWidget;
//    ShrankAnimationButton *shrankAnimationButton;
//    Waveform *waveform;
    //QWidget *m_voiceShape;
    VOICE_INFO voiceInfo;
    Waveform *m_waveform;
    QStringList m_audioInputs;
    QMultimedia::AvailabilityStatus m_audioStatus;

    WorkerController* workController;

    void initUI();
    void initConnection();
};

#endif
