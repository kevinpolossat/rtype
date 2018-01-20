//
// Created by Kévin POLOSSAT on 31/10/2017.
//

#ifndef LW_NETWORK_LW_TCP_SERVER_EXCEPTION_HPP
#define LW_NETWORK_LW_TCP_SERVER_EXCEPTION_HPP

#include <exception>
#include <string>

namespace lw_network {

    class OpenError: public std::exception {
    public:
        explicit OpenError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class CloseError: public std::exception {
    public:
        explicit CloseError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class BindError: public std::exception {
    public:
        explicit BindError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class ConnectError: public std::exception {
    public:
        explicit ConnectError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class ListenError: public std::exception {
    public:
        explicit ListenError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class SetOptError: public std::exception {
    public:
        explicit SetOptError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class GetOptError: public std::exception {
    public:
        explicit GetOptError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class AcceptError: public std::exception {
    public:
        explicit AcceptError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

    class ResolveError: public std::exception {
    public:
        explicit ResolveError(std::string const & what): what_(what) {}
        const char * what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };
}

#endif //LW_NETWORK_LW_TCP_SERVER_EXCEPTION_HPP
