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
	|	klass
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

