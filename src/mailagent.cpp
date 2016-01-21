#include "mailagent.h"

#include <QCoreApplication>
#include <QDate>
#include <QDebug>
#include <QDir>



//#define USE_GMAIL

#ifdef USE_GMAIL
#define SMTP_SERVER "smtp.gmail.com"
#else
#define SMTP_SERVER "smtp.yandex.ru"
#endif
#define SMTP_PORT   465

#ifdef USE_GMAIL
#define USERNAME "Big.Bro.Tester.2016@gmail.com"
#else
#define USERNAME "Big.Bro.2016@yandex.ru"
#endif
#define PASSWORD "q1w2e3r4t5y6u7i8o9p0aqswdefrgthyjukilozaxscdvfbgnhmj,k.l"



MailAgent::MailAgent(QObject *parent)
    : QObject(parent)
{
    mProcess = 0;

    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    mTimer.start(300000);
    onTimeout();
}

MailAgent::~MailAgent()
{
    stopProcess();
}

void MailAgent::onTimeout()
{
    qDebug() << "MailAgent::onTimeout()";

    static QString dir = QCoreApplication::applicationDirPath();

    QString prevDate = "";
    QString curDate  = QDate::currentDate().toString("yyyy-MM-dd");

    QFile file(dir + "/time.dat");

    if (file.exists())
    {
        file.open(QIODevice::ReadOnly);
        prevDate = QString::fromUtf8(file.readAll());
        file.close();
    }

    if (curDate != prevDate)
    {
        stopProcess();



        QDir reportsDir(dir + "/Reports");
        QStringList files = reportsDir.entryList(QDir::Files, QDir::Time);

        if (files.length() > 0)
        {
            while (files.length() > 7)
            {
                files.removeAt(7);
            }

            qDebug() << "Sending files:" << files;

            for (int i = 0; i < files.length(); ++i)
            {
                files[i] = "Reports/" + files.at(i);
            }
        }



        QStringList arguments;

        arguments.append("-host:" USERNAME ":" PASSWORD "@" SMTP_SERVER ":" + QString::number(SMTP_PORT));
        arguments.append("-from:" USERNAME);
        arguments.append("-to:Gris87@yandex.ru");
        arguments.append("-subject:Report");
        arguments.append("-body:Hi");
        arguments.append("-secureport");

        for (int i = 0; i < files.length(); ++i)
        {
            arguments.append("-a64:" + files.at(i));
        }

        qDebug() << arguments;

        mProcess = new QProcess(this);
        mProcess->start(QCoreApplication::applicationDirPath() + "/CMail.exe", arguments);



        file.open(QIODevice::WriteOnly);
        file.write(curDate.toUtf8());
        file.close();
    }
}

void MailAgent::stopProcess()
{
    if (mProcess)
    {
        mProcess->kill();
        mProcess->waitForFinished();

        delete mProcess;
        mProcess = 0;
    }
}
