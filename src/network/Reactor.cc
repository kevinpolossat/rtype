//
// Created by Kévin POLOSSAT on 11/01/2018.
//

#include <thread>
#include "Reactor.h"

void lw_network::Reactor::registerHandler(socket_type s, lw_network::Reactor::OperationType ot) {
//    std::unique_lock<std::mutex> lock(mutex_);
    if (!isRegistered(s, ot)) {
        handlers_[ot].insert(std::make_pair(s, std::queue<lw_network::Reactor::Handler>()));
    }
    // TODO else throw ??
}

void lw_network::Reactor::unregisterHandler(socket_type s, lw_network::Reactor::OperationType ot) {
//    std::unique_lock<std::mutex> lock(mutex_);
    auto it = getRegistered_(s, ot);
    if (isRegistered_(it, ot)) {
        handlers_[ot].erase(it);
    }
    // TODO else throw ?
}

bool lw_network::Reactor::isRegistered(socket_type s, lw_network::Reactor::OperationType ot) {
    return getRegistered_(s, ot) != handlers_[ot].end();
}

lw_network::Reactor::Handlers::iterator lw_network::Reactor::getRegistered_(
        socket_type s, lw_network::Reactor::OperationType ot) {
    return handlers_[ot].find(s);
}

bool lw_network::Reactor::isRegistered_(
        const lw_network::Reactor::Handlers::iterator &it, lw_network::Reactor::OperationType ot) {
    return it != handlers_[ot].end();
}

void lw_network::Reactor::handleEvents() {
    std::vector<std::shared_ptr<Operation>> completions;
    for (;;) {
        //std::unique_lock<std::mutex> lock(mutex_);
        handleEvent(completions);
    }
}

void lw_network::Reactor::handleOperation_(
        lw_network::Reactor::OperationType ot,
        std::vector<std::shared_ptr<Operation>> &completions) {
	auto maxSd = fdsets_[ot].maxDescriptor();
	if (maxSd == invalid_socket) {
		return ;
	}
    for (socket_type i = 0; i < maxSd + 1; ++i) {
        if (fdsets_[ot].isSet(i)) {
            if (!handlers_[ot][i].empty()) {
//            while (!handlers_[ot][i].empty()) {
				auto operation = handlers_[ot][i].front();
				if (operation->handle()) {
                    handlers_[ot][i].pop();
                    completions.push_back(operation);
                } else {
					break;
                }
				//            }
            }
            if (handlers_[ot][i].empty()) {
				masters_[ot].clear(i);
			}
        }
    }
}

void lw_network::Reactor::submit(
        socket_type s, lw_network::Reactor::Handler handler, lw_network::Reactor::OperationType ot) {
    //std::unique_lock<std::mutex> lock(mutex_);
    handlers_[ot][s].push(std::move(handler));
    masters_[ot] += s;
}

void lw_network::Reactor::completeOperations_(std::vector<std::shared_ptr<Operation>> &completions) {
    for (auto & completionHandler : completions) {
        completionHandler->complete();
    }
    completions.clear();
}

void lw_network::Reactor::handleEvent(std::vector<std::shared_ptr<Operation>> & completions) {
	socket_type maxSd = invalid_socket;
	for (auto i = 0; i < maxFdSets; ++i) {
		fdsets_[i] = masters_[i];
		if (maxSd == invalid_socket || (masters_[i].maxDescriptor() != invalid_socket && masters_[i].maxDescriptor() > maxSd)) {
			maxSd = masters_[i].maxDescriptor();
		}
    }
    auto ec = no_error;
	lw_network::socket_operations::select(
            maxSd + 1,
            fdsets_[lw_network::Reactor::OperationType::read].data(),
            fdsets_[lw_network::Reactor::OperationType::write].data(),
            0,
            /*TODO add timeout*/0,
            ec);
	if (ec < lw_network::no_error) {
		// TODO Handle error
        return ;
    }
    for (auto i = 0; i < maxFdSets; ++i) {
		handleOperation_(static_cast<lw_network::Reactor::OperationType>(i), completions);
	}
    completeOperations_(completions);
}
