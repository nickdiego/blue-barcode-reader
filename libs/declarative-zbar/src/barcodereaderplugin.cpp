/*
 * barcodereaderplugin.cpp
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
#include "barcodereaderplugin.h"

#include "barcodereader.h"
#include "barcodeviewport.h"

void BarcodeReaderPlugin::registerTypes(const char *uri)
{
    TRACE

    if(QString(uri) == "stage.rubyx.BarcodeReader")
    {
        qmlRegisterType<BarcodeReader>(uri, 1, 0, "BarcodeReader");
        qmlRegisterType<BarcodeViewport>(uri, 1, 0, "BarcodeViewport");
    }
}

Q_EXPORT_PLUGIN2(barcodereaderplugin, BarcodeReaderPlugin)
