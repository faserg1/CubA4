cmake_minimum_required (VERSION 2.8)
set(NetworkSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(NetworkSourceIoDir ${NetworkSourceDir}/io)
set(NetworkSourceDataDir ${NetworkSourceDir}/data)
set(NetworkSourceTransmitDir ${NetworkSourceDir}/transmit)
set(NetworkIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(NetworkIncludeIoDir ${NetworkIncludeDir}/io)
set(NetworkIncludeDataDir ${NetworkIncludeDir}/data)
set(NetworkIncludeTransmitDir ${NetworkIncludeDir}/transmit)

set(NetworkSourceIo
	${NetworkSourceIoDir}/Connection.cpp
)
set(NetworkHeaderIo
	${NetworkIncludeIoDir}/Connection.hpp
)
set(NetworkSourceData
	${NetworkSourceDataDir}/Packet.cpp
)
set(NetworkHeaderData
	${NetworkIncludeDataDir}/Packet.hpp
)
set(NetworkSourceTransmit
	${NetworkSourceTransmitDir}/Dispatcher.cpp
	${NetworkSourceTransmitDir}/Sender.cpp
	${NetworkSourceTransmitDir}/Receiver.cpp
)
set(NetworkHeaderTransmit
	${NetworkIncludeTransmitDir}/Dispatcher.hpp
	${NetworkIncludeTransmitDir}/Sender.hpp
	${NetworkIncludeTransmitDir}/Receiver.hpp
)

link_directories(
#third party
	${Boost_LIBRARY_DIRS})

set(NetworkHeaders
	${NetworkIncludeDir}/NetworkLibrary.hpp
	${NetworkHeaderIo}
	${NetworkHeaderData}
	${NetworkHeaderTransmit}
)

set(NetworkSources
	${NetworkSourceDir}/common.cpp
	${NetworkSourceIo}
	${NetworkSourceData}
	${NetworkSourceTransmit}
)

source_group("${SOURCE_GROUP_HEADER_START}io" FILES ${NetworkHeaderIo})
source_group("${SOURCE_GROUP_SOURCE_START}io" FILES ${NetworkSourceIo})
source_group("${SOURCE_GROUP_HEADER_START}data" FILES ${NetworkHeaderData})
source_group("${SOURCE_GROUP_SOURCE_START}data" FILES ${NetworkSourceData})
source_group("${SOURCE_GROUP_HEADER_START}transmit" FILES ${NetworkHeaderTransmit})
source_group("${SOURCE_GROUP_SOURCE_START}transmit" FILES ${NetworkSourceTransmit})

#library
add_library(Network SHARED ${NetworkHeaders} ${NetworkSources})

#self include directories
target_include_directories(Network PUBLIC ${NetworkIncludeDir})

#thrid-party
target_include_directories(Network PRIVATE ${Boost_INCLUDE_DIRS})

#set defines for library export
target_compile_definitions(Network PRIVATE NETWORK_LIBRARY)

#thridparty link libraries
target_link_libraries(Network PRIVATE Boost::system)

set_target_properties(Network PROPERTIES FOLDER "Libs")