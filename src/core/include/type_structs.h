#ifndef TYPE_STRUCTS
#define TYPE_STRUCTS

#include <cstring>


typedef struct
{
    long x;
    long y;
    long z;
} vec3D;

union tag
{
    char strval[20];
    long longval;

    tag() {}
    ~tag() {}
    tag(const char* instr) { strcpy(strval, instr); }
    tag(long in) { longval = in; }
    tag(tag& t) { memcpy(strval, t.strval, 20); }
};

#define ONE_BY_ROOT_TWO 0.707107

#endif
