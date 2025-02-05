#include "compat.h"

#include <cassert>
#include <cstring>

#include "luasocket.h"

/*
** Adapted from Lua 5.2
*/
void luasocket_setfuncs(lua_State *L, const luaL_Reg *l, int nup) {
    luaL_checkstack(L, nup + 1, "too many upvalues");
    for (; l->name != NULL; l++) { /* fill the table with given functions */
        int i;
        lua_pushstring(L, l->name);
        for (i = 0; i < nup; i++) /* copy upvalues to the top */
            lua_pushvalue(L, -(nup + 1));
        lua_pushcclosure(L, l->func, nup); /* closure with those upvalues */
        lua_settable(L, -(nup + 3));
    }
    lua_pop(L, nup); /* remove upvalues */
}

/*
** Adapted from Lua 5.2
*/
int lua_typerror(lua_State *L, int narg, const char *tname) {
#ifdef compat_error_skip
    return 0;
#else
    const char *msg = lua_pushfstring(L, "%s expected, got %s", tname,
                                      luaL_typename(L, narg));
    return luaL_argerror(L, narg, msg);
#endif
}
void *luasocket_testudata(lua_State *L, int ud, const char *tname) {
#define compat_error_skip
    void *ret = (void *)luaL_checkudata(L, ud, tname);
#undef compat_error_skip
    return ret;
}

void luaL_buffinit(lua_State *L, luaL_Buffer *B) {
    B->L = L;
    B->b = B->initb;
    B->n = 0;
    B->size = LUAL_BUFFERSIZE;
}

#define buffonstack(B) ((B)->b != (B)->initb)
char *luaL_prepbuffsize(luaL_Buffer *B, size_t sz) {
    lua_State *L = B->L;
    if (B->size - B->n < sz) { /* not enough space? */
        char *newbuff;
        size_t newsize = B->size * 2; /* double buffer size */
        if (newsize - B->n < sz)      /* not big enough? */
            newsize = B->n + sz;
        if (newsize < B->n || newsize - B->n < sz)
            luaL_error(L, "buffer too large");
        /* create larger buffer */
        newbuff = (char *)lua_newuserdata(L, newsize * sizeof(char));
        /* move content to new buffer */
        memcpy(newbuff, B->b, B->n * sizeof(char));
        if (buffonstack(B)) lua_remove(L, -2); /* remove old buffer */
        B->b = newbuff;
        B->size = newsize;
    }
    return &B->b[B->n];
}

#define luaL_addsize(B, s) ((B)->n += (s))
void luaL_addlstring(luaL_Buffer *B, const char *s, size_t l) {
    char *b = luaL_prepbuffsize(B, l);
    memcpy(b, s, l * sizeof(char));
    luaL_addsize(B, l);
}
void luaL_addstring(luaL_Buffer *B, const char *s) {
    luaL_addlstring(B, s, strlen(s));
}

void luaL_pushresult(luaL_Buffer *B) {
    lua_State *L = B->L;
    lua_pushlstring(L, B->b, B->n);
    if (buffonstack(B)) lua_remove(L, -2); /* remove old buffer */
}
