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

#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QAudioProbe>
#include <QDateTime>
#include <QEvent>
#include <QTimer>
#include <QWidget>
#include <QLabel>
#define SLIDER_TICK_INTAVAL 4
enum DISPLAY_TYPE {WHOLE=0, PART_SAMPLE=1};

//语音波形
class Waveform : public QWidget
{
    Q_OBJECT

    static const int SAMPLE_DURATION;
    static const int WAVE_WIDTH;
    static const int WAVE_DURATION;

public:
    Waveform(QWidget *parent = 0);
    
    static qreal getPeakValue(const QAudioFormat &format);
    static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

    template <class T>
    static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);
                                                                                    
    void clearWave();

    void setWholeSampleList(QList<float> wholeList);
    QList<float> getWholeSampleList();
    void setCurrDisplayType(DISPLAY_TYPE);
    void setWavePosition(int pos);
    void emptyWave();
    void startTimer();
                                                                                    
public slots:
    void renderWave();
    void updateWave(float sample);
    void OnSetWavePos(int pos);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QDateTime lastSampleTime;
    QList<float> sampleList;
    QList<float> wholeSampleList;
    //QTimer *renderTimer;
    DISPLAY_TYPE m_currDisplayType;
    int m_currWavePos;
    QLabel *m_Slider;

    QString m_blueColor;
    QString m_greyColor;
    void genSampleListFromWhole();
    QString getColor(int xPos);

    bool m_wantEmpty;
};

#endif
