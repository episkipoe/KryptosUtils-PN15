/*
 *  Return the decimal result of treating the number as a reversed five bit sequence  (c.f. Baudot code)
 *  
*/
unsigned int reverseBits(unsigned int num) {
    unsigned int NO_OF_BITS = 5;
    unsigned int reverse_num = 0, i, temp;
 
    for (i = 0; i < NO_OF_BITS; i++)
    {
        temp = (num & (1 << i));
        if(temp)
            reverse_num |= (1 << ((NO_OF_BITS - 1) - i));
    }
 
    return reverse_num;


int letterToBaudot(char letter) {
	map<char,string> letter_to_binary;
	letter_to_binary['E'] = "00001";
	letter_to_binary['A'] = "00011";
	letter_to_binary['S'] = "00101";
	letter_to_binary['I'] = "00110";
	letter_to_binary['U'] = "00111";
	letter_to_binary['D'] = "01001";
	letter_to_binary['R'] = "01010";
	letter_to_binary['J'] = "01011";
	letter_to_binary['N'] = "01100";
	letter_to_binary['F'] = "01101";
	letter_to_binary['C'] = "01100";
	letter_to_binary['K'] = "01111";
	letter_to_binary['T'] = "10000";
	letter_to_binary['Z'] = "10001";
	letter_to_binary['L'] = "10010";
	letter_to_binary['W'] = "10011";
	letter_to_binary['H'] = "10100";
	letter_to_binary['Y'] = "10101";
	letter_to_binary['P'] = "10110";
	letter_to_binary['Q'] = "10111";
	letter_to_binary['O'] = "11000";
	letter_to_binary['B'] = "11001";
	letter_to_binary['G'] = "11010";
	letter_to_binary['M'] = "11100";
	letter_to_binary['X'] = "11101";
	letter_to_binary['V'] = "11110";
	return letter_to_binary[letter];
}

