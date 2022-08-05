// L-Language Parser
//
// File:	l_language_parser.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Fri Aug  5 15:19:20 EDT 2022
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
# include <ll_parser_bracketed.h>
# include <ll_parser_oper.h>
# include <ll_parser_standard.h>
# define LLANG l_language
# define LLEX l_language::lexeme
# define PAR ll::parser
# define PARLEX ll::parser::lexeme
# define TAB ll::parser::table
# define BRA ll::parser::bracketed
# define OP ll::parser::oper
# define PARSTD ll::parser::standard


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

void LLANG::init_parser ( min::ref<PAR::parser> parser )
{
    PAR::init ( parser, 0 );
    PARSTD::init_input ( parser );

    min::gen result =
        PAR::begin_block
	    ( parser, LLEX::l_language,
	      PAR::top_level_position );

    MIN_REQUIRE ( result == min::SUCCESS() );

    PARSTD::define_standard
        ( parser,
	  PARSTD::CODE +
	  PARSTD::TOP_LEVEL +
	  PARSTD::CONCATENATOR +
	  PARSTD::ALL_OPERATORS );

    min::locatable_gen code_name
        ( min::new_str_gen ( "code" ) );

    TAB::flags code =
        1ull << TAB::find_name
            ( parser->selector_name_table, code_name );

    PAR::set_selectors
        ( code +
	  PAR::EIPARAGRAPH_OPT +
	  PAR::EALEINDENT_OPT,
	  parser );

    PAR::set_line_separator
        ( min::MISSING(), parser );

    min::uns32 block_level =
        PAR::block_level ( parser );

    BRA::bracketed_pass bracketed_pass =
        (BRA::bracketed_pass) parser->pass_stack;

    BRA::push_brackets
        ( PARLEX::left_parenthesis,
	  PARLEX::right_parenthesis,
	  code,
	  block_level, PAR::top_level_position,
	  TAB::new_flags ( 0, 0, 0 ),
	  min::NULL_STUB, min::MISSING(),
	  bracketed_pass->bracket_table );

    BRA::push_brackets
        ( PARLEX::left_square,
	  PARLEX::right_square,
	  code,
	  block_level, PAR::top_level_position,
	  TAB::new_flags ( 0, 0, 0 ),
	  min::NULL_STUB, min::MISSING(),
	  bracketed_pass->bracket_table );

    BRA::push_brackets
        ( PARLEX::left_curly,
	  PARLEX::right_curly,
	  code,
	  block_level, PAR::top_level_position,
	  TAB::new_flags ( 0, 0, 0 ),
	  min::NULL_STUB, min::MISSING(),
	  bracketed_pass->bracket_table );

    BRA::push_indentation_mark
        ( PARLEX::colon, min::MISSING(),
	  code,
	  block_level, PAR::top_level_position,
	  TAB::new_flags ( 0, 0, 0 ),
	  min::MISSING(),
	  PAR::MISSING_MASTER,
	  PAR::MISSING_MASTER,
	  bracketed_pass->bracket_table );

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
          code,
          block_level, PAR::top_level_position,
          OP::INFIX,
          9010,
          PAR::find_reformatter
              ( binary,
                OP::reformatter_stack ),
          min::MISSING(),
          oper_pass->oper_table );
}
