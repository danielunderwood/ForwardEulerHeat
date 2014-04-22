project(ForwardEulerHeat)
cmake_minimum_required(VERSION 2.8)

find_Package(PythonLibs REQUIRED)

aux_source_directory(src SRC_LIST)

set( INCLUDE_DIRS
	 include
	 ${PYTHON_INCLUDE_DIRS}
	 )

include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})