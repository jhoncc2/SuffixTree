using namespace std;
#include <string>
#include <vector>

class SuffixTreeTest: public TestSuite {
public:

	/**********write tests*************/
	void run() {
		testBasic();
		testBuild();
		testCount();
		testLocate();
	}

	void testTopKQ() {
		setContext(__func__);

		char *text = "abracadabra";
		SuffixTree *t = new SuffixTree();
		t->build(text);
		t->printTree();
	}

	void testLocate() {
		setContext(__func__);
		char *text = "abracadabra";

		SuffixTree *t = new SuffixTree();
		t->build(text);
		t->printTree();

		// individual test
		int myints[] = {0,3,5,7,10};
		std::vector<int> x (myints, myints + sizeof(myints) / sizeof(int) );
		vector <int>res =  t->locate("a");
		assertTrue(res == x);

		int myints2[] = {1,8};
		std::vector<int> x2 (myints2, myints2 + sizeof(myints2) / sizeof(int) );
		res =  t->locate("br");
		assertTrue(res == x2);


		int myints3[] = {};
		std::vector<int> x3 (myints3, myints3 + sizeof(myints3) / sizeof(int) );
		res =  t->locate("z");
		assertTrue(res == x3);

		int myints4[] = {0};
		std::vector<int> x4 (myints4, myints4 + sizeof(myints4) / sizeof(int) );
		res =  t->locate("abracadabra");
		assertTrue(res == x4);

//		assertTrue(t->count("r") == 2);
//		assertTrue(t->count("ca") == 1);
//		assertTrue(t->count("bra") == 2);
//		assertTrue(t->count("ab") == 2);
//		assertTrue(t->count("abracadabra") == 1);
//		assertTrue(t->count("abracadabras") == 0);
//		assertTrue(t->count("abracadabre") == 0);
	}

	void testBasic(){
		setContext(__func__);
		char *dna100 = getSequence100();
		assertTrue(strlen(dna100) == 100);
		char *alph = getAlphabeth();
		assertTrue(strlen(alph) == 26);

		SuffixTree *t = new SuffixTree();
		char *s = t->substringOf("abdc",1,3);
		char*s2 = "bd";
		char*s3 = "bd";
		cout << s << s2 <<  endl;
		assertTrue(s2 == s3);
//		assertTrue("bd" == s);
//		assertTrue(s2 == s3);
	}

	void testBuild() {
		setContext(__func__);

		// alph
		char *alph = getAlphabeth();
		assertTrue(strlen(alph) == 26);
		SuffixTree *t = new SuffixTree();
		t->build(alph);
		t->printTree();

		// dna
		char *dna100 = getSequence100();
		t = new SuffixTree();
		t->build(dna100);
//		t->printTree();
	}

	void testCount() {
		setContext(__func__);
		char *text = "abracadabra";

		SuffixTree *t = new SuffixTree();
		t->build(text);
		t->printTree();

		assertTrue(t->count("a") == 5);
		assertTrue(t->count("r") == 2);
		assertTrue(t->count("ca") == 1);
		assertTrue(t->count("bra") == 2);
		assertTrue(t->count("ab") == 2);
		assertTrue(t->count("abracadabra") == 1);
		assertTrue(t->count("abracadabras") == 0);
		assertTrue(t->count("abracadabre") == 0);
	}

	char* getSequence100() {
		return "acaaaggtcaattatagactcttatctgcgcagtatcattctgccctcaaatagaaagagacgtaataccgtccgcgtcataggggctgtcgtctcgacg";
	}

	char* getAlphabeth() {
		return "abcdefghijklmnopqrstuvwxyz";
	}

};
