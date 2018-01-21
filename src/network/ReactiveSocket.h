//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#ifndef LW_TCP_SERVER_SOCKET_H
#define LW_TCP_SERVER_SOCKET_H

#include <memory>
#include "Socket.h"
#include "Reactor.h"
#include "Buffer.h"

namespace lw_network {
class ReactiveSocket: public Socket {
public:
    explicit ReactiveSocket(Reactor & reactor);
    ~ReactiveSocket() = default;
    ReactiveSocket(ReactiveSocket const & other) = default;
    ReactiveSocket(ReactiveSocket && other) = default;

    ReactiveSocket & operator = (ReactiveSocket const & other);
    ReactiveSocket & operator = (ReactiveSocket && other);

    void close();
    void async_read_some(Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);
    void async_read(Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);

    void async_write_some(Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);
    void async_write(Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);

private:
    Reactor & reactor_;
};

// TODO FACTORIZE
class ReadOperation: public Operation {
public:
    ReadOperation(ReactiveSocket & s, Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);
    bool handle();
    void complete();
private:
    ReactiveSocket & s_;
    error_code ec_;
    std::size_t nbyte_;
    Buffer b_;
    std::function<void(std::size_t nbyte, error_code ec)> completionHandler_;
};

class WriteOperation: public Operation {
public:
    WriteOperation(ReactiveSocket & s, Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);
    bool handle();
    void complete();
private:
    ReactiveSocket & s_;
    error_code ec_;
    std::size_t nbyte_;
    Buffer b_;
    std::function<void(std::size_t nbyte, error_code ec)> completionHandler_;
};

class ReadSomeOperation: public Operation {
public:
    ReadSomeOperation(ReactiveSocket & s, Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);
    bool handle();
    void complete();
private:
    ReactiveSocket & s_;
    error_code ec_;
    std::size_t nbyte_;
    Buffer b_;
    std::function<void(std::size_t nbyte, error_code ec)> completionHandler_;
};

class WriteSomeOperation: public Operation {
public:
    WriteSomeOperation(ReactiveSocket & s, Buffer b, std::function<void(std::size_t nbyte, error_code ec)> completionHandler);
    bool handle();
    void complete();
private:
    ReactiveSocket & s_;
    error_code ec_;
    std::size_t nbyte_;
    Buffer b_;
    std::function<void(std::size_t nbyte, error_code ec)> completionHandler_;
};
}

#endif //LW_TCP_SERVER_SOCKET_H
