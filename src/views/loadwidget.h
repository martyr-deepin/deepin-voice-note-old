#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <DFrame>
#include <DLabel>
#include <DWaterProgress>

DWIDGET_USE_NAMESPACE

enum LoadType { DELETEING = 0, LOADING = 1 };

class LoadWidget : public DFrame
{
    Q_OBJECT
public:
    explicit LoadWidget(QWidget *parent = Q_NULLPTR);
    void setValue(int value);
    void clearValue();
    void showType(LoadType type);

private:
    QString m_deleteText;
    QString m_switchText;
    DLabel *m_Text;
    DWaterProgress *m_water;
};

#endif // LOADWIDGET_H
