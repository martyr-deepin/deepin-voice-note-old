#ifndef UIUTIL_H
#define UIUTIL_H

#include <QWidget>



class UiUtil
{
public:
    UiUtil();

    static void setWidgetBackground(QWidget *widget, QString imgPath);
    static QPixmap getPixmap(QSize size, QString imgPath);
};

#endif // UIUTIL_H
