#ifndef SLIDERHANDLE_H
#define SLIDERHANDLE_H

#include <DWidget>
#include <DLabel>
#include <DPalette>

DWIDGET_USE_NAMESPACE

//回放 slider handle
class SliderHandle : public DLabel
{
    Q_OBJECT
public:
    explicit SliderHandle(QWidget *parent = nullptr);
    void setTime(QString time);
protected:
    //void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    //QString m_imgpath;
    DLabel* m_timelabel;
};

#endif // SLIDERHANDLE_H
