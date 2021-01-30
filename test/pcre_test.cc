// Program to test pcre installation.
//
// File:	pcre_test.cc
// Author:	Bob Walton (walton@acm.org)
// Date:	Sat Jan 30 06:30:16 EST 2021
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

#include <iostream>
extern "C" {
#   include <pcre.h>
}
using std::cout;
using std::endl;
using std::ostream;

PCRE_UCHAR32 re[] =
    { 'a', '(', 'b', '*', ')', 'c', 0 };
PCRE_UCHAR32 s0[] = { 'a', 'c' };
PCRE_UCHAR32 s1[] = { 'a', 'b', 'c' };
PCRE_UCHAR32 s2[] = { 'a', 'b', 'b', 'c' };

int matches[30];  // Allow for 10 substrings

struct str { PCRE_UCHAR32 * s; int n;
             str ( PCRE_UCHAR32 * s, int n )
	         : s ( s ), n ( n ) {}
	   };

ostream & operator << ( ostream & s, str st )
{
    for ( int i = 0; i < st.n; ++ i )
        cout << (char) st.s[i];
    return s;
}

// Print matches
//
void print_matches ( PCRE_UCHAR32 * s, int n )
{
    while ( n -- )
        cout << "  " << n + 1 << ": "
	     << str ( s + matches[2*n+0],
	              matches[2*n+1] - matches[2*n+0] )
	     << endl;
}

int main ()
{
    int r;
    pcre32 * code;
    const char * errptr;
    int erroffset;

    cout << "COMPILING RE: " << str ( re, 6 ) << endl;
    code = pcre32_compile ( re, 0, & errptr, & erroffset, NULL ); 
    if ( code == NULL ) cout << "ERROR at " << erroffset
                             << ": " << errptr << endl;

    cout << "MATCHING: " << str ( s0, 2 ) << endl;
    r = pcre32_exec ( code, NULL, s0, 2, 0, 0, matches, 30 );
    if ( r < 0 ) cout << "ERROR: " << r << endl;
    else print_matches ( s0, r );

    cout << "MATCHING: " << str ( s1, 3 ) << endl;
    r = pcre32_exec ( code, NULL, s1, 3, 0, 0, matches, 30 );
    if ( r < 0 ) cout << "ERROR: " << r << endl;
    else print_matches ( s1, r );

    cout << "MATCHING: " << str ( s2, 4 ) << endl;
    r = pcre32_exec ( code, NULL, s2, 4, 0, 0, matches, 30 );
    if ( r < 0 ) cout << "ERROR: " << r << endl;
    else print_matches ( s2, r );
}

