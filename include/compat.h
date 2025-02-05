#ifndef COMPAT_H
#define COMPAT_H

#include "superblt_flat.h"

void luasocket_setfuncs(lua_State *L, const luaL_Reg *l, int nup);
void *luasocket_testudata(lua_State *L, int arg, const char *tname);
void luaL_buffinit(lua_State *L, luaL_Buffer *B);
void luaL_addstring(luaL_Buffer *B, const char *s);
void luaL_addlstring(luaL_Buffer *B, const char *s, size_t l);
void luaL_pushresult(luaL_Buffer *B);
char *luaL_prepbuffsize(luaL_Buffer *B, size_t sz);

#define luaL_testudata luasocket_testudata
#define luaL_setfuncs luasocket_setfuncs
#define luaL_addchar(B, c)                                    \
    ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), \
     ((B)->b[(B)->n++] = (c)))

#endif
