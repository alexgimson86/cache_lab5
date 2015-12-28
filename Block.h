#ifndef BLOCK_H
#define BLOCK_H
#include<string>
#include<iostream>
using namespace std;

class Block
{
    public:
        Block();
        void set_dirty_bit(int d){dirty_bit = d;}
        void set_valid_bit(int v){valid_bit = v;}
        void set_word(string s){word =s;}
        int get_dirty_bit(){return dirty_bit;}
        int get_valid_bit(){return valid_bit;}
        string get_word(){return word;}
        string get_tag()const{return tag;}
        void set_tag(string s){tag = s;}
        int get_lru_value(){return lru_value;}
        void set_lru_value(int l){lru_value=l;}
		void set_index(int i){index = i;}
		int get_index()const{return index;}


    private:
        int valid_bit;
		int index;
        int dirty_bit;
        string tag;
        string word;
        int lru_value;
};

#endif // BLOCK_H
