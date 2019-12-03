#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <DApplication>
#include <QObject>
#include "intancer.h"

DWIDGET_USE_NAMESPACE
class MyApplication : public DApplication
{
    Q_OBJECT
public:
    explicit MyApplication(int &argc, char **argv);

protected:
    void handleQuitAction();

signals:
    void sigShowRecordDialog();
    void sigShowVoiceToTextDialog();

public slots:
};

#endif // MYAPPLICATION_H
