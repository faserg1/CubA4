cmake_minimum_required (VERSION 3.12)

set(pnglibSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

set(pnglibSources
	${pnglibSourceDir}/png.c
	${pnglibSourceDir}/png.h
	${pnglibSourceDir}/pngconf.h
	${pnglibSourceDir}/pngdebug.h
	${pnglibSourceDir}/pngerror.c
	${pnglibSourceDir}/pngget.c
	${pnglibSourceDir}/pnginfo.h
	${pnglibSourceDir}/pnglibconf.h
	${pnglibSourceDir}/pngmem.c
	${pnglibSourceDir}/pngpread.c
	${pnglibSourceDir}/pngpriv.h
	${pnglibSourceDir}/pngread.c
	${pnglibSourceDir}/pngrio.c
	${pnglibSourceDir}/pngrtran.c
	${pnglibSourceDir}/pngrutil.c
	${pnglibSourceDir}/pngset.c
	${pnglibSourceDir}/pngstruct.h
	${pnglibSourceDir}/pngtest.c
	${pnglibSourceDir}/pngtrans.c
	${pnglibSourceDir}/pngwio.c
	${pnglibSourceDir}/pngwrite.c
	${pnglibSourceDir}/pngwtran.c
	${pnglibSourceDir}/pngwutil.c
)

add_library( pnglib STATIC ${pnglibSources})
use_library(pnglib zlib)

target_include_directories(pnglib INTERFACE src)
set_target_properties(pnglib PROPERTIES FOLDER "thirdparty")