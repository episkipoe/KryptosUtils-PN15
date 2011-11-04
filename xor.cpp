#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

unsigned int letterToCipher(char letter) {
	switch(letter) {
		case 'A': return 0;
		case 'L': return 1;
		case 'W': return 2;
		case 'H': return 3;
		case 'S': return 4;
		case 'E': return 5;
		case 'P': return 6;
		case 'B': return 7;
		case 'M': return 8;
		case 'X': return 9;
		case 'I': return 10;
		case 'T': return 11;
		case 'F': return 12;
		case 'Q': return 13;
		case 'C': return 14;
		case 'N': return 15;
		case 'Y': return 16;
		case 'J': return 17;
		case 'U': return 18;
		case 'G': return 19;
		case 'R': return 20;
		case 'D': return 21;
		case 'O': return 22;
		case 'Z': return 23;
		case 'K': return 24;
		case 'V': return 25;
	}
}

unsigned int reverseBits(unsigned int num) {
    unsigned int  NO_OF_BITS = sizeof(num) * 8;
    unsigned int reverse_num = 0, i, temp;
 
    for (i = 0; i < NO_OF_BITS; i++)
    {
        temp = (num & (1 << i));
        if(temp)
            reverse_num |= (1 << ((NO_OF_BITS - 1) - i));
    }
 
    return reverse_num;
}
 

int twoCharsToNumber(char first_char, char second_char) {
	int first_num = letterToCipher(first_char);
	int second_num = letterToCipher(second_char);
	int result = first_num^second_num;
	//printf("%c %c : %i xor %i = %i\n", first_char, second_char, first_num, second_num, result);		
	return result;
}

char positionToKey(int pos) {
	switch(pos) {
		case 0: return 'L';
		case 1: return '*';
		case 2: return 'R';
		case 3: return 'Q';		
		case 4: return 'Q';		
		case 5: return 'L';		
		case 6: return 'P';		
		case 7: return 'B';		
		case 8: return 'B';		
		case 9: return 'I';		
		case 10: return 'F';		
		case 11: return 'O';		
		case 12: return '*';		
		case 13: return 'R';
	}
}

char numberToPlainText(int number) {
	switch(number) {
		case 3: return 'A';
		case 25: return 'B';
		case 14: return 'C';
		case 9: return 'D';
		case 1: return 'E';
		case 13: return 'F';
		case 26: return 'G';
		case 20: return 'H';
		case 6: return 'I';
		case 11: return 'J';
		case 15: return 'K';
		case 18: return 'L';
		case 28: return 'M';
		case 12: return 'N';
		case 24: return 'O';
		case 22: return 'P';
		case 23: return 'Q';
		case 10: return 'R';
		case 5: return 'S';
		case 16: return 'T';
		case 7: return 'U';
		case 30: return 'V';
		case 19: return 'W';
		case 29: return 'X';
		case 21: return 'Y';
		case 17: return 'Z';
	}
}

int plainTextToNumber(char plain_text) {
	switch(plain_text) {
		case 'A': return 3;
		case 'B': return 25;
		case 'C': return 14;
		case 'D': return 9;
		case 'E': return 1;
		case 'F': return 13;
		case 'G': return 26;
		case 'H': return 20;
		case 'I': return 6;
		case 'J': return 11;
		case 'K': return 15;
		case 'L': return 18;
		case 'M': return 28;
		case 'N': return 12;
		case 'O': return 24;
		case 'P': return 22;
		case 'Q': return 23;
		case 'R': return 10;
		case 'S': return 5;
		case 'T': return 16;
		case 'U': return 7;
		case 'V': return 30;
		case 'W': return 19;
		case 'X': return 29;
		case 'Y': return 21;
		case 'Z': return 17;
	}
}


struct Digraphs {
	vector<string> values;
	void print_options() {
		for(size_t i = 0 ; i < values.size() ; i++) printf("\t%s\n", values[i].c_str());
	}
};

int main(int argc, char * argv[]) {
	map<int,Digraphs> value_to_digraph;
	vector<int> results;
	char first_char, second_char;
	int total=0, unique=0;
	for(char f = 'A' ; f <= 'Z'; f++) {
		for(char s = 'A' ; s <= 'Z'; s++) {
			int first_number = plainTextToNumber(f);
			int second_number = plainTextToNumber(s);
			//int result = reverseBits(first_number) ^ reverseBits(second_number);
			int result = first_number ^ second_number;
			char digraph[3];
			digraph[0]=f;
			digraph[1]=s;
			digraph[2]=0;
			value_to_digraph[result].values.push_back(digraph);
			if(result==24) printf("%c%c\n", f, s);
			//printf("%c%c : %i , %i :  %i = %s\n", f, s, first_number, second_number, result, digraph);
			bool u = true;
			for(size_t i = 0 ; i < results.size() ; i++) {
				if(results[i]==result) u = false;	
			}
			results.push_back(result);
			total++;
			if(u) unique++;
		}
	}

	int key_pos=0;	
	while(cin>>first_char>>second_char) {
		int num = twoCharsToNumber(first_char, second_char);
		char key = positionToKey(key_pos);
		int key_int, plain_int ;
		if(key != '*') {
			key_int = letterToCipher(key);
			plain_int = num ^ key_int;
			printf("c %c%c (%i) = k %c (%i) = p %i\n", first_char, second_char, num, key, key_int, plain_int);
			value_to_digraph[plain_int].print_options();
		} else {
			printf("c %c%c (%i) \n", first_char, second_char, num);
			printf("**\n");
		}
		key_pos++;	
	}
}
