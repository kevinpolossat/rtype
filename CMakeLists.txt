CMAKE_MINIMUM_REQUIRED(VERSION 3.2.1)
project(rtype CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED audio graphics window system)
find_package( Threads )

set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
set(CLIENT_SOURCES
		# GAME ENGINE
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/AGameState.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/AWorld.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/AWorld.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/GameEngine.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/GameEngine.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/LoopTimer.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/LoopTimer.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/ResourcesManager.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/ResourcesManager.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/StatesManager.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/StatesManager.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/Vector2D.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/Entity/Component.cpp
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/Entity/Component.h

		#Sates
		${CMAKE_SOURCE_DIR}/src/client/States/IntroState.cc
		${CMAKE_SOURCE_DIR}/src/client/States/IntroState.h
		${CMAKE_SOURCE_DIR}/src/client/States/PlayState.cc
		${CMAKE_SOURCE_DIR}/src/client/States/PlayState.h
		${CMAKE_SOURCE_DIR}/src/client/States/LoginState.cc
		${CMAKE_SOURCE_DIR}/src/client/States/LoginState.h
		${CMAKE_SOURCE_DIR}/src/client/States/CreateState.cc
		${CMAKE_SOURCE_DIR}/src/client/States/CreateState.h
		${CMAKE_SOURCE_DIR}/src/client/States/JoinState.cc
		${CMAKE_SOURCE_DIR}/src/client/States/JoinState.h
		${CMAKE_SOURCE_DIR}/src/client/States/MenuState.cc
		${CMAKE_SOURCE_DIR}/src/client/States/MenuState.h
		${CMAKE_SOURCE_DIR}/src/client/States/WaitingState.cc
		${CMAKE_SOURCE_DIR}/src/client/States/WaitingState.h

		# GAME
		${CMAKE_SOURCE_DIR}/src/client/IntroWorld.cc
		${CMAKE_SOURCE_DIR}/src/client/IntroWorld.h
		${CMAKE_SOURCE_DIR}/src/client/PlayWorld.cc
		${CMAKE_SOURCE_DIR}/src/client/PlayWorld.h
		${CMAKE_SOURCE_DIR}/src/client/MenuValue.h
		${CMAKE_SOURCE_DIR}/src/client/MenuValue.cc

		${CMAKE_SOURCE_DIR}/src/loadlib/LoadIa.cc
		${CMAKE_SOURCE_DIR}/src/loadlib/LoadIa.hpp

		# CONF
		${CMAKE_SOURCE_DIR}/src/client/GameConfiguration.h
        ${CMAKE_SOURCE_DIR}/src/client/GameConfiguration.cc
		#[[add source files here]])

set(AI_HEADER ${CMAKE_SOURCE_DIR}/ai)

set(NETWORK_GAME_ENGINE
		${CMAKE_SOURCE_DIR}/src/client/network/NetworkCommunication.h
		${CMAKE_SOURCE_DIR}/src/client/network/NetworkManager.h
		${CMAKE_SOURCE_DIR}/src/client/network/NetworkManager.cc
		${CMAKE_SOURCE_DIR}/src/client/network/TCPNonBlockingCommunication.h
		${CMAKE_SOURCE_DIR}/src/client/network/TCPNonBlockingCommunication.cc
		${CMAKE_SOURCE_DIR}/src/client/network/UDPNonBlockingCommunication.h
		${CMAKE_SOURCE_DIR}/src/client/network/UDPNonBlockingCommunication.cc)

set(SERVER_SOURCES
		${CMAKE_SOURCE_DIR}/src/server/Server.cc
		${CMAKE_SOURCE_DIR}/src/server/Server.h
		${CMAKE_SOURCE_DIR}/src/server/Connection.cc
		${CMAKE_SOURCE_DIR}/src/server/Connection.h
		${CMAKE_SOURCE_DIR}/src/server/ConnectionManager.cc
		${CMAKE_SOURCE_DIR}/src/server/ConnectionManager.h
		${CMAKE_SOURCE_DIR}/src/server/GameManager.cc
		${CMAKE_SOURCE_DIR}/src/server/GameManager.h
		${CMAKE_SOURCE_DIR}/src/server/GameLobby.cc
		${CMAKE_SOURCE_DIR}/src/server/GameLobby.h
		${CMAKE_SOURCE_DIR}/src/server/Launcher.cc
		${CMAKE_SOURCE_DIR}/src/server/Launcher.h
		${CMAKE_SOURCE_DIR}/src/server/Game.h
		${CMAKE_SOURCE_DIR}/src/server/Game.cpp
		${CMAKE_SOURCE_DIR}/src/server/GameLauncher.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/Entity/Component.cpp
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/Entity/Component.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/Vector2D.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/LoopTimer.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/LoopTimer.h
		#[[add source files here]])

set(NETWORK_SOURCES
		${PROJECT_SOURCE_DIR}/src/network/Socket.cc
		${PROJECT_SOURCE_DIR}/src/network/Socket.h
		${PROJECT_SOURCE_DIR}/src/network/ReactiveSocket.cc
		${PROJECT_SOURCE_DIR}/src/network/ReactiveSocket.h
		${PROJECT_SOURCE_DIR}/src/network/Acceptor.cc
		${PROJECT_SOURCE_DIR}/src/network/Acceptor.h
		${PROJECT_SOURCE_DIR}/src/network/FDSet.cc
		${PROJECT_SOURCE_DIR}/src/network/FDSet.h
		${PROJECT_SOURCE_DIR}/src/network/EndPoint.cc
		${PROJECT_SOURCE_DIR}/src/network/EndPoint.h
		${PROJECT_SOURCE_DIR}/src/network/Protocol.cc
		${PROJECT_SOURCE_DIR}/src/network/Protocol.h
		${PROJECT_SOURCE_DIR}/src/network/Reactor.cc
		${PROJECT_SOURCE_DIR}/src/network/Reactor.h
		${PROJECT_SOURCE_DIR}/src/network/Resolver.cc
		${PROJECT_SOURCE_DIR}/src/network/Resolver.h
		${PROJECT_SOURCE_DIR}/src/network/socket_operations.cc
		${PROJECT_SOURCE_DIR}/src/network/socket_operations.h
		${PROJECT_SOURCE_DIR}/src/network/WinSockInit.cc
		${PROJECT_SOURCE_DIR}/src/network/WinSockInit.h
		${PROJECT_SOURCE_DIR}/src/network/Operation.h
		${PROJECT_SOURCE_DIR}/src/network/Buffer.cc
		${PROJECT_SOURCE_DIR}/src/network/Buffer.h
		${PROJECT_SOURCE_DIR}/src/network/lw_network_error.h)

set(TCP_PROTOCOL
		${PROJECT_SOURCE_DIR}/src/tcp/TcpProtocol.h
		${PROJECT_SOURCE_DIR}/src/tcp/TcpProtocol.cc)
set(UDP_PROTOCOL
		${PROJECT_SOURCE_DIR}/src/udp/UdpProtocol.h
		${PROJECT_SOURCE_DIR}/src/udp/Events.h
		${PROJECT_SOURCE_DIR}/src/udp/UdpProtocol.cc)

set(CEREAL_HEADER ${PROJECT_SOURCE_DIR}/src/serialization)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build . WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src" "${CMAKE_BINARY_DIR}/googletest-build")

#client
add_executable(rtype_client src/client/main.cc)
target_sources(rtype_client
		PRIVATE ${CLIENT_SOURCES}
		PRIVATE ${NETWORK_SOURCES}
		PRIVATE ${TCP_PROTOCOL}
		PRIVATE ${UDP_PROTOCOL}
		PRIVATE ${NETWORK_GAME_ENGINE})
target_include_directories(rtype_client
		PRIVATE ${PROJECT_SOURCE_DIR}/src
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client/network
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client/GameEngine
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client/GameEngine/Entity
		PRIVATE ${PROJECT_SOURCE_DIR}/src/network
        PRIVATE ${PROJECT_SOURCE_DIR}/src/tcp
		PRIVATE ${PROJECT_SOURCE_DIR}/src/udp
		PRIVATE ${CEREAL_HEADER}
		PRIVATE ${AI_HEADER}
		PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(rtype_client
		PRIVATE ${SFML_LIBRARIES}
		PRIVATE ${SFML_DEPENDENCIES}
		PRIVATE ${CMAKE_DL_LIBS})

set_target_properties(rtype_client
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
#server
add_executable(rtype_server ${PROJECT_SOURCE_DIR}/src/server/main.cc)
set_target_properties(rtype_server
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
target_sources(rtype_server
		PRIVATE ${SERVER_SOURCES}
		PRIVATE ${NETWORK_SOURCES}
		PRIVATE ${TCP_PROTOCOL}
		PRIVATE ${UDP_PROTOCOL}
		PRIVATE ${AI_HEADER}
		PRIVATE ${NETWORK_GAME_ENGINE})
target_include_directories(rtype_server
		PRIVATE ./src/network
		PRIVATE ${CEREAL_HEADER}
		PRIVATE ${PROJECT_SOURCE_DIR}/src/tcp
		PRIVATE ${PROJECT_SOURCE_DIR}/src/udp
		PRIVATE ./src/client/network)
target_link_libraries(rtype_server
		PRIVATE Threads::Threads)

enable_testing()
#test executable
add_executable(rtype_server_test
		${PROJECT_SOURCE_DIR}/test/test.cc
		#[[add test source files here]])

target_include_directories(rtype_server_test
		PRIVATE "${gtest_SOURCE_DIR}/include"
		PRIVATE "${gmock_SOURCE_DIR}/include"
		PRIVATE ${PROJECT_SOURCE_DIR}/src/server
		PRIVATE ${PROJECT_SOURCE_DIR}/src/tcp
		PRIVATE ${PROJECT_SOURCE_DIR}/src/udp
		PRIVATE ${SFML_INCLUDE_DIR}
		PRIVATE ${PROJECT_SOURCE_DIR}/src/network
		PRIVATE ${CEREAL_HEADER})

target_link_libraries(rtype_server_test
		PRIVATE gmock_main)
target_sources(rtype_server_test
		PRIVATE ${TCP_PROTOCOL}
		PRIVATE ${UDP_PROTOCOL}
		PRIVATE ${PROJECT_SOURCE_DIR}/test/protocol_test.cc
		PRIVATE ${PROJECT_SOURCE_DIR}/test/protocol_udp_test.cc)

add_test(NAME testing_rtype_test COMMAND rtype_server_test)

set(BASIC_SOURCE
		ai/Basic/Basic.cpp
		ai/Basic/Basic.h)
set(CIRCLE_SOURCE
		ai/Circle/Circle.cpp
		ai/Circle/Circle.h)
set(LINEAR_SOURCE
		ai/Linear/Linear.cpp
		ai/Linear/Linear.h)
set(RANDOM_SOURCE
		ai/Random/Random.cpp
		ai/Random/Random.h)
set(SINUS_SOURCE
		ai/Sinus/Sinus.cpp
		ai/Sinus/Sinus.h)
set(BOSS_SOURCE
		ai/Boss/Boss.cpp
		ai/Boss/Boss.h
		ai/Boss/TreeSearch.cpp
		ai/Boss/TreeSearch.hpp)

include_directories(./)
add_library(Basic SHARED ${BASIC_SOURCE})
add_library(Circle SHARED ${CIRCLE_SOURCE})
add_library(Linear SHARED ${LINEAR_SOURCE})
add_library(Random SHARED ${RANDOM_SOURCE})
add_library(Sinus SHARED ${SINUS_SOURCE})
add_library(Boss SHARED ${BOSS_SOURCE})

set_target_properties(Basic Circle Linear Random Sinus Boss
		PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/resources/ai")
target_include_directories(Basic
		PRIVATE ${PROJECT_SOURCE_DIR}/ai)
target_include_directories(Circle
		PRIVATE ${PROJECT_SOURCE_DIR}/ai)
target_include_directories(Linear
		PRIVATE ${PROJECT_SOURCE_DIR}/ai)
target_include_directories(Random
		PRIVATE ${PROJECT_SOURCE_DIR}/ai)
target_include_directories(Sinus
		PRIVATE ${PROJECT_SOURCE_DIR}/ai)
target_include_directories(Boss
		PRIVATE ${PROJECT_SOURCE_DIR}/ai)

add_dependencies(rtype_server Basic Random Circle Linear Sinus Boss)
add_custom_command(TARGET rtype_server POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:rtype_client>/resources)
