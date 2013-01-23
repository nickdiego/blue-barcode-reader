/*
 * barcodereader.cpp
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

#include "barcodereader.h"
#include "barcodevideoprocessor.h"

#include "zbar.h"

#include <QCamera>
#include <QVideoRendererControl>

class BarcodeReaderPrivate
{
    Q_DECLARE_PUBLIC(BarcodeReader)
public:
    BarcodeReaderPrivate(BarcodeReader* const q);

    void _q_camera_error(QCamera::Error);
    void _q_camera_state_changed(QCamera::State);

    BarcodeReader* const q_ptr;
    QCamera camera;

    // TODO: Pass a reference to "BarcodeReader" to
    // processor, to be used to select appropriate
    // frames based on "camera" status, etc..
    BarcodeVideoProcessor processor;
};

BarcodeReaderPrivate::BarcodeReaderPrivate(BarcodeReader* const q) :
    q_ptr(q),
    camera(q),
    processor(q)
{
    TRACE

    QVideoRendererControl* control = NULL;

    this->camera.setCaptureMode(QCamera::CaptureVideo);

    control = qobject_cast<QVideoRendererControl*>(this->camera.service()->requestControl("com.nokia.Qt.QVideoRendererControl/1.0"));
    control->setSurface(&this->processor);

    QObject::connect(&this->camera, SIGNAL(error(QCamera::Error)), q, SLOT(_q_camera_error(QCamera::Error)));
    QObject::connect(&this->processor, SIGNAL(decode(int,QString)), q, SIGNAL(decode(int,QString)));
    QObject::connect(&this->camera, SIGNAL(stateChanged(QCamera::State)), q, SLOT(_q_camera_state_changed(QCamera::State)));
    QObject::connect(&this->camera, SIGNAL(statusChanged(QCamera::Status)), q, SIGNAL(statusChanged(QCamera::Status)));
    QObject::connect(&this->camera, SIGNAL(captureModeChanged(QCamera::CaptureMode)), q, SIGNAL(captureModeChanged(QCamera::CaptureMode)));
    QObject::connect(&this->camera, SIGNAL(lockStatusChanged(QCamera::LockStatus, QCamera::LockChangeReason)), q, SIGNAL(lockStatusChanged(QCamera::LockStatus, QCamera::LockChangeReason)));
    QObject::connect(&this->camera, SIGNAL(lockStatusChanged(QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason)), q, SIGNAL(lockStatusChanged(QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason)));
}

BarcodeReader::BarcodeReader(QObject *parent)
    : QObject(parent), d_ptr(new BarcodeReaderPrivate(this))
{
    TRACE
}

BarcodeReader::BarcodeReader(BarcodeReaderPrivate &dd, QObject *parent)
    : QObject(parent), d_ptr(&dd)
{
    TRACE
}

BarcodeReader::~BarcodeReader()
{
    TRACE
}

BarcodeViewport* BarcodeReader::viewport() const
{
    TRACE
    Q_D(const BarcodeReader);

    return d->processor.viewport();
}

void BarcodeReader::setViewport(BarcodeViewport *viewport)
{
    TRACE
    Q_D(BarcodeReader);

    return d->processor.setViewport(viewport);
}

bool BarcodeReader::enabled() const
{
    Q_D(const BarcodeReader);

    return d->processor.enabled();
}

void BarcodeReader::setEnabled(bool enabled)
{
    Q_D(BarcodeReader);

    d->processor.setEnabled(enabled);
    emit enabledChanged();
}

BarcodeReader::State BarcodeReader::state() const
{
    TRACE
    Q_D(const BarcodeReader);

    switch (d->camera.state())
    {
        case QCamera::UnloadedState:
        case QCamera::LoadedState:
            return BarcodeReader::Idle;
        case QCamera::ActiveState:
            return BarcodeReader::CapturingImages;
    }

    return BarcodeReader::Idle;
}

QCamera::Status BarcodeReader::status() const
{
    TRACE
    Q_D(const BarcodeReader);

    return d->camera.status();
}

QCamera::CaptureMode BarcodeReader::captureMode() const
{
    TRACE
    Q_D(const BarcodeReader);

    return d->camera.captureMode();
}

QCamera::LockStatus BarcodeReader::lockStatus() const
{
    TRACE
    Q_D(const BarcodeReader);

    return d->camera.lockStatus();
}

QCamera::LockStatus BarcodeReader::lockStatus(QCamera::LockType lock) const
{
    TRACE
    Q_D(const BarcodeReader);

    return d->camera.lockStatus(lock);
}

void BarcodeReader::start()
{
    TRACE
    Q_D(BarcodeReader);

    d->camera.start();
}

void BarcodeReader::stop()
{
    TRACE
    Q_D(BarcodeReader);

    d->camera.stop();
    d->processor.stop();
}

int BarcodeReader::set_config(const QString& cfgstr)
{
    TRACE
    Q_D(BarcodeReader);

    return d->processor.set_config(cfgstr);
}

void BarcodeReaderPrivate::_q_camera_error(QCamera::Error)
{
    TRACE

    qDebug() << "*** ERROR" << this->camera.errorString();
}

void BarcodeReaderPrivate::_q_camera_state_changed(QCamera::State state)
{
    TRACE
    Q_Q(BarcodeReader);

    switch (state)
    {
        case QCamera::UnloadedState:
        case QCamera::LoadedState:
            return emit q->stateChanged(BarcodeReader::Idle);
        case QCamera::ActiveState:
            return emit q->stateChanged(BarcodeReader::CapturingImages);
    }
}

#include "moc_barcodereader.cpp"
