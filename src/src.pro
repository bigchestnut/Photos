QT += core gui widgets

CONFIG += c++11

# 将SDK文件夹添加到src工程的全局引用
INCLUDEPATH += sdk

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sdk/albumtitle.cpp \
    sdk/albumlistcontent.cpp \
    sdk/albumlistview.cpp \
    sdk/albumlistmodel.cpp \
    sdk/albumglobal.cpp \
    sdk/albummodel.cpp \
    sdk/albumbadimagemodel.cpp \
    sdk/albumproxymodel.cpp \
    sdk/albumcamerarollmodel.cpp \
    sdk/albumbadimagepicker.cpp \
    sdk/albumimagelistview.cpp \
    plugin/albumbadexposedetect/albumbadexposedetect.cpp \
    sdk/albumimagefinder.cpp

HEADERS += \
    mainwindow.h \
    sdk/albumtitle.h \
    sdk/albumlistcontent.h \
    sdk/albumlistview.h \
    sdk/albumlistmodel.h \
    sdk/albumglobal.h \
    sdk/albummodel.h \
    sdk/albumbadimagemodel.h \
    sdk/albumproxymodel.h \
    sdk/albumcamerarollmodel.h \
    sdk/albumbadimagepicker.h \
    sdk/albumbadimagechecker.h \
    sdk/albumimagelistview.h \
    plugin/albumbadexposedetect/albumbadexposedetect.h \
    sdk/albumimagefinder.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    res/resource.qrc
