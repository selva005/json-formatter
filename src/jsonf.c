#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char **argv )
{
    char*           ofile;
    int             index;
    int             c;

    opterr = 0;

    while ( ( c = getopt( argc, argv, "o:" ) ) != -1 )
        switch ( c )
        {
        case 'o':
            ofile = optarg;
            break;
        case '?':
            if ( optopt == 'o' )
                fprintf( stderr, "Option -%c requires an argument.\n", optopt );
            else if ( isprint( optopt ) )
                fprintf( stderr, "Unknown option `-%c'.\n", optopt );
            else
                fprintf( stderr, "Unknown option character `\\x%x'.\n", optopt );
            return 1;
        default:
            abort(  );
        }

    for ( index = optind; index < argc; index++ )
        printf( "Non-option argument %s\n", argv[index] );
    return 0;
}

void usage(  )
{
    fprintf( stderr,
             "Usage:  [options] <Input filename> <Input filename>..\n"
             "\n"
             " Options:\n"
             "  -o <filename>   output filename \n" "\n");
    exit( 1 );
}
