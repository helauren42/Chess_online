QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -L/usr/lib/x86_64-linux-gnu -lPocoFoundation -lPocoNet -lPocoUtil -lPocoXML -lPocoZip
INCLUDEPATH += /usr/include/Poco

SOURCES += \
    ../BackEnd/srcs/Utils.cpp \
    ../BackEnd/srcs/Board.cpp \
    ../BackEnd/srcs/Pieces.cpp \
    game.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    signup.cpp

HEADERS += \
    ../BackEnd/inc/Utils.hpp \
    ../BackEnd/inc/Board.hpp \
    ../BackEnd/inc/Pieces.hpp \
    common.hpp \
    game.hpp \
    login.hpp \
    mainwindow.hpp \
    menu.hpp \
    signup.hpp

FORMS += \
    game.ui \
    login.ui \
    mainwindow.ui \
    menu.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
