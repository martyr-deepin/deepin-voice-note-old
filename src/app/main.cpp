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
    //DApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    DApplication a(argc, argv);

    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    a.setApplicationDisplayName(QObject::tr("语音记事本"));
    a.setApplicationDescription(QObject::tr("语音记事本是一款提供文本记事、语音录音记录的轻量级语音工具。"));
    if (!a.setSingleInstance("deepin-voice-note"))
    {
        return 0;
    }

    VoiceNotebookApp app(a);
}
