#include "exportedinterface.h"
#include "mainwindow.h"
ExportedInterface::ExportedInterface(QObject *parent): Dtk::Core::DUtil::DExportedInterface(parent)
{
    m_object = parent;
}
QVariant ExportedInterface::invoke(const QString &action, const QString &parameters) const
{

    if (action == "CREATEVOICEMEMO")
    {
        m_mainWindow->CreateVoiceMemo();
    }
    else
    {
       //qDebug()<<"action error";
       UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("error: "), QString("action error"));
       return QVariant(false);
    }
    return QVariant(true);
}
void ExportedInterface::setMainWindowObj(MyMainWindow *obj)
{
   m_mainWindow = obj;
}
