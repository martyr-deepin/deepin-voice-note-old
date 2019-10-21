#ifndef SLIDERHANDLE_H
#define SLIDERHANDLE_H

#include <DWidget>
#include <DLabel>
DWIDGET_USE_NAMESPACE

class SliderHandle : public DLabel
{
    Q_OBJECT
public:
    explicit SliderHandle(QString imgpath,QWidget *parent = nullptr);
protected:
    //void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    QString m_imgpath;
    DLabel* m_timelabel;
};

#endif // SLIDERHANDLE_H
