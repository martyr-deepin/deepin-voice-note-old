#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QTimer>
#include <QStyle>
#include <QStyleOptionSlider>

#include "mysliderbar.h"
#include "dthememanager.h"

DWIDGET_BEGIN_NAMESPACE

static const int CustomDrawingLeftPadding = 10;
static const int CustomDrawingRightPadding = 10;
static const int CustomDrawingScaleHeight = 6;

// TODO: optimize for better vertical slider support
class MySliderBarPrivate
{
    MySliderBarPrivate(MySliderBar *q):
        m_hoverShowValue(false),
        m_handleHovering(false),
        m_hoverTimout(false),
        m_hoverShowValueInterval(-1),
        q_ptr(q)
    {
        m_hoverTimer.setSingleShot(true);
    }

    int m_handleType = MySliderBar::RoundHandle;

    QString m_leftTip;
    QString m_rightTip;
    QList<int> m_scales;

    QColor m_tipColor = Qt::black;
    QColor m_scaleColor = Qt::black;
    QColor m_hoverValueColor;
    bool m_hoverShowValue;
    bool m_handleHovering;
    bool m_hoverTimout;
    bool mousePressed = false;
    int clickOffset = 0;
    int m_hoverShowValueInterval;
    QTimer m_hoverTimer;

    int getScalePosition(int value);
    int pixelPosToRangeValue(int pos) const;

    inline int pick(const QPoint &pt) const
    {
        Q_Q(const MySliderBar);
        return q->orientation() == Qt::Horizontal ? pt.x() : pt.y();
    }

    MySliderBar *q_ptr;
    Q_DECLARE_PUBLIC(MySliderBar)
};


MySliderBar::MySliderBar(QWidget *parent) :
    QSlider(parent),
    d_ptr(new MySliderBarPrivate(this))
{
    init();
}

MySliderBar::MySliderBar(Qt::Orientation orientation, QWidget *parent) :
    QSlider(orientation, parent),
    d_ptr(new MySliderBarPrivate(this))
{
    init();
}

MySliderBar::~MySliderBar()
{
    delete d_ptr;
}

int MySliderBar::handleType() const
{
    Q_D(const MySliderBar);

    return d->m_handleType;
}

void MySliderBar::setHandleType(HandleType handleType)
{
    Q_D(MySliderBar);

    d->m_handleType = handleType;
}

QString MySliderBar::rightTip() const
{
    Q_D(const MySliderBar);

    return d->m_rightTip;
}

void MySliderBar::setRightTip(const QString &rightTip)
{
    Q_D(MySliderBar);

    if (d->m_rightTip == rightTip) {
        return;
    }

    if (d->m_rightTip.isEmpty() || rightTip.isEmpty()) {
        d->m_rightTip = rightTip;
        updateGeometry();
    } else {
        d->m_rightTip = rightTip;
    }

    repaint();
}

QString MySliderBar::leftTip() const
{
    Q_D(const MySliderBar);

    return d->m_leftTip;
}

void MySliderBar::setLeftTip(const QString &leftTip)
{
    Q_D(MySliderBar);

    if (d->m_leftTip == leftTip) {
        return;
    }

    if (d->m_leftTip.isEmpty() || leftTip.isEmpty()) {
        d->m_leftTip = leftTip;
        updateGeometry();
    } else {
        d->m_leftTip = leftTip;
    }

    repaint();
}

QColor MySliderBar::scaleColor() const
{
    Q_D(const MySliderBar);

    return d->m_scaleColor;
}

void MySliderBar::setScaleColor(const QColor &scaleColor)
{
    Q_D(MySliderBar);

    d->m_scaleColor = scaleColor;

    repaint();
}

QColor MySliderBar::tipColor() const
{
    Q_D(const MySliderBar);

    return d->m_tipColor;
}

void MySliderBar::setTipColor(const QColor &tipColor)
{
    Q_D(MySliderBar);

    d->m_tipColor = tipColor;

    repaint();
}

void MySliderBar::addScale(int value)
{
    Q_D(MySliderBar);

    d->m_scales.append(value);

    if (d->m_scales.count() == 1) {
        updateGeometry();
    }

    repaint();
}

