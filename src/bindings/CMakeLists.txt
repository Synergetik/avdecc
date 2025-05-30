# Bindings libraries

if(BUILD_AVDECC_BINDINGS_C)
	message(STATUS "Building Avdecc C bindings library")
	add_subdirectory(c)
endif()

if(BUILD_AVDECC_BINDINGS_PYTHON)
	message(STATUS "Building Avdecc python bindings library")
	add_subdirectory(python)
endif()