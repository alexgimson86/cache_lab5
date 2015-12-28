#include <iostream>
#include "Block.h"
#include "Cache.h"
#include<fstream>
#include<string>
using namespace std;
const int blocks = 4;

int main()
{
    ifstream infile;
    infile.open("Trace.txt");
    if(!infile.is_open())
    {
        cout<<"couldn't open file!"<<endl;
		return 0;
    }

    Block b;
    Cache c(4,blocks);
	Cache c_2(8,blocks);
    string buffer;
	int count = 0;
	int size =0;

	string s;
	int i = 0;
    while(infile>>buffer)
    {
        b.set_word(buffer);
        c.grab_word(b,(i%3==2));
		b.set_dirty_bit(0);
		i++;
	}
	infile.clear();
	infile.seekg(0,infile.beg);
	i=0;
	while(infile>>buffer)
	{
		b.set_word(buffer);
		c_2.grab_word(b,(i%3==2));
		b.set_dirty_bit(0);
		i++;
	}
	c.print();
	c_2.print();
	//system("pause");
    return 0;
}
