

set (SOURCE_FILES
	Viewer.cpp)



include_directories (${PROJECT_SOURCE_DIR}/include/Myelin/Generator)




################################################################################
#     build viewer                                                             #
################################################################################

add_executable (myelin-view ${SOURCE_FILES})
set_target_properties (myelin-view PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")

target_link_libraries (myelin-view Myelin dl)

install (TARGETS myelin-view DESTINATION bin)
