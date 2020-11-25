#include "Driver.h"

int main(int argc, char *argv[]){
    if (argc != 3){
        cerr << "Usage: findpath vertex_data edge_data" << endl;
        exit(1);
    } 
    Driver graphing;
    graphing.run(argv);
    return 0;
}