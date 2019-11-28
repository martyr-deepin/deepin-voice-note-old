#ifndef ADDFOLDERBUTTON_H
#define ADDFOLDERBUTTON_H

#include <QWidget>
#include <DFloatingButton>

DWIDGET_USE_NAMESPACE
class AddFolderButton : public DFloatingButton
{
    Q_OBJECT
public:
    explicit AddFolderButton(QWidget *parent = nullptr);

protected:
    void initStyleOption(DStyleOptionButton *option)const;
};

#endif // ADDFOLDERBUTTON_H
