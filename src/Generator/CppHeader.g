/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

grammar CppHeader;

options
{
	language = C;
	output = AST;
	ASTLabelType = pANTLR3_BASE_TREE;
	backtrack = true;
	k = 2;
}


tokens
{
	// syntax tokens
	TOKEN_LPAREN = '(';
	TOKEN_RPAREN = ')';
	TOKEN_LCURLY_BRACE = '{';
	TOKEN_LCURLY_BRACE = '}';
	TOKEN_LSQUARE_BRACE = '[';
	TOKEN_RSQUARE_BRACE = ']';
	TOKEN_LESS_THAN = '<';
	TOKEN_GREATER_THAN = '>';
	TOKEN_COMMA = ',';
	TOKEN_COLON = ':';
	TOKEN_SEMICOL = ';';
	TOKEN_ASTERIX = '*';
	TOKEN_AMPERSAND = '&';
	TOKEN_HASH = '#';
	TOKEN_TILDE = '~';
	TOKEN_BACKSLASH = '\\';
	TOKEN_FORWARD_SLASH = '/';
	TOKEN_PERIOD = '.';
	TOKEN_EQUALS = '=';
	TOKEN_EXCLAMATION = '!';
	TOKEN_PIPE = '|';
	
	
	// types
	NODE_POINTER;
	NODE_REFERENCE;
	
	
	// specifiers
	NODE_NAMESPACE;
	NODE_CLASS;
	NODE_STRUCTURE;
	NODE_UNION;
	NODE_TYPEDEF;
	NODE_TEMPLATE;
	
	
	// syntax types
	NODE_SOURCE;
	NODE_QUALIFIER;
	NODE_TYPE;
	NODE_TYPE_NAME;
	NODE_FUNCTION_PTR;
	NODE_TYPEDEF;
	NODE_TEMPLATE_PARAMS;
	NODE_PARAMETER;
	NODE_NAMESPACE;
	NODE_CONSTRUCTOR;
	NODE_DESTRUCTOR;
	NODE_FUNCTION;
	NODE_ENUMERATION;
}




// Parser Rules


/* primitive types */
fragment
primitive
	:	('char'
	|	'short'
	|	'int'
	|	'long'
	|	'signed'
	|	'unsigned')+
	;


/* a simple assignment rule */
fragment
assignment
	:	TOKEN_EQUALS (ID | INT)
	;


/* an entire block, ie. everything between { and } */
fragment
block
	:	TOKEN_LCURLY_BRACE (options {greedy=false;} : ~TOKEN_RCURLY_BRACE)* TOKEN_RCURLY_BRACE
	;




/******************************************************************************
 * Declaration specifiers                                                     *
 ******************************************************************************/


/* cv_qualifiers for types */
fragment
type_qualifier
	:	('volatile' | 'const')+
			-> ^(NODE_QUALIFIER 'const' 'volatile')
	;


/* how the declaration is stored */
fragment
storage_specifier
	:	'static'
	|	'extern'
	|	'register'
	;


/* function modifiers */
fragment
function_specifier
	:	'inline'
	|	'virtual'
	|	'explicit'
	;




/******************************************************************************
 * Specifiers                                                            *
 ******************************************************************************/


/* access specifier */
fragment
access_specifier
	:	'private'
	|	'protected'
	|	'public'
	;


/* class specifier */
fragment
class_specifier
	:	'class'
			-> ^(NODE_CLASS)
	;


/* structure specifier */
fragment
structure_specifier
	:	'class'
			-> ^(NODE_STRUCTURE)
	;


/* union specifier */
fragment
union_specifier
	:	'union'
			-> ^(NODE_UNION)
	;


/* namespace specifier */
fragment
namespace_specifier
	:	'namespace'
			-> ^(NODE_NAMESPACE)
	;


/* namespace specifier */
fragment
typedef_specifier
	:	'typedef'
			-> ^(NODE_TYPEDEF)
	;


/* template specifier */
fragment
template_specifier
	:	'template'
			-> ^(NODE_TEMPLATE)
	;


/* types within a template declarator */
fragment
template_type_specifier
	:	'typename'
	|	'class'
	;





/* pointer specifier */
fragment
type_pointer_specifier
	:	type_qualifier? TOKEN_ASTERIX
			-> ^(NODE_POINTER type_qualifier)
	;


/* reference specifier */
fragment
type_reference_specifier
	:	type_qualifer? TOKEN_AMPERSAND
			-> ^(NODE_REFERENCE type_qualifier TOKEN_AMPERSAND)
	;





fragment
template_type_declarator
	:	TK_LT template_type_specifier ID (COMMA (template_type_specifier ID)* TK_GT
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
	:	qualifiers? (primitive | qualified_name) pointer? reference?
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
	|	klass
	;


klass
	:	'class' compiler_attr? ID class_inheritance? LPAREN
		class_decl*
		RPAREN SEMICOL
			-> ^(CLASS ID class_decl*)
	;


structure
	:	'struct' compiler_attr? ID class_inheritance? LPAREN
		class_decl*
		RPAREN SEMICOL
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


template_structure
	:	'template' template_decl structure
	;


template_variable
	:	'template' template_decl variable
	;


operator_overload
	:	modifiers? type 'operator' ('[]'|'->'|'+'|'-'|'/'|'*'|'='|'=='|'!=')? 
			LBRACE (param (COMMA param)*)? RBRACE
				qualifiers? (SEMICOL | block)
	;


func
	:	compiler_attr? modifiers? type ID LBRACE (param (COMMA param)*)? RBRACE
			qualifiers? ((assignment? SEMICOL) | block)
			-> ^(FUNCTION type ID param* qualifiers)
	;


variable
	:	compiler_attr? modifiers? type type_name SEMICOL
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
	|	structure!
	|	template_structure!
	|	forward_klass!
	|	c_api!
	|	template_variable!
	|	variable!
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

