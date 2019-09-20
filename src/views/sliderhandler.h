#ifndef SLIDERHANDLER_H
#define SLIDERHANDLER_H

#include <QLabel>
#include <QLayout>
#include <QWidget>

//语音控制条handle
class SliderHandler : public QWidget
{
    Q_OBJECT
public:
    SliderHandler(QWidget *parent = 0);
    ~SliderHandler();
    QLabel *m_timeLabel;

private:
    QLabel *m_line;
    QLabel *m_handle;
    QLayout *m_layout;

    void initUI();
    void initConnection();

};

#endif // SLIDERHANDLER_H
