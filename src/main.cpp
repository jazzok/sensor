#include <QApplication>
#include <QLocale>
#include <QTranslator>
//#include <QTextCodec>
#include <QDateTime>
#include <QFile>
#include <QIODevice>

#include "cmainwindow.h"

/*
 *
 */
void messageToFile(QtMsgType                type,
                   const QMessageLogContext &context,
                   const QString            &msg)
{
    QString fileName;
    fileName = "log-";
    fileName += QDateTime::currentDateTime().toString("yyyy_MM_dd");
    fileName += ".log";
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    switch (type) {
    case QtDebugMsg:
        out << " [[ Debug ]] " << msg  << " >> " << context.file;
        break;
    case QtInfoMsg:
        out << " [[ Info ]] " << msg << " >> " << context.file;
        break;
    case QtWarningMsg:
        out << " [[ Warning ]] " << msg << " >> " << context.file;
        break;
    case QtCriticalMsg:
        out << " [[ QtCriticalMsg ]] " << msg << " >> " << context.file;
        break;
    case QtFatalMsg:
        out << " [[ Fatal ]] " << msg << " >> " <<  context.file;
        break;
//    case QtSystemMsg:
//        out << "Debug: " << msg << context.file << endl;
//        break;
//    default:
//        out << "[[ Unknown ]] " << msg << " >> " <<  context.file << endl;
//        break;
    }
}

int main(int argc, char *argv[])
{
// Создание приложения
    QApplication app(argc, argv);
//    qInstallMessageHandler(messageToFile);
//
    QCoreApplication::setOrganizationName("Continent");
    QCoreApplication::setOrganizationDomain("continet.com");
    QCoreApplication::setApplicationName("Navigator");
    Q_INIT_RESOURCE(res);
// Установка кодеков проекта
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));
#ifdef Q_OS_WIN
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP866"));
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
#endif

// Установка русификации Qt
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "LoginIN_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
// Установка стиля приложения
    QApplication::setStyle("windows");

// Создание главного окна
    CMainWindow mainWindows;
    mainWindows.show();

// Запуск приложения
    return app.exec();
}
