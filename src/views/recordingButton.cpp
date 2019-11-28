/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2018 Deepin, Inc.
 *               2011 ~ 2018 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
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

#include <QDebug>
#include <QVBoxLayout>
#include <DApplicationHelper>

#include "dimagebutton.h"
#include "recordingButton.h"

DWIDGET_USE_NAMESPACE

RecordingButton::RecordingButton(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        resumeButton = new MyRecodeButtons(
                    ":/image/icon/normal/record_normal.svg",
                    ":/image/icon/press/record_press.svg",
                    ":/image/icon/hover/record_hover.svg",
                    "",
                    ":/image/icon/focus/record_focus.svg",
                    QSize(60,60),
                    this);

        pauseButton = new MyRecodeButtons(
                    ":/image/icon/normal/pause_red_normal.svg",
                    ":/image/icon/press/pause_red_press.svg",
                    ":/image/icon/hover/pause_red_hover.svg",
                    "",
                    ":/image/icon/focus/record_focus.svg",
                    QSize(60,60),
                    this);

    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        resumeButton = new MyRecodeButtons(
                    ":/image/icon_dark/normal/record_normal_dark.svg",
                    ":/image/icon_dark/press/record_press_dark.svg",
                    ":/image/icon_dark/hover/record_hover_dark.svg",
                    "",
                    ":/image/icon_dark/focus/record_focus_dark.svg",
                    QSize(60,60),
                    this);

        pauseButton = new MyRecodeButtons(
                    ":/image/icon_dark/normal/pause_red_normal_dark.svg",
                    ":/image/icon_dark/press/pause_red_press_dark.svg",
                    ":/image/icon_dark/hover/pause_red_hover_dark.svg",
                    "",
                    ":/image/icon_dark/focus/pause_red_focus_dark.svg",
                    QSize(60,60),
                    this);
    }



    //resumeButton = new DFloatingButton(this);
    //resumeButton->setFixedSize(QSize(45, 45));
    //resumeButton->setIcon(QIcon(":/image/icon/normal/record_small_normal.svg"));
    //resumeButton->setIconSize(QSize(28,28));
//    DPalette pb = DApplicationHelper::instance()->palette(resumeButton);
//    pb.setBrush(DPalette::Highlight, QColor(0x00FD5E5E));
//    resumeButton->setPalette(pb);
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(handleResume()));
    

//    pauseButton = new DFloatingButton(this);
//    pauseButton->setFixedSize(QSize(45, 45));
//    pauseButton->setIcon(QIcon(":/image/icon/normal/pause_blue_normal.svg"));
//    pauseButton->setIconSize(QSize(28,28));
//    DPalette pa = DApplicationHelper::instance()->palette(pauseButton);
//    pa.setBrush(DPalette::Highlight, QColor(0x00FD5E5E));
//    pauseButton->setPalette(pa);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePause()));

    layout->addWidget(pauseButton);

    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &RecordingButton::changeTheme);
}

void RecordingButton::handlePause() {
    layout->removeWidget(pauseButton);
    pauseButton->setParent(NULL);
    layout->addWidget(resumeButton);
    emit pause();
}

void RecordingButton::handleResume() {
    layout->removeWidget(resumeButton);
    resumeButton->setParent(NULL);
    layout->addWidget(pauseButton);
    emit resume();
}

void RecordingButton::onlyhandleResume()
{
    layout->removeWidget(resumeButton);
    resumeButton->setParent(NULL);
    layout->addWidget(pauseButton);
}

void RecordingButton::changeTheme()
{
    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        if(nullptr != resumeButton)
        {
            resumeButton->setPicChange(
                        ":/image/icon/normal/record_normal.svg",
                        ":/image/icon/press/record_press.svg",
                        ":/image/icon/hover/record_hover.svg",
                        "",
                        ":/image/icon/focus/record_focus.svg");
        }

        if(nullptr != pauseButton)
        {
            pauseButton->setPicChange(
                        ":/image/icon/normal/pause_red_normal.svg",
                        ":/image/icon/press/pause_red_press.svg",
                        ":/image/icon/hover/pause_red_hover.svg",
                        "",
                        ":/image/icon/focus/record_focus.svg");
        }


    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        if(nullptr != resumeButton)
        {
            resumeButton->setPicChange(
                        ":/image/icon_dark/normal/record_normal_dark.svg",
                        ":/image/icon_dark/press/record_press_dark.svg",
                        ":/image/icon_dark/hover/record_hover_dark.svg",
                        "",
                        ":/image/icon_dark/focus/record_focus_dark.svg");
        }
        if(nullptr != pauseButton)
        {
            pauseButton->setPicChange(
                        ":/image/icon_dark/normal/pause_red_normal_dark.svg",
                        ":/image/icon_dark/press/pause_red_press_dark.svg",
                        ":/image/icon_dark/hover/pause_red_hover_dark.svg",
                        "",
                        ":/image/icon_dark/focus/pause_red_focus_dark.svg");
        }
    }
}
