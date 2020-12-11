
// L-Language Parser
//
// File:	l_language_parser.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Fri Dec 11 04:37:15 EST 2020
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

// Table of Contents
//
//	Usage and Setup
//	Strings
//	Tokens
//	Parser Closures
//	Parser
//	Reformatters
//	Parser Functions

// Usage and Setup
// ----- --- -----

# include <l_language.h>
# define LLANG l_language
# define LLEX l_language::lexeme
# define PAR ll::parser

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
}
