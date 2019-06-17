#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

class TrieAbstract {

public:
	TrieAbstract *root;

	virtual void insertString(string s){}
	virtual bool isLeaf(){}
	virtual bool isRoot(){}
	virtual TrieAbstract *getRoot(){}
	virtual int getHeight(){}

	/**
	 * asserts booleans, for expected behavior
	 */
	virtual void asserter(bool boolean, string msg){
		if (!boolean){
	        throw std::invalid_argument("\n{asserter error} unexpected value : " + msg);
		}
	}
};
