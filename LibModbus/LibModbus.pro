include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_modbus)

QT -= gui
QT += qml

# Configure the library for building
VER_MAJ = $$CUTEHMI_MODBUS_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_MODBUS_BUILD
DEFINES += CUTEHMI_MODBUS_DYNAMIC
#CONFIG += dynamic

# Translations.
TRANSLATIONS = locale/cutehmi_base_pl.ts

include(../cutehmi_base.pri)
include(../libmodbus.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/modbus/AbstractConnection.cpp \
    src/modbus/Client.cpp \
    src/modbus/Exception.cpp \
    src/modbus/functions.cpp \
    src/modbus/HoldingRegister.cpp \
    src/modbus/InputRegister.cpp \
    src/modbus/RTUConnection.cpp \
    src/modbus/TCPConnection.cpp \
    src/modbus/CommunicationThread.cpp \
    src/modbus/ClientRunner.cpp \
    src/modbus/NodeDataObject.cpp \
    src/modbus/VisitorDelegate.cpp \
    src/modbus/UIVisitorDelegateHolder.cpp

HEADERS += \
    src/platform.hpp \
    src/modbus/AbstractConnection.hpp \
    src/modbus/Client.hpp \
    src/modbus/Exception.hpp \
    src/modbus/functions.hpp \
    src/modbus/HoldingRegister.hpp \
    src/modbus/InputRegister.hpp \
    src/modbus/RegisterTraits.hpp \
    src/modbus/RTUConnection.hpp \
    src/modbus/TCPConnection.hpp \
    src/modbus/CommunicationThread.hpp \
    src/modbus/ClientRunner.hpp \
    src/modbus/NodeDataObject.hpp \
    src/modbus/VisitorDelegate.hpp \
    src/modbus/UIVisitorDelegateHolder.hpp

DISTFILES +=

RESOURCES +=