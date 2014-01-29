QT       += core gui

TARGET = UTimetableStudent
TEMPLATE = app

DESTDIR = ../bin

SOURCES += main.cpp\
        URangeTimes.cpp \
        QtJson/json.cpp \
    UTimetableStudentForm.cpp

HEADERS  += \
        URangeTimes.h \
        QtJson/json.h \
    UTimetableStudentForm.h \
    Global.h

OTHER_FILES += \
    ../bin/TimetableLessons - Нечетная неделя.json
