grammar CppHeader;

options
{
	language = C;
	output = AST;
	ASTLabelType = pANTLR3_BASE_TREE;
	backtrack = true;
}


tokens
{
	LBRACE = '(';
	RBRACE = ')';
	LPAREN = '{';
	RPAREN = '}';
	LSQUARE_BRACKET = '[';
	RSQUARE_BRACKET = ']';
	TK_LT = '<';
	TK_GT = '>';
	COMMA = ',';
	COLON = ':';
	SEMICOL = ';';
	ASTERIX = '*';
	AMPERSAND = '&';
	HASH = '#';
	TILDE = '~';
	BACKSLASH = '\\';
	FORWARD_SLASH = '/';
	PERIOD = '.';
	EQUALS = '=';
	
	
	SOURCE;
	QUALIFIERS;
	POINTER;
	REFERENCE;
	TYPE;
	TYPE_NAME;
	FUNCTION_PTR;
	TYPEDEF;
	TEMPLATE_PARAMS;
	PARAMETER;
	NAMESPACE;
	CLASS;
	CONSTRUCTOR;
	DESTRUCTOR;
	FUNCTION;
	ENUMERATION;
}




// Parser Rules

fragment
assignment
	:	EQUALS (ID | INT)
	;


fragment
block
	:	LPAREN (options {greedy=false;} : ~RPAREN)* RPAREN
	;


fragment
qualifiers
	:	('volatile' 'const') | ('const' 'volatile') | ('const' | 'volatile')
			-> ^(QUALIFIERS 'const' 'volatile')
	;


fragment
modifiers
	:	('static' | 'virtual')
	;


fragment
pointer
	:	qualifiers? ASTERIX
			-> ^(POINTER qualifiers ASTERIX)
	;

fragment
reference
	:	qualifiers? AMPERSAND
			-> ^(REFERENCE qualifiers AMPERSAND)
	;

fragment
template_decl
	:	TK_LT ('typename' | 'class') ID (COMMA ('typename' | 'class') ID)* TK_GT
	;

fragment
template_params
	:	TK_LT (type (COMMA type)*)? TK_GT
			-> ^(TEMPLATE_PARAMS type*)
	;

fragment
type_name
	:	ID template_params?
			-> ^(TYPE_NAME ID template_params)
	;

fragment
qualified_name
	:	type_name (COLON COLON type_name)*
			-> type_name*
	;


fragment
type
	:	qualifiers? qualified_name pointer? reference?
			-> ^(TYPE qualifiers qualified_name pointer reference)
	;


fragment
function_pointer
	:	type LBRACE ASTERIX ID RBRACE LBRACE (param (COMMA param)*)? RBRACE
			-> ^(FUNCTION_PTR type ID param*)
	;


fragment
param
	:	type ID assignment?
			-> ^(PARAMETER type ID)
	;


fragment
compiler_attr
	:	(options {greedy=false;} : ID)* ID
	;


fragment
class_inheritance
	:	COLON 'public' ID
	;


fragment
private_section
	:	'private' COLON
	;

fragment
protected_section
	:	'protected' COLON
	;

fragment
public_section
	:	'public' COLON
	;


fragment
member
	:	modifiers? type ID SEMICOL
	;


fragment
init_list
	:	COLON ID LBRACE (ID | INT) RBRACE (COMMA ID LBRACE (ID | INT) RBRACE)*
	;


c_api
	:	'extern' '"C"' block
	;


nspace
	:	'namespace' ID LPAREN declaration* RPAREN
			-> ^(NAMESPACE ID declaration*)
	;


forward_klass
	:	'class' ID SEMICOL
	;


class_decl
	:	private_section!
	|	protected_section!
	|	public_section!
	|	enumeration
	|	type_def
	|	template_func!
	|	operator_overload!
	|	func
	|	constructor
	|	destructor
	|	member!
	;


klass
	:	'class' compiler_attr? ID class_inheritance? LPAREN
		class_decl*
		RPAREN SEMICOL
			-> ^(CLASS ID class_decl*)
	;


constructor
	:	'explicit'? ID LBRACE (param (COMMA param)*)? RBRACE init_list? (SEMICOL | block)
			-> ^(CONSTRUCTOR ID param*)
	;


destructor
	:	modifiers? TILDE ID LBRACE (param (COMMA param)*)? RBRACE (SEMICOL | block)
			-> ^(DESTRUCTOR ID param*)
	;


template_func
	:	'template' template_decl (func | operator_overload)
	;


operator_overload
	:	modifiers? type 'operator' ('[]'|'->'|'+'|'-'|'/'|'*'|'='|'=='|'!=')? 
			LBRACE (param (COMMA param)*)? RBRACE
				qualifiers? (SEMICOL | block)
	;


func
	:	modifiers? type ID LBRACE (param (COMMA param)*)? RBRACE
			qualifiers? ((assignment? SEMICOL) | block)
			-> ^(FUNCTION type ID param* qualifiers)
	;


enumeration
	:	'enum' ID block SEMICOL
			-> ^(ENUMERATION ID)
	;


type_def
	:	'typedef' ((type ID) | function_pointer) SEMICOL
			-> ^(TYPEDEF type ID function_pointer)
	;


declaration
	:	template_func!
	|	func
	|	enumeration
	|	type_def
	|	klass
	|	forward_klass!
	|	c_api!
	;


source
	:	(nspace | declaration)* EOF
			-> ^(SOURCE nspace* declaration*)
	;





// Lexer Rules

ID 
	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
	;


INT
	:	'0'..'9'+
	;


FLOAT
	:	('0'..'9')+ '.' ('0'..'9')* EXPONENT?
	|	'.' ('0'..'9')+ EXPONENT?
	|	('0'..'9')+ EXPONENT
	;


COMMENT
	:	'//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
	|	'/*' (options {greedy=false;} : .)* '*/' {$channel=HIDDEN;}
	;


PREPROCESSOR
	:	'#' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
	;


WS
	:	(' '|'\t'|'\r'|'\n')+ {$channel=HIDDEN;}
	;


STRING
	:	'"' (ESC_SEQ | ~('\\' | '"'))* '"'
	;


CHAR
	:	'\'' (ESC_SEQ | ~('\'' | '\\')) '\''
	;


fragment
EXPONENT
	:	('e'|'E') ('+'|'-')? ('0'..'9')+
	;


fragment
HEX_DIGIT
	:	('0'..'9' | 'a'..'f' | 'A'..'F')
	;


fragment
ESC_SEQ
	:	'\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
	|	UNICODE_ESC
	|	OCTAL_ESC
	;


fragment
OCTAL_ESC
	:	'\\' ('0'..'3') ('0'..'7') ('0'..'7')
	|	'\\' ('0'..'7') ('0'..'7')
	|	'\\' ('0'..'7')
	;


fragment
UNICODE_ESC
	:	'\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
	;

