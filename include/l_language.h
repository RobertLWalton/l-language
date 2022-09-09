// L-Language Programming Language
//
// File:	l_language.h
// Author:	Bob Walton (walton@acm.org)
// Date:	Fri Sep  9 04:24:17 EDT 2022
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

# ifndef L_LANGUAGE_H
# define L_LANGUAGE_H

# include <ll_parser.h>

namespace l_language
{
    namespace lexeme
    {
	extern min::locatable_gen
	    l_language,		// l-language
	    equal_at,		// =@
	    curly_star,		// {*
	    star_curly,		// *}
	    Dnumber,		// D#
	    Bnumber,		// B#
	    Xnumber,		// X#
	    Cnumber,		// C#
	    type,		// type
	    pointer_type,	// pointer type
	    function,		// function
	    reference_function, // reference function
	    out_of_line_function, // out-of-line function
	    long_arrow, 	// --->
	    is_type, 		// is type
	    is_function; 	// it function
    }
    void init_parser
        ( min::ref<ll::parser::parser> parser );
}

# endif // L_LANGUAGE_H

