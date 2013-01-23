/*
 * barcodereader.h
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
#ifndef BARCODEREADER_H
#define BARCODEREADER_H

#include "barcodeviewport.h"

#include <QObject>
#include <QCamera>
#include <QScopedPointer>

class BarcodeReaderPrivate;

class BarcodeReader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BarcodeViewport *viewport READ viewport WRITE setViewport)
    Q_PROPERTY(BarcodeReader::State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QCamera::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QCamera::CaptureMode captureMode READ captureMode NOTIFY captureModeChanged)
    Q_PROPERTY(QCamera::LockStatus lockStatus READ lockStatus NOTIFY lockStatusChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    Q_ENUMS(State)
public:
    enum State
    {
        Idle,
        CapturingImages,
    };

    explicit BarcodeReader(QObject *parent = 0);
            ~BarcodeReader();

    BarcodeViewport* viewport() const;
    void setViewport(BarcodeViewport *viewport);

    State state() const;
    QCamera::Status status() const;
    QCamera::CaptureMode captureMode() const;
    QCamera::LockStatus lockStatus() const;
    QCamera::LockStatus lockStatus(QCamera::LockType lock) const;

    bool enabled() const;
    void setEnabled(bool enabled);

Q_SIGNALS:
    void stateChanged(BarcodeReader::State);
    void statusChanged(QCamera::Status);
    void captureModeChanged(QCamera::CaptureMode);
    void lockStatusChanged(QCamera::LockStatus, QCamera::LockChangeReason);
    void lockStatusChanged(QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason);
    void enabledChanged();

    void decode(int type, const QString &data);

public Q_SLOTS:
    void start();
    void stop();

    /// set config parsed from configuration string.
    /// @see zbar_image_scanner_parse_config()
    /// @since 0.4
    int set_config (const QString& cfgstr);

protected:
    const QScopedPointer<BarcodeReaderPrivate> d_ptr;
    BarcodeReader(BarcodeReaderPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(BarcodeReader)
    Q_DECLARE_PRIVATE(BarcodeReader)
    Q_PRIVATE_SLOT(d_func(), void _q_camera_error(QCamera::Error))
    Q_PRIVATE_SLOT(d_func(), void _q_camera_state_changed(QCamera::State))
};

#endif // BARCODEREADER_H
