using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>


class TextPreprocessing {

public:
	void convert() {
		string input = "/Users/jhonc/Workspace/algo/datasets/english_eg.rtf";
		string output ="/Users/jhonc/Workspace/algo/datasets/english_eg_out.txt";

		loadAndRemoveChars(input, output);
//		text = removeChars(text);
//		store(text, output);
	}

  
	void store(char *text, string filename) {
		fstream output;
		output.open(filename, ios::out);
		output << text;
		output.close();
	}

	void loadAndRemoveChars(string filename, string outfilename) {
		string line;
		// open
		ifstream file;
		file.open(filename.c_str(), ios::in);

		// output
		fstream output;
		output.open(outfilename, ios::out);

		// reading header [remove]
		getline(file, line);
		getline(file, line);
		getline(file, line);
		getline(file, line);
		getline(file, line);
		getline(file, line);
		getline(file, line);
		getline(file, line);
		getline(file, line);
		getline(file, line);

		// reading content
		while(getline(file, line)) {
			if (line.empty())
				continue;
//			cout << line << endl;
			line = removeChars2(line);
//			cout << line << endl;
			output << line;
		}

		file.close();
		output.close();

		return;
	}

	string removeChars2(string str) {
//		int *whiteList= &conf::ascii table;
		string res = "";
		char tc;
		for(int i=0; i< str.size(); i ++){
			tc = str[i];
			if(tc > 64  && tc<91) //
				tc = tc + 32;

			if(str[i] == ' ' && i != str.size()-1 && str[i] == str[i+1]) {
				continue;
			}

			if (conf::universe[(int)tc] != -1)
				res += tc;
		}
		return res;
	}

	string removeChars(string *text) {
		string str = *text;
		string res ="";
		string omitList = ".,;:[]{}!@#$%^&*()\"\\'?<>-=_+|/`~";
		bool omit = false;
		for(int i=0; i< str.size(); i ++){
			char tc = str[i];
			if(str[i] == ' ' && i != str.size()-1 && str[i] == str[i+1]) {
				continue;
			}

			for(char c: omitList) {
				if (tc == c){
					omit = true;
					break;
				}
//				str.erase(remove(str.begin(), str.end(), c), str.end());
			}
			if(!omit)
				res += tc;

			omit = false;
		}
//		for(char c: omitList) {
//			str.erase(remove(str.begin(), str.end(), c), str.end());
//		}

		return res;
	}

};
