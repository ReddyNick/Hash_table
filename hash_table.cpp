#include "hash_table.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"
#include <string>


int (*func[MAX_func])(char*);
int (*gethash)(char*);

int Htable::Insert(char *str)
{
    int key = gethash(str);

    insert_k(str, key);

    return 0;
}

int Htable::insert_k(char *str, int key)
{
    if (table[key] == nullptr)
    {
        Node* num = new Node;
        table[key] = num;
    }

    Node* ptr = table[key];
    bool already_exist = false;

    while(ptr->next != nullptr && !already_exist)
    {
        ptr = ptr->next;

        if (strcmp(ptr->str, str) == 0)
        {
            ptr->data++;
            already_exist = true;
        }
    }

    if (!already_exist)
    {
        table[key]->data++;

        Node *node = new Node;
        strcpy(node->str, str);

        ptr->next = node;

    }

    return 0;
}

int Htable::Find(char *str)
{
    int key = gethash(str);

    Node* ptr = table[key];

    while(ptr != nullptr)
    {
        if (!strcmp(ptr->str, str))
            return 1;
        ptr = ptr->next;
    }

    return 0;
}

int Htable::Del()
{
    for(int i = 0; i < KEY_MAX; i++)
    {
        while(table[i] != nullptr)
        {
            Node* ptr = table[i];
            table[i] = table[i]->next;

            delete ptr;
        }
    }
}

int Htable::Write_info(FILE* out)
{

    for (int i = 0; i < KEY_MAX; i++)
    {
        if (table[i] == nullptr)
            fprintf(out,"0; ");
        else
            fprintf(out, "%d; ", table[i]->data);
    }

    fprintf(out, "\n");
    return 0;
}

int Htable::read_write(FILE *in, FILE* out)
{
    char str[MAX_STR];

    func[0] = geth1;
    func[1] = geth2;
    func[2] = geth3;
    func[3] = geth4;
    func[4] = geth5;
    func[5] = MD5_to_int;
    func[6] = Sha_1;
    func[7] = Keccak_func;


    for(int i = 0; i < MAX_func; i++)
    {
        gethash = func[i];

        rewind(in);

        while (fscanf(in, " %s ", str) != -1)
            Insert(str);

        Write_info(out);

        Del();
    }


    return 0;
}

Htable::~Htable()
{
    for(int i = 0; i < KEY_MAX; i++)
    {
        while(table[i] != nullptr)
        {
            Node* ptr = table[i];
            table[i] = table[i]->next;

            delete ptr;
        }
    }

}

int geth1(char *str)
{
    return 0;
}

int geth2(char *str)
{
    assert(str != NULL);
    return (unsigned char)str[0] % KEY_MAX;
}

int geth3(char *str)
{
    return strlen(str)% KEY_MAX;
}

int geth4(char *str)
{
    int size = strlen(str);
    int res = 0;

    for (int i = 0; i < size - 1; i++)
        res += (unsigned char)str[i];

    return res % KEY_MAX;
}

int geth5(char *str)
{
    int size = strlen(str);
    unsigned int hash = str[0];

    for (int i = 1; i < size; i++)
    {
        hash =  ((hash << 31) | (hash >> 1)) ^ str[i];
    }

    return hash % KEY_MAX;
}

int geth_string(std::string str)
{
    int size = str.size();
    unsigned int hash = str[0];

    for (int i = 1; i < size; i++)
    {
        hash =  ((hash << 31) | (hash >> 1)) ^ str[i];
    }

    return hash % KEY_MAX;
}

int MD5_to_int(char *str)
{
    hash2::MD5 make_hash;
    return geth_string(make_hash(str));
}

int Sha_1(char *str)
{
    SHA1 sh1;
    return geth_string(sh1(str));
}

int Keccak_func(char *str)
{
    Keccak kec;
    return geth_string(kec(str));
}
