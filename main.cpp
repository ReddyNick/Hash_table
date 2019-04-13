#include <iostream>
#include "hash_table.h"
#include "assert.h"


int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    assert(in != NULL);

    Htable table;
    table.read_write(in, out);

    fclose(in);
    fclose(out);
    return 0;
}