//
// Created by Kévin POLOSSAT on 13/01/2018.
//

#include <algorithm>
#include <iostream>
#include "Buffer.h"

lw_network::Buffer::Buffer(void *data, std::size_t size): data_(data), size_(size) {}

void *lw_network::Buffer::Data() {
    return data_;
}

void const *lw_network::Buffer::Data() const {
    return data_;
}

void lw_network::Buffer::SetData(void *data) {
    data_ = data;
}

std::size_t lw_network::Buffer::Size() const {
    return size_;
}

void lw_network::Buffer::reSize(std::size_t size) {
    size_ = size;
}

lw_network::Buffer &lw_network::Buffer::operator+=(std::size_t nbyte) {
    std::size_t offset = (nbyte < size_ ? nbyte : size_);
    data_ = static_cast<char *>(data_) + offset;
    size_ -= offset;
    return *this;
}

bool lw_network::Buffer::exhausted() const {
    return size_ == 0;
}

io_buffer lw_network::Buffer::toIoBuffer() const {
#if defined (__linux__) || defined (__APPLE__)
	return io_buffer{const_cast<void *>(this->Data()), this->Size()};
#elif defined (_WIN32) || defined (_WIN64)
	return io_buffer{ this->Size(), static_cast<char *>(const_cast<void *>(this->Data())) };
#else
#error "unknown platform"
#endif

}

io_buffer lw_network::Buffer::toIoBuffer() {
#if defined (__linux__) || defined (__APPLE__)
    return io_buffer{this->Data(), this->Size()};
#elif defined (_WIN32) || defined (_WIN64)
	return io_buffer{ this->Size(), static_cast<char *>(this->Data()) };
#else
#error "unknown platform"
#endif
}