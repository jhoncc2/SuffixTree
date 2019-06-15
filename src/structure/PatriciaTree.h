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

	vector <PatriciaTree*> children; // 26 children

	PatriciaTree(){
		children.resize(conf::univ_size);
		cout << children.size() << endl;
		localString = "";
		short charIndex = 0;
		parent = NULL;
		leaf = true;
	}

	/**
	 * only called by the root node
	 */
	void insertString(char *str){
		this->findPrefixNodeAndInsert(str, 0);
	}

	void findPrefixNodeAndInsert(char *str, int idx) {
		short pos = getAlphabetIndex(str[idx + nextCharDist]);
		if ((idx + nextCharDist) >= strlen(str)// no enough room for comparison
				|| children[pos] == NULL //next node in the tree is not correct
			) {
			short diffIndex = findUnmatchedCharIndex(localString, str, idx, idx + nextCharDist);
			this->createNodeAtIndex(str, diffIndex);
		} else {
			short diffIndex = findUnmatchedCharIndex(localString, str, idx, idx + nextCharDist);
			if (diffIndex == -1)
				findPrefixNodeAndInsert(str, idx + nextCharDist); // continue finding in other nodes
			else
				createNodeAtIndex(str, diffIndex);
		}
	}

	void createNodeAtIndex(char *str, short diffIndex){
		short pos = getAlphabetIndex(str[diffIndex]);
		if(diffIndex == 0 && isRoot()) {
			PatriciaTree *l = this->createNewLeaf(str, diffIndex);
			children[pos] = l;
			cout << " here " << children.size() << endl;
		} else if (diffIndex == -1 && isLeaf() && strlen(str) == charIndex + nextCharDist) {
			return;
		}else if (diffIndex == -1 && isLeaf() && strlen(str) > charIndex + nextCharDist) {
			PatriciaTree *l = this->createNewLeaf(str, diffIndex);
			this->setNextCharDist(diffIndex - (charIndex-1));
			children[str[diffIndex]] = l;
		} else if (diffIndex < charIndex + nextCharDist) { // new string cutting branches
			this->bifurcateWithString(str, diffIndex);
		} else {
			cout << "[error] undefined case: " << str << " :  "<< diffIndex << endl;
		}
	}

	PatriciaTree *createNewLeaf(char *str, short breakIdx) {
		PatriciaTree *t = new PatriciaTree();
		t->setCharIndex(breakIdx);
		t->setNextCharDist(0);
		t->setLocalString(str);

		t->setParent(this);

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
		PatriciaTree *t2 = new PatriciaTree();
		t2->setCharIndex(breakIdx);
		t2->setNextCharDist(0);
		t2->setLocalString(str);
		t2->setIsLeaf(true);
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
		if(stra.size() == 0 || strb.size() ==0)
			return ini;

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
		cout << children.size() << endl;
		for (int i = 0; i < children.size() ; ++i) {
			if(children[i] != NULL) {

				res = res + children[i]->numberOfNodes();

			}
		}
		return res;
	}

};
