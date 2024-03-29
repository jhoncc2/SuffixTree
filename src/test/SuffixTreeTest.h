using namespace std;
#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

class SuffixTreeTest: public TestSuite {
public:

	/**********write tests*************/
	void run() {
		conf::use_universe(conf::alph_universe);
		testBasic();
		testBuild();
		testCount();
		testLocate();
		testTopKQ();
		testTextfile();
		build50MBTree();
	}

	void build50MBTree(){
		setContext(__func__);
		string filename = "/Users/jhonc/Workspace/algo/datasets/english_50MB_out.txt";

//		string *line;
//		char *l = readFile(filename);

		string *line = new string();
		readFile2(filename, line);

//		cout << (*line).substr(0,500) << endl;
//		string *s2 = line;
//		cout << s2 << "-" << line  << endl;

		string text = "asdj lajsdlfjalsdj a ljasdk jiwem la ijao jlakjod ja 12 12 2  2 2";
		conf::use_universe(conf::text_universe);

		SuffixTree *t = new SuffixTree();
//		string chunk = line->substr(0, pow(2,15));
		t->buildRange(line, 0, pow(2,17));
//		t->printTree();
	}

	/**
	 * read first line of a inputfile
	 * expected single line text
	 */
	void readFile2(string filename, string *line){
		ifstream file;
//		string line;
		file.open(filename.c_str(), ios::in);
		// reading header [remove]
		getline(file, *line);
		file.close();

//		return cstr;
	}

	/**
	 * read first line of a inputfile
	 * expected single line text
	 */
	char* readFile(string filename){
		ifstream file;
		string line;
		file.open(filename.c_str(), ios::in);
		// reading header [remove]
		getline(file, line);
		// cout << line << endl;
		file.close();

		char *cstr = new char[line.length() + 1];
		strcpy(cstr, line.c_str());

		return cstr;
	}

	void testTextfile() {
		setContext(__func__);
		string text = "asdj lajsdlfjalsdj a ljasdk jiwem la ijao jlakjod ja 12 12 2  2 2";
		conf::use_universe(conf::text_universe);

		SuffixTree *t = new SuffixTree();
		t->build(&text);
		t->printTree();
	}

	void testTopKQ() {
		setContext(__func__);

		string text = "abracadabraabracadabra";
		SuffixTree *t = new SuffixTree();
		t->build(&text);
		t->printTree();

		vector<string> res;

//		char *s = "abracadabraabracadabra";
		char *s = "a";
//		vector<string> res = t->topkq(10, strlen(s));
		vector<pair <string, int> > p;
		t->topkqTest(100, 1, &p);
		cout << p.size() << endl;
		for (int i=0;  i< p.size(); i++) {
			cout << '<' << p[i].first << ',' << p[i].second << '>' << "-";
		}
		cout << endl;

		// test 1 character long,
		//expected the ∑ alphabeth size
		res = t->topkq(100, 1);
		assertTrue(res.size() == 5);
		// Character 'a' is the most repeated
		assertTrue(res[0] == "a");
		// Character 'c' and 'd' are the least one
		// d is the last lexicographically
		assertTrue(res[res.size()-1] == "d");
		assertTrue(res[res.size()-2] == "c");

		// test n = |text|
		// expected 1, with one occurrence
		res = t->topkq(100, text.length());
		assertTrue(res.size() == 1);
		assertTrue(res[0] == text);

		res = t->topkq(100, 100);
		assertTrue(res.size() == 0);

		// for most visual answers use method SuffixTree::topkqTest method
	}

	void testLocate() {
		setContext(__func__);
		string text = "abracadabra";

		SuffixTree *t = new SuffixTree();
		t->build(&text);
		t->printTree();

		// individual test
		int myints[] = {0,3,5,7,10};
		std::vector<int> x (myints, myints + sizeof(myints) / sizeof(int) );
		string str = "a";
		vector <int>res =  t->locate(&str);
		assertTrue(res == x);

		int myints2[] = {1,8};
		std::vector<int> x2 (myints2, myints2 + sizeof(myints2) / sizeof(int) );
		str = "br";
		res =  t->locate(&str);
		assertTrue(res == x2);


		int myints3[] = {};
		std::vector<int> x3 (myints3, myints3 + sizeof(myints3) / sizeof(int) );
		str = "z";
		res =  t->locate(&str);
		assertTrue(res == x3);

		int myints4[] = {0};
		std::vector<int> x4 (myints4, myints4 + sizeof(myints4) / sizeof(int) );
		str = "abracadabra";
		res =  t->locate(&str);
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

		string str = "1,2,3,4";
//		int *ii ==s;
//		int* pend = strlen(ss);
//		string s = std::remove(str.begin(), str.end(), 'a');
		str.erase(std::remove(str.begin(), str.end(), ','), str.end());
//		cout << "daldsf " << str << endl;
//		assertTrue("1234" == s);
	}

	void testBuild() {
		setContext(__func__);

		// alph
		string alph = getAlphabeth();
		assertTrue(alph.length() == 26);
		SuffixTree *t = new SuffixTree();
		t->build(&alph);
		t->printTree();

		// dna
		string dna100 = getSequence100();
		t = new SuffixTree();
		t->build(&dna100);
//		t->printTree();
	}

	void testCount() {
		setContext(__func__);
		string text = "abracadabra";

		SuffixTree *t = new SuffixTree();
		t->build(&text);
		t->printTree();
		string str = "a";
		assertTrue(t->count(&str) == 5);
		str= "r";
		assertTrue(t->count(&str) == 2);
		str= "ca";
		assertTrue(t->count(&str) == 1);
		str= "bra";
		assertTrue(t->count(&str) == 2);
		str= "ab";
		assertTrue(t->count(&str) == 2);
		str= "abracadabra";
		assertTrue(t->count(&str) == 1);
		str= "abracadabras";
		assertTrue(t->count(&str) == 0);
		str= "abracadabre";
		assertTrue(t->count(&str) == 0);

	}

	char* getSequence100() {
		return "acaaaggtcaattatagactcttatctgcgcagtatcattctgccctcaaatagaaagagacgtaataccgtccgcgtcataggggctgtcgtctcgacg";
	}

	char* getAlphabeth() {
		return "abcdefghijklmnopqrstuvwxyz";
	}

};
