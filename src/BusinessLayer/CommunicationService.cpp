#include "CommunicationService.h"
#include "View.h"
#include "PeripheralInterface.h"
#include "SerialPortPeripheral.h"
#include "QIODevice"
#include "QSerialPort"

/*--------------------------------------------------------
                Communication Service
    Initially sets up with a SerialPort connection unless
    specified otherwise.
--------------------------------------------------------*/

CommunicationService::CommunicationService(View& view)
:view_(view)
{
    setPeripheralSerialPort();
    connect(&view_, SIGNAL(attemptConnectionSignal()), this, SLOT(attemptConnection()));
}
void CommunicationService::setPeripheralSerialPort()
{
    outputDevice_(new QSerialPort());
    outputPeripheral_(new SerialPortPeripheral(outputDevice_));
}

PeripheralInterface& CommunicationService::getPeripheral()
{
    return outputPeripheral_;
}

void CommunicationService::attemptConnection()
{
    outputPeripheral_.setPortName(view_.getCommunicationPort());
    view_.setConnectionStatus(outputPeripheral_.attemptConnection());
}
