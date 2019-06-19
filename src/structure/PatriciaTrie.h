#include <utility>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


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

	vector <PatriciaTrie*> children; // children
	long charIndex, intervalIndex;

	vector <int> occurrences; // stored index of substring occurrences (prefix)

	int numberOfStrings = 0;

	PatriciaTrie(){
//		children.resize(conf::univ_size);
		children = createVectorUniverse();

		localString = "";
		intervalIndex = 0;
		charIndex = 0;
		parent = NULL;
		numberOfStrings = 0;
	}

	PatriciaTrie(char *str){
		children.resize(conf::univ_size);

		localString = str;
		intervalIndex = strlen(localString) -1;
		charIndex = 0;
		parent = NULL;
		numberOfStrings = 0;
	}

	/**
	 * find the prefix {str} in the tree
	 * returns a Tree node | NULL if not match prefix {str}
	 */
	PatriciaTrie *getPrefixNodeMatching(char *str){
		// compare localstring with str

		int idx = findUnmatchedCharIndex(localString, str, charIndex, intervalIndex + 1);
		long strSize = strlen(str);
		if (idx != -1)
			if (idx == strSize)
				return this;
			else
				return NULL;
		else if (idx == -1)
			if (intervalIndex +1 == strSize)
				return this;

		long pos = getUniverseIndex(str[intervalIndex +1]);
		if (children[pos] == NULL)
			return NULL;

		return children[pos]->getPrefixNodeMatching(str);

	}

	void findMatchingLength(int q, vector<PatriciaTrie*> *list) {
		// omit trailing character
		if(isLeaf() && intervalIndex ==q)
			return;
		if(intervalIndex>=q) {
			(*list).push_back(this);
			return;
		}
		for(int i =0; i<children.size(); i++) {
			if(children[i] != NULL) {
				children[i]->findMatchingLength(q, list);
			}
		}
	}

	string getString(int q){
		string s(localString);
		return s.substr(1,q);
	}

	PatriciaTrie *getPrefixNode(char *str){
		string s(str);
		s = string(1,conf::ini_char) + s ;

		char *cstr = new char[s.length() + 1];
		strcpy(cstr, s.c_str());

		return getPrefixNodeMatching(cstr);
	}

	PatriciaTrie *insertString(char *strToInsert) {
		string s(strToInsert);

		s.append(1, conf::end_char);
//		s.insert(0, 1, conf::end_char);
		s = string(1,conf::ini_char) + s ;

		char *cstr = new char[s.length() + 1];
		strcpy(cstr, s.c_str());

		return insertStringInTrie(cstr);
	}

	/**
	 * only called by the root node
	 */
	PatriciaTrie *insertStringInTrie(char *str){
		if (strlen(localString) == 0) {
			this->setLocalString(str);
			this->setIntervalIndex(strlen(str)-1);
			this->increaseNumberOfStrings();
			return this;
		}

		PatriciaTrie *t = this->findLongestPrefixNode(str);

		return t->bifurcate(str);
	}

	PatriciaTrie *bifurcate(char *str) {
		long diffIndex = getUnmatchedChar(str);
		// Already in trie
		if (diffIndex == -1){
			if (isLeaf() && strlen(str) == strlen(localString)){
				return this;
				cout << "already inserted" << endl;
			}

//			if(strlen(localString) < strlen(str)){
//				char *tmp = str;
//				str = localString;
//				localString = tmp;
//			}

			long pos = getUniverseIndex(str[intervalIndex+1]);
			if (children[pos] == NULL) {
				PatriciaTrie *t = createNewTrie(str, intervalIndex+1, strlen(str)-1);
				return insertChildren(pos, t);
			}
		}

		// bifurcate
		PatriciaTrie *t1 = createNewTrie(localString, diffIndex, intervalIndex);
		t1->setChildren(children);
		t1->setOccurrences(occurrences);
		t1->setNumberOfStrings(this->getNumberOfStrings());

		PatriciaTrie *t2 = createNewTrie(str, diffIndex, strlen(str)-1);

		// update current Node
		this->setIntervalIndex(diffIndex-1);
		this->setChildren(createVectorUniverse()); // empty vector

		long pos1, pos2;
		pos1 = getUniverseIndex(localString[diffIndex]);
		pos2 = getUniverseIndex(str[diffIndex]);
		this->insertChildrenSilently(pos1, t1);
		this->insertChildren(pos2, t2);

		return t2;
	}

	PatriciaTrie *insertChildren(long idx, PatriciaTrie *t) {
		asserter(children[idx] == NULL, "already exists element at " + to_string(idx));
		children[idx] = t;
		t->increaseNumberOfStrings();
		return t;
	}

	PatriciaTrie *insertChildrenSilently(long idx, PatriciaTrie *t) {
		asserter(children[idx] == NULL, "silent - already exists element at " + to_string(idx));
		children[idx] = t;
		return t;
	}

	void increaseNumberOfStrings(){
		numberOfStrings += 1;
		if(!isRoot())
			parent->increaseNumberOfStrings();
	}

	void appendOccurrences(int idx) {
		occurrences.push_back(idx);
		if(!isRoot())
			parent->appendOccurrences(idx);
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
//		cout << "[" ;
//		for ( auto &it : occurrences ) {
//				    cout << it << "-";
//				}
//		cout << "] ";
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
	PatriciaTrie *createNewTrie(char *str, long idx, long intervalIndex) {
		PatriciaTrie *t = new PatriciaTrie(str);
		t->setCharIndex(idx);
		t->setIntervalIndex(intervalIndex);
		t->setLocalString(str);
		t->setParent(this);
		t->updateNumberOfStrings();

		return t;
	}

	void setIntervalIndex(long ic) {
		intervalIndex = ic;
	}

	long getUnmatchedChar(char *str) {
		return findUnmatchedCharIndex(localString, str, charIndex, intervalIndex+1);
	}

	PatriciaTrie *findLongestPrefixNode(char *str) {
		// ensure the interval i-e are equals with str, then call recursive

		// next different character
		if(intervalIndex < strlen(str)
			&& str[intervalIndex] == localString[intervalIndex]) {
			if(intervalIndex + 1 < strlen(str)
				&& children[getUniverseIndex(str[intervalIndex + 1])] != NULL
				&& this->getUnmatchedChar(str) == -1){

				return children[getUniverseIndex(str[intervalIndex + 1])]->findLongestPrefixNode(str);
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

	vector<PatriciaTrie*> createVectorUniverse(){
		vector<PatriciaTrie*> v;
		v.resize(conf::universe.size());
		asserter(v.size() == conf::universe.size(), "unexpected {resize on vector not working}");
		return v;
	}

	/**
	 * returns the index related to the universe
	 * universe is configured in file conf
	 */
	long getUniverseIndex(char a) {
		return conf::universe_descriptor[(short) a];
	}

	/**
	 * Deprecated
	 */
	long getAlphabetIndex(char a) {
		return ((short)a) - conf::char_diff;
	}

	void setLocalString(char *str) {
//		strcpy(localString, str.c_str());
		localString = str;
	}
	void setCharIndex(long index) {
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

	/**
	 * return the char index that does not match between strings a and b
	 * if a is shorter than end then returns the size of the string (analogous for b)
	 */
	long findUnmatchedCharIndex(string stra, string strb, long ini, long end) {
		long res = -1; // completely equals
		long limit = end;
		if(limit > stra.size()) {
			limit = stra.size();
			if (stra.size() > strb.size())
				limit = strb.size();
			res = limit; // one string is shorter for the comparison
		}

		for(long i = ini; i < limit; i ++) {
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

		for (long i =0; i< children.size() ; i ++){
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

	const vector<int>& getOccurrences() const {
		return occurrences;
	}

	void setOccurrences(const vector<int>& occurrences) {
		this->occurrences = occurrences;
	}
};
