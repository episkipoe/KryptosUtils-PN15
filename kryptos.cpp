/**  The key is read from a file called "key"
 **  The cipher-text is read from stdin
**/

#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

/*
Cipher alphabet:  A L W H S E P B M X I T F Q C N Y J U G R D O Z K V
				      1                   2
                  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
*/

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

 
/*
 *  Given a digraph return the xor of the two numbers that the letters represent
*/
int twoCharsToNumber(char first_char, char second_char) {
	int first_num = letterToCipher(first_char);
	int second_num = letterToCipher(second_char);
	int result = first_num^second_num;
	//printf("%c %c : %i xor %i = %i\n", first_char, second_char, first_num, second_num, result);		
	return result;
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

/*
 * Transcribed from Elonka's spreadsheet
*/
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

/*
 * Show each possible digraph only once per position
*/
int incr_idx(vector<Digraphs> & solutions, vector<int> & cur_positions) {
	int num_incr=0;
	for(size_t i = 0 ; i < cur_positions.size() ; i++) {
		if(cur_positions[i]<solutions[i].values.size()-1) { 
			num_incr++;
			cur_positions[i]++; 
		}
	}
	return num_incr;
}

/*
 * Run through every permutation (intractable for non-trivial input)
*/
int next_idx(vector<Digraphs> & solutions, vector<int> & cur_positions) {
	size_t incr_idx = solutions.size()-1;
	cur_positions[incr_idx]++;
	for(int i = incr_idx ; i >= 0 ; i--) {
		if(cur_positions[i]==solutions[i].values.size()) {
			cur_positions[i]=0;
			if(i>0) {
				cur_positions[i-1]++;
			} else {
				return 0;
			}
		}	
	}
	return 1;
}

void print_digraphs(vector<Digraphs> & solutions, vector<int> & cur_positions) {
	printf("P: ");
	for(size_t i = 0 ; i < solutions.size() ; i++) {
		printf("%s\t", solutions[i].values[cur_positions[i]].c_str());	
	}
	printf("\n");
}

void print_permutations(vector<Digraphs> & solutions) {
	vector<int> cur_positions(solutions.size());
	while(1) {
		print_digraphs(solutions, cur_positions);
		if(!incr_idx(solutions, cur_positions)) break;
		//if(!next_idx(solutions, cur_positions)) break;
	}
}

int main(int argc, char * argv[]) {
	//read the key
	string key_str;
	ifstream key_stream("key");
	key_stream>>key_str;

	/*
	*  Build a look-up table which maps the plaintext number to the corresponding digraph  
	*  (based on xor'd five digit binary numbers)
	*/
	map<int,Digraphs> value_to_digraph;
	value_to_digraph[-1].values.push_back("**");
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
			//if(result==24) printf("%c%c\n", f, s);
			//printf("%c%c : %i , %i :  %i = %s\n", f, s, first_number, second_number, result, digraph);
		}
	}

	/*
	 *  Read cipher-text digraphs from stdin apply the key and produce possible plaintext values
	*/
	vector<Digraphs> solutions;
	int key_pos=0;	
	char first_char, second_char;
	while(cin>>first_char>>second_char) {
		int num = twoCharsToNumber(first_char, second_char);
		char key_char = key_str[key_pos];
		int key_int, plain_int ;
		if(key_char != '*') {
			key_int = letterToCipher(key_char);
			plain_int = num ^ key_int;
			printf("c %c%c (%i) = k %c (%i) = p %i\n", first_char, second_char, num, key_char, key_int, plain_int);
			value_to_digraph[plain_int].print_options();
		} else {
			plain_int = -1;
			printf("c %c%c (%i) \n", first_char, second_char, num);
			printf("**\n");
		}
		solutions.push_back(value_to_digraph[plain_int]);
		key_pos++;	
	}
	print_permutations(solutions);
}
