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
		conf::use_universe(conf::text_universe);
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
		int i = 0;
		while(getline(file, line)) {
			if (i > 500)
				return ;
			i++;

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
		int idx;
		for(int i=0; i< str.size(); i ++){
			tc = str[i];
			if(tc > 64  && tc<91) //lower_case
				tc = tc + 32;

			if(str[i] == ' ' && i != str.size()-1 && str[i] == str[i+1]) {
				continue;
			}

			idx = (int)tc;
			if (
					idx>=0 && idx < conf::universe_descriptor_size
					&& conf::universe_descriptor[idx] != -1 )
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
