/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *               2016 ~ 2018 dragondjf
 *
 * Author:     dragondjf<dingjiangfeng@deepin.com>
 *
 * Maintainer: dragondjf<dingjiangfeng@deepin.com>
 *             zccrs<zhangjide@deepin.com>
 *             Tangtong<tangtong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "voicenotebookapp.h"
#include "intancer.h"   //Add 20191111
#include "exportedinterface.h"  //Add createVoiceMemo 新建语音备忘录对应
#include <DApplication>
//#include <DApplicationSettings>
//#include <DMainWindow>
#include <DApplicationHelper>
#include <DWidgetUtil>
#include <QtDBus>
#include <QDBusConnection>
#include <QDBusError>
#include <DLog>

#include "myapplication.h"
DWIDGET_USE_NAMESPACE
using namespace Dtk::Core;


int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    //DApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //DApplication a(argc, argv);
    MyApplication a(argc, argv);
    if(!a.setSingleInstance(a.applicationName()))
    //if(!DApplicationHelper::instance()->setSingleInstance(a.applicationName(),DGuiApplicationHelper::UserScope))
    {
        exit(-1);
    }
    //Add start createVoiceMemo 新建语音备忘录对应
//    MyMainWindow * mainWindowObject = app.getMainWindowObject();
    ExportedInterface einterface(&a);
    einterface.registerAction("CREATEVOICEMEMO","create a new VoiceMemo");
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.registerService("com.deepin.VoiceNote");
    dbus.registerObject("com.deepin.VoiceNote",&a);
    //Add end createVoiceMemo 新建语音备忘录对应

    //Add start 20191111
    QString str = argv[0];
    QStringList strList = str.split('/');
    if (strList.size() > 0)
    {
        Intancer::get_Intancer()->setApplicationName(strList.at(strList.size()-1));
    }
    //Add end 20191111

    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    a.loadTranslator();//3702
    a.setApplicationDisplayName(QObject::tr("Voice Notes"));
//    a.setApplicationDisplayName(QObject::tr("语音记事本"));
    a.setApplicationDescription(QObject::tr("Voice Notes is a lightweight memo tool to make text notes and voice recordings."));
//    a.setApplicationDescription(QObject::tr("语音记事本是一款提供文本记事、语音录音记录的轻量级语音工具。"));

    Dtk::Core::DLogManager::registerConsoleAppender();
    Dtk::Core::DLogManager::registerFileAppender();

    MyMainWindow  *mainWindowObject = new MyMainWindow();  //Add  createVoiceMemo 新建语音备忘录对应
    einterface.setMainWindowObj(mainWindowObject); //Add  createVoiceMemo 新建语音备忘录对应
    VoiceNotebookApp app(a, mainWindowObject); //Edit  createVoiceMemo 新建语音备忘录对应
}
