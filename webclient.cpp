#include "webclient.h"
#include<QString>
#include<QAbstractSocket>
#include<QTcpSocket>
#include<QDebug>
#include<QObject>
#include"ui_webclient.h"
#include<QColor>




Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void Webclient::connected()
{
    // connecting the socket


    m_socket->write(QString("GET / HTTP/1.1\r\nHost:"+ m_hostname+ "\r\n\r\n").toLocal8Bit());
}

void Webclient::readyRead()
{
    resultWindow->setText(m_socket->readAll());
    m_socket->disconnectFromHost();

}

void Webclient::on_go_clicked()
{
    m_socket = new QTcpSocket(this);
    m_hostname = inputHost->text();


    connect(m_socket,&QTcpSocket::connected,this, &Webclient::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::readyRead);

    m_socket->connectToHost(m_hostname, port);

    if(!m_socket->waitForConnected(5000))
    {
        resultWindow->setText("not connected");
    }
}
