#include <utility>
#include <iostream>
#include <vector>
#include <string.h>
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

	string *localString; //

	vector <PatriciaTrie*> children; // children
	long charIndex, intervalIndex;

	vector <int> occurrences; // stored index of substring occurrences (prefix)

	int numberOfStrings = 0;

	PatriciaTrie(){
//		children.resize(conf::univ_size);
		children = createVectorUniverse();

		localString = new string();
		intervalIndex = 0;
		charIndex = 0;
		parent = NULL;
		numberOfStrings = 0;
	}

	PatriciaTrie(string *str){
		children = createVectorUniverse();

		localString = str;
		intervalIndex = (*localString).length() -1;
		charIndex = 0;
		parent = NULL;
		numberOfStrings = 0;
	}

	/**
	 * find the prefix {str} in the tree
	 * returns a Tree node | NULL if not match prefix {str}
	 */
	PatriciaTrie *getPrefixNodeMatching(string *str){
		// compare localstring with str

		int idx = findUnmatchedCharIndex(localString, str, charIndex, intervalIndex + 1);
		long strSize = (*str).length();
		if (idx != -1)
			if (idx == strSize)
				return this;
			else
				return NULL;
		else if (idx == -1)
			if (intervalIndex +1 == strSize)
				return this;

		long pos = getUniverseIndex((*str)[intervalIndex +1]);
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

	string getNodeString(){

		int lim = intervalIndex -charIndex;
		lim = min(lim, 10);
		return (*localString).substr(charIndex, lim);
	}

	string getString(int q){
//		string s(localString);
		return (*localString).substr(1,q);
	}

	PatriciaTrie *getPrefixNode(string *str){
		string s = conf::ini_char + (*str);
//		s = string(1,conf::ini_char) + s ;

//		string *cstr = new char[s.length() + 1];
//		strcpy(cstr, s.c_str());

		return getPrefixNodeMatching(&s);
	}

	PatriciaTrie *insertString(string *strToInsert) {
//		string s(strToInsert);
//
//		s.append(1, conf::end_char);
////		s.insert(0, 1, conf::end_char);
//		s = string(1,conf::ini_char) + s ;
//
//		string *cstr = new char[s.length() + 1];
//		strcpy(cstr, s.c_str());

		string *s = new string(conf::ini_char + (*strToInsert) + conf::end_char);
//		cout << strToInsert << *strToInsert << "-" << *s << s << endl;

		return insertStringInTrie(s);
	}

	/**
	 * only called by the root node
	 */
	PatriciaTrie *insertStringInTrie(string *str){
		if ((*localString).length() == 0) {
			this->setLocalString(str);
			this->setIntervalIndex((*str).length()-1);
			this->increaseNumberOfStrings();
			return this;
		}

		PatriciaTrie *t = this->findLongestPrefixNode(str);
		return t->bifurcate(str);
	}

	PatriciaTrie *bifurcate(string *str) {
		long diffIndex = getUnmatchedChar(str);
		// Already in trie
		if (diffIndex == -1){
			if (isLeaf() && (*str).length() == (*localString).length()){
				return this;
			}

//			if((*localString).length() < (*str).length()){
//				string *tmp = str;
//				str = localString;
//				localString = tmp;
//			}

			long pos = getUniverseIndex((*str)[intervalIndex+1]);

			if (children[pos] == NULL) {
				PatriciaTrie *t = createNewTrie(str, intervalIndex+1, (*str).length()-1);
				return insertChildren(pos, t);
			}
		}
//		cout << "bifurcating2: " << *str << " " << (*str)[intervalIndex+1] << endl;
//		long pos = getUniverseIndex((*str)[intervalIndex+1]);


		// bifurcate
		PatriciaTrie *t1 = createNewTrie(localString, diffIndex, intervalIndex);
		t1->setChildren(children);
		t1->setOccurrences(occurrences);
		t1->setNumberOfStrings(this->getNumberOfStrings());

		PatriciaTrie *t2 = createNewTrie(str, diffIndex, (*str).length()-1);

		// update current Node
		this->setIntervalIndex(diffIndex-1);
		this->setChildren(createVectorUniverse()); // empty vector

		long pos1, pos2;
		pos1 = getUniverseIndex((*localString)[diffIndex]);
		pos2 = getUniverseIndex((*str)[diffIndex]);
		this->insertChildrenSilently(pos1, t1);
		this->insertChildren(pos2, t2);

		return t2;
	}

	PatriciaTrie *insertChildren(long idx, PatriciaTrie *t) {
		asserter(idx >=0 && idx < children.size() , "index out of bounds { " + to_string(idx));
		if(children[idx] != NULL) {
			this->printSubstring();
			t->printSubstring();
		}
		asserter(children[idx] == NULL, "already exists element at "
									+ to_string(idx) + "\n"
									+ " " + to_string(charIndex) + "- " + to_string(intervalIndex) + "\n"
									+ " " + getNodeString() + "\n"
									+ " " + t->getNodeString()
									);
		children[idx] = t;
		t->increaseNumberOfStrings();
		return t;
	}

	PatriciaTrie *insertChildrenSilently(long idx, PatriciaTrie *t) {
		asserter(idx >=0 && idx < children.size() , "index out of bounds { " + to_string(idx));
		asserter(children[idx] == NULL, "silent - already exists element at "
								+ to_string(idx)
								+ " " + to_string(charIndex)
								+ " " + getNodeString()
								+ " " + t->getNodeString()
								);
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
		int limit = intervalIndex;
		limit = min(limit, 50);

		for (int i = 0; i<=limit; i++)
			s = s + (*localString)[i];

		if (limit < intervalIndex) {
			s+= "...";
		}
		return s;
//		return *localString;
	}

	/**
	 * Each node leaf poins at the last char of the string
	 */
	PatriciaTrie *createNewTrie(string *str, long idx, long intervalIndex) {
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

	long getUnmatchedChar(string *str) {
		return findUnmatchedCharIndex(localString, str, charIndex, intervalIndex+1);
	}

	PatriciaTrie *findLongestPrefixNode(string *str) {
		// ensure the interval i-e are equals with str, then call recursive

		// next different character
		if(intervalIndex < (*str).length()
			&& (*str)[intervalIndex] == (*localString)[intervalIndex]) {
			if(intervalIndex + 1 < (*str).length()
				&& children[getUniverseIndex((*str)[intervalIndex + 1])] != NULL
				&& this->getUnmatchedChar(str) == -1){

				return children[getUniverseIndex((*str)[intervalIndex + 1])]->findLongestPrefixNode(str);
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
		int index = conf::universe_descriptor[(int) a];
		asserter(index >=0 && index < conf::universe.length(), ("character not in universe :" + to_string(a)) );
//		cout << a << " index found " << index<< endl;
		return index;
	}

	/**
	 * Deprecated
	 */
	long getAlphabetIndex(char a) {
		return ((short)a) - conf::char_diff;
	}

	void setLocalString(string *str) {
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
	long findUnmatchedCharIndex(string *stra, string *strb, long ini, long end) {
		long res = -1; // completely equals
		long limit = end;
		if(limit > (*stra).size()) {
			limit = (*stra).size();
			if ((*stra).size() > (*strb).size())
				limit = (*strb).size();
			res = limit; // one string is shorter for the comparison
		}

		for(long i = ini; i < limit; i ++) {
			if((*stra)[i] != (*strb)[i]) {
				res = i;
				return res;
			}
		}
		return res;
	}



	/** Interaction **/
	bool isLeaf(){
		return (*localString)[intervalIndex] == conf::end_char;
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
