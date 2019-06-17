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

class PatriciaTrie : public TrieAbstract {

public:

	// local
	PatriciaTrie *parent;

	char *localString; //

	vector <PatriciaTrie*> children; // 26 children
	vector <short> intervals; // 26 children
	short charIndex, intervalIndex;

	int numberOfStrings = 0;

	PatriciaTrie(){
		children.resize(conf::univ_size);
		intervals.resize(conf::univ_size);

		localString = "";
		intervalIndex = 0;
		charIndex = 0;
		parent = NULL;
		numberOfStrings = 0;
	}

	PatriciaTrie(char *str){
		children.resize(conf::univ_size);
		intervals.resize(conf::univ_size);

		localString = str;
		intervalIndex = strlen(localString) -1;
		charIndex = 0;
		parent = NULL;
		numberOfStrings = 0;
	}

	void insertString(char *strToInsert) {
		string s(strToInsert);

		s.append(1, conf::end_char);
//		s.insert(0, 1, conf::end_char);
		s = string(1,conf::ini_char) + s ;

		char *cstr = new char[s.length() + 1];
		strcpy(cstr, s.c_str());

		insertStringInTrie(cstr);
	}

	/**
	 * only called by the root node
	 */
	void insertStringInTrie(char *str){
		if (strlen(localString) == 0) {
			this->setLocalString(str);
			this->setIntervalIndex(strlen(str)-1);
			this->increaseNumberOfStrings();
			return;
		}

		PatriciaTrie *t = this->findLongestPrefixNode(str);

		t->bifurcate(str);
	}

	void bifurcate(char *str) {
		short diffIndex = getUnmatchedChar(str);
		// Already in trie
		if (diffIndex == -1){
			if (isLeaf() && strlen(str) == strlen(localString)){
				return;
				cout << "already inserted" << endl;
			}

//			if(strlen(localString) < strlen(str)){
//				char *tmp = str;
//				str = localString;
//				localString = tmp;
//			}

			short pos = getAlphabetIndex(str[intervalIndex+1]);
			if (children[pos] == NULL) {
				PatriciaTrie *t = createNewTrie(str, intervalIndex+1, strlen(str)-1);
				insertChildren(pos, t);
				return;
			}
		}

		printSubstring();

		// bifurcate
		PatriciaTrie *t1 = createNewTrie(localString, diffIndex, intervalIndex);
		t1->setChildren(children);
		t1->setNumberOfStrings(this->getNumberOfStrings());
		PatriciaTrie *t2 = createNewTrie(str, diffIndex, strlen(str)-1);

		// update current Node
		this->setIntervalIndex(diffIndex-1);
		this->setChildren(createVector()); // empty vector

		short pos1, pos2;
		pos1 = getAlphabetIndex(localString[diffIndex]);
		pos2 = getAlphabetIndex(str[diffIndex]);
		this->insertChildrenSilently(pos1, t1);
		this->insertChildren(pos2, t2);
	}

	void insertChildren(short idx, PatriciaTrie *t) {
		asserter(children[idx] == NULL, "already exists element at " + to_string(idx));
		children[idx] = t;
		t->increaseNumberOfStrings();
	}

	void insertChildrenSilently(short idx, PatriciaTrie *t) {
		asserter(children[idx] == NULL, "already exists element at " + to_string(idx));
		children[idx] = t;
	}

	void increaseNumberOfStrings(){
		numberOfStrings += 1;
		if(!isRoot())
			parent->increaseNumberOfStrings();
	}

	void printTrie() {
		if(isRoot())
			cout << "--printing tree--" << endl;

		printSubstring();
		for (int i = 0; i < children.size() ; ++i) {
			if(children[i] != NULL) {
				children[i]->printTrie();
			}
		}

	}

	void printSubstring() {
		cout << std::string(charIndex, '.')
					<< '<' << charIndex
						<< ',' << intervalIndex
						<< ',' << numberOfStrings << '>'
					<< nodeSubstring() << endl;
	}

