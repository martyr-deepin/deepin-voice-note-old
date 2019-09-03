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

//#include "dimagebutton.h"
#include <DImageButton>
//#include "expand_animation_button.h"
#include "recordingButton.h"
#include "waveform.h"
//#include "shrank_animation_button.h"
//#include "waveform.h"
#include <QDateTime>
#include <QTimer>
#include "consts.h"

DWIDGET_USE_NAMESPACE

class RecordPage : public QWidget
{
    Q_OBJECT
    
public:
    RecordPage(QWidget *parent = 0);


    //QLabel *m_voiceTimeLabel;

    
    DImageButton *m_finishButton;
    //QVBoxLayout *layout;
    RecordingButton *m_recordingButton;
    
    QString generateRecordingFilepath();
    QString getRecordingFilepath();
                                  
protected:
    bool eventFilter(QObject *object, QEvent *event);
    
signals:
    void finishRecord(VOICE_INFO voiceInfo);
    void cancelRecord();
    
public slots:
    void exitRecord();
    void handleClickFinishButton();
//    void handleExpandAnimationFinish();
//    void handleShrankAnimationFinish();
    void pauseRecord();
    void renderLevel(const QAudioBuffer &buffer);
    void renderRecordingTime();
    void resumeRecord();
    void startRecord();
    void stopRecord();
    
private:
    //ExpandAnimationButton *expandAnimationButton;
    QHBoxLayout *m_hBoxLayout;
    QAudioProbe *audioProbe;
    QAudioRecorder *m_audioRecorder;
    QDateTime lastUpdateTime;
    QHBoxLayout *buttonLayout;
    QLabel *m_recordTimeLabel;
    //QLabel *titleLabel;
    QString recordPath;
    QTimer *m_tickerTimer;
    QVBoxLayout *expandAnimationButtonLayout;
    QVBoxLayout *shrankAnimationButtonLayout;
    QVBoxLayout *buttonAreaLayout;
    QWidget *buttonAreaWidget;
    QWidget *buttonWidget;
//    ShrankAnimationButton *shrankAnimationButton;
//    Waveform *waveform;
    int m_recordingTime;
    //QWidget *m_voiceShape;
    VOICE_INFO voiceInfo;
    Waveform *m_waveform;

    void initUI();
    void initConnection();
};

#endif
