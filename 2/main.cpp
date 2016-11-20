#include <tbb/flow_graph.h>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
using namespace tbb::flow;

void print_usage(){
    cout << "-b num -I num [-f fileName]s" << endl;
    exit (1);
}

int main(int argc, char *argv[]) {
    if (argc != 5 && argc != 7){
        print_usage();
    }

    int brightness = 0;
    int max_parallel = 0;
    string path = "";

    if (argv[1] == string("-b")){
        brightness = stoi(argv[2]);
    } else {
        print_usage();
    }

    if (argv[3] == string("-I")){
        max_parallel = stoi(argv[4]);
    } else {
        print_usage();
    }

    if (argc > 5 && argv[5] == string("-f")){
        path = argv[6];
    } else {
        print_usage();
    }

    graph g;
    continue_node< continue_msg> hello( g,
      [&path]( const continue_msg &) {
          cout << path;
      }
    );
    continue_node< continue_msg> world( g,
      []( const continue_msg &) {
          cout << " World\n";
      }
    );
    make_edge(hello, world);
    hello.try_put(continue_msg());
    g.wait_for_all();
    return 0;
}
