/*

Copyright (c) 2020 Filystyn filystyn@int.pl

Permission to use, copy, modify, and distribute
this software for any purpose with or without fee
is hereby granted, provided that the above copyright
notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR
DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

  Prise Christ and Saint Maria.

*/

#include "bd_wadextract.h"
#include "../usefd/bd_usefd.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// check if compilation as wadchecker
// if not simply no code is inserred

#ifndef BD_WADCHK_PROGRAM
  #define BD_WADCHK_PROGRAM 0
#endif

#if ( BD_WADCHK_PROGRAM == 0 )
  #define BD_WADCHK_CODE(x)
#else
  #define BD_WADCHK_CODE(x) x
#endif

void bd_init_wadhead( 
    struct bd_wadhead *const wh )

  memset( wh->wadtype, '\0', sizeof wh->wadtype );
  wh->lumpcount = 0;
  wh->lumplistpos = 0;

}

void bd_init_wadent( 
    struct bd_wadent *const we )  {

  we->pos = 0;
  we->size = 0;
  memset( we->name, '\0', sizeof we->name );
  we->lump = NULL;

}


int bd_load_wadhead( 
    const int fd,
    struct bd_wadhead *const wh )  {

  int ret = 0;
  
  ret = bd_readfd_strictsize( fd, &wh->wadtype,
     BD_WAD_TYPESIZE );
  if( ret == -1 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Could not load wad type." ) );
    return -1;

  }
  
  ret = bd_readfd_strictsize( fd, &wh->entcount,
    BD_WAD_INTSIZE );
  if( ret == -1 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Could not load ent count." ) );
    return -1;

  }

  ret = bd_readfd_strictsize( fd, &( wh->entlistpos ),
    BD_WAD_INTSIZE );
  if( ret == -1 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Could not load ent position in file." ) );
    return -1;

  }

  return 0;

}

int bd_load_wadent( 
    const int fd,
    struct bd_wadent *const we )  {

  int ret = 0;
  ret = bd_readfd_strictsize( fd, &( we->pos ),
    BD_WAD_INTSIZE );
  if( ret == -1 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Could not load lump pos in file" ) );
    return -1;

  }
 
  ret = bd_readfd_strictsize( fd, &( we->size ),
    BD_WAD_INTSIZE );
  if( ret == -1 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Could not load lump size" ) );
    return -1;

  }

  ret = bd_readfd_strictsize( fd, &( we->name ),
    BD_WAD_NAMESIZE );
  if( ret == -1 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Could not load lump name" ) );
    return -1;

  }

  return 0;

}

int bd_load_wadlump( 
    const int fd,
    const struct bd_wadhead *const wh,
    struct bd_wadlump *const lumplist, 
    void *const buff,
    const size_t buff_size )  {

}

int bd_load_wad(
    const char *const wadname,
    struct bd_wad *const wad,
    void *const buff,
    const size_t buff_size )  {

  int fd = bd_openreadfd( wadname );
  if( fd == -1 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Could not open wad file." ) );
    return -1;

  }

  // We need this to check if file does not try to go too far
  off_t max_fdoffset = lseek( fd, 0, SEEK_END );
  if( max_fdoffset == -1 )  goto failret;

  bd_init_wadhead( &( wad->head ) );
  if( bd_load_wadhead( fd, &( wad->head ) ) == -1 )
    goto failret;

  // broken wad file checks
  if( wad->head.lumpcount < 0 )  {

    BD_WADCHK_CODE( fprintf( stderr,
      "Wad lump count has minus value." ) );
    goto failret;

  }
  if( wad->head.entlistpos < 0 )  {
  
    BD_WADCHK_CODE( fprintf( stderr,
      "Lump list position on minus value." ) );
    goto failret;

  }
  if( wad->head.entlistpos >= max_fdoffset )  {

    BD_WADCHK_CODE( fprintf( stderr, "Lump list"
      "position is higher than wad file size" ) );
    goto failret;

  }

  wad->lump = malloc( wad->head.entcount * 
    sizeof *( wad->ent ) );
  if( wad->ent == NULL )  goto failret;

  // move to wad entries list and load it
  if( lseek( fd, ( off_t )wad->head.entlistpos ,SEEK_SET )
     == -1 ) goto failret2;
  for( int32_t i = 0; i < wad->head.entcount; i++ )  {

    bd_init_wadent( &( wad->ent[i] ) );
    if( bd_load_wadent( fd, &( wad->head.ent[i] ) ) == -1 )  {

      BD_WADCHK_CODE( fprintf( stderr, "Broken lump"
        "at %" PRId32 "d", i ) );
      goto failret2;

    }

  }

  // now that we filled the list
  // allocate the lumps

failret2:
  free( wad->head.lump );
failret:
  int saveerrno = errno;
  close( fd );
  errno = saveerrno;
  return -1;

}
