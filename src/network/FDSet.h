//
// Created by Kévin POLOSSAT on 13/01/2018.
//

#ifndef LW_TCP_SERVER_FDSET_H
#define LW_TCP_SERVER_FDSET_H

#include <sys/select.h>
#include "socket_operations.h"
namespace lw_network {
class FDSet {
public:
    FDSet();
    FDSet(FDSet const & other);
    FDSet(FDSet && other);

    FDSet & operator = (FDSet const & other);
    FDSet & operator = (FDSet && other);
    FDSet & operator -= (socket_type s);
    FDSet & operator += (socket_type s);
    fd_set * data();
    void set(socket_type s);
    void clear(socket_type s);
    void reset();
    bool isSet(socket_type s) const;
private:
    fd_set fdset_;
};
}


#endif //LW_TCP_SERVER_FDSET_H
