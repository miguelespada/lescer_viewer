#include "ofxJSON.h"
class Metadata{
    
public:
    string name;
    string exercice;
    int variation;
    
    Metadata(){
        name = "";
        exercice = "";
        variation = 0;
    }
    
    void update(ofxJSONElement data){
        name = data["patient"].asString();
        exercice = data["exercice"].asString();
    }
    
    bool hasData(){
        return name != "";
    }
};