#include "mailagent.h"

#include <QDebug>



MailAgent::MailAgent(QObject *parent)
    : QObject(parent)
{
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    mTimer.start(300000);

    onTimeout();
}

void MailAgent::onTimeout()
{
    qDebug() << "MailAgent::onTimeout()";

    // big.bro.2016@yandex.ru
    // q1w2e3r4t5y6u7i8o9p0aqswdefrgthyjukilozaxscdvfbgnhmj,k.l
}