	string nodeSubstring() {
		string s = "";
		for (int i = charIndex; i<=intervalIndex; i++)
			s = s + localString[i];

		return s;
	}

	/**
	 * Each node leaf poins at the last char of the string
	 */
	PatriciaTrie *createNewTrie(char *str, short idx, short intervalIndex) {
		PatriciaTrie *t = new PatriciaTrie(str);
		t->setCharIndex(idx);
		t->setIntervalIndex(intervalIndex);
		t->setLocalString(str);
		t->setParent(this);
		t->updateNumberOfStrings();

		return t;
	}

	void setIntervalIndex(short ic) {
		intervalIndex = ic;
	}

	short getUnmatchedChar(char *str) {
		return findUnmatchedCharIndex(localString, str, charIndex, intervalIndex+1);
	}

	PatriciaTrie *findLongestPrefixNode(char *str) {
		// ensure the interval i-e are equals with str, then call recursive

		// next different character
		if(intervalIndex < strlen(str)
			&& str[intervalIndex] == localString[intervalIndex]) {
			if(intervalIndex + 1 < strlen(str)
				&& children[getAlphabetIndex(str[intervalIndex + 1])] != NULL
				&& this->getUnmatchedChar(str) == -1){

				return children[getAlphabetIndex(str[intervalIndex + 1])]->findLongestPrefixNode(str);
			}
		}

		return this;
	}

	void updateNumberOfStrings(){
		numberOfStrings == numberOfStrings + 1 ;
		if (!isRoot()) {
			parent->updateNumberOfStrings();
		}
	}

	void setParent(PatriciaTrie *t) {
		parent = t;
	}

	vector<PatriciaTrie*> createVector(){
		vector<PatriciaTrie*> v;
		v.resize(conf::univ_size);
		asserter(v.size() == conf::univ_size, "unexpected {resize on vector not working}");
		return v;
	}

	void setLocalString(char *str) {
//		strcpy(localString, str.c_str());
		localString = str;
	}
	void setCharIndex(short index) {
		charIndex = index;
	}
	void setChildren(vector <PatriciaTrie*> childn) {
		children = childn;
	}
	vector<PatriciaTrie*> getChildren(){
		return children;
	}

	PatriciaTrie *getParent() {
		return parent;
	}

	/*old version*/

	bool isFinalToken(char c) {
		return c == conf::end_char;
	}

	short getAlphabetIndex(char a) {
		return ((short)a) - conf::char_diff;
	}

	/**
	 * return the char index that does not match between strings a and b
	 * if a is shorter than end then returns the size of the string (analogous for b)
	 */
	short findUnmatchedCharIndex(string stra, string strb, short ini, short end) {
		short res = -1; // completely equals
		short limit = end;
		if(limit > stra.size()) {
			limit = stra.size();
			if (stra.size() > strb.size())
				limit = strb.size();
			res = limit; // one string is shorter for the comparison
		}

		for(short i = ini; i < limit; i ++) {
			if(stra [i] != strb[i]) {
				return i;
			}
		}
		return res;
	}



	/** Interaction **/
	bool isLeaf(){
		return localString[intervalIndex] == conf::end_char;
	}

	bool isRoot(){
//		return this == dynamic_cast<PatriciaTrie*>(getRoot());
		return parent == NULL;
	}

	TrieAbstract *getRoot(){
		return root;
	}

	int getHeight() {
		return 1;
	}

	int numberOfNodes() {
		int res = 1;
		for (int i = 0; i < children.size() ; ++i) {
			if(children[i] != NULL) {
				res = res + children[i]->numberOfNodes();
			}
		}
		return res;
	}

	int getWidth(){
		int counter = 0;
		if(isLeaf())
			counter = counter + 1;

		for (short i =0; i< children.size() ; i ++){
			if (children[i] != NULL)
				counter = counter + children[i]->getWidth();
		}
		return counter;
	}

	int getNumberOfStrings() const {
		return numberOfStrings;
	}

	void setNumberOfStrings(int numberOfStrings = 0) {
		this->numberOfStrings = numberOfStrings;
	}
};