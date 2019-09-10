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

#include "dimagebutton.h"

DWIDGET_USE_NAMESPACE

PlayingButton::PlayingButton(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    pauseButton = new DImageButton(
        ":/image/icon/normal/pause_blue_normal.svg",
        ":/image/icon/hover/pause_blue_hover.svg",
        ":/image/icon/press/pause_blue_press.svg"
        );
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePause()));

    resumeButton = new DImageButton(
        ":/image/icon/normal/play_normal.svg",
        ":/image/icon/hover/play_hover.svg",
        ":/image/icon/press/play_press.svg"
        );
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(handleResume()));

    layout->addWidget(resumeButton);
    //this->setStyleSheet("background: red");
}

void PlayingButton::handlePause() {
    layout->removeWidget(pauseButton);
    pauseButton->setParent(NULL);
    layout->addWidget(resumeButton);
    emit pause();
}

void PlayingButton::handleResume() {
    layout->removeWidget(resumeButton);
    resumeButton->setParent(NULL);
    layout->addWidget(pauseButton);
    emit resume();
}

void PlayingButton::handleStop() {
    layout->removeWidget(pauseButton);
    pauseButton->setParent(NULL);
    layout->addWidget(resumeButton);
    emit stop();
}
