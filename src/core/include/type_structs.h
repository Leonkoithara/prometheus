#ifndef TYPE_STRUCTS
#define TYPE_STRUCTS

#include <cstring>


typedef struct
{
    float x;
    float y;
    float z;
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

#endif
