#ifndef __State__
#define __State__

#include "ofMain.h"

class App;

class BaseState
{
    
protected:
    App *app;
    float timer;
    
public:
    BaseState(App *a);
    ~BaseState();
    
    bool isDone(int duration);
    void initialize();
    
    virtual void next()=0;
    virtual string toString()=0;
    virtual void draw()=0;
    virtual void update()=0;
    virtual void keypressed(int key){}
    virtual void click(int x, int y);
    virtual void changeMode(){};
    
};


#endif