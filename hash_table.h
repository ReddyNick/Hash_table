#ifndef HASH_TABLES_HASH_TABLE_H
#define HASH_TABLES_HASH_TABLE_H

#include "stdio.h"
#include "stdlib.h"
#include "md5.h"
#include "sha1.h"
#include "keccak.h"

const int MAX_func = 8;
const int KEY_MAX = 200;
const int MAX_STR = 100;

struct Node
{
    Node* next = nullptr;
    int data = 0;
    char str[MAX_STR] = {};
};

int geth1(char* str);
int geth2(char* str);
int geth3(char* str);
int geth4(char* str);
int geth5(char* str);
int MD5_to_int(char* str);
int Sha_1(char* str);
int Keccak_func(char* str);

class Htable
{
private:

    Node* table[KEY_MAX] = {};

public:

    int (*func[MAX_func])(char*);

    ~Htable();
    int Del();
    int read_write(FILE* in, FILE* out);
    int Insert(char* str);
    int insert_k(char* str, int key);
    int Find(char* str);
    int Delete(char* str);

    int Write_info(FILE* out);

    int GetHash(char* str) { return geth4(str); }

};







#endif //HASH_TABLES_HASH_TABLE_H
