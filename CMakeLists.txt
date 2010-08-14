
cmake_minimum_required (VERSION 2.6)
project (Myelin)


set (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)


option (BUILD_TESTS "Build unit tests and create test target?")


configure_file (
	${PROJECT_SOURCE_DIR}/MyelinConfig.cmake.in
	${PROJECT_BINARY_DIR}/MyelinConfig.cmake
	@ONLY)



set (SOURCE_FILES)


set (HEADER_FILES
	include/Myelin/MetaClass.h)



include_directories (
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/Axon)



#add_library (Myelin SHARED ${SOURCE_FILES} ${HEADER_FILES})


#install (TARGETS Myelin EXPORT AxonTargets DESTINATION lib)
#install (EXPORT MyelinTargets DESTINATION lib/cmake/Myelin)
#install (FILES ${PROJECT_BINARY_DIR}/MyelinConfig.cmake DESTINATION lib/cmake/Myelin)

#install (FILES ${HEADER_FILES} DESTINATION include/Myelin)




################################################################################
#     build engine tests                                                       #
################################################################################
if (BUILD_TESTS)

	set (TEST_SOURCE_FILES
		test/MetaClassTest.cpp)
		
		
	enable_testing ()
	find_package (GTest REQUIRED)
	find_package (GMock REQUIRED)
	
	include_directories (${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})
	
	add_executable (MyelinTest ${TEST_SOURCE_FILES})
	
	target_link_libraries (MyelinTest
		${GTEST_LIBRARIES}
		${GMOCK_BOTH_LIBRARIES}
		pthread)
	
	add_test (AllTestsInMyelin MyelinTest)

endif()