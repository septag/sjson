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
    sjson_append_member(ctx, jroot, "string", sjson_mkstring(ctx, "Dances with Frogs"));
    sjson_append_member(ctx, jroot, "boolean", sjson_mkbool(ctx, true));
    sjson_append_member(ctx, jroot, "number",  sjson_mknumber(ctx, 1.666));
    sjson_append_member(ctx, jroot, "nil", sjson_mknull(ctx));

    sjson_node* jarr = sjson_mkarray(ctx);
    sjson_append_member(ctx, jroot, "arr", jarr);
    {
        sjson_append_element(jarr, sjson_mknumber(ctx, 9.0));
        sjson_append_element(jarr, sjson_mkbool(ctx, false));
        sjson_append_element(jarr, sjson_mkstring(ctx, "element3"));
    }

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