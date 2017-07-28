TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $$PWD/build/bin/
MOC_DIR = $$PWD/build/moc/
OBJECTS_DIR = $$PWD/build/obj/

SOURCES += \
  src/main.cpp \
  src/gamepark.cpp \
  src/myeventreceiver.cpp \
  src/config/ini.cpp \
  src/config/inireader.cpp \
  src/config/config.cpp \
  src/player.cpp

HEADERS += \
  src/gamepark.h \
  src/myeventreceiver.h \
  src/config/ini.h \
  src/config/inireader.h \
  src/config/config.h \
  src/player.h

LIBS += -L/home/user/irrlicht-1.8.4/lib/Linux/ -lIrrlicht -lGL -lGLU -lXxf86vm -lXext -lX11


INCLUDEPATH += /home/user/irrlicht-1.8.4/include
INCLUDEPATH += src

OTHER_FILES += $$PWD/config/config.ini

