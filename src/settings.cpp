#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject(parent)
    , m_orientation(Settings::PortraitOrientation)
{
}

Settings::Orientation Settings::orientation() const
{
    return m_orientation;
}

void Settings::setOrientation(Settings::Orientation orientation)
{
    if (m_orientation != orientation) {
        m_orientation = orientation;

        emit orientationChanged();
    }
}
