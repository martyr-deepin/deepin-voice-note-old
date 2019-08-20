#include "uiutil.h"

UiUtil::UiUtil()
{

}

void UiUtil::setWidgetBackground(QWidget *widget, QString imgPath)
{
    widget->setAutoFillBackground(true);
    QPalette pal;// = widget->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap(imgPath)));
    widget->setPalette(pal);
}
