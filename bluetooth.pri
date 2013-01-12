# Add more folders to ship with the application, here

# TODO: Keeping separate for now, till camera/zxing is
#       not fully integrated in the project
# TODO: Add qmls to a .qrc file
#qml.source = qml/bluebarcode-reader
#qml.target = qml
#DEPLOYMENTFOLDERS = qml

symbian:TARGET.CAPABILITY += NetworkServices
# Speed up launching on MeeGo/Harmattan when using applauncherd daemon

CONFIG += qdeclarative-boostable

# Mobility config
MOBILITY += connectivity

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += \
    src/bluetooth/hidstringsender.h \
    src/bluetooth/hidkeymapper.h

SOURCES += \
    src/bluetooth/hidstringsender.cpp \
    src/bluetooth/hidkeymapper.cpp

INCLUDEPATH += src src/bluetooth
