// Reckon Interpreter/Compiler
//
// File:	l_language_compiler.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Fri Jul  8 02:44:05 EDT 2022
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

// Table of Contents
//

// Usage and Setup
// ----- --- -----

# include <l_language.h>
# define LLANG l_language
# define PAR ll::parser

int main ( int argc, const char * argv[] )
{
    min::initialize();

    PAR::init ( PAR::default_parser );
    PAR::init_ostream
        ( PAR::default_parser, std::cout );
    LLANG::init_parser ( PAR::default_parser );
    PAR::init_input_stream
        ( PAR::default_parser, std::cin,
	    min::DISPLAY_PICTURE
	  + min::DISPLAY_NON_GRAPHIC
	  + min::DISPLAY_EOL );
    PAR::init_ostream
        ( PAR::default_parser, std::cout );
    PAR::init_line_display
	( PAR::default_parser,
	  min::DISPLAY_PICTURE );
    PAR::default_parser->trace_flags |=
	PAR::TRACE_PARSER_COMMANDS;
    PAR::parse();

    return 0;
}
