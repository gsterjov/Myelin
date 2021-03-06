/** \file
 *  This C header file was generated by $ANTLR version 3.5
 *
 *     -  From the grammar source file : /devel/source/Myelin/src/Generator/CppHeader.g
 *     -                            On : 2013-03-20 21:27:18
 *     -                for the parser : CppHeaderParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser 
CppHeaderParser

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pCppHeaderParser, which is returned from a call to CppHeaderParserNew().
 *
 * The methods in pCppHeaderParser are  as follows:
 *
 *  - 
 CppHeaderParser_primitive_return
      pCppHeaderParser->primitive(pCppHeaderParser)
 *  - 
 CppHeaderParser_storage_qualifier_return
      pCppHeaderParser->storage_qualifier(pCppHeaderParser)
 *  - 
 CppHeaderParser_storage_class_return
      pCppHeaderParser->storage_class(pCppHeaderParser)
 *  - 
 CppHeaderParser_access_specifier_return
      pCppHeaderParser->access_specifier(pCppHeaderParser)
 *  - 
 CppHeaderParser_function_specifier_return
      pCppHeaderParser->function_specifier(pCppHeaderParser)
 *  - 
 CppHeaderParser_block_return
      pCppHeaderParser->block(pCppHeaderParser)
 *  - 
 CppHeaderParser_assignment_return
      pCppHeaderParser->assignment(pCppHeaderParser)
 *  - 
 CppHeaderParser_pointer_specifier_return
      pCppHeaderParser->pointer_specifier(pCppHeaderParser)
 *  - 
 CppHeaderParser_reference_specifier_return
      pCppHeaderParser->reference_specifier(pCppHeaderParser)
 *  - 
 CppHeaderParser_type_name_return
      pCppHeaderParser->type_name(pCppHeaderParser)
 *  - 
 CppHeaderParser_qualified_name_return
      pCppHeaderParser->qualified_name(pCppHeaderParser)
 *  - 
 CppHeaderParser_type_return
      pCppHeaderParser->type(pCppHeaderParser)
 *  - 
 CppHeaderParser_param_return
      pCppHeaderParser->param(pCppHeaderParser)
 *  - 
 CppHeaderParser_class_inheritance_return
      pCppHeaderParser->class_inheritance(pCppHeaderParser)
 *  - 
 CppHeaderParser_function_declaration_return
      pCppHeaderParser->function_declaration(pCppHeaderParser)
 *  - 
 CppHeaderParser_class_members_return
      pCppHeaderParser->class_members(pCppHeaderParser)
 *  - 
 CppHeaderParser_class_declaration_return
      pCppHeaderParser->class_declaration(pCppHeaderParser)
 *  - 
 CppHeaderParser_namespace_declaration_return
      pCppHeaderParser->namespace_declaration(pCppHeaderParser)
 *  - 
 CppHeaderParser_declaration_return
      pCppHeaderParser->declaration(pCppHeaderParser)
 *  - 
 CppHeaderParser_source_return
      pCppHeaderParser->source(pCppHeaderParser)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_CppHeaderParser_H
#define _CppHeaderParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct CppHeaderParser_Ctx_struct CppHeaderParser, * pCppHeaderParser;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/* ========================
 * BACKTRACKING IS ENABLED
 * ========================
 */

typedef struct CppHeaderParser_primitive_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_primitive_return;



typedef struct CppHeaderParser_storage_qualifier_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_storage_qualifier_return;



typedef struct CppHeaderParser_storage_class_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_storage_class_return;



typedef struct CppHeaderParser_access_specifier_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_access_specifier_return;



typedef struct CppHeaderParser_function_specifier_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_function_specifier_return;



typedef struct CppHeaderParser_block_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_block_return;



typedef struct CppHeaderParser_assignment_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_assignment_return;



typedef struct CppHeaderParser_pointer_specifier_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_pointer_specifier_return;



typedef struct CppHeaderParser_reference_specifier_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_reference_specifier_return;



typedef struct CppHeaderParser_type_name_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_type_name_return;



typedef struct CppHeaderParser_qualified_name_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_qualified_name_return;



typedef struct CppHeaderParser_type_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_type_return;



typedef struct CppHeaderParser_param_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_param_return;



typedef struct CppHeaderParser_class_inheritance_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_class_inheritance_return;



typedef struct CppHeaderParser_function_declaration_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_function_declaration_return;



typedef struct CppHeaderParser_class_members_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_class_members_return;



typedef struct CppHeaderParser_class_declaration_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_class_declaration_return;



typedef struct CppHeaderParser_namespace_declaration_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_namespace_declaration_return;



