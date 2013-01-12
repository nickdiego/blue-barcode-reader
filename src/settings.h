#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QObject>

class Settings : public QObject
{
    Q_OBJECT
    Q_ENUMS(Orientation)
    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

public:
    enum Orientation {
        LandscapeOrientation,
        PortraitOrientation,
        AutoOrientation
    };

    Settings(QObject *parent = 0);

    Orientation orientation() const;
    void setOrientation(Orientation newOrientation);

signals:
    void orientationChanged();

private:
    Orientation m_orientation;
};

#endif
