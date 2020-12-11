// Reckon Interpreter/Compiler
//
// File:	l_language_compiler.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Thu Dec 10 22:48:19 EST 2020
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

// Table of Contents
//

// Usage and Setup
// ----- --- -----

# include <ll_parser_standard.h>
# define PAR ll::parser

int main ( int argc, const char * argv[] )
{
    min::initialize();

    PAR::init ( PAR::default_parser, true );
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
