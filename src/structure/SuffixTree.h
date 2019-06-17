#include <iostream>
#include <vector>
#include <string>

using namespace std;


/**
 * String ($), ...... , $ |  ($): initial Character, $ end character
 * Where 0 is the pinter to ($) &  e is the  pointer to $
 *
 * Trie {(($)..str,0, j) -> [(str, i, e)0, ... ], ..... , (str..$, i, e)}
 * Root node (($)..str, 0, j)
 * Internal node (str, i, j)
 * Leaf node (str..$, i, e)
 *
 * Each node contains 26 + 1 children.
 *
 *
 */

class SuffixTree {

public:

	PatriciaTrie *tree;

	void build(char* text) {
		tree = new PatriciaTrie();
		tree->insertString(text);
		int end = strlen(text);
		for (int i = 1; i < strlen(text) ; i ++) {
			char *sb = substringOf(text, i, end);
			tree->insertString(sb);
		}
	}

	char *substringOf(char* str, int i, int e) {
		string s(str);

		string str2 = s.substr(i,e-i);

		char *cstr = new char[str2.length() + 1];
		strcpy(cstr, str2.c_str());
		return cstr;
	}

	void count(char * srt) {

	}

};
