#include "playingbutton.h"
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
#include "uiutil.h"
#include "dimagebutton.h"

DWIDGET_USE_NAMESPACE

PlayingButton::PlayingButton(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        pauseButton = new MyRecodeButtons(
                    ":/image/icon/normal/pause_blue_normal.svg",
                    ":/image/icon/press/pause_blue_press.svg",
                    ":/image/icon/hover/pause_blue_hover.svg",
                    "",
                    ":/image/icon/focus/pause_blue_focus.svg",
                    QSize(60,60)
                    );
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        pauseButton = new MyRecodeButtons(
                    ":/image/icon_dark/normal/pause_blue_normal_dark.svg",
                    ":/image/icon_dark/press/pause_blue_press_dark.svg",
                    ":/image/icon_dark/hover/pause_blue_hover_dark.svg",
                    "",
                    ":/image/icon_dark/focus/pause_blue_focus_dark.svg",
                    QSize(60,60)
                    );
    }
    else
    {
        pauseButton = new MyRecodeButtons(
                    ":/image/icon/normal/pause_blue_normal.svg",
                    ":/image/icon/press/pause_blue_press.svg",
                    ":/image/icon/hover/pause_blue_hover.svg",
                    "",
                    ":/image/icon/focus/pause_blue_focus.svg",
                    QSize(60,60)
                    );
    }

    pauseButton->setFocusPolicy(Qt::NoFocus);
//    pauseButton = new DFloatingButton(this);
//    pauseButton->setFixedSize(QSize(45, 45));
//    //pauseButton->setIcon(QIcon(":/image/icon/normal/pause_blue_normal.svg"));
//    pauseButton->setIcon(QIcon(UiUtil::renderSVG(":/image/icon/normal/pause_blue_normal.svg", QSize(28,28),qApp)));
//    pauseButton->setIconSize(QSize(28,28));
//    DPalette pa = DApplicationHelper::instance()->palette(pauseButton);
//    pa.setBrush(DPalette::Highlight, pa.color(DPalette::DarkLively));
//    //pauseButton->setPalette(pa);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePause()));



    if(themeType == DGuiApplicationHelper::LightType)
    {
        resumeButton = new MyRecodeButtons(
                    ":/image/icon/normal/play_normal.svg",
                    ":/image/icon/press/play_press.svg",
                    ":/image/icon/hover/play_hover.svg",
                    ":/image/icon/disabled/play_disabled.svg",
                    ":/image/icon/focus/play_focus.svg",
                    QSize(60,60),
                    this
                    );
    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        resumeButton = new MyRecodeButtons(
                    ":/image/icon_dark/normal/play_normal_dark.svg",
                    ":/image/icon_dark/press/play_press_dark.svg",
                    ":/image/icon_dark/hover/play_hover_dark.svg",
                    ":/image/icon_dark/disabled/play_disabled_dark.svg",
                    ":/image/icon_dark/focus/play_focus_dark.svg",
                    QSize(60,60),
                    this
                    );
    }
    else
    {
        resumeButton = new MyRecodeButtons(
                    ":/image/icon/normal/play_normal.svg",
                    ":/image/icon/press/play_press.svg",
                    ":/image/icon/hover/play_hover.svg",
                    ":/image/icon/disabled/play_disabled.svg",
                    ":/image/icon/focus/play_focus.svg",
                    QSize(60,60),
                    this
                    );
    }
    resumeButton->setFocusPolicy(Qt::NoFocus);
//    resumeButton = new DFloatingButton(this);
//    resumeButton->setFixedSize(QSize(45, 45));
//    //resumeButton->setIcon(QIcon(":/image/icon/normal/play_normal.svg"));
//    resumeButton->setIcon(QIcon(UiUtil::renderSVG(":/image/icon/normal/play_normal.svg", QSize(28,28),qApp)));
//    resumeButton->setIconSize(QSize(28,28));
//    DPalette pe = DApplicationHelper::instance()->palette(resumeButton);
//    pe.setBrush(DPalette::Highlight, pe.color(DPalette::DarkLively));
//    //resumeButton->setPalette(pe);
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(handleResume()));

    layout->addWidget(resumeButton);
    layout->addWidget(pauseButton);
    pauseButton->setVisible(false);
    //pauseButton->setFixedSize(QSize(0,0));

    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &PlayingButton::changeTheme);
}

