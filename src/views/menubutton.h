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
    void setBtnPalette();

//protected:
//    DStyleOptionButton baseStyleOption() const;
//    void initStyleOption(DStyleOptionButton *option) const;

signals:

public slots:
};

#endif // MENUBUTTON_H
