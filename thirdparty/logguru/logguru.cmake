find_path(LOGURU_INCLUDE_DIRS "loguru/loguru.cpp")

set(LOGURU_THIRDPARTY_SOURCE
	${CMAKE_CURRENT_LIST_DIR}/empty.cpp
)

if (WIN32)
    list(APPEND LOGURU_THIRDPARTY_SOURCE
        ${LOGURU_INCLUDE_DIRS}/loguru/loguru.cpp
    )
endif (WIN32)

add_library(logguru_win_lib STATIC ${LOGURU_THIRDPARTY_SOURCE})
target_compile_definitions(logguru_win_lib PRIVATE
    LOGURU_USE_FMTLIB=1
)
target_link_libraries(logguru_win_lib PRIVATE fmt::fmt)