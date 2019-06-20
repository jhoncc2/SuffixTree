#include <utility>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#ifndef GESTORDB_2_2018_UTILS_H
#define GESTORDB_2_2018_UTILS_H
#endif

using namespace std;

//src
#include "structure/conf.h"
#include "structure/TrieAbstract.h"
#include "structure/PatriciaTrie.h"
#include "structure/SuffixTree.h"

// import tests
#include "test/TestException.h"
#include "test/TestSuite.h"
#include "test/TestBasic.h"
#include "test/SuffixTreeTest.h"
#include "test/PatriciaTrieTest.h"


// Experiments
#include "experiment/BaseExperiment.h"
#include "experiment/ExperimentEnglish.h"
#include "experiment/ExperimentDNA.h"

// importing utils for pre-computing
#include "utils/utils.h"
#include "utils/TextPreprocessing.h"
#include "utils/command.h"

// resources
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	// try
    // {
		struct rusage r_usage;

        int r = console::handlecommands(argc, argv);

        getrusage(RUSAGE_SELF,&r_usage);
		printf("Memory usage = %ld\n",r_usage.ru_maxrss);
		return r;

    // }
    // catch(const std::exception&)  // Consider using a custom exception type for intentional
    // {                             // throws. A good idea might be a `return_exception`.
    //     cerr << endl << "error running the code" << endl;
    //     return EXIT_FAILURE;
    // }
}
