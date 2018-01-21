//
// Created by Kévin POLOSSAT on 11/01/2018.
//

#ifndef LW_TCP_SERVER_PROTOCOL_H
#define LW_TCP_SERVER_PROTOCOL_H

namespace lw_network {

class Protocol {
public:
    Protocol(int family = 0, int type = 0, int protocol = 0);
    Protocol(Protocol const &other);
    Protocol(Protocol &&other);

    Protocol &operator=(Protocol const &other);
    Protocol &operator=(Protocol &&other);

    int family() const;
    void setFamily(int f);
    int type() const;
    void setType(int t);
    int protocol() const;
    void setProtocol(int p);

private:
    int family_;
    int type_;
    int protocol_;
};
}


#endif //LW_TCP_SERVER_PROTOCOL_H
