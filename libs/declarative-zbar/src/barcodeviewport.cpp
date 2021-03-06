/*
 * barcodeviewport.cpp
 *
 * Copyright (C) 2011  Imogen Software Carsten Valdemar Munk
 *
 * Author: Tom Swindell - <t.swindell@rubyx.co.uk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.#ifndef GRANDEWEBRUNTIME_H
 *
 */
#include "common.h"
#include "barcodeviewport.h"

#include <QPainter>

class BarcodeViewportPrivate
{
public:
    QImage currentFrame;
};

BarcodeViewport::BarcodeViewport(QDeclarativeItem *parent)
    : QDeclarativeItem(parent), d(new BarcodeViewportPrivate)
{
    TRACE
    this->setFlag(QGraphicsItem::ItemHasNoContents, false);
}

BarcodeViewport::~BarcodeViewport()
{
    TRACE
    delete this->d;
}

void BarcodeViewport::present(const QImage &frame)
{
    //TRACE
    d->currentFrame = frame;
    this->update(this->boundingRect());
}

void BarcodeViewport::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    //TRACE
    painter->drawImage(this->boundingRect(), d->currentFrame);
}
