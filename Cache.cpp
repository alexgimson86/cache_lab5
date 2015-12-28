#include "Cache.h"
#include<iostream>
#include<iomanip>

Cache::Cache(int sets,int blocks_per_set)
{
	cm = dr = m = h = 0;
    s = sets;
    blocks = blocks_per_set;

    int number = 2;
    int i;
    for(i =1; number < s;i++){
        number= number<<1;
    }
    index_length = i;

    ptr = new Block*[sets];
    for(int i = 0; i < sets;i++){
        ptr[i] = new Block[blocks_per_set];
    }
}
void Cache::grab_word(Block &b,bool is_write)
{
    string ref_word = b.get_word();
    string binary_word;
    for(int i = 0; i < 6; i++){
        binary_word+=parse_string(ref_word[i]);
    }
	if(is_write)
		b.set_dirty_bit(1);

    int index = find_index(binary_word);
    string ref_tag = find_tag(binary_word);
    b.set_tag(ref_tag);
    b.set_valid_bit(1);
	b.set_lru_value(3);
	b.set_index(index);
	insert_word(b,is_write);
	
}
void Cache::insert_word(const Block &b,bool is_write)
{
	bool is_hit = true;
	bool is_full = true;
	int i;
	int ind_i = b.get_index();
	
	for(i = 0; i < 4;i++){
		if(ptr[b.get_index()][i].get_tag()==b.get_tag()){
			h++;
			break;
		}
		if(i==3)
			is_hit = false;
	}
	if(is_hit == true){
		int num = ptr[b.get_index()][i].get_dirty_bit();
		int number = ptr[b.get_index()][i].get_lru_value();
		ptr[b.get_index()][i] = b;

		if(num ==1)
			ptr[b.get_index()][i].set_dirty_bit(1);
		
		for(int j = 0; j <4;j++){
			if(j!=i && ptr[b.get_index()][j].get_lru_value()>number)
				ptr[b.get_index()][j].set_lru_value(ptr[b.get_index()][j].get_lru_value()-1);
		}

	}
	else{
		int ind;
		for(i = 0; i < 4;i++){
			if(ptr[b.get_index()][i].get_lru_value()==0){
				ind = i;
				break;
			}
		}
		for(i = 0; i < 4;i++){
			if(ptr[b.get_index()][i].get_valid_bit()!=0 && ptr[b.get_index()][i].get_lru_value()!=0)
				ptr[b.get_index()][i].set_lru_value(ptr[b.get_index()][i].get_lru_value()-1);
		}
		for(i = 0; i < 4;i++){
			if(ptr[b.get_index()][i].get_valid_bit()==0){
				is_full = false;
				break;
			}
		}
		if(is_full ==false){
			ptr[b.get_index()][i] = b;
			cm++;
		}
		else{
			ptr[b.get_index()][ind]=b;
			if(ptr[b.get_index()][ind].get_dirty_bit()==1){
				m++;
				dr++;
			}
			else
				m++;
		}
			
	}
}
int Cache::find_index(const string str)
{
    string index = str.substr(str.length()- index_length-4,index_length);
    int number = 1;
    int index_number = 0;
    for(int j = index.length()-1;j>=0;j--){
        if((index[j] -'0') == 1){
            index_number+=number;
        }
        number =number<<1;
    }
    return index_number;
}
string Cache::find_tag(const string str)
{
    return str.substr(0,str.length()-index_length-4);
}
string Cache::parse_string(char c)
{
	switch(toupper(c))
	{
	case '0':
		return "0000";
	case '1':
		return "0001";
	case '2':
		return "0010";
	case '3':
		return "0011";
	case '4':
		return "0100";
	case '5':
		return "0101";
	case '6':
		return "0110";
	case '7':
		return "0111";
	case '8':
		return "1000";
	case '9':
		return "1001";
	case 'A':
		return "1010";
	case 'B':
		return "1011";
	case 'C':
		return "1100";
	case 'D':
		return "1101";
	case 'E':
		return "1110";
	case 'F':
		return "1111";
	}
}
void Cache::print()
{
    double cmr = cm/30000.0;
	double hr = h/30000.0;
	double drr = dr/30000.0;
	cout<<"CACHE SIZE OF "<<s<<endl;
	cout<<"--------------"<<endl;
	cout<<"DIRTY REPLACEMENT: "<<dr<<endl;
	cout<<"HITS: "<<h<<endl;
	cout<<"MISSES: "<<m<<endl;
	cout<<"COMPULSARY MISSES: "<<cm<<endl;
	cout<<"COMPULSARY MISS RATIO: "<<fixed<<setprecision(5)<<cmr<<endl;
	cout<<"HIT RATIO: "<<fixed<<setprecision(5)<<hr<<endl;
	cout<<"DIRTY REPLACEMENT RATIO "<<fixed<<setprecision(5)<<drr<<endl<<endl;

}
Cache::~Cache()
{
    for(int i = 0; i < s;i++)
        delete [] ptr[i];
    delete [] ptr;
}
