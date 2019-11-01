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

#include <DApplication>
//#include <DApplicationSettings>
//#include <DMainWindow>

#include <DWidgetUtil>
#include <QtDBus>
#include <QDBusConnection>
#include <QDBusError>

DWIDGET_USE_NAMESPACE
using namespace Dtk::Core;


int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    DApplication a(argc, argv);


    if (!a.setSingleInstance("deepin-voice-note"))
    {
        return 0;
    }

    // 创建QDBusInterface接口
    //QDBusConnection::sessionBus().connectToBus(QDBusConnection::SessionBus,"com.deepin.daemon.Audio");

//    QDBusConnection connect = QDBusConnection::sessionBus();
//    QDBusInterface interface("com.deepin.daemon.Audio", "com/deepin/daemon/Audio",
//                            "com.deepin.daemon.Audio.DefaultSource",
//                            QDBusConnection::sessionBus());
//    if (!interface.isValid())
//    {
//       qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
//    }
//    else {
//        //调用远程的value方法
//        QDBusReply<int> reply = interface.call("DefaultSource");
//        if (reply.isValid())
//        {
//           int value = reply.value();
//           qDebug() << QString("value =  %1").arg(value);
//        }
//        else
//        {
//           qDebug() << "value method called failed!";
//        }
//    }
    VoiceNotebookApp app(a);
}
