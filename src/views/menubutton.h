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
    explicit MenuButton(QStyle::StandardPixmap iconType = static_cast<QStyle::StandardPixmap>(-1), QWidget *parent = nullptr);
    explicit MenuButton(DStyle::StandardPixmap iconType = static_cast<DStyle::StandardPixmap>(-1), QWidget *parent = nullptr);
    explicit MenuButton(const QString &text, QWidget *parent = nullptr);

protected:
    void initStyleOption(DStyleOptionButton *option)const;

};

#endif // MENUBUTTON_H
