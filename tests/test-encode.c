#include <stdio.h>
#include <stdlib.h>

#define SJSON_IMPLEMENTATION
#include "../sjson.h"

int main(int argc, char* argv[])
{
    sjson_context* ctx = sjson_create_context(0, 0, NULL);
    if (!ctx) {
        puts("Could not create sjson_context");
        return -1;
    }

    sjson_node* jroot = sjson_mkobject(ctx);
    sjson_put_string(ctx, jroot, "string", "Dances with Frogs");
    sjson_put_bool(ctx, jroot, "boolean", true);
    sjson_put_double(ctx, jroot, "number",  1.666);
    sjson_append_member(ctx, jroot, "nil", sjson_mknull(ctx));      // lower-level API

    // Lower-level api for constructing any type of array
    sjson_node* jarr = sjson_mkarray(ctx);
    sjson_append_member(ctx, jroot, "arr", jarr);
    {
        sjson_append_element(jarr, sjson_mknumber(ctx, 9.0));
        sjson_append_element(jarr, sjson_mkbool(ctx, false));
        sjson_append_element(jarr, sjson_mkstring(ctx, "element3"));
    }

    // Higher level for constructing for example float array
    const float pt[] = {1.5f, 3.0f, 5.0f, 1.0f};
    sjson_put_floats(ctx, jroot, "vector", pt, 4);

    char errmsg[256];
    if (!sjson_check(jroot, errmsg)) {
        puts(errmsg);
        return -1;
    }

    char* encoded = sjson_stringify(ctx, jroot, "  ");
    puts("Encoded: ");
    puts(encoded);    

    sjson_destroy_context(ctx);
    return 0;
}