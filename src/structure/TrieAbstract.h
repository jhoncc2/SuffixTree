#include <algorithm>
#include <string>

using namespace std;

class TrieAbstract {

public:
	TrieAbstract *root;

	virtual void insertString(string s){}
	virtual bool isLeaf(){}
	virtual bool isRoot(){}
	virtual TrieAbstract *getRoot(){}
	virtual int getHeight(){}

};
