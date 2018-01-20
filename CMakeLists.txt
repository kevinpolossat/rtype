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
		${CMAKE_SOURCE_DIR}/loadlib/LoadIa.cc
		${CMAKE_SOURCE_DIR}/loadlib/LoadIa.hpp
		${CMAKE_SOURCE_DIR}/src/ia/IArtificialIntelligence.hpp
		#[[add source files here]])

set(SERVER_SOURCES
		#[[add source files here]])

set(TCP_PROTOCOL_HEADER ${PROJECT_SOURCE_DIR}/src/tcp/protocol.h)
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

add_executable(rtype_client src/client/main.cc)
target_sources(rtype_client PRIVATE ${CLIENT_SOURCES})
target_include_directories(rtype_client
		PRIVATE ${PROJECT_SOURCE_DIR}/src
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client
		PRIVATE ${PROJECT_SOURCE_DIR}/src/client/GameEngine
		PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(rtype_client
		PRIVATE ${SFML_LIBRARIES}
		PRIVATE ${SFML_DEPENDENCIES}
		PRIVATE ${CMAKE_DL_LIBS})

set_target_properties(rtype_client
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_custom_command(TARGET rtype_client POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:rtype_client>/resources)

add_executable(rtype_server ${PROJECT_SOURCE_DIR}/src/server/main.cc)
set_target_properties(rtype_server
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
target_sources(rtype_server
		PRIVATE ${SERVER_SOURCES})

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
		PRIVATE ${SOURCES} ${TCP_PROTOCOL_HEADER}
		PRIVATE ${PROJECT_SOURCE_DIR}/test/protocol_test.cc)

add_test(NAME testing_rtype_test COMMAND rtype_test)
