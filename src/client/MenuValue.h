#ifndef MENUVALUE_H_
#define MENUVALUE_H_

#include "TcpProtocol.h"
#include "GameEngine.h"
#include "TCPNonBlockingCommunication.h"
#include "GameConfiguration.h"

namespace ge
{
  class MenuValue
  {
  public:
      ~MenuValue() = default;
    static MenuValue& Instance();

    rtype::protocol_tcp::QueryCreateGame  c_game;
    rtype::protocol_tcp::QueryJoinGame    j_game;
    rtype::protocol_tcp::QueryList        l_game;
    std::vector<std::string>              games;
	std::vector<rtype::protocol_tcp::GameInfo> gi;
    std::shared_ptr<ge::network::TCPNonBlockingCommunication> tcpConnection;
    std::string  Port;

      GameConfiguration const & getGameConfiguration() const;
  private:
      GameConfiguration configuration_;
      MenuValue() = default;
      MenuValue(MenuValue const &) = delete;
      MenuValue(MenuValue &&) = delete;
      MenuValue & operator = (MenuValue const &) = delete;
      MenuValue & operator = (MenuValue &&) = delete;
  };
}

#endif
