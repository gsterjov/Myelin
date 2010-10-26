

set (SOURCE_FILES
	Parser.cpp
	Generator.cpp)



include_directories (${PROJECT_SOURCE_DIR}/include/Myelin/Generator)




################################################################################
#     build generator                                                          #
################################################################################

add_executable (myelin-generator ${SOURCE_FILES})
target_link_libraries (myelin-generator Myelin)

set_target_properties (myelin-generator PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")

install (TARGETS myelin-generator DESTINATION bin)
