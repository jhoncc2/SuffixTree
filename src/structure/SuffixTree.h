#include <tuple>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

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

class SuffixTree : public PatriciaTrie {

public:

	void build(char * text){
		buildRange(text, 0, strlen(text));
	}
	void buildRange(char* text, int ini, int limit) {
//		tree = new PatriciaTrie();
		asserter(ini >= 0, "initial index no valid {build suffix tree}");
		asserter(limit <= strlen(text), "limit no valid {build suffix tree}");

		int end = strlen(text);
		PatriciaTrie *t = this->insertString(text);
		t->appendOccurrences(0);

		for (int i = 1; i < strlen(text) ; i ++) {
			char *sb = substringOf(text, i, end);
			t = this->insertString(sb);
			t->appendOccurrences(i);
		}
	}

	char *substringOf(char* str, int i, int e) {
		string s(str);

		string str2 = s.substr(i,e-i);

		char *cstr = new char[str2.length() + 1];
		strcpy(cstr, str2.c_str());
		return cstr;
	}

	/**
	 * counts the number of strings
	 * that match the parameter str
	 * returns the number of them
	 */
	int count(char * str) {
		PatriciaTrie *t = this->getPrefixNode(str);
		if(t == NULL)
			return 0;

		return t->getNumberOfStrings();
	}

	/**
	 * finds the node which match the str char
	 * return its indices
	 */
	vector<int> locate(char *str) {
		PatriciaTrie *t = this->getPrefixNode(str);
		if(t == NULL){
			vector<int> v;
			return v;
		}

		return t->getOccurrences();
	}

	vector<string> topkq(int k, int q) {
		vector <string> result ;
		vector <PatriciaTrie*> r;
		findMatchingLength(q, &r);

		sort(r.begin(), r.end(), SuffixTree::compareTries);

		int size = r.size();
		int lim = min(k, size);
//		cout << "found: " << r.size() << endl;
		for (int i = 0 ; i < lim; i++) {
			result.push_back(r[i]->getString(q));
		}

		return result;
	}

	/**
	 * Printable version for testing and visual results
	 */
	vector<string> topkqTest(int k, int q, vector< pair<string,int> > *l) {
			vector <string> result ;
			vector <PatriciaTrie*> r;
			findMatchingLength(q, &r);

			sort(r.begin(), r.end(), SuffixTree::compareTries);

			int size = r.size();
			int lim = min(k, size);
	//		cout << "found: " << r.size() << endl;
			for (int i = 0 ; i < lim; i++) {
				pair <string, int> p;
				p.first = r[i]->getString(q);
				p.second = r[i]->getNumberOfStrings();
				l->push_back(p);
				result.push_back(r[i]->getString(q));
			}

			return result;
		}

	static bool compareTries(PatriciaTrie *t1, PatriciaTrie *t2){
		return (t1->getNumberOfStrings() > t2->getNumberOfStrings());
	}

	void printTree(){
		this->printTrie();
	}

};
