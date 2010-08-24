
cmake_minimum_required (VERSION 2.6)
project (Myelin)


set (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)


option (BUILD_TESTS "Build unit tests and create test target?")


configure_file (
	${PROJECT_SOURCE_DIR}/MyelinConfig.cmake.in
	${PROJECT_BINARY_DIR}/MyelinConfig.cmake
	@ONLY)



set (SOURCE_FILES
	src/Class.cpp
	src/Function.cpp
	src/List.cpp
	src/Object.cpp
	src/Repository.cpp
	src/Value.cpp)


set (HEADER_FILES
	include/Myelin/Class.h
	include/Myelin/Function.h
	include/Myelin/Functor.h
	include/Myelin/GenericClass.h
	include/Myelin/GenericFunction.h
	include/Myelin/GenericObject.h
	include/Myelin/List.h
	include/Myelin/Object.h
	include/Myelin/Repository.h
	include/Myelin/Type.h
	include/Myelin/Value.h)



include_directories (
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/Myelin)




add_library (Myelin SHARED ${SOURCE_FILES} ${HEADER_FILES})


add_library (MyelinTestLibrary SHARED test/LibraryTest.cpp)
target_link_libraries (MyelinTestLibrary Myelin)


install (TARGETS Myelin EXPORT MyelinTargets DESTINATION lib)
install (EXPORT MyelinTargets DESTINATION lib/cmake/Myelin)
install (FILES ${PROJECT_BINARY_DIR}/MyelinConfig.cmake DESTINATION lib/cmake/Myelin)

install (FILES ${HEADER_FILES} DESTINATION include/Myelin)




################################################################################
#     build engine tests                                                       #
################################################################################
if (BUILD_TESTS)
	
	set (TEST_SOURCE_FILES
		test/ClassTest.cpp
		test/FunctionTest.cpp
		test/ValueTest.cpp)
	
	
	enable_testing ()
	find_package (GTest REQUIRED)
	find_package (GMock REQUIRED)
	
	include_directories (${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})
	
	add_executable (MyelinTest ${TEST_SOURCE_FILES})
	
	target_link_libraries (MyelinTest
		Myelin
		${GTEST_LIBRARIES}
		${GMOCK_BOTH_LIBRARIES}
		pthread)
	
	add_test (AllTestsInMyelin MyelinTest)
	
endif()
