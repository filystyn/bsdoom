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

#include "bd_readfd.h"

#include <sys/types.h>

#include <unistd.h>


ssize_t bd_readfd( 
    const int fd, 
    void *const buff, 
    const size_t buff_size )  {

  // sizeof( ssize_t ) should == sizeof( size_t )
  if( buff_size >= SSIZE_MAX )  {

    errno = 0;
    return -1;

  }

  if( buff_size == 0 )  {  // will we read 0 we wanted or faced EOF ???
    
    errno = 0;
    return -1;

  }

  uint8_t *buff_pos = buff;
  ssize_t readsum = 0;
  size_t left_size = buff_size;

  ssize_t readret = -1;
  for(; left_size;)  {

    readret = read( fd, buff_pos, left_size );
    if( readret == -1 )  {

      if( errno == EINTR )  continue;
      return -1;

    }

    buff_pos += readret;
    buff_size -= ( size_t )readret;
    readsum += readret;

    if( readret == 0 )  return readsum;

  }

  return readsum;

}

int bd_readfd_strictsize( 
    const int fd, 
    void *const buff, 
    const size_t buff_size )  {

  ssize_t readret = bd_readfd( fd, buff, buff_size );
  if( readret != buff_size )  return -1;
  return 0;

}
