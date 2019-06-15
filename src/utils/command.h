#include <utility>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

namespace console{

  int handlecommands(int argc, char *argv[]) {
      // contants
      // std::string datafolder = BaseController::dataFolder();
      // test
      if (exist(argv, argv + argc, "--greet")) {
        std::string name = "";
        if (exist(argv, argv + argc, "--name")){
          name = console::get(argv, argv + argc, "--name");
        }
        std::cout << "Hello " << name;
      } else if (exist(argv, argv + argc, "--testing")) {
        std::cout << "----- running tests -----" << endl;
        try{
          (new TestSuite())->run();
          (new PatriciaTreeTest())->run();

          std::cout << "----- end test section -----" << endl;
        } catch(TestException e) {
          std::cout << "exception caught" << endl;
          std::cout << e.what() << endl;
        }

      } else if (exist(argv, argv + argc, "--exp-random")) {
//        (new RandomExperiment())->run();
      }
      return 0;
  }
}
