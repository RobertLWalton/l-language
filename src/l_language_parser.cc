// L-Language Parser
//
// File:	l_language_parser.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Sat Dec 19 06:18:52 EST 2020
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

// Table of Contents
//
//	Usage and Setup
//	Parser
//	Reformatters

// Usage and Setup
// ----- --- -----

# include <l_language.h>
# include <ll_parser_oper.h>
# define LLANG l_language
# define LLEX l_language::lexeme
# define PAR ll::parser
# define TAB ll::parser::table
# define OP ll::parser::oper


// L-Language Parser
// ---------- ------

min::locatable_gen LLEX::l_language;
min::locatable_gen LLEX::equal_at;

static void initialize ( void )
{
    LLEX::l_language =
        min::new_str_gen ( "l-language" );
    LLEX::equal_at = min::new_str_gen ( "=@" );
}
static min::initializer initializer ( ::initialize );

void LLANG::init_parser ( PAR::parser parser )
{
    min::gen result =
        PAR::begin_block
	    ( parser, LLEX::l_language,
	      PAR::top_level_position );

    MIN_REQUIRE ( result == min::SUCCESS() );

    min::uns32 block_level =
        PAR::block_level ( parser );

    min::locatable_gen code_name
        ( min::new_str_gen ( "code" ) );
    min::locatable_gen math_name
        ( min::new_str_gen ( "math" ) );

    TAB::flags code =
        1ull << TAB::find_name
            ( parser->selector_name_table, code_name );
    TAB::flags math =
        1ull << TAB::find_name
            ( parser->selector_name_table, math_name );

    min::locatable_gen oper
        ( min::new_str_gen ( "operator" ) );

    PAR::pass pass = parser->pass_stack;
    while ( pass != min::NULL_STUB
            &&
	    pass->name != oper )
        pass = pass->next;
    MIN_REQUIRE ( pass != min::NULL_STUB );
    OP::oper_pass oper_pass = (OP::oper_pass) pass;

    min::locatable_gen binary
        ( min::new_str_gen ( "binary" ) );

    OP::push_oper
        ( LLEX::equal_at,
          min::MISSING(),
          code + math,
          block_level, PAR::top_level_position,
          OP::INFIX,
          9010,
          PAR::find_reformatter
              ( binary,
                OP::reformatter_stack ),
          min::NULL_STUB,
          oper_pass->oper_table );
}
