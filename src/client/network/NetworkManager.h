//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#ifndef RTYPE_NETWORKMANAGER_H
#define RTYPE_NETWORKMANAGER_H

#include <vector>
#include <memory>
#include "NetworkCommunication.h"

namespace ge {
	namespace network {
		class NetworkManager {
		public:
			NetworkManager() = default;
			~NetworkManager() = default;
			NetworkManager(NetworkManager const &) = delete;
			NetworkManager(NetworkManager &&) = delete;

			NetworkManager &operator=(NetworkManager const &) = delete;
			NetworkManager &operator=(NetworkManager &&) = delete;

			void addCommuncation(std::shared_ptr<ge::network::NetworkCommunication> c);
			void removeCommuncation(std::shared_ptr<ge::network::NetworkCommunication> c);

			void shutdownGracefully();
			void handleSendEvent();
			void handleRecvEvent();

		private:
			std::vector<std::shared_ptr<ge::network::NetworkCommunication>> communications_;
		};
	}
}

#endif //RTYPE_NETWORKMANAGER_H
