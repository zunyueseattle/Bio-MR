#include "Biomr.h"

#include <QNetworkDatagram>

Biomr::Biomr(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	// Set up sockets
	m_pIMotionsListener = new QUdpSocket();
	m_pIMotionsListener->bind(QHostAddress::LocalHost, RECEIVE_FROM_IMOTIONS_PORT);
	connect(m_pIMotionsListener, &QUdpSocket::readyRead, this, &Biomr::ReadImotionsDatagrams);

	m_pGameEngineSender = new QUdpSocket();
}




// Reading from Imotions
void Biomr::ReadImotionsDatagrams()
{
	while (m_pIMotionsListener->hasPendingDatagrams()) 
	{
		QNetworkDatagram datagram = m_pIMotionsListener->receiveDatagram();
		ProcessImotionsDatagram(datagram);
	}
}
void Biomr::ProcessImotionsDatagram(QNetworkDatagram& datagram)
{
	QByteArray& rawData = datagram.data();
	QString dataString = QString::fromUtf8(rawData);
	QStringList splitData = dataString.split(";");

	QString response = "RainIntensity;1;";
	SendGameEngineDatagram(response);
}


// Sending to game engine
void Biomr::SendGameEngineDatagram(QString& datagram)
{
	QByteArray& rawData = datagram.toUtf8();
	m_pGameEngineSender->writeDatagram(rawData, QHostAddress::LocalHost, SEND_TO_GAME_ENGINE_PORT);
}