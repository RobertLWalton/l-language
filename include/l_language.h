// L-Language Programming Language
//
// File:	l_language.h
// Author:	Bob Walton (walton@acm.org)
// Date:	Fri Dec 11 05:10:36 EST 2020
//
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

// Table of Contents
//
//	Usage and Setup

// Usage and Setup
// ----- --- -----

# ifndef L_LANGUAGE_H
# define L_LANGUAGE_H

# include <ll_parser.h>


namespace l_language
{
    namespace lexeme
    {
	extern min::locatable_gen
	    l_language,
	    equal_at;
    }
    void init_parser
        ( ll::parser::parser parser );
}

# endif // L_LANGUAGE_H

