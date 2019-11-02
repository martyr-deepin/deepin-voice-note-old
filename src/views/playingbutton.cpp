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

#include "dimagebutton.h"

DWIDGET_USE_NAMESPACE

PlayingButton::PlayingButton(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    pauseButton = new DFloatingButton(this);
    pauseButton->setFixedSize(QSize(45, 45));
    pauseButton->setIcon(QIcon(":/image/icon/normal/pause_blue_normal.svg"));
    pauseButton->setIconSize(QSize(28,28));
    DPalette pa = DApplicationHelper::instance()->palette(pauseButton);
    pa.setBrush(DPalette::Highlight, QColor(0x000081FF));
    pauseButton->setPalette(pa);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePause()));
    resumeButton = new DFloatingButton(this);
    resumeButton->setFixedSize(QSize(45, 45));
    resumeButton->setIcon(QIcon(":/image/icon/normal/play_normal.svg"));
    resumeButton->setIconSize(QSize(28,28));
    DPalette pe = DApplicationHelper::instance()->palette(resumeButton);
    pe.setBrush(DPalette::Highlight, QColor(0x000081FF));
    resumeButton->setPalette(pe);
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(handleResume()));

    layout->addWidget(resumeButton);
    layout->addWidget(pauseButton);
    pauseButton->setVisible(false);
}

void PlayingButton::onlySetResumeForButton()
{
    pauseButton->setVisible(false);
    resumeButton->setVisible(true);
//    layout->removeWidget(pauseButton);
//    pauseButton->setParent(NULL);
//    layout->addWidget(resumeButton);

}
void PlayingButton::setPlayDiseable()
{
   if(nullptr != resumeButton)
   {
       resumeButton->setDisabled(true);
       resumeButton->setDown(true);
   }
}

void PlayingButton::setPlayEnable()
{
    if(nullptr != resumeButton)
    {
        resumeButton->setDisabled(false);
        resumeButton->setDown(false);
    }
}

void PlayingButton::handlePause() {
//    layout->removeWidget(pauseButton);
//    pauseButton->setParent(NULL);
//    layout->addWidget(resumeButton);
    pauseButton->setVisible(false);
    resumeButton->setVisible(true);
    emit pause();
}

void PlayingButton::handleResume() {
//    layout->removeWidget(resumeButton);
//    resumeButton->setParent(NULL);
//    layout->addWidget(pauseButton);
    pauseButton->setVisible(true);
    resumeButton->setVisible(false);
    emit resume();
}

void PlayingButton::handleStop() {
//    layout->removeWidget(pauseButton);
//    pauseButton->setParent(NULL);
//    layout->addWidget(resumeButton);
    pauseButton->setVisible(false);
    resumeButton->setVisible(true);
    emit stop();
}

