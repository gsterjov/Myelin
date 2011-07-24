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


qualified_name
	:	ID*
	;


type
	:	^(TYPE qualifiers? qualified_name pointer? reference?)
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

