#include "../Robot.h"
#include <vector> 
using namespace std;

class Behavior {
private:
    vector<Behavior *> _nextBehaviors;

protected:
    Robot *_robot;

public:
    virtual bool startCond() = 0;
    virtual bool stopCond() = 0;
    virtual void action() = 0;

    Behavior *addNext(Behavior *beh);
    Behavior *selectNext();

    Behavior(Robot *robot);
    virtual ~Behavior();
};
