//
// Created by Kévin POLOSSAT on 13/01/2018.
//

#ifndef LW_TCP_SERVER_BUFFER_H
#define LW_TCP_SERVER_BUFFER_H

#include <cstddef>
#include "socket_operations.h"

namespace lw_network {
class Buffer {
public:
    Buffer(void * data, std::size_t size);

    void *Data();
    void const *Data() const;
    void SetData(void *data);

    std::size_t Size() const;
    void reSize(std::size_t size);

    Buffer &operator += (std::size_t nbyte);
    bool exhausted() const;
private:
    void *data_;
    std::size_t size_;
};
}

#endif //LW_TCP_SERVER_BUFFER_H
