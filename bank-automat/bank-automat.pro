QT       += core gui
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asiakas.cpp \
    kortti.cpp \
    main.cpp \
    mainwindow.cpp \
    nosto.cpp \
    pankki.cpp \
    saldo.cpp \
    talletus.cpp \
    tili.cpp \
    tilitap.cpp \

HEADERS += \
    asiakas.h \
    kortti.h \
    mainwindow.h \
    nosto.h \
    pankki.h \
    saldo.h \
    talletus.h \
    tili.h \
    tilitap.h \


FORMS += \
    asiakas.ui \
    kortti.ui \
    mainwindow.ui \
    nosto.ui \
    pankki.ui \
    saldo.ui \
    talletus.ui \
    tili.ui \
    tilitap.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../RFID_DLL/build/debug/ -lRFID_DLL

INCLUDEPATH += $$PWD/../RFID_DLL
DEPENDPATH += $$PWD/../RFID_DLL


win32: LIBS += -L$$PWD/../pinUI_DLL/build/debug/ -lpinUI_DLL

INCLUDEPATH += $$PWD/../pinUI_DLL
DEPENDPATH += $$PWD/../pinUI_DLL


win32: LIBS += -L$$PWD/../pinUI_DLL/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/ -lpinUI_DLL

INCLUDEPATH += $$PWD/../pinUI_DLL
DEPENDPATH += $$PWD/../pinUI_DLL

win32: LIBS += -L$$PWD/../RFID_DLL/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/ -lRFID_DLL

INCLUDEPATH += $$PWD/../RFID_DLL
DEPENDPATH += $$PWD/../RFID_DLL

win32: LIBS += -L$$PWD/../restapi_DLL/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/ -lrestapi_DLL

INCLUDEPATH += $$PWD/../restapi_DLL
DEPENDPATH += $$PWD/../restapi_DLL


win32: LIBS += -L$$PWD/../restapi_DLL/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/ -lrestapi_DLL

win32: LIBS += -L$$PWD/../restapi_DLL/build/debug/ -lrestapi_DLL


INCLUDEPATH += $$PWD/../restapi_DLL
DEPENDPATH += $$PWD/../restapi_DLL


