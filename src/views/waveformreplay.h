#ifndef WAVEFORMREPLAY_H
#define WAVEFORMREPLAY_H

#include <QAudioProbe>
#include <QDateTime>
#include <QEvent>
#include <QTimer>
#include <QWidget>
#include <QLabel>
#define SLIDER_TICK_INTAVAL 4
enum DISPLAY_TYPE {WHOLE=0, PART_SAMPLE=1};

//语音波形(没有使用)
class WaveFormReplay : public QWidget
{
    Q_OBJECT

    static const int SAMPLE_DURATION;
    static const int WAVE_WIDTH;
    static const int WAVE_DURATION;

public:
    WaveFormReplay(QWidget *parent = 0);

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

public slots:
    void renderWave();
    void updateWave(float sample);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QDateTime lastSampleTime;
    QList<float> sampleList;
    QList<float> wholeSampleList;
    QTimer *renderTimer;
    DISPLAY_TYPE m_currDisplayType;
    int m_currWavePos;
    QLabel *m_Slider;

    QString m_blueColor;
    QString m_greyColor;
    void genSampleListFromWhole();
    QString getColor(int xPos);

    bool m_wantEmpty;
};

#endif // WAVEFORMREPLAY_H
