cmake_minimum_required(VERSION 3.21)

set(LIBRARY_NAME ucilib)
project(${LIBRARY_NAME})

set(NOTES
	notes/classes.txt
	notes/example1.txt
	notes/synchronization.txt
	notes/uci_definition.txt
)

set(SRC
	src/uci_base.cpp
	src/uci_base.h
	src/uci_client.cpp
	src/uci_client.h
	src/uci_server.cpp
	src/uci_server.h
)

add_library(${LIBRARY_NAME} SHARED 
	${NOTES}
	${SRC}
)
