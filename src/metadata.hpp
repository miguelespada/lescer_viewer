#include "ofxJSON.h"
class Metadata{
    
public:
    string name;
    string exercice;
    string variation;
    
    Metadata(){
        name = "";
        exercice = "";
        variation = "";
    }
    
    void update(ofxJSONElement data){
        name = data["patient"].asString();
        exercice = data["exercice"].asString();
    }
    
    bool hasData(){
        return name != "";
    }
};