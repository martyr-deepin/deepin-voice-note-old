#ifndef UIUTIL_H
#define UIUTIL_H

#include <QWidget>
#include <DDialog>
//#include <ddialog.h>


DWIDGET_USE_NAMESPACE
class UiUtil
{
public:
    UiUtil();

    static void setWidgetBackground(QWidget *widget, QString imgPath);
    static QPixmap getPixmap(QSize size, QString imgPath);
    static DDialog *createDialog(const QString &title, const QString &content, QWidget *parent);
    static QString getElidedText(QFont font, QString str, int MaxWidth, bool& isConverted);

};

#endif // UIUTIL_H
