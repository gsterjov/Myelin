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
	TOKEN_LBRACE = '{';
	TOKEN_RBRACE = '}';
	TOKEN_LBRACKET = '[';
	TOKEN_RBRACKET = ']';
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

	NODE_PRIMITIVE;
	NODE_STORAGE_QUALIFIER;
	NODE_STORAGE_CLASS;

	NODE_FUNCTION_SPECIFIER;

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
	|	'unsigned'
	|	'void')
			-> ^(NODE_PRIMITIVE 'char' 'short' 'int' 'long' 'signed' 'unsigned' 'void')
	;


/* cv qualifiers */
fragment
storage_qualifier
	:	('volatile' | 'const')
			-> ^(NODE_STORAGE_QUALIFIER 'const' 'volatile')
	;


/* storage type */
fragment
storage_class
	:	('static' | 'extern' | 'register')
			-> ^(NODE_STORAGE_CLASS 'static' 'extern' 'register')
	;


/* function specifiers */
fragment
function_specifier
	:	('virtual' | 'inline')
			-> ^(NODE_FUNCTION_SPECIFIER 'virtual' 'inline')
	;



/******************************************************************************
 * Declaration specifiers                                                     *
 ******************************************************************************/


/* an entire block, ie. everything between { and } */
fragment
block
	:	TOKEN_LBRACE (options {greedy=false;} : ~TOKEN_RBRACE)* TOKEN_RBRACE
	;


/* a simple assignment rule */
fragment
assignment
	:	TOKEN_EQUALS (ID | INT)
	;


/* pointer specifier */
fragment
pointer_specifier
	:	storage_qualifier? TOKEN_ASTERIX
			-> ^(NODE_POINTER storage_qualifier)
	;


/* reference specifier */
fragment
reference_specifier
	:	storage_qualifier? TOKEN_AMPERSAND
			-> ^(NODE_REFERENCE storage_qualifier)
	;


fragment
type_name
	:	ID
			-> ^(NODE_TYPE_NAME ID)
	;


fragment
qualified_name
	:	type_name (TOKEN_COLON TOKEN_COLON type_name)*
			-> type_name*
	;


fragment
type
	:	storage_qualifier* (primitive | qualified_name) pointer_specifier? reference_specifier?
			-> ^(NODE_TYPE storage_qualifier* primitive qualified_name pointer_specifier reference_specifier)
	;


fragment
param
	:	type ID -> ^(NODE_PARAMETER type ID)
	;


fragment
class_inheritance
	:	TOKEN_COLON ID
	;



function_declaration
	:	storage_class? type
		ID TOKEN_LPAREN (param (TOKEN_COMMA param)*)? TOKEN_RPAREN
		storage_qualifier* ((assignment? TOKEN_SEMICOL) | block)
			-> ^(NODE_FUNCTION storage_class type ID param* storage_qualifier*)
	;


class_members
	: function_declaration
	| class_declaration
	;


class_declaration
	:	'class' ID class_inheritance? TOKEN_LBRACE class_members* TOKEN_RBRACE TOKEN_SEMICOL
			-> ^(NODE_CLASS ID class_members*)
	;


declaration
	:	function_declaration
	|	class_declaration
	;


source
	:	(declaration)* EOF
			-> ^(NODE_SOURCE declaration*)
	;





// Lexer Rules

ID 
	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
	;


INT
	:	'0'..'9'+
	;


//FLOAT
//	:	('0'..'9')+ '.' ('0'..'9')* EXPONENT?
//	|	'.' ('0'..'9')+ EXPONENT?
//	|	('0'..'9')+ EXPONENT
//	;


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