void PlayingButton::onlySetResumeForButton()
{
    pauseButton->setVisible(false);
    resumeButton->setVisible(true);
//    pauseButton->setFixedSize(QSize(0,0));
//    pauseButton->setFixedSize(QSize(60,60));

//    layout->removeWidget(pauseButton);
//    pauseButton->setParent(NULL);
//    layout->addWidget(resumeButton);

}
void PlayingButton::setPlayDiseable()
{
   if(nullptr != resumeButton)
   {
       resumeButton->DisableBtn();
       resumeButton->setDown(true);
   }
}

void PlayingButton::setPlayEnable()
{
    if(nullptr != resumeButton)
    {
        resumeButton->EnAbleBtn();
        resumeButton->setDown(false);
    }
}

void PlayingButton::handlePause() {
//    layout->removeWidget(pauseButton);
//    pauseButton->setParent(NULL);
//    layout->addWidget(resumeButton);
//    pauseButton->setFixedSize(QSize(0,0));
//    resumeButton->setFixedSize(QSize(60,60));

    resumeButton->setVisible(true);
    pauseButton->setVisible(false);
    emit pause();
}

void PlayingButton::handleResume() {
//    layout->removeWidget(resumeButton);
//    resumeButton->setParent(NULL);
//    layout->addWidget(pauseButton);
//    pauseButton->setFixedSize(QSize(60,60));
//    resumeButton->setFixedSize(QSize(0,0));
    pauseButton->setVisible(true);
    resumeButton->setVisible(false);

    emit resume();
}

void PlayingButton::handleStop() {
//    layout->removeWidget(pauseButton);
//    pauseButton->setParent(NULL);
//    layout->addWidget(resumeButton);
//    pauseButton->setFixedSize(QSize(0,0));
//    resumeButton->setFixedSize(QSize(60,60));

    resumeButton->setVisible(true);
    pauseButton->setVisible(false);
    emit stop();
}

void PlayingButton::changeTheme()
{
    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();
    if(themeType == DGuiApplicationHelper::LightType)
    {
        if(nullptr != pauseButton)
        {
            pauseButton->setPicChange(
                        ":/image/icon/normal/pause_blue_normal.svg",
                        ":/image/icon/press/pause_blue_press.svg",
                        ":/image/icon/hover/pause_blue_hover.svg",
                        "",
                        ":/image/icon/focus/pause_blue_focus.svg"
                        );
        }

        if(nullptr != resumeButton)
        {
            resumeButton->setPicChange(
                        ":/image/icon/normal/play_normal.svg",
                        ":/image/icon/press/play_press.svg",
                        ":/image/icon/hover/play_hover.svg",
                        ":/image/icon/disabled/play_disabled.svg",
                        ":/image/icon/focus/play_focus.svg"
                        );
        }


    }
    else if(themeType == DGuiApplicationHelper::DarkType)
    {
        if(nullptr != pauseButton)
        {
            pauseButton->setPicChange(
                        ":/image/icon_dark/normal/pause_blue_normal_dark.svg",
                        ":/image/icon_dark/press/pause_blue_press_dark.svg",
                        ":/image/icon_dark/hover/pause_blue_hover_dark.svg",
                        "",
                        ":/image/icon_dark/focus/pause_blue_focus_dark.svg"
                        );
        }
        if(nullptr != resumeButton)
        {
            resumeButton->setPicChange(
                        ":/image/icon_dark/normal/play_normal_dark.svg",
                        ":/image/icon_dark/press/play_press_dark.svg",
                        ":/image/icon_dark/hover/play_hover_dark.svg",
                        ":/image/icon_dark/disabled/play_disabled_dark.svg",
                        ":/image/icon_dark/focus/play_focus_dark.svg"
                        );
        }
    }
}
