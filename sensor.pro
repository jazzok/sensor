QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(src/src.pri)

#RESOURCES = src/res/res.qrc
# Определение каталогов для версии Debug
CONFIG(debug, debug|release){
        message(***** Debug bulid!!! *****)
        unix: {	MOC_DIR =		 ./build/debug/unix/moc
                        OBJECTS_DIR =	 ./build/debug/unix/obj
                        RCC_DIR =		 ./build/debug/unix/res
                        UI_HEADERS_DIR = ./build/debug/unix/ui
                        DESTDIR =		 ./final/debug/unix
        }
        else: {	MOC_DIR =		 ./build/debug/windows/moc
                        OBJECTS_DIR =	 ./build/debug/windows/obj
                        RCC_DIR =		 ./build/debug/windows/res
                        UI_HEADERS_DIR = ./build/debug/windows/ui
                        DESTDIR =		 ./final/debug/windows
        }
}

# Определение каталогов для версии Release
CONFIG(release, debug|release){
        message(***** Release build!!! *****)
        unix: {	MOC_DIR =		 ./build/release/unix/moc
                        OBJECTS_DIR =	 ./build/release/unix/obj
                        RCC_DIR =		 ./build/release/unix/res
                        UI_HEADERS_DIR = ./build/release/unix/ui
                        DESTDIR =		 ./final/release/unix
        }
        else: {	MOC_DIR =		 ./build/release/windows/moc
                        OBJECTS_DIR =	 ./build/release/windows/obj
                        RCC_DIR =		 ./build/release/windows/res
                        UI_HEADERS_DIR = ./build/release/windows/ui
                        DESTDIR =		 ./final/release/windows
        }
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
