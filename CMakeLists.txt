CMAKE_MINIMUM_REQUIRED(VERSION 3.2.1)
project(rtype CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED audio graphics window system)

set(SOURCES
		# GAME ENGINE
		${CMAKE_SOURCE_DIR}/src/GameEngine/AGameState.h
		${CMAKE_SOURCE_DIR}/src/GameEngine/Animator.cc
		${CMAKE_SOURCE_DIR}/src/GameEngine/Animator.h
		${CMAKE_SOURCE_DIR}/src/GameEngine/AWorld.cc
		${CMAKE_SOURCE_DIR}/src/GameEngine/AWorld.h
		${CMAKE_SOURCE_DIR}/src/GameEngine/ComponentsManager.cc
		${CMAKE_SOURCE_DIR}/src/GameEngine/ComponentsManager.h
		${CMAKE_SOURCE_DIR}/src/GameEngine/GameEngine.cc
		${CMAKE_SOURCE_DIR}/src/GameEngine/GameEngine.h
		${CMAKE_SOURCE_DIR}/src/GameEngine/ResourcesManager.cc
		${CMAKE_SOURCE_DIR}/src/GameEngine/ResourcesManager.h
		${CMAKE_SOURCE_DIR}/src/GameEngine/Settings.h
		${CMAKE_SOURCE_DIR}/src/GameEngine/StatesManager.cc
		${CMAKE_SOURCE_DIR}/src/GameEngine/StatesManager.h
		
		# GAME
		${CMAKE_SOURCE_DIR}/src/Components.h
		${CMAKE_SOURCE_DIR}/src/IntroState.cc
		${CMAKE_SOURCE_DIR}/src/IntroState.h
		${CMAKE_SOURCE_DIR}/src/IntroWorld.cc
		${CMAKE_SOURCE_DIR}/src/IntroWorld.h
		${CMAKE_SOURCE_DIR}/src/PlayState.cc
		${CMAKE_SOURCE_DIR}/src/PlayState.h
		${CMAKE_SOURCE_DIR}/src/PlayWorld.cc
		${CMAKE_SOURCE_DIR}/src/PlayWorld.h
		#[[add source files here]])

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

add_executable(rtype ${PROJECT_SOURCE_DIR}/src/main.cc)

target_sources(rtype PRIVATE ${SOURCES})
target_include_directories(rtype
		PRIVATE ${PROJECT_SOURCE_DIR}/src
		PRIVATE ${PROJECT_SOURCE_DIR}/src/GameEngine
		PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(rtype
		PRIVATE ${SFML_LIBRARIES}
		PRIVATE ${SFML_DEPENDENCIES})

set_target_properties(rtype
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_custom_command(TARGET rtype POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:rtype>/resources)

enable_testing()
#test executable
add_executable(rtype_test
		${PROJECT_SOURCE_DIR}/test/test.cc
		#[[add test source files here]])

target_include_directories(rtype_test
		PRIVATE "${gtest_SOURCE_DIR}/include"
		PRIVATE "${gmock_SOURCE_DIR}/include"
		PRIVATE ${PROJECT_SOURCE_DIR}/src
		PRIVATE ${PROJECT_SOURCE_DIR}/src/GameEngine
		PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(rtype_test
		PRIVATE gmock_main
		PRIVATE ${SFML_LIBRARIES}
		PRIVATE ${SFML_DEPENDENCIES})
target_sources(rtype_test PRIVATE ${SOURCES})

add_test(NAME testing_rtype_test COMMAND rtype_test)
