#include "mainview.h"
#include "./ui_mainview.h"
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

static int PORT_NUMBER = 3000;
static int WAIT_FOR_DATA_MS = 200;

MainView::MainView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainView),
      m_server(new QTcpServer(this)),
      m_socket(nullptr)
{
    ui->setupUi(this);
    ui->btnStopServer->setEnabled(false);

    connect(m_server,&QTcpServer::newConnection,this, &MainView::ExchangeData);
}

MainView::~MainView()
{
    delete ui;
}


void MainView::on_btnStartServer_clicked()
{
    if (StartServer()) {
        qInfo("Server started and listening...");
        ui->btnStartServer->setEnabled(false);
        ui->btnStopServer->setEnabled(true);
    }
}

void MainView::on_btnStopServer_clicked()
{
    StopServer();
    ui->btnStartServer->setEnabled(true);
    ui->btnStopServer->setEnabled(false);

}

bool MainView::StartServer()
{
    bool result = m_server->listen(QHostAddress::Any, PORT_NUMBER);

    if (!result) {
        QMessageBox::critical(this,tr("Echo Server Error"),tr("Unable to Start Server %1").arg(m_server->errorString()));
        return false;
    }

    return true;
}

void MainView::StopServer()
{

    m_server->close();
    if (m_socket != nullptr && !m_socket->isOpen()) {
        disconnect(m_socket, &QTcpSocket::readyRead, this, &MainView::EchoReadData);
        m_socket->close();
    }
    qInfo("Server stopped.");
}

void MainView::ExchangeData(){
    m_socket = m_server->nextPendingConnection();
    if (m_socket->isOpen()) {
        connect(m_socket, &QTcpSocket::readyRead, this, &MainView::EchoReadData);
    }
}

void MainView::EchoReadData(){
    if (!m_server->isListening()) {
        m_socket->write("Server is not Listening");
        return;
    }
    m_socket->write("<echo-server>\n");
    QString result;
    while(!m_socket->atEnd()){
        result.append(m_socket->readAll());
        m_socket->waitForReadyRead(WAIT_FOR_DATA_MS);
    }
    m_socket->write(qPrintable(result));
    m_socket->write("</echo-server>\n");
}
