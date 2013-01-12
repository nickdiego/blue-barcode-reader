symbian:TARGET.CAPABILITY += NetworkServices

# Mobility config
MOBILITY += connectivity

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += \
    bluetooth/hidstringsender.h \
    bluetooth/hidkeymapper.h

SOURCES += \
    bluetooth/hidstringsender.cpp \
    bluetooth/hidkeymapper.cpp

INCLUDEPATH += bluetooth