typedef struct CppHeaderParser_declaration_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_declaration_return;



typedef struct CppHeaderParser_source_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    CppHeaderParser_source_return;




/** Context tracking structure for 
CppHeaderParser

 */
struct CppHeaderParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;

     CppHeaderParser_primitive_return
     (*primitive)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_storage_qualifier_return
     (*storage_qualifier)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_storage_class_return
     (*storage_class)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_access_specifier_return
     (*access_specifier)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_function_specifier_return
     (*function_specifier)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_block_return
     (*block)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_assignment_return
     (*assignment)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_pointer_specifier_return
     (*pointer_specifier)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_reference_specifier_return
     (*reference_specifier)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_type_name_return
     (*type_name)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_qualified_name_return
     (*qualified_name)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_type_return
     (*type)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_param_return
     (*param)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_class_inheritance_return
     (*class_inheritance)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_function_declaration_return
     (*function_declaration)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_class_members_return
     (*class_members)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_class_declaration_return
     (*class_declaration)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_namespace_declaration_return
     (*namespace_declaration)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_declaration_return
     (*declaration)	(struct CppHeaderParser_Ctx_struct * ctx);

     CppHeaderParser_source_return
     (*source)	(struct CppHeaderParser_Ctx_struct * ctx);
    // Delegated rules

    const char * (*getGrammarFileName)();
    void            (*reset)  (struct CppHeaderParser_Ctx_struct * ctx);
    void	    (*free)   (struct CppHeaderParser_Ctx_struct * ctx);
/* @headerFile.members() */
pANTLR3_BASE_TREE_ADAPTOR	adaptor;
pANTLR3_VECTOR_FACTORY		vectors;
/* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pCppHeaderParser CppHeaderParserNew         (
pANTLR3_COMMON_TOKEN_STREAM
 instream);
ANTLR3_API pCppHeaderParser CppHeaderParserNewSSD      (
pANTLR3_COMMON_TOKEN_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
parser
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__60      60
#define T__61      61
#define T__62      62
#define T__63      63
#define T__64      64
#define T__65      65
#define T__66      66
#define T__67      67
#define T__68      68
#define T__69      69
#define T__70      70
#define T__71      71
#define T__72      72
#define T__73      73
#define T__74      74
#define T__75      75
#define T__76      76
#define T__77      77
#define T__78      78
#define CHAR      4
#define COMMENT      5
#define ESC_SEQ      6
#define EXPONENT      7
#define HEX_DIGIT      8
#define ID      9
#define INT      10
#define NODE_ACCESS_SPECIFIER      11
#define NODE_CLASS      12
#define NODE_CONSTRUCTOR      13
#define NODE_DESTRUCTOR      14
#define NODE_ENUMERATION      15
#define NODE_FUNCTION      16
#define NODE_FUNCTION_PTR      17
#define NODE_FUNCTION_SPECIFIER      18
#define NODE_NAMESPACE      19
#define NODE_PARAMETER      20
#define NODE_POINTER      21
#define NODE_PRIMITIVE      22
#define NODE_REFERENCE      23
#define NODE_SOURCE      24
#define NODE_STORAGE_CLASS      25
#define NODE_STORAGE_QUALIFIER      26
#define NODE_STRUCTURE      27
#define NODE_TEMPLATE      28
#define NODE_TEMPLATE_PARAMS      29
#define NODE_TYPE      30
#define NODE_TYPEDEF      31
#define NODE_TYPE_NAME      32
#define NODE_UNION      33
#define OCTAL_ESC      34
#define PREPROCESSOR      35
#define STRING      36
#define TOKEN_AMPERSAND      37
#define TOKEN_ASTERIX      38
#define TOKEN_BACKSLASH      39
#define TOKEN_COLON      40
#define TOKEN_COMMA      41
#define TOKEN_EQUALS      42
#define TOKEN_EXCLAMATION      43
#define TOKEN_FORWARD_SLASH      44
#define TOKEN_GREATER_THAN      45
#define TOKEN_HASH      46
#define TOKEN_LBRACE      47
#define TOKEN_LBRACKET      48
#define TOKEN_LESS_THAN      49
#define TOKEN_LPAREN      50
#define TOKEN_PERIOD      51
#define TOKEN_PIPE      52
#define TOKEN_RBRACE      53
#define TOKEN_RBRACKET      54
#define TOKEN_RPAREN      55
#define TOKEN_SEMICOL      56
#define TOKEN_TILDE      57
#define UNICODE_ESC      58
#define WS      59
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for CppHeaderParser
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
