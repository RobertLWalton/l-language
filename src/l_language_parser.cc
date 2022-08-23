// L-Language Parser
//
// File:	l_language_parser.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Tue Aug 23 14:43:45 EDT 2022
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
min::locatable_gen LLEX::curly_star;
min::locatable_gen LLEX::star_curly;
min::locatable_gen LLEX::Dnumber;
min::locatable_gen LLEX::Bnumber;
min::locatable_gen LLEX::Xnumber;
min::locatable_gen LLEX::Cnumber;
min::locatable_gen LLEX::type;
min::locatable_gen LLEX::pointer_type;
min::locatable_gen LLEX::function;
min::locatable_gen LLEX::out_of_line_function;
min::locatable_gen LLEX::long_arrow;

static void initialize ( void )
{
    LLEX::l_language =
        min::new_str_gen ( "l-language" );
    LLEX::equal_at = min::new_str_gen ( "=@" );
    LLEX::curly_star =
        min::new_lab_gen ( "{", "*" );
    LLEX::star_curly =
        min::new_lab_gen ( "*", "}" );
    LLEX::Dnumber = min::new_str_gen ( "D#" );
    LLEX::Bnumber = min::new_str_gen ( "B#" );
    LLEX::Xnumber = min::new_str_gen ( "X#" );
    LLEX::Cnumber = min::new_str_gen ( "C#" );
    LLEX::type = min::new_str_gen ( "type" );
    LLEX::pointer_type =
        min::new_lab_gen ( "pointer", "type" );
    LLEX::function = min::new_str_gen ( "function" );
    LLEX::out_of_line_function =
        min::new_lab_gen ( "out-of-line", "function" );
    LLEX::long_arrow = min::new_str_gen ( "--->" );

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

    BRA::push_brackets
        ( LLEX::curly_star,
	  LLEX::star_curly,
	  code,
	  block_level, PAR::top_level_position,
	  TAB::new_flags
	      ( PAR::LINE_LEVEL_SELECTOR, 0, 0 ),
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

    min::locatable_gen unary
        ( min::new_str_gen ( "unary" ) );
    min::locatable_gen binary
        ( min::new_str_gen ( "binary" ) );

    PAR::reformatter unary_reformatter =
          PAR::find_reformatter
              ( unary,
                OP::reformatter_stack );
    PAR::reformatter binary_reformatter =
          PAR::find_reformatter
              ( binary,
                OP::reformatter_stack );

    OP::push_oper
        ( LLEX::equal_at,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::INFIX,
          1100,
	  binary_reformatter,
          min::MISSING(),
          oper_pass->oper_table );

    OP::push_oper
        ( LLEX::Dnumber,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          OP::prefix_precedence,
          unary_reformatter,
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::Bnumber,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          OP::prefix_precedence,
          unary_reformatter,
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::Xnumber,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          OP::prefix_precedence,
          unary_reformatter,
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::Cnumber,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          OP::prefix_precedence,
          unary_reformatter,
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::type,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          0000,
          min::NULL_STUB,	// TBD
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::pointer_type,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          0000,
          min::NULL_STUB,	// TBD
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::function,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          0000,
          min::NULL_STUB,	// TBD
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::out_of_line_function,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::PREFIX,
          0000,
          min::NULL_STUB,	// TBD
          min::MISSING(),
          oper_pass->oper_table );
    OP::push_oper
        ( LLEX::long_arrow,
          min::MISSING(),
          code,
          block_level, PAR::top_level_position,
          OP::INFIX,
          0000,
          binary_reformatter,
          min::MISSING(),
          oper_pass->oper_table );
}
