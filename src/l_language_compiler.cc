// Reckon Interpreter/Compiler
//
// File:	l_language_compiler.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Sun Aug 27 00:47:36 EDT 2023
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

    LLANG::init_parser ( PAR::default_parser );
    PAR::init_ostream
        ( PAR::default_parser, std::cout );
    PAR::init_input_stream
        ( PAR::default_parser, std::cin,
	    min::picture_line_format );
    PAR::default_parser->trace_flags |=
	PAR::TRACE_PARSER_COMMANDS;
    PAR::parse();

    return 0;
}
