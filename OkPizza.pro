QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}\\\"\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    model/IDatabase.cpp \
    model/Ingredient.cpp \
    model/Pizza.cpp \
    model/database/FileDatabase.cpp \
    utils/Json.cpp \
    view/mainwindow.cpp

HEADERS += \
    model/IDatabase.hpp \
    model/Ingredient.hpp \
    model/Pizza.hpp \
    model/database/FileDatabase.hpp \
    utils/IJsonSerializable.hpp \
    utils/Json.hpp \
    view/mainwindow.hpp

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

OTHER_FILES += \
    Database/ingredients.json \
    Database/pizzas.json