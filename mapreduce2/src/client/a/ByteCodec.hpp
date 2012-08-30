/**
 * @file ByteCodec.hpp
 * @description:
 *  int number codec.
 *  It use lowest 2 bits to present byte length for this number.
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_BYTECODEC
#define TPLATFORM_MAPREDUCE_BYTECODEC

namespace mapreduce{

    class CByteCode{
    public:
        /**
         * Save codec of val to s , and forward s 
         **/ 
	    inline static void	code(int value,char*&s){
		    register unsigned long val = ((unsigned long)value) << 2;
		    *(unsigned long*)s = val;
    		
		    if(!(val & 0xffffff00)){
			    s++;
			    return;	
		    }
		    else if(!(val & 0xffff0000)){
			    *s |=  1 ; 
			    s  += 2;
			    return;	
		    }
		    else if(!(val & 0xff000000)){
			    *s |=  2 ; 
			    s  += 3;
			    return;	
		    }
		    else{
			    *s |=  3 ; 
			    s  += 4;
			    return;	
		    }
	    }
    	
        /**
         * Decode from s , and forward s 
         **/ 
	    inline static int	decode(char*&s){
		    register unsigned long val = *(unsigned long*)s;
    		
		    switch(val & 3){
			    case 0:
				    val = (val & 0xff )  >> 2;
				    s ++;
				    break;
			    case 1:
				    val = (val & 0xffff) >> 2;
				    s += 2;
				    break;
			    case 2:
				    val = (val & 0xffffff) >> 2;
				    s += 3;
				    break;
			    case 3:
				    val = val >> 2;
				    s += 4;
				    break;
		    }
    		
		    return val;	
	    }
    	
    };

}    
#endif
