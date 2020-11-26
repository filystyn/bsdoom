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


#include <string.h>

void bd_init_wadhead( 
    struct bd_wadhead *const wh )

  memset( wh->wadtype, '\0', sizeof wh->wadtype );
  wh->lumpcount = 0;
  wh->lumplistpos = 0;

}

void bd_init_wadlump( 
    struct bd_wadlump *const wl )  {

  wl->pos = 0;
  wl->size = 0;
  memset( wl->name, '\0', sizeof wl->name );
  wh->mem = NULL;

}


int bd_load_wadhead( 
    const int fd,
    struct bd_wadhead *const wh )  {

  int ret = 0;
  
  readret = bd_readfd_strictsize( fd, wh->wadtype,
     WAD_TYPESIZE );
  if( ret == -1 ) return -1;
  
  readret = bd_readfd_strictsize( fd, wh->lumpcount,
    WAD_INTSIZE );
  if( ret == -1 )  return -1;

  readret = bd_readfd_strictsize( fd, wh->lumplistpos,
    WAD_INTSIZE );
  if( ret == -1 )  return -1;

  return 0;

}


int bd_load_wadentlist( 
    const int fd,
    const struct bd_wadhead *const wh,
    struct bd_wadlump *const lumplist )  {

    

}

int bd_load_wadent( 
    const int fd,
    const struct bd_wadhead *const wh,
    struct bd_wadlump *const lumplist, 
    void *const buff,
    const size_t buff_size )  {

int bd_load_wad(
    const char *const wadname,
    struct bd_wad *const wad,
    void *const buff,
    const size_t buff_size )  {

  int fd = bd_openreadfd( wadname );
  if( fd == -1 )  return -1;

  off_t max_fdoffset = lseek( fd, 0, SEEK_END );
  if( max_fdoffset == -1 )  goto failret;
  // than check lump and other stuff pos - does it not
  // jump too far where should be no file

  bd_init_wadhead( &( wad->head ) );
  if( bd_load_wadhead( fd, &( wad->head ) ) == -1 )
    goto failret;

  // broken wad file
  if( wad->head.lumpcount < 0 )  return -1;

  wad->lump = malloc( wad->head.lumpcount * 
    sizeof *( wad->lump ) );
  if( wad->lump == NULL )  goto failret;



  for( int32_t i = 0; i < wad->head.lumpcount; i++ )  {

    bd_init_wadlump( &( wad->lump[i] ) );

    
  
  }



failret2:
  free( wad0>head.lump );
failret:
  int saveerrno = errno;
  close( fd );
  errno = saveerrno;
  return -1;

}
