#ifndef STATE_H_
#define STATE_H_

class State{
public:
    State(){}
    virtual ~State() = 0;
    virtual int update() = 0;
    virtual void draw() = 0;
};

#endif