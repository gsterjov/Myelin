
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
	src/Constructor.cpp
	src/Converter.cpp
	src/List.cpp
	src/Function.cpp
	src/Namespace.cpp
	src/Object.cpp
	src/Repository.cpp
	src/RepositoryFactory.cpp
	src/Type.cpp
	src/Value.cpp
	src/VTable.cpp)


set (HEADER_FILES
	include/Myelin/Class.h
	include/Myelin/Config.h
	include/Myelin/Constructor.h
	include/Myelin/Converter.h
	include/Myelin/Function.h
	include/Myelin/List.h
	include/Myelin/Myelin.h
	include/Myelin/Namespace.h
	include/Myelin/Object.h
	include/Myelin/RefCounter.h
	include/Myelin/Repository.h
	include/Myelin/RepositoryFactory.h
	include/Myelin/Type.h
	include/Myelin/TypeTraits.h
	include/Myelin/Value.h
	include/Myelin/VTable.h)

set (TYPES_HEADER_FILES
	include/Myelin/Types/ClassType.h
	include/Myelin/Types/ConstructorType.h
	include/Myelin/Types/ConverterType.h
	include/Myelin/Types/FreeFunctionType.h
	include/Myelin/Types/FunctionType.h
	include/Myelin/Types/MemberFunctionType.h
	include/Myelin/Types/ParameterType.h)



include_directories (
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/Myelin)




################################################################################
#     build introspection                                                      #
################################################################################

set (SOURCE_FILES ${SOURCE_FILES} src/Introspection/CreateRepository.cpp)




add_library (Myelin SHARED ${SOURCE_FILES} ${HEADER_FILES} ${TYPES_HEADER_FILES})
set_target_properties (Myelin PROPERTIES COMPILE_FLAGS "-DMYELIN_DLL -DMYELIN_DLL_EXPORTS -fvisibility=hidden -fvisibility-inlines-hidden")


install (TARGETS Myelin EXPORT MyelinTargets DESTINATION lib)
install (EXPORT MyelinTargets DESTINATION lib/cmake/Myelin)
install (FILES ${PROJECT_BINARY_DIR}/MyelinConfig.cmake DESTINATION lib/cmake/Myelin)

install (FILES ${HEADER_FILES} DESTINATION include/Myelin)
install (FILES ${TYPES_HEADER_FILES} DESTINATION include/Myelin/Types)




################################################################################
#     build engine tests                                                       #
################################################################################
if (BUILD_TESTS)
	
	set (TEST_SOURCE_FILES
		test/ClassTest.cpp
		test/FunctionTest.cpp
		test/IntrospectionTest.cpp
		test/TypeTest.cpp
		test/ValueTest.cpp
		test/WrapperTest.cpp)
	
	
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
	
	
	
	add_library (LibraryTest SHARED test/LibraryTest.cpp)
	target_link_libraries (LibraryTest Myelin)
	
	add_library (SimpleTest SHARED test/SimpleTest.cpp)
	target_link_libraries (SimpleTest Myelin)
	
endif()




################################################################################
#     build bindings                                                           #
################################################################################
add_subdirectory (bindings)

