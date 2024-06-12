#include <stdio.h>
#include <stdlib.h>

#define SJSON_IMPLEMENT
#include "../sjson.h"

char* read_file(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (!f) {
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    char* buff = NULL;
    if (size > 0) {
        buff = (char*)malloc(size + 1);
        if (buff) {
            fseek(f, 0, SEEK_SET);
            fread(buff, size, 1, f);
            buff[size] = '\0';
        }
    } 
    fclose(f);

    return buff;
}

int main(int argc, char* argv[])
{
    sjson_context* ctx = sjson_create_context(0, 0, NULL);
    if (!ctx) {
        puts("Could not create sjson_context");
        return -1;
    }

    char* twitter_json = read_file("twitter.json");
    if (!twitter_json) {
        puts("Could not read 'twitter.json'. Check if the file exists in the current path");
        return -1;
    }

    sjson_node* jroot = sjson_decode(ctx, twitter_json);
    if (!jroot) {
        puts("Parsing twitter.json failed");
        return -1;
    }
    
    char* text = sjson_stringify(ctx, jroot, "  ");
    puts("Re-encoded: ");
    puts(text);
    sjson_free_string(ctx, text);

    free(twitter_json);
    sjson_destroy_context(ctx);
    return 0;
}

