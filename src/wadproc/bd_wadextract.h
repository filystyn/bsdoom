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

#ifndef BD_WADEXTRACT_H
#define BD_WADEXTRACT_H

#define BD_WAD_INTSIZE 4
#define BD_WAD_TYPESIZE 4
#define BD_WAD_NAMESIZE 8

struct bd_wadhead  {

  char wadtype[8];
  int32_t entcount;
  int32_t entlistpos;

};

struct bd_wadent  {

  int32_t pos;
  int32_t size;
  char name[12];
  void *lump;

};

struct bd_wad  {

  struct bd_wadhead head;
  struct bd_wadlump *ent;

};

void bd_init_wadhead( 
    struct bd_wadhead *const wh );

void bd_init_wadent( 
    struct bd_wadent *const we );

int bd_load_wadhead( 
    const int fd,
    struct bd_wadhead *const wh );

int bd_load_wadent( 
    const int fd,
    struct bd_wadent *const we );

int bd_load_wadlump( 
    const int fd,
    const struct bd_wadhead *const wh,
    struct bd_wadlump *const lumplist,
    void *const buff,
    const size_t buff_size );

int bd_load_wad(
    const char *const wadname,
    struct bd_wad *const wad,
    void *const buff,
    const size_t buff_size );

#endif
