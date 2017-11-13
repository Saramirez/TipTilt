project( TipTilt )
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
#set(CMAKE_BUILD_TYPE Debug)

#FIND_PACKAGE( Boost COMPONENTS regex REQUIRED )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR})

aux_source_directory(./src SRC_LIST)
aux_source_directory(./include INC_LIST)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS}) #${Boost_INCLUDE_DIRS})

add_executable( TipTilt ${INC_LIST} ${SRC_LIST})
target_compile_features( TipTilt PRIVATE cxx_thread_local)
target_link_libraries( TipTilt ${OpenCV_LIBS} -lpthread) #${Boost_LIBRARIES} )
