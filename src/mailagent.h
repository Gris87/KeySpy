#ifndef MAILAGENT_H
#define MAILAGENT_H

#include <QObject>
#include <QTimer>



class MailAgent : public QObject
{
    Q_OBJECT
public:
    explicit MailAgent(QObject *parent = 0);
    ~MailAgent();

private:
    QTimer mTimer;

private slots:
    void onTimeout();
};

#endif // MAILAGENT_H
