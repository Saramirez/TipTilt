cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project( TipTilt )
set(CMAKE_BUILD_TYPE Debug)
aux_source_directory(./src SRC_LIST)
aux_source_directory(./include INC_LIST)

find_package( OpenCV REQUIRED )

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( TipTilt ${INC_LIST} ${SRC_LIST})
target_compile_features( TipTilt PRIVATE cxx_thread_local)
target_link_libraries( TipTilt ${OpenCV_LIBS} -lpthread)

