#include <iostream>
#include <vector>

using namespace std;

class PatriciaTree : public TrieAbstract {

public:

	// local
	PatriciaTree *parent;
	short size = 0;
	short nextCharDist = 0;
	short charIndex = 0;
	char *localString; //
	bool leaf;
	int numberOfStrings = 0;

	vector <PatriciaTree*> children; // 26 children

	PatriciaTree(){
		children.resize(conf::univ_size);
		localString = "";
		short charIndex = 0;
		parent = NULL;
		leaf = true;
	}

	PatriciaTree(bool isLeaf) {
		children.resize(conf::univ_size);
		localString = "";
		short charIndex = 0;
		parent = NULL;
		leaf = isLeaf;
	}

	void findLeafAndInsert(char *str, short idx) {
		PatriciaTree *t = findPrefixNode(str, idx);

		if (t->isRoot()) {
			createNewLeaf(str);
		} else if (t->isLeaf()) {
			if (idx+1 == strlen(str)) {
				return;
			} else {

			}
		}
	}

	/**
	 * only called by the root node
	 */
	void insertString(char *str){
		this->findPrefixNodeAndInsert(str, 0);
	}

	void findPrefixNodeAndInsert(char *str, int idx) {
		// aphaPos is either idx + 0 for leaf and root
		// or idx + nextCharDist
		short alphPos = getAlphabetIndex(str[idx+ nextCharDist]);
		if (isRoot() && children[alphPos] == NULL){
			PatriciaTree *l = createNewLeaf(str);
			children[alphPos] = l;
		} else if (isLeaf() && strlen(str) == (idx+1)) {
			return;
		} else if (isLeaf() && strlen(str) > (idx+1)) {
			PatriciaTree *l = createNewLeaf(str);
			short diffIndex = strlen(str)-1;
			// update trie
			children[alphPos] = l;
			short leafPos = getAlphabetIndex(str[diffIndex]);
			this->setNextCharDist(leafPos);
		} else if (children[alphPos] == NULL
				|| strlen(str) <= idx + nextCharDist){
			short diffIndex = findUnmatchedCharIndex(localString, str, idx, idx + nextCharDist);
			bifurcateWithString(str, diffIndex);
		} else if (children[alphPos] != NULL){
			short diffIndex = findUnmatchedCharIndex(localString, str, idx, idx + nextCharDist);
			if (diffIndex != -1){
				bifurcateWithString(str, diffIndex);
			} else {
				findPrefixNodeAndInsert(str, idx + nextCharDist);
			}
		} else {
			cout << "{error in creation} unexpected case" << endl;
		}
	}

	void updateNumberOfStrings(){
		numberOfStrings == numberOfStrings + 1 ;
		if (!isRoot()) {
			parent->updateNumberOfStrings();
		}
	}


	/**
	 * Each node leaf poins at the last char of the string
	 */
	PatriciaTree *createNewLeaf(char *str) {
		PatriciaTree *t = new PatriciaTree();
		t->setCharIndex(strlen(str) -1);
		t->setNextCharDist(0);

		t->setLocalString(str);
		t->setIsLeaf(true);

		t->setParent(this);
		t->updateNumberOfStrings();

		return t;
	}

	void setParent(PatriciaTree *t) {
		parent = t;
	}

	/**
	 * Bifurcation of a tree with children
	 * called when there is a character which is no equals between charIndex & nextCharDist
	 */
	void bifurcateWithString(char *str, short breakIdx) {
		// child with stored bifurcations until nextCharDist
		PatriciaTree *t = new PatriciaTree();
		t->setCharIndex(breakIdx);
		t->setNextCharDist(nextCharDist - (breakIdx - charIndex));
		t->setChildren(this->getChildren());
		t->setLocalString(localString);

		// new child with new string
		PatriciaTree *t2 = createNewLeaf(str);

		// t2->setChildren(); // no children: leaf

		// Updtea current node
		vector <PatriciaTree*> cs = createVector();
		cs[this->getAlphabetIndex(str[breakIdx - 1])] = t;
		cs[this->getAlphabetIndex(localString[breakIdx - 1])] = t2;
		this->setNextCharDist(breakIdx - charIndex);

		this->setChildren(cs);
	}

	vector<PatriciaTree*> createVector(){
		vector<PatriciaTree*> v;
		v.reserve(conf::univ_size);
		return v;
	}

	void setLocalString(char *str) {
//		strcpy(localString, str.c_str());
		localString = str;
	}
	void setCharIndex(short index) {
		charIndex = index;
	}
	void setNextCharDist(short dist) {
		nextCharDist = dist;
	}
	void setChildren(vector <PatriciaTree*> childn) {
		children = childn;
	}
	vector<PatriciaTree*> getChildren(){
		return children;
	}

	PatriciaTree *getParent() {
		return parent;
	}

	/*old version*/

	bool isFinalToken(char c) {
		return c == conf::end_char;
	}

	PatriciaTree *findPrefixNode(string str, short idx) {
//		short pos = getAlphabetIndex(str[idx + charBreak]);
		if ((idx + nextCharDist) >= str.size()  // no enough room for comparison
				|| children [getAlphabetIndex(str[idx + nextCharDist])] == NULL //next node in the tree is not correct
				|| findUnmatchedCharIndex(localString, str, idx, idx + nextCharDist) != -1) { // there is a missmatch in the chars in this node
			return this;
		} else {
			return findPrefixNode(str, idx + nextCharDist); // continue finding in other nodes
		}
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
	void setIsLeaf(bool b) {
		leaf = b;
	}
	bool isLeaf(){
		return leaf;
	}

	bool isRoot(){
//		return this == dynamic_cast<PatriciaTree*>(getRoot());
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

};
