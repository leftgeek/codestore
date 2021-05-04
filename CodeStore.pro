# -------------------------------------------------
# Project created by QtCreator 2011-10-30T21:56:47
# -------------------------------------------------
QT += core \
    gui \
    xml \
    webkit \
    sql \
    network
TARGET = CodeStore
TEMPLATE = app
SOURCES += sources/main.cpp \
    sources/mainWindow.cpp \
    sources/widgets/tabWidget.cpp \
    sources/widgets/textEditor.cpp \
    sources/widgets/replaceWidget.cpp \
    sources/widgets/propertyWidget.cpp \
    sources/widgets/searchWidget.cpp \
    sources/widgets/newFileWidget.cpp \
    sources/highlighter.cpp \
    sources/widgets/importFileWidget.cpp \
    sources/codeTree.cpp \
    sources/widgets/codeTreeWidget.cpp \
    sources/database.cpp \
    sources/model/userModel.cpp \
    sources/model/categoryModel.cpp \
    sources/model/codeModel.cpp \
    sources/control/categoryControl.cpp \
    sources/control/userControl.cpp \
    sources/control/codeControl.cpp \
    sources/widgets/helpWidget.cpp \
    sources/widgets/loginWidget.cpp \
    sources/widgets/registerWidget.cpp \
    sources/widgets/modifyPasswordWidget.cpp \
    sources/widgets/findPasswordWidget.cpp \
    sources/logTree.cpp \
    sources/widgets/startPageWidget.cpp \
    sources/widgets/categoryPropertyWidget.cpp \
    sources/widgets/codePropertyWidget.cpp \
    sources/sendEmail.cpp \
    sources/widgets/newCategoryWidget.cpp \
    sources/widgets/personalCenterWidget.cpp \
    sources/widgets/developWidget.cpp \
    sources/widgets/newsWidget.cpp \
    sources/sync.cpp \
    sources/recentFile.cpp
HEADERS += headers/mainWindow.h \
    headers/searchWidget.h \
    headers/highlighter.h \
    headers/tabWidget.h \
    headers/textEditor.h \
    headers/replaceWidget.h \
    headers/propertyWidget.h \
    headers/newFileWidget.h \
    headers/importFileWidget.h \
    headers/codeTree.h \
    headers/codeTreeWidget.h \
    headers/database.h \
    headers/user.h \
    headers/category.h \
    headers/code.h \
    headers/helpWidget.h \
    headers/loginWidget.h \
    headers/registerWidget.h \
    headers/modifyPasswordWidget.h \
    headers/findPasswordWidget.h \
    headers/logTree.h \
    headers/startPageWidget.h \
    headers/personalCenterWidget.h \
    headers/newCategoryWidget.h \
    headers/categoryPropertyWidget.h \
    headers/codePropertyWidget.h \
    headers/sendEmail.h \
    headers/developWidget.h \
    headers/newsWidget.h \
    headers/sync.h \
    headers/recentFile.h
RESOURCES += resource.qrc
