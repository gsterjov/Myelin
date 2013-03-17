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
	TOKEN_RCURLY_BRACE = '}';
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
	NODE_PRIMITIVE;
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

	NODE_ID;
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
	|	'void')+
			-> ^(NODE_PRIMITIVE 'char' 'short' 'int' 'long' 'signed' 'unsigned' 'void')
	;



/******************************************************************************
 * Declaration specifiers                                                     *
 ******************************************************************************/


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
	:	(primitive | qualified_name)
			-> ^(NODE_TYPE primitive qualified_name)
	;


fragment
param
	:	type ID -> ^(NODE_PARAMETER type ID)
	;


function_declaration
	:	type ID TOKEN_LPAREN (param (TOKEN_COMMA param)*)? TOKEN_RPAREN TOKEN_SEMICOL
			-> ^(NODE_FUNCTION type ID param*)
	;


variable_declaration
	:	type ID TOKEN_SEMICOL
	;


declaration
	:	function_declaration
	|	variable_declaration
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