void MySliderBar::removeScale(int value)
{
    Q_D(MySliderBar);

    d->m_scales.removeOne(value);

    if (d->m_scales.isEmpty()) {
        updateGeometry();
    }

    repaint();
}

void MySliderBar::mousePressEvent(QMouseEvent *event)
{
    //if(event->y() < 116)//ynb 20191109
    {
        QAbstractSlider::mousePressEvent(event);

        if (event->button() == Qt::LeftButton) {
            if (orientation() == Qt::Vertical) {
                setValue(minimum() + ((maximum() - minimum()) * (height() - event->y())) / height()) ;
            } else {
                // FIXME
                // the value 10 is specified in MySliderBar.theme, it's ugly here, but I don't have any
                // good idea for now, maybe someone can help.
                setValue(minimum() + ((maximum() - minimum()) * (event->x() - 10)) / (width() - 10 - 10)) ;
            }

            event->accept();

            Q_D(MySliderBar);

            QStyleOptionSlider opt;
            initStyleOption(&opt);
            setRepeatAction(SliderNoAction);
            QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

            d->clickOffset = d->pick(event->pos() - sr.topLeft());
            d->mousePressed = true;

            Q_EMIT sliderPressed();
        }
    }
}

void MySliderBar::mouseReleaseEvent(QMouseEvent *event)
{
    //if(event->y() < 116)//ynb 20191109
    {
        QAbstractSlider::mouseReleaseEvent(event);

        if(event->button() == Qt::LeftButton) {
            d_func()->mousePressed = false;

            Q_EMIT sliderReleased();
        }
    }
}

void MySliderBar::paintEvent(QPaintEvent *event)
{
    Q_D(MySliderBar);

//    int sliderPos = (this->sliderPosition() * (this->width())) / (this->maximum()) - (m_sliderhandler->width() / 2);
//    //int sliderPos = this->sliderPosition() - (m_sliderhandler->width() / 2);
//    qDebug() << "slider pos:" << sliderPos;
//    qDebug() << "maximum:" << this->maximum() << ", minimum:" << this->minimum() << ", value:" << this->value() << ", sliderPosition:" << this->sliderPosition();

    //m_sliderhandler->setGeometry(sliderPos, 0, m_sliderhandler->width(), m_sliderhandler->height());

//    QPainter painter;
//    painter.begin(this);

//    // draw tips
//    QFont font = painter.font();
//    font.setPixelSize(12);
//    painter.setFont(font);

//    QPen pen = painter.pen();
//    pen.setColor(d->m_tipColor);
//    painter.setPen(pen);

//    QRect tmp = rect().adjusted(CustomDrawingLeftPadding - 5, 0, -CustomDrawingRightPadding + 5, 0);

//    QTextOption leftBottomOption;
//    leftBottomOption.setAlignment(Qt::AlignLeft | Qt::AlignBottom);
//    painter.drawText(tmp, d->m_leftTip, leftBottomOption);

//    QTextOption rightBottomOption;
//    rightBottomOption.setAlignment(Qt::AlignRight | Qt::AlignBottom);
//    painter.drawText(tmp, d->m_rightTip, rightBottomOption);

//    // draw scales
//    pen.setColor(d->m_scaleColor);
//    painter.setPen(pen);

//    Q_FOREACH(int scale, d->m_scales) {
//        int x = d->getScalePosition(scale);
//        int y = height() - 8;
//        painter.drawLine(x, y, x, y - CustomDrawingScaleHeight);
//    }

//    if (d->m_handleHovering && !d->m_hoverTimout) {
//        QString str = QString::number(value());
//        int x = d->getScalePosition(value()) - painter.fontMetrics().width(str) / 2.0;
//        painter.setPen(d->m_hoverValueColor);
//        painter.drawText(x, 10, str);
//    }

//    painter.end();

//    QSlider::paintEvent(event);
}

