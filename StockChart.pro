QT += charts

TARGET = candlestickchart

SOURCES += main.cpp \
    candlestickdatareader.cpp \
    mainwindow.cpp

HEADERS += \
    candlestickdatareader.h \
    mainwindow.h

RESOURCES += \
    candlestickdata.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/charts/candlestickchart
INSTALLS += target

FORMS += \
    mainwindow.ui
