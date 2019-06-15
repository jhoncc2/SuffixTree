using namespace std;
#include <string>

class PatriciaTreeTest: public TestSuite {
public:

	/**********write tests*************/
	void run() {
		testBasic();
		testBasic2();
		testInsert();
	}

	void testBasic2(){
		setContext(__func__);
		char *str = "qwert";
		char *str3 = "qwert";
//		str[2] = 'z';
		assertTrue(strlen(str) == 5);
		const char *str2 = str;
		assertTrue(str2 == str);
		assertTrue(str2 == str3);

		cout << &(str2[0]) << "-" << &(str[0])  << endl;
		cout << &str2 << "-" << &str  << endl;

//		PatriciaTree *t1 = new PatriciaTree();
//		PatriciaTree *t2 = t1;
//		cout << t1 << "-" << t2  << endl;
//		cout << &t1 << "-" << &t2  << endl;

	}

	void testBasic() {
		setContext(__func__);
		string str = "dafjads";
		string *stc = &str;
		cout << str << endl;
		cout << str[1] << endl;
		cout << (*stc)[1] << endl;
		cout << (int)str[1] << endl;
		cout << (int) 'z' << endl;

		PatriciaTree *t = new PatriciaTree();
		assertTrue(t->findUnmatchedCharIndex("qwerty", "qwerty", 0, 6) == -1);
		assertTrue(t->findUnmatchedCharIndex("qwerty", "qw2rty", 0, 6) == 2);
		assertTrue(t->findUnmatchedCharIndex("qwerty", "qwe", 0, 6) == 3);

		assertTrue(t->getAlphabetIndex('a') == 0);
		assertTrue(t->getAlphabetIndex('p') == 15);
	}

	void testInsert() {
		setContext(__func__);
		PatriciaTree *t = new PatriciaTree();
		assertTrue(t->numberOfNodes() == 1); //root
		t->insertString("romane");
		cout << "checkpoint 1 " << endl;
		assertTrue(t->numberOfNodes() == 2);
		cout << "here " << endl;
		t->insertString("romane"); //already inserted
		assertTrue(t->numberOfNodes() == 2);
//
//		t->insertString("romanus");
//		assertTrue(t->numberOfNodes() == 3);
//
//		t->insertString("romulus");
//		t->insertString("rubens");
//		t->insertString("ruber");
//		t->insertString("rubicon");
//		t->insertString("rubicundus");
//
//		assertTrue(t->getHeight() == 3);
//		//assertTrue(t.getHeight() == 3);
//
//		cout << "hello world!!";
	}
};