void MySliderBar::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(MySliderBar);

    if(d->mousePressed) {
        int newPosition = d->pixelPosToRangeValue(d->pick(event->pos()) - d->clickOffset);
        setSliderPosition(newPosition);

        Q_EMIT sliderMoved(newPosition);
    }

    if (!d->m_hoverShowValue) {
        return;
    }

    QPoint pos = event->pos();
    QRect rect(d->getScalePosition(value()) - CustomDrawingLeftPadding, 10, 20, 20);
    if (d->m_handleHovering) {
        d->m_handleHovering = rect.contains(pos);
    } else {
        d->m_handleHovering = rect.contains(pos);
        if (d->m_handleHovering) {
            d->m_hoverTimout = false;
            if (d->m_hoverShowValueInterval > 0) {
                d->m_hoverTimer.start(d->m_hoverShowValueInterval);
            }
        }
    }

    update();
}

void MySliderBar::hoverTimout()
{
    Q_D(MySliderBar);

    d->m_hoverTimout = true;
    update();
}

void MySliderBar::init()
{
    Q_D(MySliderBar);  
//    DThemeManager::registerWidget(this);
    setMouseTracking(true);
    connect(&d->m_hoverTimer, &QTimer::timeout, this, &MySliderBar::hoverTimout);
}

QSize MySliderBar::sizeHint() const
{
    Q_D(const MySliderBar);

    QSize size = QSlider::sizeHint();
    if (!d->m_leftTip.isEmpty() || !d->m_rightTip.isEmpty() || !d->m_scales.isEmpty()) {
        size.setHeight(size.height() + 25);
    } else {
        if (d->m_hoverShowValue) {
            size.setHeight(size.height() + 25);
        } else {
            size.setHeight(size.height() + 3);
        }
    }

    return size;
}

bool MySliderBar::hoverShowValue() const
{
    Q_D(const MySliderBar);

    return d->m_hoverShowValue;
}

QColor MySliderBar::hoverValueColor() const
{
    Q_D(const MySliderBar);

    return d->m_hoverValueColor;
}

int MySliderBar::hoverShowValueInterval() const
{
    Q_D(const MySliderBar);

    return d->m_hoverShowValueInterval;
}

void MySliderBar::setHoverShowValue(bool hoverShowValue)
{
    Q_D(MySliderBar);

    if (d->m_hoverShowValue == hoverShowValue) {
        return;
    }

    d->m_hoverShowValue = hoverShowValue;
    d->m_handleHovering &= hoverShowValue;

    updateGeometry();
    repaint();
}

void MySliderBar::setHoverValueColor(QColor hoverValueColor)
{
    Q_D(MySliderBar);

    d->m_hoverValueColor = hoverValueColor;
}

void MySliderBar::setHoverShowValueInterval(int hoverShowValueInterval)
{
    Q_D(MySliderBar);

    d->m_hoverShowValueInterval = hoverShowValueInterval;
}

MySliderBar::MySliderBar(MySliderBarPrivate &d): d_ptr(&d)
{
    init();
}

int MySliderBarPrivate::getScalePosition(int value)
{
    Q_Q(MySliderBar);

    float valueRange = q->maximum() - q->minimum();
    float posRange = q->width() - CustomDrawingLeftPadding - CustomDrawingRightPadding;
    return CustomDrawingLeftPadding + (value - q->minimum()) * posRange / valueRange;
}

int MySliderBarPrivate::pixelPosToRangeValue(int pos) const
{
    Q_Q(const MySliderBar);

    QStyleOptionSlider opt;
    q->initStyleOption(&opt);
    QRect gr = q->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, q);
    QRect sr = q->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, q);
    int sliderMin, sliderMax, sliderLength;

    if (q->orientation() == Qt::Horizontal) {
        sliderLength = sr.width();
        sliderMin = gr.x();
        sliderMax = gr.right() - sliderLength + 1;
    } else {
        sliderLength = sr.height();
        sliderMin = gr.y();
        sliderMax = gr.bottom() - sliderLength + 1;
    }
    return QStyle::sliderValueFromPosition(q->minimum(), q->maximum(), pos - sliderMin,
                                           sliderMax - sliderMin, opt.upsideDown);
}

DWIDGET_END_NAMESPACE
