#include "tableModel.h"
#include "tableView.h"
#include "pile.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    bool debug = false;
    string cmd;
    if (argc == 2)
    {
        cmd = argv[1];
        cout << cmd << endl;
        if (cmd == "-testing")
        {
            debug = true;
        }
    }
    TableView game;
    game.setDebug(debug);
    game.beginGame();
}
