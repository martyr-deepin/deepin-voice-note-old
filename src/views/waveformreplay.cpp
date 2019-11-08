

#include <QDateTime>
#include <QDebug>
#include <QEvent>
#include <QPaintEvent>
#include <QApplication>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <DWidget>

#include "uiutil.h"
#include "waveformreplay.h"

const int WaveFormReplay::SAMPLE_DURATION = 30;
const int WaveFormReplay::WAVE_WIDTH = 2;
const int WaveFormReplay::WAVE_DURATION = 4;


WaveFormReplay::WaveFormReplay(QWidget *parent) : QWidget(parent), m_currDisplayType(PART_SAMPLE), m_currWavePos(0), m_blueColor("#0079FF"), m_greyColor("#848484")//m_greyColor("#848484")
{
    //setFixedSize(350, 50);
    m_wantEmpty = false;
    if(PART_SAMPLE == m_currDisplayType)
    {
        m_Slider = new QLabel(this);
        m_Slider->setFixedSize(5, 52);
        QPalette pal;
        pal.setBrush(QPalette::Background, QBrush(UiUtil::renderSVG(":/image/icon/normal/cursor.svg", QSize(m_Slider->width(), m_Slider->height()),qApp)));
        m_Slider->setAutoFillBackground(true);
        m_Slider->setPalette(pal);
        m_Slider->setAlignment(Qt::AlignHCenter| Qt::AlignTop);
        m_Slider->move(0,0);
    }


    lastSampleTime = QDateTime::currentDateTime();

    renderTimer = new QTimer(this);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(renderWave()));
    renderTimer->start(SAMPLE_DURATION);
}

void WaveFormReplay::paintEvent(QPaintEvent *)
{

    if(m_wantEmpty)
    {
        return;
    }

    //qDebug()<<"WaveFormReplay::paintEvent:";
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if (WHOLE == m_currDisplayType)
    {
        genSampleListFromWhole();
    }

    // Background render just for test.
    // QRect testRect(rect());
    // QLinearGradient testGradient(testRect.topLeft(), testRect.bottomLeft());
    // testGradient.setColorAt(0, QColor("#0000ff"));
    // testGradient.setColorAt(1, QColor("#00ff00"));
    // painter.fillRect(testRect, testGradient);

    // FIXME:
    // I don't know why need clip less than rect width when HiDPI.
    qreal devicePixelRatio = qApp->devicePixelRatio();
    if (devicePixelRatio > 1.0) {
        painter.setClipRect(QRect(rect().x(), rect().y(), rect().width() - 1, rect().height()));
    } else {
        painter.setClipRect(QRect(rect().x(), rect().y(), rect().width(), rect().height()));
    }

    //qDebug()<<"pointNum:"<<sampleList.size();
    if(PART_SAMPLE == m_currDisplayType)
    {
        m_Slider->move(rect().x() + rect().width(),m_Slider->y());
    }


    int volume = 0;
    //qDebug()<<"sampleList.size():"<<sampleList.size();
    for (int i = 0; i < sampleList.size(); i++) {
        volume = sampleList[i] * rect().height() * 2;

        if (volume == 0) {
            QPainterPath path;
            path.addRect(QRectF(rect().x() + i * WAVE_DURATION, rect().y() + (rect().height() - 1) / 2, WAVE_DURATION, 1));
            painter.fillPath(path, QColor(getColor(rect().x() + i * WAVE_DURATION)));
        } else {
            QRect sampleRect(rect().x() + i * WAVE_DURATION, rect().y() + (rect().height() - volume) / 2, WAVE_WIDTH , volume);

//            qDebug()<<"sampleRect.x:"<<sampleRect.x();
//            qDebug()<<"rect.x:"<<rect().x();
            //QLinearGradient 不渐变色
//           QLinearGradient gradient(sampleRect.topLeft(), sampleRect.bottomLeft());
//            gradient.setColorAt(0, QColor(getColor(rect().x() + i * WAVE_DURATION)));
//            gradient.setColorAt(1, QColor(getColor(rect().x() + i * WAVE_DURATION)));
            //QLinearGradient 可以做渐变色
//            //QLinearGradient gradient(rect().topLeft(), rect().topRight());
            QLinearGradient gradient(sampleRect.topLeft(), sampleRect.bottomLeft());
            gradient.setColorAt(0, QColor("#03D0D6"));
            gradient.setColorAt(1, QColor("#0079FF"));


            painter.fillRect(sampleRect, gradient);
        }
        if((PART_SAMPLE == m_currDisplayType)&&(i == sampleList.size() - 1))
        {
            m_Slider->move(rect().x() + i * WAVE_DURATION,m_Slider->y());
        }
    }

    //qDebug()<<"sampleList.size():"<<sampleList.size();
    if (sampleList.size() < rect().width() / WAVE_DURATION) {
        QPainterPath path;
        path.addRect(QRectF(rect().x() + sampleList.size() * WAVE_DURATION,
                            rect().y() + (rect().height() - 1) / 2,
                            rect().width() - (rect().x() + sampleList.size() * WAVE_DURATION),
                            1));
        painter.fillPath(path, QColor(rect().x() + sampleList.size() * WAVE_DURATION));
    }

}

QString WaveFormReplay::getColor(int xPos)
{
    if (-1 == m_currWavePos)
    {
        return m_blueColor;
    }
    else if ((xPos > 0) && (xPos <= m_currWavePos))
    {
        return m_blueColor;
    }
    else
    {
        return m_greyColor;
    }
}

