//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#ifndef LW_TCP_SERVER_OPERATION_H
#define LW_TCP_SERVER_OPERATION_H


#include <functional>

class Operation {
public:
    virtual ~Operation() = default;
    virtual void complete() = 0;
    virtual bool handle() = 0;
};


#endif //LW_TCP_SERVER_OPERATION_H
