/*
 * barcodeviewport.h
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
#ifndef BARCODEVIEWPORT_H
#define BARCODEVIEWPORT_H

#include <QDeclarativeItem>

class BarcodeViewportPrivate;

class BarcodeViewport : public QDeclarativeItem
{
    Q_OBJECT

public:
    explicit BarcodeViewport(QDeclarativeItem *parent = 0);
            ~BarcodeViewport();

    void present(const QImage &frame);

protected:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

private:
    BarcodeViewportPrivate *d;
};

#endif // BARCODEVIEWPORT_H
