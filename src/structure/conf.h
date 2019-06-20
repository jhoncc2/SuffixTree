using namespace std;

namespace conf  {
    const static char end_char = '`';
    const static char ini_char = '$';
    const int char_diff = 96; // the initial char of the list '`' -> 96
    static const int univ_size = 26 + 1; // is the final char of all text


//    char *text_universe = [' ','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
//    int white_list_idxs []= {32,48,49,50,51,52,53,54,55,56,57,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};

    // visible universe
    string alph_universe = "abcdefghijklmnopqrstuvwxyz";
    string dna_universe = "GTCA";
    string text_universe = " 0123456789abcdefghijklmnopqrstuvwxyz";

    // universe = visible universe + end_char
    string universe;

    int universe_descriptor[127];

    int find_index_in_universe(string univ, char c) {
//		int size = (sizeof(text_universe)/sizeof(*text_universe));
    	int size = univ.size();
		for (int i=0; i< size; i++) {
			if (univ[i] == c)
				return i;
		}
	}

    /**
     * uses an universe, then includes terminal char
     */
    void use_universe(string univ){
    	std::fill_n(universe_descriptor, 127, -1);
		for (char c : univ) {
			int pointer = (int) c;
//			cout << c << "-" << find_index_in_universe(univ, c) << endl;
			universe_descriptor[pointer] = find_index_in_universe(univ, c);
		}
		// training char
		universe_descriptor[(int)conf::end_char] = univ.size();
		conf::universe = univ + conf::end_char;

		cout << "universe: [" << conf::universe << "]"  << endl;
	}


}
