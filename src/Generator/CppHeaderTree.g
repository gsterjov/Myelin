tree grammar CppHeaderTree;


options
{
	language = C;
	output = AST;
	tokenVocab = CppHeader;
	ASTLabelType = pANTLR3_BASE_TREE;
}



source
	:	^(SOURCE nspace* declaration*)
	;



declaration
	:	func
	|	enumeration
	|	type_def
	|	klass
	;


qualifiers
	:	^(QUALIFIERS 'const'? 'volatile'?)
	;


pointer
	:	^(POINTER qualifiers? ASTERIX)
	;

reference
	:	^(REFERENCE qualifiers? AMPERSAND)
	;


template_params
	:	^(TEMPLATE_PARAMS type*)
	;


type_name
	:	^(TYPE_NAME ID template_params?)
	;


qualified_name
	:	type_name*
	;


type
	:	^(TYPE qualifiers? qualified_name pointer? reference?)
	;
	

function_pointer
	:	^(FUNCTION_PTR type ID param*)
	;


param
	:	^(PARAMETER type ID)
	;


nspace
	:	^(NAMESPACE ID declaration*)
	;


class_decl
	:	func
	|	enumeration
	|	type_def
	|	constructor
	|	destructor
	;


klass
	:	^(CLASS ID class_decl*)
	;


constructor
	:	^(CONSTRUCTOR ID param*)
	;


destructor
	:	^(DESTRUCTOR ID param*)
	;


func
	:	^(FUNCTION type ID param* qualifiers?)
	;


enumeration
	:	^(ENUMERATION ID)
	;


type_def
	:	^(TYPEDEF ((type ID) | function_pointer))
	;

