using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>



class ExperimentEnglish : public BaseExperiment {

public:

	void run(string inputFile, string outFolder) {
		// configuration of sencond memory

		cout << "running experiment enlish " <<endl;
		conf::use_universe(conf::text_universe);
		string line = "";
		readFile(inputFile, &line);
		// cout <<inputFile << text << endl;

		this->runMultiple(&line, outFolder);
		cout << "finished experiment enlish " <<endl;
	}

	/**
		 * read first line of a inputfile
		 * expected single line text
		 */
	void readFile(string filename, string *line){
		ifstream file;
		file.open(filename.c_str(), ios::in);
		// reading header [remove]
		getline(file, *line);
		file.close();

//		return cstr;
	}

	void runMultiple(string *text, string outFolder) {
		fstream output;
		string filename = outFolder + "englishCountLocate.txt";
		output.open(filename, ios::out);
		output << "n \t Count \t Locate " << endl;

		fstream outputTop;
		string filename2 = outFolder + "englishTopkq.txt";
		outputTop.open(filename2, ios::out);

		SuffixTree *t;
		int ini = 10;
		int end = 23;

		for (int i=ini; i<=end; i ++) {
			t = new SuffixTree();

			int size = pow(2,i);
			if (size >= (*text).length() ){
				break;
			}

			// build suffix tree
			cout << "processing n=" << size << " i=" << i << endl;
//			output << "processing n=" << size << endl;
			t->buildRange(text, 0, size);
			cout << "finished building tree" << endl;

			// run experiments
			runCountAndLocate(t, text, size, output);
			runTopkq(t, size, outputTop);
		}
		output.close();
	}

//	void runSingleWith(SuffixTree *t, char *text,  int n, fstream &out){
//		runCountAndLocate(t, text, n, out);
//	}

	void runTopkq(SuffixTree *t, int size, fstream &out){
		int arrk[] = {3,5,10};
		int arrq[] = { 4, 5, 6, 7 };

		vector<int> ks(arrk, arrk + sizeof(arrk) / sizeof(arrk[0]));
		vector<int> qs(arrq, arrq + sizeof(arrq) / sizeof(arrq[0]));

		out << "k\\q-> \t 4 \t 5 \t 6 \t 7" << endl;

		double times = runTopkqInd(t, size, ks, qs, out);

		out << "total: "<< times << endl;
	}

	double runTopkqInd(SuffixTree *t, int size, vector<int> ks, vector<int> qs, fstream &out){
//		out << "number : " << endl;
		double res;

		double sum = 0;
		double lapse;
		for (int i = 0; i < ks.size(); i++) {
			out << ks[i] << "\t";
			for (int j = 0; j < qs.size(); j++) {
				startTimer();
				t->topkq(ks[i], qs[j]);
				lapse = stopTimer();
				sum += lapse;
				out << lapse << "\t" ;
			}
			out << endl;
		}


		return sum;
	}

	void runCountAndLocate(SuffixTree *t, string *text, int n, fstream &out) {
		// for locate and riun
		vector<pair<int,int> > rwords = findRandom(text, n/10);
		cout << "random input selected" << endl;
		out << n << "\t";
		runCount(t, rwords, text, out);
		runLocate(t, rwords, text, out);
		out << endl;
	}

	void runCount(SuffixTree *t, vector<pair<int,int> > rwords, string *text, fstream &out){
		startTimer();
		for (int i = 0; i < rwords.size(); i++) {
			string s = text->substr(rwords[i].first, rwords[i].second);
			t->count(&s);
		}
		double lapse = stopTimer();
		out << lapse << "\t" ;
	}

	void runLocate(SuffixTree *t, vector<pair<int,int> > rwords, string *text, fstream &out){
		startTimer();
		for (int i = 0; i < rwords.size(); i++) {
			string s = text->substr(rwords[i].first, rwords[i].second);
			t->locate(&s);
		}

		double lapse = stopTimer();
		out << lapse << "\t";
	}

	vector <pair<int, int> > findRandom(string *text, int size) {
		vector<pair<int,int> > res;
		int tlenght = (*text).length();
		int rval;

		for (int i = 0; i < size; i++) {
			pair<int, int> p;
			p.first = rand() % (tlenght-30);
			while((*text)[p.first] != ' ')
				p.first++;
			p.first ++;
			p.second = 0;

			while((*text)[p.first + p.second] != ' '
					&& p.second < tlenght
					&& p.second < 30)
				p.second++;

			res.push_back(p);
		}
		return res;
	}

	char *substringOf(char* str, int ini, int end) {
		string s(str);
		string st = "";

		for (int i = ini; i < end; i++) {
			st += str[i];
		}

		char *cstr = new char[st.length() + 1];
		strcpy(cstr, st.c_str());
		return cstr;
	}

};

