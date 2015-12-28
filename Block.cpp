#include "Block.h"

Block::Block()
{
     valid_bit=0;
     dirty_bit=0;
     tag="";
     word="";
     lru_value=-1;
	 index = -1;
}
