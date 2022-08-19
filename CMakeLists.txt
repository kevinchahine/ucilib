cmake_minimum_required(VERSION 3.21)

set(LIBRARY_NAME ucilib)
project(${LIBRARY_NAME})

add_compile_definitions(WIN32_LEAN_AND_MEAN)

set(COMMANDS 
	uci/commands/commands.hpp
	uci/commands/helpers.cpp
	uci/commands/helpers.h

	uci/commands/command_base.h
	uci/commands/bestmove.cpp
	uci/commands/bestmove.h
	uci/commands/command.cpp
	uci/commands/command.h
	uci/commands/copyprotection.cpp
	uci/commands/copyprotection.h
	uci/commands/debug.cpp
	uci/commands/debug.h
	uci/commands/go.cpp
	uci/commands/go.h
	uci/commands/id.cpp
	uci/commands/id.h
	uci/commands/info.cpp
	uci/commands/info.h
	uci/commands/isready.h
	uci/commands/option.cpp
	uci/commands/option.h
	uci/commands/ponderhit.h
	uci/commands/position.cpp
	uci/commands/position.h
	uci/commands/quit.h
	uci/commands/readyok.h
	uci/commands/register.cpp
	uci/commands/register.h
	uci/commands/registration.h
	uci/commands/setoption.cpp
	uci/commands/setoption.h
	uci/commands/stop.h
	uci/commands/uci.h
	uci/commands/ucinewgame.h
	uci/commands/uciok.h
)

set(NOTES
	notes/classes.txt
	notes/example1.txt
	notes/state_machine.txt
	notes/state_machine_examples.txt
	notes/synchronization.txt
	notes/uci_client_examples.txt
	notes/uci_definition.txt
)

set(OPTIONS
	#"uci/options/option.cpp"	# move to commands
	#"uci/options/option.h"		# move to commands
	#"uci/options/list.cpp"		
	#"uci/options/list.h"
	#"uci/options/setoption.h"	# move to commands
)

set(UCI
	#uci/debug.cpp				# move to commands
	#uci/debug.h					# move to commands
	#uci/go.cpp					# move to commands
	#uci/go.h					# move to commands
	#uci/info.cpp				# move to commands
	#uci/info.h					# move to commands
	uci/uci.hpp					
	uci/base.cpp
	uci/base.h
	uci/engine.cpp
	uci/engine.h
	uci/gui.cpp
	uci/gui.h
)

add_library(${LIBRARY_NAME} STATIC 
	${COMMANDS}
	${NOTES}
	${OPTIONS}
	${UCI}
)

target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_17)

include_directories(${LIBRARY_NAME}	".")
include_directories(${LIBRARY_NAME} "uci")

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

source_group(commands FILES ${COMMANDS})
source_group(notes FILES ${NOTES})
source_group("options" FILES ${OPTIONS})
source_group(uci FILES ${UCI})

# --- Libraries (VCPKG) ---
if (MSVC)
	message(STATUS "\nVCPKG packages will be automatically linked to visual studio\n")

	add_compile_definitions(_WIN32_WINNT=0x0601)	# same as '#define _WIN32_WINNT'
	add_compile_definitions(WIN32_LEAN_AND_MEAN)
else ()
	# --- For VCPKG packages ---
	#message(STATUS "\nCall cmake with: cmake .. -DCMAKE_TOOLCHAIN_FILE=/__path__/__to__/vcpkg/scripts/buildsystems/vcpkg.cmake")

	# ----- BOOST -----

	message(STATUS "\n----- BOOST -----")
	set(Boost_USE_STATIC_LIBS		OFF)
	set(Boost_USE_MULTITHREADED		OFF)
	set(Boost_USE_STATIC_RUNTIME	OFF)

	find_package(Boost REQUIRED COMPONENTS
		#algorithm		# leave out header-only packages
		#asio 			# leave out header-only packages
		#process		# leave out header-only packages
		system 
		filesystem 
		regex
		thread
	)

	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})

	target_link_libraries(${PROJECT_NAME} PUBLIC
		#Boost::algorithm	# leave out header-only packages
		#Boost::asio		# leave out header-only packages
		#Boost::process		# leave out header-only packages
		Boost::system
		Boost::filesystem
		Boost::regex
		${Boost_LIBRARIES}	# TODO: do we need this
	)

	message(STATUS "Include dirs ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost libraries ${Boost_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PUBLIC
		${Boost_INCLUDE_DIRS}
	)
endif (MSVC)

# --- ForgeLib ---
message(STATUS "\n----- ForgeLib -----\n")

target_link_libraries(${LIBRARY_NAME} PUBLIC forgelib)

