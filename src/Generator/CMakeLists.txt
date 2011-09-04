

project (MyelinGenerator)


set (ANTLR_TOOL "" CACHE FILEPATH "The path to the ANTLR generator tool")


set (ANTLR_RUNTIME
	antlr/antlr3baserecognizer.c
	antlr/antlr3basetree.c
	antlr/antlr3basetreeadaptor.c
	antlr/antlr3bitset.c
	antlr/antlr3collections.c
	antlr/antlr3commontoken.c
	antlr/antlr3commontree.c
	antlr/antlr3commontreeadaptor.c
	antlr/antlr3commontreenodestream.c
	antlr/antlr3convertutf.c
	antlr/antlr3cyclicdfa.c
	antlr/antlr3debughandlers.c
	antlr/antlr3encodings.c
	antlr/antlr3exception.c
	antlr/antlr3filestream.c
	antlr/antlr3inputstream.c
	antlr/antlr3intstream.c
	antlr/antlr3lexer.c
	antlr/antlr3parser.c
	antlr/antlr3rewritestreams.c
	antlr/antlr3string.c
	antlr/antlr3stringstream.c
	antlr/antlr3tokenstream.c
	antlr/antlr3treeparser.c
	antlr/antlr3ucs2inputstream.c
)


set (GRAMMAR_FILES
	CppHeader.g
	CppHeaderTree.g
)


set (SOURCE_FILES
	Parser.cpp
	Generator.cpp
	main.cpp
	
	NamespaceParser.cpp
	ClassParser.cpp
	FunctionParser.cpp
	TypeParser.cpp
	TypedefParser.cpp
)



include_directories (
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/Generator
	${CMAKE_SOURCE_DIR}/include/Generator/antlr
	${PROJECT_BINARY_DIR}
)




################################################################################
#     generate parser                                                          #
################################################################################

if (ANTLR_TOOL)
	add_custom_command (
		OUTPUT ${PROJECT_BINARY_DIR}/CppHeaderLexer.c
		       ${PROJECT_BINARY_DIR}/CppHeaderParser.c
		       ${PROJECT_BINARY_DIR}/CppHeaderTree.c
		COMMAND java -jar ${ANTLR_TOOL} ${GRAMMAR_FILES}
		        -o ${PROJECT_BINARY_DIR}/
		DEPENDS ${GRAMMAR_FILES}
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
		COMMENT "Generating C++ source code parser"
	)
	
	
	set (SOURCE_FILES ${SOURCE_FILES}
		${PROJECT_BINARY_DIR}/CppHeaderLexer.c
		${PROJECT_BINARY_DIR}/CppHeaderParser.c
		${PROJECT_BINARY_DIR}/CppHeaderTree.c
	)
endif()




################################################################################
#     process templates                                                        #
################################################################################

add_custom_command (
	OUTPUT ${PROJECT_BINARY_DIR}/TemplateVars.h
	COMMAND template-converter TemplateVars ${PROJECT_SOURCE_DIR}/template.tpl TemplateVars.h
	DEPENDS template.tpl
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	COMMENT "Processing template files"
)

set (SOURCE_FILES ${SOURCE_FILES}
	${PROJECT_BINARY_DIR}/TemplateVars.h
)


################################################################################
#     build generator                                                          #
################################################################################

add_executable (myelin-generate ${SOURCE_FILES} ${ANTLR_RUNTIME})
set_source_files_properties (${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")

target_link_libraries (myelin-generate ctemplate_nothreads)

install (TARGETS myelin-generate DESTINATION bin)

