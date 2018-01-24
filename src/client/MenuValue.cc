#include "MenuValue.h"

ge::MenuValue::MenuValue(std::shared_ptr<ge::network::TCPNonBlockingCommunication> tcpConnect)
{
  tcpConnection = tcpConnect;
}

ge::MenuValue::~MenuValue()
{}
