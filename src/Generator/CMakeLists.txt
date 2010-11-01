

set (SOURCE_FILES
	Parser.cpp
	Generator.cpp)



include_directories (${PROJECT_SOURCE_DIR}/include/Myelin/Generator)




################################################################################
#     build generator                                                          #
################################################################################

add_executable (myelin-generate ${SOURCE_FILES})
set_target_properties (myelin-generate PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")

install (TARGETS myelin-generate DESTINATION bin)
