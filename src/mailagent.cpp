#include "mailagent.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>



#define USERNAME "big.bro.2016@yandex.ru"
#define PASSWORD "q1w2e3r4t5y6u7i8o9p0aqswdefrgthyjukilozaxscdvfbgnhmj,k.l"



MailAgent::MailAgent(QObject *parent)
    : QObject(parent)
{
    mSmtp = new Smtp(USERNAME, PASSWORD, "smtp.yandex.ru", 465, 3000);

    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    mTimer.start(300000);
    onTimeout();
}

MailAgent::~MailAgent()
{
    delete mSmtp;
}

void MailAgent::onTimeout()
{
    qDebug() << "MailAgent::onTimeout()";

    static QString dir = QCoreApplication::applicationDirPath();

    QDir reportsDir(dir + "/Reports");
    QStringList files = reportsDir.entryList(QDir::Files, QDir::Time);

    while (files.length() > 7)
    {
        files.removeAt(7);
    }

    qDebug() << "Sending files:" << files;

    mSmtp->sendMail(USERNAME, "Gris87@yandex.ru", "Reports", "", files);
}
