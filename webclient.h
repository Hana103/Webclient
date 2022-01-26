#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "ui_webclient.h"
#include<QTcpSocket>
#include<QString>


class Webclient : public QWidget, private Ui::Webclient
{
    Q_OBJECT

public:
    explicit Webclient(QWidget *parent = nullptr);

private slots:
    void on_go_clicked();

public slots:
    void connected();
    void readyRead();

private:
    QTcpSocket *m_socket;

    QString m_hostname;
    const unsigned short port= 80;

};

#endif // WEBCLIENT_H
