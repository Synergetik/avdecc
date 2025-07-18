# Python Bindings CMake file

find_package(Python 3.11 EXACT COMPONENTS Interpreter Development REQUIRED)

string(TOLOWER "${PROJECT_NAME}_python" PYTHON_PROJECT_TARGET)
string(TOLOWER "${PROJECT_NAME}" PYTHON_OUTPUT)
set(PYBIND11_FINDPYTHON TRUE)
set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
message(STATUS "ATDECC: Using python library from ${Python_LIBRARIES}")

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.13.6
)
FetchContent_MakeAvailable(pybind11)

# Get the full git commit hash and check if the working directory is dirty
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE CU_BUILD_GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND git diff --quiet
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE GIT_DIFF_RESULT
)

if (GIT_DIFF_RESULT EQUAL 1)
    set(CU_BUILD_GIT_COMMIT_HASH "${CU_BUILD_GIT_COMMIT_HASH}+")
endif()

# Setup project
cu_setup_project(${PYTHON_PROJECT_TARGET} ${LA_AVDECC_VERSION} "AVDECC Python Bindings Library")

# Configure files based on CMakeLists.txt version number
string(TIMESTAMP CU_BUILD_DATE "%Y-%m-%d" UTC)
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.hpp"
)

# Public header files
set (PUBLIC_HEADER_FILES
	${CU_ROOT_DIR}/src/bindings/python/avdecc_python.hpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_entity_python.hpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_controller_python.hpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_utils_python.hpp
	${CU_ROOT_DIR}/src/bindings/python/utils.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
)

# Common files
set (SOURCE_FILES_COMMON
	${CU_ROOT_DIR}/src/bindings/python/avdecc_python.cpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_entity_python.cpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_entity_model_types_python.cpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_entity_protocol_python.cpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_entity_model_python.cpp
	${CU_ROOT_DIR}/src/bindings/python/avdecc_controller_python.cpp
)

# Group sources
source_group("Header Files\\Public" FILES ${PUBLIC_HEADER_FILES})
source_group("Source Files" FILES ${SOURCE_FILES_COMMON})

# Configure module
pybind11_add_module(${PYTHON_PROJECT_TARGET} ${SOURCE_FILES_COMMON})
set_target_properties(${PYTHON_PROJECT_TARGET} PROPERTIES OUTPUT_NAME ${PYTHON_OUTPUT} SUFFIX .pyd)

target_include_directories(${PYTHON_PROJECT_TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Using NIH library
target_link_libraries(${PYTHON_PROJECT_TARGET} PRIVATE ${PYTHON_OUTPUT}_static)

# Add custom command to generate stubs
add_custom_command(
    TARGET ${PYTHON_PROJECT_TARGET} POST_BUILD
    COMMAND ${Python_EXECUTABLE} -m pybind11_stubgen ${PYTHON_OUTPUT} --output-dir ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating Python stubs with pybind11-stubgen"
)