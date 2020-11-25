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



struct bd_wadhead  {

  char wadtype[8];
  int32_t lumpcount;
  int32_t dirpos;

};

struct bd_wadlump  {

  int32_t pos;
  int32_t size;
  char name[12];
  void *mem;

};

struct bd_wad  {

  struct bd_wadhead head;
  struct bd_wadlump *lump;

};

int bd_init_wadhead( 
  struct bd_wadhead *const wh );

int bd_init_wadlump( 
  struct bd_wadlump *const wl );

int bd_loadwadhead( 
  const int fd,
  struct bd_wadhead *const  );

int bd_loadwadentlist( 
  const int fd,
  const struct bd_wadhead *const wh,
  struct bd_wadlump *const lumplist );

int bd_loadwadentries( 
  const int fd,
  const struct bd_wadhead *const wh,
  struct bd_wadlump *const lumplist );

int bd_loadwad(
  const char *const wadname,
  struct bd_wad *const wad );
