#ifndef _TABLEVIEW_H_
#define _TABLEVIEW_H_
#include <vector>
#include <string>
#include "observer.h"
#include "tableModel.h"

class TableView : public Observer
{
    TableModel table;
    bool debug;

public:
    TableView();
    ~TableView() = default;
    void init(unsigned int numPlayers);
    void beginGame(); // begins the game
    virtual void update(bool won) override;
    void receiveInput(bool swapped = false);
    void setDebug(bool debug);
};

#endif
