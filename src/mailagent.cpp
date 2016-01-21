#include "mailagent.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>



//#define USE_GMAIL

#ifdef USE_GMAIL
#define POP3_SERVER "pop.gmail.com"
#else
#define POP3_SERVER "pop.yandex.ru"
#endif
#define POP3_PORT   995

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
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    mTimer.start(300000);
    onTimeout();
}

MailAgent::~MailAgent()
{
}

void MailAgent::onTimeout()
{
    qDebug() << "MailAgent::onTimeout()";

    static QString dir = QCoreApplication::applicationDirPath();

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
}
