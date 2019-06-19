using namespace std;

namespace conf  {
    const static int end_char = '`';
    const static int ini_char = '$';
    const int char_diff = 96; // the initial char of the list '`' -> 96
    static const int univ_size = 26 + 1; // is the final char of all text


    //
    // white_list_text for English
//    char *text_universe = [' ','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
    int white_list_idxs []= {32,48,49,50,51,52,53,54,55,56,57,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
    char white_list_chars []= {' ','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int ascii_table [127];


    int findIndexInAlph(char c) {
		int size = (sizeof(white_list_chars)/sizeof(*white_list_chars));
		for (int i=0; i< size; i++) {
			if (white_list_chars[i] == c)
				return i;
		}
	}

    void generate_ascii_table(){
		std::fill_n(ascii_table, 127, -1);
		for (char c : white_list_chars) {
			int pointer = (int) c;
			ascii_table[pointer] = findIndexInAlph(c);
		}
	}


}
