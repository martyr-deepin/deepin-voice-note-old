#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QWidget>
#include <DFloatingButton>

DWIDGET_USE_NAMESPACE

class MenuButton : public DFloatingButton
{
    Q_OBJECT
public:
    explicit MenuButton(QWidget *parent = nullptr);
    explicit MenuButton(QString normal, QString press, QString hover, QString disable, QString foucs, QSize size, QSize iconsize, QWidget *parent = nullptr);
//    explicit MenuButton(QStyle::StandardPixmap iconType = static_cast<QStyle::StandardPixmap>(-1), QWidget *parent = nullptr);
//    explicit MenuButton(DStyle::StandardPixmap iconType = static_cast<DStyle::StandardPixmap>(-1), QWidget *parent = nullptr);
//    explicit MenuButton(const QString &text, QWidget *parent = nullptr);

    void setPicChange(QString normal,QString press,QString hover, QString disable, QString foucs);
    void DisableBtn();
    void EnAbleBtn();
protected:
//    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void initStyleOption(DStyleOptionButton *option)const;
private:
    bool m_isPressed;
    bool m_isIn;
    bool m_isDisabled;
    QSize m_iconSize;

    QPixmap m_normal;
    QPixmap m_hover;
    QPixmap m_press;
    QPixmap m_disable;
    QPixmap m_foucs;
};

#endif // MENUBUTTON_H
