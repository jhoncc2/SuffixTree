using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>



class ExperimentDNA : public BaseExperiment {

public:

	void run(string inputFile, string outFolder) {
		// configuration of sencond memory

		cout << "running experiment dna " <<endl;
		conf::use_universe(conf::dna_universe);
		char *text = readFile(inputFile);
		cout << inputFile << text << endl;

		this->runMultiple(text, outFolder);
		cout << "finished experiment dna " <<endl;
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
		cout << line << endl;
		file.close();

		char *cstr = new char[line.length() + 1];
		strcpy(cstr, line.c_str());

		return cstr;
	}

	void runMultiple(char *text, string outFolder) {
		fstream output;
		string filename = outFolder + "englishCountLocate.txt";
		output.open(filename, ios::out);

		fstream outputTop;
		string filename2 = outFolder + "englishTopkq.txt";
		outputTop.open(filename2, ios::out);

		SuffixTree *t;
		int ini = 10;
		int end = 23;

		for (int i=ini; i<=end; i ++) {
			t = new SuffixTree();

			int size = pow(2,i);
			if (size >= strlen(text) ){
				break;
			}

			// build suffix tree
			cout << "processing n=" << size << endl;
//			output << "processing n=" << size << endl;
//			t->buildRange(text, 0, size);
			cout << "finished building tree" << endl;

			// run experiments
			output << "n \t Count \t Locate " << endl;
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

	void runCountAndLocate(SuffixTree *t, char* text, int n, fstream &out){
		// for locate and riun
		vector<char*> rwords = findRandom(text, n/10);
		out << n << "\t" ;
		runCount(t, rwords, out);
		runLocate(t, rwords, out);
		out << endl;
	}

	void runCount(SuffixTree *t, vector<char*> rwords, fstream &out){
		startTimer();
		for (int i = 0; i < rwords.size(); i++) {
//			t->count(rwords[i]);
		}
		double lapse = stopTimer();
		out << lapse << "\t" ;
	}

	void runLocate(SuffixTree *t, vector<char*> rwords, fstream &out){
		startTimer();
		for (int i = 0; i < rwords.size(); i++) {
//			t->locate(rwords[i]);
		}
		double lapse = stopTimer();
		out << lapse << "\t";
	}

	vector <char*> findRandom(char *text, int size) {
		vector<char*> res;
		int tlenght = strlen(text);
		int rval, ini, end;
		for (int i = 0; i < size; i++) {
			ini = rand() % tlenght;
			while(text[ini] != ' ')
				ini++;
			ini ++;
			end = ini;

			while(text[end] != ' ')
				end++;

			res.push_back(substringOf(text, ini, end-ini));
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
