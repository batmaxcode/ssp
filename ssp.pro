TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

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
  src/player.cpp \
  src/RealisticWater.cpp \
  src/childsquarenode.cpp \
  src/collision.cpp \
  src/abstractscenenode.cpp \
  src/fountainsquarenode.cpp \
  src/common.cpp \
  src/attractionsquarenode.cpp \
  src/grass/TKGrassSceneNode.cpp \
  src/churchscenenode.cpp \
  src/hotelscenenode.cpp

HEADERS += \
  src/gamepark.h \
  src/myeventreceiver.h \
  src/config/ini.h \
  src/config/inireader.h \
  src/config/config.h \
  src/player.h \
  src/RealisticWater.h \
  src/postprocessmotionblur.h \
  src/childsquarenode.h \
  src/collision.h \
  src/abstractscenenode.h \
  src/fountainsquarenode.h \
  src/common.h \
  src/attractionsquarenode.h \
  src/grass/TKGrassSceneNode.h \
  src/grass/TKGrassSceneNode_ShaderCB.h \
  src/churchscenenode.h \
  src/hotelscenenode.h

LIBS += -L../../irrlicht-1.8.4/lib/Linux/ -lIrrlicht -lGL -lGLU -lXxf86vm -lXext -lX11
LIBS += -L../../irrKlang-64bit-1.5.0/bin/linux-gcc-64/ -lIrrKlang
#LIBS += -L../../irrlicht-1.7.3/lib/Linux/ -lIrrlicht -lGL -lGLU -lXxf86vm -lXext -lX11


INCLUDEPATH += ../../irrlicht-1.8.4/include
INCLUDEPATH += ../../irrKlang-64bit-1.5.0/include
#INCLUDEPATH += ../../irrlicht-1.7.3/include
INCLUDEPATH += src

OTHER_FILES += $$PWD/config/config.ini

