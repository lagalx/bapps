QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addlistitemdialog.cpp \
    crypton.cpp \
    listitemwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    passwordparser.cpp \
    passwordswindow.cpp

HEADERS += \
    addlistitemdialog.h \
    crypton.h \
    listitemwidget.h \
    mainwindow.h \
    passwordparser.h \
    passwordswindow.h

FORMS += \
    addlistitemdialog.ui \
    listitemwidget.ui \
    mainwindow.ui \
    passwordswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# Qt-Secret
include($$PWD/../Qt-Secret/src/Qt-Secret.pri)

# Выбираем директорию сборки исполняемого файла
# в зависимости от режима сборки проекта
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

COMMON_DIR = $$OUT_PWD/common
# разделяем по директориям все выходные файлы проекта
MOC_DIR = $$COMMON_DIR/moc
RCC_DIR = $$COMMON_DIR/rcc
UI_DIR = $$COMMON_DIR/ui

unix:OBJECTS_DIR = $$COMMON_DIR/o/unix
win32:OBJECTS_DIR = $$COMMON_DIR/o/win32
macx:OBJECTS_DIR = $$COMMON_DIR/o/mac

# Добавляем модуль file_copies
CONFIG += file_copies

# Добавляем переменную, описывающую копируемые файлы
COPIES +=   \
            qt_secret \
            debug_protector \

QT_SECRET_DIR = $$PWD/../Qt-Secret
QT_SECRET_MINI_GMP = $$QT_SECRET_DIR/src/mini-gmp/src/build
QT_SECRET_BUILD = $$QT_SECRET_DIR/src/build

PROTECTOR_DIR = $$OUT_PWD/../DebugProtector

# в зависимости от режима сборки проекта
# запускаем win deploy приложения в целевой директории, то есть собираем все dll
CONFIG(debug, debug|release) {
    PROTECTOR_DIR = $$PROTECTOR_DIR/debug
    QT_SECRET_MINI_GMP = $$QT_SECRET_MINI_GMP/debug
    QT_SECRET_BUILD = $$QT_SECRET_BUILD/debug
} else {
    PROTECTOR_DIR = $$PROTECTOR_DIR/release
    QT_SECRET_MINI_GMP = $$QT_SECRET_MINI_GMP/release
    QT_SECRET_BUILD = $$QT_SECRET_BUILD/release

    QMAKE_POST_LINK += $$(QTDIR)/bin/windeployqt $$DESTDIR
}

# Определяем, с каким расширением нам необохдимо скопировать файлы и по какому пути они расположены
debug_protector.files = $$files($$PROTECTOR_DIR/*.exe)

qt_secret.files += $$files($$QT_SECRET_MINI_GMP/*.dll)
qt_secret.files += $$files($$QT_SECRET_BUILD/*.dll)

# Указываем путь, куда копировать файлы
qt_secret.path = $$DESTDIR
debug_protector.path = $$DESTDIR

