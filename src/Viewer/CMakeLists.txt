

project (MyelinViewer)


set (SOURCE_FILES Viewer.cpp)
include_directories (${CMAKE_SOURCE_DIR}/include)




################################################################################
#     build viewer                                                             #
################################################################################

add_executable (myelin-view ${SOURCE_FILES})
set_target_properties (myelin-view PROPERTIES COMPILE_FLAGS "-DMYELIN_DLL -fvisibility=hidden -fvisibility-inlines-hidden")

link_directories (${Myelin_BUILD_DIR})
target_link_libraries (myelin-view Myelin dl)

install (TARGETS myelin-view DESTINATION bin)
