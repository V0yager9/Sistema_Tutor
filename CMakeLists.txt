# Autore: Davide Cossalter

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")

project(ProgettoFinale)

set(HEADERS
	include/autostrada.h
	include/editor.h
	include/simulatore.h
	include/tempo.h
	include/tutor.h
	include/veicolo.h
)

set(SOURCES
	src/main_simulazione.cpp
	src/main_tutor.cpp
	src/autostrada.cpp
	src/editor.cpp
	src/simulatore.cpp
	src/tempo.cpp
	src/tutor.cpp
	src/veicolo.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)


message(STATUS "Configuration of ${PROJECT_NAME}")
message(STATUS "Version : ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
message(STATUS "Sources : ${SOURCES}")
message(STATUS "Header : ${HEADERS}")
