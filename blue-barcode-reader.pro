TEMPLATE = app
TARGET = bluebarcodereader

# Add more folders to ship with the application, here
qml.source = qml/bluebarcodereader
qml.target = qml
DEPLOYMENTFOLDERS = qml

symbian:TARGET.UID3 = 0xE96EF9BF

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices
# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable
CONFIG += mobility
MOBILITY += connectivity

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += \
    src/bluetooth/hidstringsender.h \
    src/bluetooth/hidkeymapper.h

SOURCES += \
    src/main.cpp \
    src/bluetooth/hidstringsender.cpp \
    src/bluetooth/hidkeymapper.cpp

INCLUDEPATH += src src/bluetooth

include($$PWD/libs/libs.pri)
include(qmlapplicationviewer/qmlapplicationviewer.pri)

qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
