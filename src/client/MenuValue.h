#ifndef MENUVALUE_H_
#define MENUVALUE_H_

#include "TcpProtocol.h"
#include "GameEngine.h"
#include "TCPNonBlockingCommunication.h"

namespace ge
{
  class MenuValue
  {
  public:
    MenuValue(std::shared_ptr<ge::network::TCPNonBlockingCommunication>  tcpConnection);
    ~MenuValue();
    rtype::protocol_tcp::GameInfo      i_game;
    rtype::protocol_tcp::CreateGame    c_game;
    rtype::protocol_tcp::JoinGameInfo  j_game;
    rtype::protocol_tcp::GameState     s_game;
    std::shared_ptr<ge::network::TCPNonBlockingCommunication> tcpConnection;
  };
}

#endif
