CONFIG += qtestlib unicorn moose
QT += testlib xml gui network
TEMPLATE = app
INCLUDEPATH += ..

include( $$SRC_DIR/common/qmake/include.pro )

SOURCES += TestStopWatch.cpp ../StopWatch.cpp
HEADERS += ../StopWatch.h