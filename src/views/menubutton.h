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

protected:
    void initStyleOption(DStyleOptionButton *option)const;
};

#endif // MENUBUTTON_H
