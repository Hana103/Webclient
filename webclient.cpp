#include "webclient.h"
#include<QAbstractSocket>
#include"ui_webclient.h"


Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void Webclient::connected()
{
    this->m_socket->write(QString("GET / HTTP/1.1\r\nHost:"+ m_hostname+ "\r\n\r\n").toLocal8Bit());
}

void Webclient::readyRead()
{

    resultWindow->setText("Success!\r\n"+ m_socket->readAll());
    m_socket->disconnectFromHost();

}

void Webclient::on_go_clicked()
{
    m_socket = new QTcpSocket(this);
    m_hostname = inputHost->text();

    connect(m_socket,&QTcpSocket::connected,this, &Webclient::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::readyRead);

    if(!inputHost->text().isEmpty())
    {
        m_socket->connectToHost(m_hostname, port);

        if(!m_socket->waitForConnected(5000))
        {
            resultWindow->setTextBackgroundColor(QColor("magenta"));
            resultWindow->setText("Not connected");
        }
        resultWindow->setTextBackgroundColor(QColor("white"));
    }

    if(inputHost->text().isEmpty())
    {
        resultWindow->setTextBackgroundColor(QColor("red"));
        resultWindow->setText("Please enter a hostname!");
    }

}
