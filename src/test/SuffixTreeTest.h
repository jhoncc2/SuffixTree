using namespace std;
#include <string>
#include <vector>

class SuffixTreeTest: public TestSuite {
public:

	/**********write tests*************/
	void run() {
//		testBasic();
		testBuild();
	}

	void testBasic(){
		setContext(__func__);
		char *dna100 = getSequence100();
		assertTrue(strlen(dna100) == 100);

		SuffixTree *t = new SuffixTree();
		char *s = t->substringOf("abdc",1,3);
		char*s2 = "bd";
		char*s3 = "b";
		cout << s << s2 <<  endl;
		assertTrue(s2 == s);
//		assertTrue("bd" == s);
//		assertTrue(s2 == s3);
	}

	void testBuild() {
		setContext(__func__);
		char *dna100 = getSequence100();
		SuffixTree *t = new SuffixTree();
		t->build(dna100);
	}

	char* getSequence100() {
		return "acaaaggtcaattatagactcttatctgcgcagtatcattctgccctcaaatagaaagagacgtaataccgtccgcgtcataggggctgtcgtctcgacg";
	}

};
