cmake_minimum_required (VERSION 3.12)

set(zlibSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

set(zlibSources
	${zlibSourceDir}/adler32.c
	${zlibSourceDir}/compress.c
	${zlibSourceDir}/crc32.c
	${zlibSourceDir}/crc32.h
	${zlibSourceDir}/deflate.c
	${zlibSourceDir}/deflate.h
	${zlibSourceDir}/gzclose.c
	${zlibSourceDir}/gzguts.h
	${zlibSourceDir}/gzlib.c
	${zlibSourceDir}/gzread.c
	${zlibSourceDir}/gzwrite.c
	${zlibSourceDir}/infback.c
	${zlibSourceDir}/inffast.c
	${zlibSourceDir}/inffast.h
	${zlibSourceDir}/inffixed.h
	${zlibSourceDir}/inflate.c
	${zlibSourceDir}/inflate.h
	${zlibSourceDir}/inftrees.c
	${zlibSourceDir}/inftrees.h
	${zlibSourceDir}/trees.c
	${zlibSourceDir}/trees.h
	${zlibSourceDir}/uncompr.c
	${zlibSourceDir}/zconf.h
	${zlibSourceDir}/zlib.h
	${zlibSourceDir}/zutil.c
	${zlibSourceDir}/zutil.h
)

add_library(zlib STATIC ${zlibSources})

target_include_directories(zlib INTERFACE src)

set_target_properties(zlib PROPERTIES FOLDER "thirdparty")