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
    static MenuValue& Instance();

    rtype::protocol_tcp::QueryCreateGame  c_game;
    rtype::protocol_tcp::QueryJoinGame    j_game;
    rtype::protocol_tcp::QueryList        l_game;
    std::vector<std::string>              games;
	std::vector<rtype::protocol_tcp::GameInfo> gi;
    std::shared_ptr<ge::network::TCPNonBlockingCommunication> tcpConnection;
    std::string  Port;
    MenuValue();
    ~MenuValue();
  private:
    MenuValue& operator= (const MenuValue&){}
    MenuValue (const MenuValue&);
    static MenuValue m_instance;
  };
}

#endif
