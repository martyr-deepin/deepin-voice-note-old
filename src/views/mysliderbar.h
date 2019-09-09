#ifndef MY_SLIDER_BAR_H
#define MY_SLIDER_BAR_H

#include <QSlider>

#include "dtkwidget_global.h"
#include "sliderhandler.h"

DWIDGET_BEGIN_NAMESPACE

class MySliderBarPrivate;
class LIBDTKWIDGETSHARED_EXPORT MySliderBar : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(int handleType READ handleType)
    Q_PROPERTY(QColor tipColor READ tipColor WRITE setTipColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(bool hoverShowValue READ hoverShowValue WRITE setHoverShowValue)
    Q_PROPERTY(QColor hoverValueColor READ hoverValueColor WRITE setHoverValueColor)
    Q_PROPERTY(int hoverShowValueInterval READ hoverShowValueInterval WRITE setHoverShowValueInterval)

public:
    enum HandleType {
        SharpHandler,
        RoundHandle
    };

    MySliderBar(QWidget *parent = 0);
    MySliderBar(Qt::Orientation orientation, QWidget *parent = 0);
    ~MySliderBar();

    int handleType() const;
    void setHandleType(HandleType handleType);

    QString leftTip() const;
    void setLeftTip(const QString &leftTip);

    QString rightTip() const;
    void setRightTip(const QString &rightTip);

    QColor tipColor() const;
    void setTipColor(const QColor &tipColor);

    QColor scaleColor() const;
    void setScaleColor(const QColor &scaleColor);

    void addScale(int value);
    void removeScale(int value);

    bool hoverShowValue() const;
    QColor hoverValueColor() const;
    int hoverShowValueInterval() const;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

public Q_SLOTS:
    void setHoverShowValue(bool hoverShowValue);
    void setHoverValueColor(QColor hoverValueColor);
    void setHoverShowValueInterval(int hoverShowValueInterval);

protected:
    MySliderBar(MySliderBarPrivate &d);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;

private Q_SLOTS:
    void hoverTimout();

private:
    MySliderBarPrivate *d_ptr;
    SliderHandler *m_sliderhandler;

    void init();

    Q_DECLARE_PRIVATE(MySliderBar)
    Q_DISABLE_COPY(MySliderBar)
};

DWIDGET_END_NAMESPACE

#endif // MY_SLIDER_BAR_H
