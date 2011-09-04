

project (Myelin)

include (SourceUtils)


option (BUILD_INTROSPECTION "Build Myelin with introspection metadata?")

set (HEADERS_DIR ${CMAKE_SOURCE_DIR}/include/Myelin)



configure_file (
	${PROJECT_SOURCE_DIR}/MyelinConfig.cmake.in
	${PROJECT_BINARY_DIR}/MyelinConfig.cmake
	@ONLY)



set (SOURCE_FILES
	Class.cpp
	Constructor.cpp
	Converter.cpp
	List.cpp
	Function.cpp
	Namespace.cpp
	Object.cpp
	Repository.cpp
	Type.cpp
	TypeUtils.cpp
	Value.cpp
	VTable.cpp
)


set_headers (HEADER_FILES PATH ${HEADERS_DIR}
	Class.h
	Config.h
	Constructor.h
	Converter.h
	Function.h
	List.h
	Myelin.h
	Namespace.h
	Object.h
	RefCounter.h
	Repository.h
	Type.h
	TypeTraits.h
	TypeUtils.h
	Value.h
	VTable.h
)

set_headers (TYPES_HEADER_FILES PATH ${HEADERS_DIR}/Types
	ClassType.h
	ConstructorType.h
	ConverterType.h
	FreeFunctionType.h
	FunctionType.h
	MemberFunctionType.h
	ParameterType.h
)

set_headers (INTROSPECTION_HEADERS PATH ${HEADERS_DIR}
	Class.h
	Config.h
	Constructor.h
	Converter.h
	Function.h
	List.h
	Myelin.h
	Namespace.h
	Object.h
	RefCounter.h
	Repository.h
	Type.h
	#TypeTraits.h
	#TypeUtils.h
	#Value.h
	#VTable.h
)



# introspection enabled
if (BUILD_INTROSPECTION)
	
	add_custom_command (
		OUTPUT ${PROJECT_BINARY_DIR}/Introspection.cpp
		COMMAND ${MyelinGenerator_BINARY_DIR}/myelin-generate
			-I ${HEADERS_DIR}
			-o ${PROJECT_BINARY_DIR}
			Myelin
			${INTROSPECTION_HEADERS}
		DEPENDS ${INTROSPECTION_HEADERS}
	)
	
	set (SOURCE_FILES ${SOURCE_FILES} ${PROJECT_BINARY_DIR}/Introspection.cpp)
	
endif()



include_directories (
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/Myelin
)




################################################################################
#     build library                                                            #
################################################################################

add_library (Myelin SHARED ${SOURCE_FILES} ${HEADER_FILES} ${TYPES_HEADER_FILES})
set_target_properties (Myelin PROPERTIES COMPILE_FLAGS "-DMYELIN_DLL -DMYELIN_DLL_EXPORTS -fvisibility=hidden -fvisibility-inlines-hidden")


install (TARGETS Myelin EXPORT MyelinTargets DESTINATION lib)
install (EXPORT MyelinTargets DESTINATION lib/cmake/Myelin)
install (FILES ${PROJECT_BINARY_DIR}/MyelinConfig.cmake DESTINATION lib/cmake/Myelin)

install (FILES ${HEADER_FILES} DESTINATION include/Myelin)
install (FILES ${TYPES_HEADER_FILES} DESTINATION include/Myelin/Types)

