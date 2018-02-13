#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#include "jansson.h"
#include "jsonf.h"

void            usage(  );
int             read_file( char *, char ** );

int main( int argc, char **argv )
{
    json_t         *root;
    json_error_t    error;
    char           *ofile,
                   *file_content;
    int             c,
                    index,
                    indent;

    opterr = 0;
    ofile = NULL;
    indent = 3;

    while ( ( c = getopt( argc, argv, "o:n:" ) ) != -1 )
    {
        switch ( c )
        {
        case 'n':
            indent = atoi( optarg );
            break;
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
            usage(  );
        }
    }
    if ( argc < 2 || optind >= argc )
    {
        usage(  );
        exit( 1 );
    }

    for ( index = optind; index < argc; index++ )
    {
        LOGDEBUG( "Formatting %s", argv[index] );
        if ( !read_file( argv[index], &file_content ) )
        {
            if ( ( root = json_loads( file_content, 0, &error ) ) == NULL )
                goto ERROR;
            json_dump_file( root, ofile, JSON_INDENT( indent ) );
        }
        else
        {
          ERROR:
            LOGDEBUG( "Error formatting %s", argv[index] );
        }
    }

    return 0;
}

void usage(  )
{
    fprintf( stderr, "Usage:  [options] <Input filename> <Input filename>..\n" "\n" );
    fprintf( stderr, " Options:\n" );
    fprintf( stderr, "    -o <filename>   output filename \n" );
    fprintf( stderr, "    -n <# of char>  indent size \n" );
}

int read_file( char *file_name, char **file_content )
{
    FILE           *f_handle;
    long            f_size;

    LOGDEBUG( "in read_file" );
    if ( ( f_handle = fopen( file_name, "rb" ) ) == NULL )
    {
        LOGDEBUG( "Failed to open %s", file_name );
        goto ERROR;
    }
    fseek( f_handle, 0, SEEK_END );
    f_size = ftell( f_handle );
    LOGDEBUG( "File Size is %ld", f_size );
    fseek( f_handle, 0, SEEK_SET );

    *file_content = calloc( 1, f_size + 1 );
    fread( *file_content, f_size, 1, f_handle );
    fclose( f_handle );

    LOGDEBUG( "Returning data" );

    return 0;

  ERROR:
    return 1;
}
