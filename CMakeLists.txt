
cmake_minimum_required (VERSION 2.6)


set (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)


option (BUILD_MYELIN "Build the Myelin introspection library")
option (BUILD_GENERATOR "Build the Myelin introspection generator?")
option (BUILD_VIEWER "Build the Myelin introspection viewer?")

option (BUILD_TESTS "Build unit tests and create test target?")



# build the generator
if (BUILD_GENERATOR)
	add_subdirectory (src/Generator)
endif()

# build the main library
if (BUILD_MYELIN)
	add_subdirectory (src/Myelin)
endif()

# build the viewer
if (BUILD_VIEWER)
	add_subdirectory (src/Viewer)
endif()



################################################################################
#     build bindings                                                           #
################################################################################
add_subdirectory (bindings)



################################################################################
#     build tests                                                              #
################################################################################
if (BUILD_TESTS)
	
	set (TEST_SOURCE_FILES
		test/ClassTest.cpp
		test/FunctionTest.cpp
		test/TypeTest.cpp
		test/ValueTest.cpp
		test/WrapperTest.cpp
		
		test/main.cpp
		test/gtest/gmock-gtest-all.cc)
	
	
	enable_testing ()
	
	include_directories (test/gtest)
	
	add_executable (MyelinTest ${TEST_SOURCE_FILES})
	target_link_libraries (MyelinTest Myelin pthread)
	
	add_test (AllTestsInMyelin MyelinTest)
	
	
	
	add_library (LibraryTest SHARED test/LibraryTest.cpp)
	target_link_libraries (LibraryTest Myelin)
	
	add_library (SimpleTest SHARED test/SimpleTest.cpp)
	target_link_libraries (SimpleTest Myelin)
	
endif()
