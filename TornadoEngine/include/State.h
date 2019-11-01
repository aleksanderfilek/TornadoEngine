#ifndef STATE_H_
#define STATE_H_

//abstract class for creating states of game
class State{
    State();
    virtual ~State() = 0;
    virtual int update() = 0;
    virtual void draw() = 0;
};

#endif