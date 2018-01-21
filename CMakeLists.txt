CMAKE_MINIMUM_REQUIRED(VERSION 3.2.1)
project(rtype CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED audio graphics window system)

set(CLIENT_SOURCES
		# GAME ENGINE
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/AGameState.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/AWorld.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/AWorld.h
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/GameEngine.cc
		${CMAKE_SOURCE_DIR}/src/client/GameEngine/GameEngine.h
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

		# GAME
		${CMAKE_SOURCE_DIR}/src/client/IntroWorld.cc
		${CMAKE_SOURCE_DIR}/src/client/IntroWorld.h
		${CMAKE_SOURCE_DIR}/src/client/PlayWorld.cc
		${CMAKE_SOURCE_DIR}/src/client/PlayWorld.h

		# Network
		${CMAKE_SOURCE_DIR}/src/client/network/NetworkCommunication.h
		${CMAKE_SOURCE_DIR}/src/client/network/NetworkManager.h
		${CMAKE_SOURCE_DIR}/src/client/network/NetworkManager.cc
		${CMAKE_SOURCE_DIR}/src/client/network/TCPNonBlockingCommunication.h
		${CMAKE_SOURCE_DIR}/src/client/network/TCPNonBlockingCommunication.cc

		#[[add source files here]])

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
		${CMAKE_SOURCE_DIR}/src/server/GameLauncher.h
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
		${PROJECT_SOURCE_DIR}/src/tcp/RtypeProtocol.h
		${PROJECT_SOURCE_DIR}/src/tcp/RtypeProtocol.cc)
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
target_sources(rtype_client PRIVATE ${CLIENT_SOURCES} ${NETWORK_SOURCES} ${TCP_PROTOCOL})
target_include_directories(rtype_client
		PRIVATE ${PROJECT_SOURCE_DIR}/src
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client/network
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client/GameEngine
		PRIVATE ${PROJECT_SOURCE_DIR}/src/network
        PRIVATE ${PROJECT_SOURCE_DIR}/src/tcp
		PRIVATE ${CEREAL_HEADER}
		PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(rtype_client
		PRIVATE ${SFML_LIBRARIES}
		PRIVATE ${SFML_DEPENDENCIES})

set_target_properties(rtype_client
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_custom_command(TARGET rtype_client POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:rtype_client>/resources)

#server
add_executable(rtype_server ${PROJECT_SOURCE_DIR}/src/server/main.cc)
set_target_properties(rtype_server
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
target_sources(rtype_server
		PRIVATE ${SERVER_SOURCES}
		PRIVATE ${NETWORK_SOURCES}
		PRIVATE ${TCP_PROTOCOL})
target_include_directories(rtype_server
		PRIVATE ./src/network
		PRIVATE ${CEREAL_HEADER}
		PRIVATE ${PROJECT_SOURCE_DIR}/src/tcp)

enable_testing()
#test executable
add_executable(rtype_test
		${PROJECT_SOURCE_DIR}/test/test.cc
		#[[add test source files here]])

target_include_directories(rtype_test
		PRIVATE "${gtest_SOURCE_DIR}/include"
		PRIVATE "${gmock_SOURCE_DIR}/include"
		PRIVATE ${PROJECT_SOURCE_DIR}/src
		PRIVATE ${PROJECT_SOURCE_DIR}/src/tcp
		PRIVATE src/client/GameEngine
		PRIVATE ${SFML_INCLUDE_DIR}
		PRIVATE ${CEREAL_HEADER})
target_link_libraries(rtype_test
		PRIVATE gmock_main
		PRIVATE ${SFML_LIBRARIES}
		PRIVATE ${SFML_DEPENDENCIES})
target_sources(rtype_test
		PRIVATE ${SOURCES} ${TCP_PROTOCOL}
		PRIVATE ${PROJECT_SOURCE_DIR}/test/protocol_test.cc)

add_test(NAME testing_rtype_test COMMAND rtype_test)