void WaveFormReplay::setWavePosition(int pos)
{
    m_currWavePos = pos;
}

void WaveFormReplay::emptyWave()
{
    m_wantEmpty = true;
    this->update();
}

void WaveFormReplay::updateWave(float sample)
{
    //sample = 4.0;
    QDateTime currentTime = QDateTime::currentDateTime();

    if (lastSampleTime.msecsTo(currentTime) > SAMPLE_DURATION) {
        if (sampleList.size() > (rect().width() / WAVE_DURATION) - 1) {
        //if (sampleList.size() > rect().width() / WAVE_DURATION) {
            sampleList.pop_front();
        }
        sampleList << sample;
        lastSampleTime = currentTime;
    }
    wholeSampleList << sample;
}

void WaveFormReplay::setWholeSampleList(QList<float> wholeList)
{
    wholeSampleList.clear();
    //sampleList.clear();
    wholeSampleList = wholeList;
    qDebug()<<"wholeSampleList.size:"<<wholeSampleList.size();
//    int pointNum = rect().width() / WAVE_DURATION;
//    float sample = wholeList.size() * 1.0 / pointNum;
////    qDebug() << "whole list";
////    for (int t = 0; t < wholeList.size(); t++)
////    {
////        qDebug() << t << ":" << wholeList.at(t);
////    }
//    for (int i = 0; i < pointNum; i++)
//    {
//        if (i == 0)
//        {
//            sampleList << wholeList[i];
//        }

//        else
//        {
//            float pointPos = i * sample;
//            if (pointPos > wholeList.size() - 1)
//            {
//                sampleList << wholeList[wholeList.size() - 1];
//            }
//            else
//            {
//                int prePoint = static_cast<int>(pointPos);
//                int nextPoint = prePoint + 1;
//                float currPointValue = (pointPos - prePoint) * wholeList[nextPoint] + (nextPoint - pointPos) * wholeList[prePoint];
//                sampleList << currPointValue;
//            }
//        }
//    }

//    qDebug() << "sample list";
//    for (int t = 0; t < sampleList.size(); t++)
//    {
//        qDebug() << t << ":" << sampleList.at(t);
//    }

}

QList<float> WaveFormReplay::getWholeSampleList()
{
    return wholeSampleList;
}

void WaveFormReplay::renderWave()
{
    repaint();
}

void WaveFormReplay::clearWave()
{
    sampleList.clear();
}

// returns the audio level for each channel
QVector<qreal> WaveFormReplay::getBufferLevels(const QAudioBuffer& buffer)
{
    QVector<qreal> values;

    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if (buffer.format().codec() != "audio/pcm")
        return values;

    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = WaveFormReplay::getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch (buffer.format().sampleType()) {
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if (buffer.format().sampleSize() == 32)
            values = WaveFormReplay::getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = WaveFormReplay::getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = WaveFormReplay::getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        break;
    case QAudioFormat::Float:
        if (buffer.format().sampleSize() == 32) {
            values = WaveFormReplay::getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
        }
        break;
    case QAudioFormat::SignedInt:
        if (buffer.format().sampleSize() == 32)
            values = WaveFormReplay::getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = WaveFormReplay::getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = WaveFormReplay::getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] /= peak_value;
        break;
    }

    return values;
}

template <class T>
QVector<qreal> WaveFormReplay::getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }

    return max_values;
}

// This function returns the maximum possible sample value for a given audio format
qreal WaveFormReplay::getPeakValue(const QAudioFormat& format)
{
    // Note: Only the most common sample formats are supported
    if (!format.isValid())
        return qreal(0);

    if (format.codec() != "audio/pcm")
        return qreal(0);

    switch (format.sampleType()) {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if (format.sampleSize() != 32) // other sample formats are not supported
            return qreal(0);
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if (format.sampleSize() == 32)
            return qreal(INT_MAX);
        if (format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
    case QAudioFormat::UnSignedInt:
        if (format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if (format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }

    return qreal(0);
}

void WaveFormReplay::setCurrDisplayType(DISPLAY_TYPE type)
{
    m_currDisplayType = type;
    if(PART_SAMPLE != type)
    {
        m_Slider->hide();
    }
}

void WaveFormReplay::genSampleListFromWhole()
{
    sampleList.clear();
    int pointNum = rect().width() / WAVE_DURATION;
    float sample = wholeSampleList.size() * 1.0 / pointNum;
    //qDebug()<<"pointNum:"<<pointNum;
//    qDebug() << "whole list";
//    for (int t = 0; t < wholeList.size(); t++)
//    {
//        qDebug() << t << ":" << wholeList.at(t);
//    }
    for (int i = 0; i < pointNum; i++)
    {
        if (i == 0)
        {
            sampleList << wholeSampleList[i];
        }

        else
        {
            float pointPos = i * sample;
            if (pointPos > wholeSampleList.size() - 1)
            {
                sampleList << wholeSampleList[wholeSampleList.size() - 1];
            }
            else
            {
                int prePoint = static_cast<int>(pointPos);
                int nextPoint = prePoint + 1;
                float currPointValue = (pointPos - prePoint) * wholeSampleList[nextPoint] + (nextPoint - pointPos) * wholeSampleList[prePoint];
                sampleList << currPointValue;
            }
        }
    }
}
