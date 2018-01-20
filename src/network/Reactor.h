//
// Created by Kévin POLOSSAT on 11/01/2018.
//

#ifndef LW_TCP_SERVER_REACTOR_H
#define LW_TCP_SERVER_REACTOR_H

#include <array>
#include <memory>
#include <unordered_map>
#include <queue>
#include <mutex>
#include "socket_operations.h"
#include "FDSet.h"
#include "Operation.h"

namespace lw_network {
class Reactor {
public:

    enum OperationType {
        read,
        write
    };

    using Handler = std::shared_ptr<Operation>;

    Reactor() = default;

    ~Reactor() = default;

    Reactor(Reactor const &other) = delete;

    Reactor(Reactor &&other) = delete;

    Reactor &operator=(Reactor const &other) = delete;

    Reactor &operator=(Reactor &&other) = delete;

    bool isRegistered(socket_type s, lw_network::Reactor::OperationType ot);

    void registerHandler(socket_type s, lw_network::Reactor::OperationType ot);

    void unregisterHandler(socket_type s, lw_network::Reactor::OperationType ot);

    void submit(socket_type s, Handler handler, lw_network::Reactor::OperationType ot);

    void handleEvents();
    void handleEvent(std::vector<std::shared_ptr<Operation>> & completions);
private:
    static constexpr int maxFdSets = 2;
    std::array<FDSet, maxFdSets> masters_;
    std::array<FDSet, maxFdSets> fdsets_;
    std::mutex mutex_;

    using OperationQueue = std::queue<Handler>;
    using Handlers = std::unordered_map<socket_type, OperationQueue>;
    std::array<Handlers, 2> handlers_;

    Handlers::iterator getRegistered_(socket_type s, lw_network::Reactor::OperationType ot);

    bool isRegistered_(Handlers::iterator const &it, lw_network::Reactor::OperationType ot);

    void handleOperation_(lw_network::Reactor::OperationType ot, std::vector<std::shared_ptr<Operation>> &completions);
    void completeOperations_(std::vector<std::shared_ptr<Operation>> & completions);
};
}

#endif //LW_TCP_SERVER_REACTOR_H
