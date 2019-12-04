#ifndef EXPORTEDINTERFACE_H
#define EXPORTEDINTERFACE_H


#include <QObject>
#include <DExportedInterface>
#include "mainwindow.h"
DCORE_USE_NAMESPACE

class ExportedInterface : public Dtk::Core::DUtil::DExportedInterface
{
public:
    explicit ExportedInterface(QObject *parent = nullptr);
    //需要自己实现的接口函数：action--动作名称，parameters--动作参数(JSON格式)
    QVariant invoke(const QString &action, const QString &parameters) const;
    void setMainWindowObj(MyMainWindow *obj);
private:
    QObject                *m_object;
    MyMainWindow           *m_mainWindow;
};

#endif // EXPORTEDINTERFACE_H


