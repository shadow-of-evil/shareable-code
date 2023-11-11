

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <tgmath.h>

	// byte data type for manipulation and storeage of byte information.

typedef struct byte{
	
	
	public:
		int overflow;
		int zero;
		int bit[4];
	
		byte(){
			bit[0] =0;
			bit[1] =0;
			bit[2] =0;
			bit[3] =0;
			zero = 0;
			overflow = 0;
		}
		
		//sets bits equal to a string if it 4 characters long
		
		setbits(char* in){	
			char s[5];
			strcpy(s, in);
			if(bitsValid(s)){
				bit[0] =s[0]-48;
				bit[1] =s[1]-48;
				bit[2] =s[2]-48;
				bit[3] =s[3]-48;
			}
			else{
				printf("\ninput in not 4 bit binary\n\n");
			}
		}
		
		// checks if byte contains only zeros then sets equal depending on result. 
		
		setzero(){
			zero=true;
			for(int i=0;i<4;i++){
				if(bit[i]!=0){
					zero=false;
				}
			}
		}
	
		// Prints out byte data preformated
	
		printBits(){
			printf("Result:");
			printf("%i",bit[0]);	
			printf("%i",bit[1]);
			printf("%i",bit[2]);
			printf("%i ",bit[3]);
			printf("%i ",overflow);
			printf("%i\n",zero);
		};
		
		//private method to check if string input contains only 1's or 0's
		
	private:
		bool bitsValid(char*str){
		bool ret=true;
		for(int i =0; i<3;i++){
			if(str[i]-48 > 1 || str[i]-48 < 0){
				ret=false;				}
		}		
		return ret;	
		}
	
};
	
	// The OR Method
	
	byte logicalOr(byte x,byte y){
		byte ret = byte();
		for(int i=0; i<4;i++){
			if(x.bit[i]>0 || y.bit[i]>0 ){
				ret.bit[i]=1;
			}
			else{
				ret.bit[i]=0;
			}
		}
	ret.overflow=0;
	ret.setzero();	
	return ret;
	}

	// The AND Method
	
	byte logicalAnd(byte l, byte p){
			byte ret = byte();
		for(int i=0; i<4;i++){
			if(l.bit[i]>0 && p.bit[i]>0 ){
				ret.bit[i]=1;
				
			}
			else{
				ret.bit[i]=0;
			}
		}
		ret.overflow=0;
	ret.setzero();
	return ret;
	}
	
		// The ADD Method
	
	byte logicalAdd(byte x, byte y){
			byte ret;
			int AxorB=0;
			int AandB=0;
			int c=0;
		for(int i=4; i>=0;i--){
			AxorB=x.bit[i]^y.bit[i];
			AandB=x.bit[i]&y.bit[i];
			if(AxorB^c){
				
				
				if(i==0 && c==1) {  
					ret.overflow=1;
				}
				else if(c==1){
					c=0;
					ret.bit[i]=1;
				}
				else{
					ret.bit[i]=1;
			 }
				
				
			}
			if((c&AxorB)|(AandB)){				
					c=1;
				if(i==0 && c==1) {  
					ret.overflow=1;
				}
			
			}
		}
		
	if(ret.overflow!=1){
		ret.overflow=0;
	}
	ret.setzero();
	return ret;
	}

		// The Method that returns 2's compliment

	byte inverse1(byte w){
		byte ret = byte();
		byte one = byte();
		byte res = byte();
		
		one.bit[3]=1;
	if(w.zero==0){
	
		for(int i=0; i<4;i++){
			if(w.bit[i]==0 ){
				ret.bit[i]=1;
			}
			else {
				ret.bit[i]=0;
			}
		}

		res = logicalAdd(ret,one);

		return ret;
		}
		else {
			return w;
		}	
	}
	
		// The SUBRACTION Method

	byte logicalSub(byte x, byte y){
		byte result = byte();	
		result = inverse1(y);
		byte one = byte();
			one.bit[3]=1;
		result = logicalAdd(x,result);
		result.overflow=0;
		
		if(result.bit[3]==0){
			result.bit[3]=1;
			result = logicalAdd(result,one);
		} 
		
		if(x.zero == 0 && y.zero==0){
		
		return result;
		}
		else{
			return x;
		}
	}
	
		// The SET LESS THAN Method
	
	byte logicalSLT(byte r, byte v){
		byte resr = byte();
		byte resv = byte();
		resr=r;
		bool check;
		resr = logicalSub(r,v);
		resr.printByte();
		if(r.bit[3]==1){
			if(resr.bit[3]==1){
				resv.bit[3]=0;
			}
			else{
				resv.bit[3]=1;
			}
		}else{
			if(resr.bit[3]==0){
				resv.bit[3]=0;
			}
			else{
				resv.bit[3]=1;
			}
		}
		
		return resv;
	}

	// The MAIN Method

int main(int argc, char* argv[]){
	
	char opcode[32];
	
	byte output;
	
	bool zero =false;
	bool overflow=false;
	
	char xin[5];
	char yin[5];
	
	byte x;
	byte y;
	
	scanf("%s",xin);
	scanf("%s",yin);
	
	x.setbits(xin);
	y.setbits(yin);
	
	x.setzero();
	y.setzero();
	

	// multiple if and else if statments to determin what uperation to do then set output equal to result of operation.
	// got removed because of accident
	
	output.printBits();
	return 0;
}

