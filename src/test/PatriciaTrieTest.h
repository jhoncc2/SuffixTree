using namespace std;
#include <string>
#include <vector>

class PatriciaTrieTest: public TestSuite {
public:

	/**********write tests*************/
	void run() {
		// setup context in conf
		conf::use_universe(conf::alph_universe);

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

		vector<PatriciaTrie*> list;
		list.resize(12);
		assertTrue(list.size() == 12);
		for (int i =0; i < list.size(); i ++)
			assertTrue(list[i] == NULL);


//		cout << &(str2[0]) << "-" << &(str[0])  << endl;
//		cout << &str2 << "-" << &str  << endl;

//		PatriciaTrie *t1 = new PatriciaTrie();
//		PatriciaTrie *t2 = t1;
//		cout << t1 << "-" << t2  << endl;
//		cout << &t1 << "-" << &t2  << endl;

	}

	void testBasic() {
		setContext(__func__);
		string str = "dafjads";
		string *stc = &str;
//		cout << str << endl;
//		cout << str[1] << endl;
//		cout << (*stc)[1] << endl;
//		cout << (int)str[1] << endl;
//		cout << (int) 'z' << endl;

		PatriciaTrie *t = new PatriciaTrie();

		assertTrue(t->findUnmatchedCharIndex(getNSP("qwerty$"),getNSP("qwerty$"), 0, 6) == -1);
		assertTrue(t->findUnmatchedCharIndex(getNSP("qwerty$"),getNSP("qw2rty$"), 0, 6) == 2);
		assertTrue(t->findUnmatchedCharIndex(getNSP("qwerty$"),getNSP("qwe$"), 0, 6) == 3);
		assertTrue(t->findUnmatchedCharIndex(getNSP("qwerty$"),getNSP("qwe$"), 0, 3) == -1);
		assertTrue(t->findUnmatchedCharIndex(getNSP("qwerty$"),getNSP("qwe$"), 0, 4) == 3);
		assertTrue(t->findUnmatchedCharIndex(getNSP("`qwerty`"),getNSP("`qwe`"), 0,8) == 4);
		assertTrue(t->findUnmatchedCharIndex(getNSP("`qwe`"),getNSP("`qwerty`"),  0,8) == 4);
		assertTrue(t->findUnmatchedCharIndex(getNSP("`qwe"),getNSP("`qwerty`"),  0,8) == 4);
		assertTrue(t->findUnmatchedCharIndex(getNSP("$romane`"),getNSP("$ruber`"), 0, 3) == 2);

		// context alphabet universe
		assertTrue(conf::universe_descriptor[(int)'a'] == 0);
		cout << "sdafas " << endl;
		assertTrue(t->getUniverseIndex('a') == 0);
//		cout << t->getUniverseIndex('$') << endl;
		cout << ((short)'p') << " - " << ((short)'`') << endl;
		assertTrue(t->getUniverseIndex('`') == conf::alph_universe.size());
		assertTrue(t->getUniverseIndex('p') == 15);
	}

	void testInsert() {
		setContext(__func__);
		PatriciaTrie *t = new PatriciaTrie();
		assertTrue(t->numberOfNodes() == 1); //root
		assertTrue(t->getWidth() == 0);

		t->insertString(getNSP("romane"));
		assertTrue(t->numberOfNodes() == 1);
		assertTrue(t->getNumberOfStrings() == 1);

		t->insertString(getNSP("romane")); //already inserted
		assertTrue(t->numberOfNodes() == 1);
		assertTrue(t->getNumberOfStrings() == 1);
		//		//


		t->insertString(getNSP("romanus"));
		t->printTrie();
		assertTrue(t->numberOfNodes() == 3);
		assertTrue(t->getNumberOfStrings() == 2);
		cout << "djsfksldf" << endl;

		t->insertString(getNSP("romulus"));
		assertTrue(t->getNumberOfStrings() == 3);

		t->insertString(getNSP("rubens"));
		assertTrue(t->getNumberOfStrings() == 4);

		t->insertString(getNSP("rubenson"));
		assertTrue(t->getNumberOfStrings() == 5);
		t->printTrie();
		t->insertString(getNSP("ruber"));
		assertTrue(t->getNumberOfStrings() == 6);

		t->insertString(getNSP("rubicon"));
		assertTrue(t->getNumberOfStrings() == 7);

		t->insertString(getNSP("rubicundus"));
		assertTrue(t->getNumberOfStrings() == 8);
		t->insertString(getNSP("ruba"));
		assertTrue(t->getNumberOfStrings() == 9);
		t->insertString(getNSP("rub"));
		assertTrue(t->getNumberOfStrings() == 10);


		t->insertString(getNSP("pub"));
		assertTrue(t->getNumberOfStrings() == 11);

		t->insertString(getNSP("pop"));
		assertTrue(t->getNumberOfStrings() == 12);

		t->printTrie();

//		cout << t->getWidth() <<endl;
		assertTrue(t->getWidth() == 12);
		assertTrue(t->getNumberOfStrings() == 12);
	}

	string *getNSP(string st) {
		string *str = new string(st);
		cout << str << endl;
		return str;
	}
};
