#ifndef CACHE_H
#define CACHE_H
#include "Block.h"
#include<string>

class Cache
{
    public:
        Cache(int,int);
        void grab_word(Block &b,bool is_write);
        string parse_string(char word);
		int get_cm(){return cm;}
		void print();
        ~Cache();
    private:
        int find_index(const string str);
        string find_tag(const string str);
		void insert_word(const Block &b,bool is_write);
        Block **ptr;
        int s;
        int blocks;
        int index_length;
        int offset_length;
        int tag_length;
        int cm,dr,m,h;
};

#endif // CACHE_H
