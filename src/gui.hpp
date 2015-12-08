#include "ofxGui.h"
#include "app.h"
#include "session.h"

class Gui
{
    ofxPanel gui;
    App *app;
    OscAdapter *osc;
    bool bVisible;
    
    
    ofxFloatSlider timeCount;
    ofxIntSlider nivel;
    
    
    ofxIntSlider playback_speed;
    ofxIntSlider trace;
    
    ofxButton startTimeGame;
    ofxButton startFruitGame;
    ofxButton calibrate;
    ofxButton clear;
    
    ofxLabel name;
    ofxLabel exercice;
    ofxLabel timestamp;
    ofxLabel counter;
    ofxLabel index;
    ofxLabel current;
    
    
public:
    
    Gui(App *a, OscAdapter *o){
        app = a;
        osc = o;
        gui.setup();
        init();
        
        bVisible = true;
        load();
    }
    
    void draw(){
        name = app->metadata.name;
        exercice = app->metadata.exercice;
        string stamp =  app->session->timestamp;
        timestamp = stamp.substr(0, stamp.size()-7);
        counter = ofToString(app->session->getSize());
        index  = ofToString(app->session->index);
        current.setup( "actual", ofToString(app->currentTimeOrFruits) );
        
        app->heatmap.L = trace;
        app->session->speed = playback_speed;
        if(bVisible)
            gui.draw();
    }
    
    void load(){
        string path = ofToDataPath("gui.xml");
        ofLogNotice() << "Loading gui from: " << path;
        gui.loadFromFile(path);
    }
    
    void save(){
        string path = ofToDataPath("gui.xml");
        ofLogNotice() << "Saving gui to: " << path;
        gui.saveToFile(path);
    }
    
    void toggleVisibility(){
        bVisible = !bVisible;
    }
    
    
    //--------------------------------------------------------------
    void init(){
        
        gui.add(name.setup("Nombre", name));
        gui.add(exercice.setup("Ejercicio", exercice));
        
        gui.add(timestamp.setup("Fecha", timestamp));
        gui.add(counter.setup("Contador", counter));
        
        gui.add(index.setup("Posicion", index));
        
        gui.add(playback_speed.setup( "speed",  2, 1, 20));
        gui.add(trace.setup( "trace",  400, 100, 5000 ));
        
        gui.add(calibrate.setup("Calibrate"));
        gui.add(clear.setup("Clear"));
        
        gui.add(nivel.setup( "nivel", 1, 1, 4 ));
        gui.add(timeCount.setup( "numero", 50, 0, 200 ));
        gui.add(current.setup( "actual", ofToString(app->currentTimeOrFruits) ));
        
    
        
        startTimeGame.addListener(this, &Gui::startTimeGamePressed);
        startFruitGame.addListener(this,&Gui::startFruitGamePressed);
        calibrate.addListener(this,&Gui::calibratedPressed);
        clear.addListener(this,&Gui::clearPressed);
        
        gui.add(startTimeGame.setup("Time game"));
        gui.add(startFruitGame.setup("Fruit game"));
        
    }
    
    void calibratedPressed(){
        app->setRotationRef();
    }
    
    void clearPressed(){
        app->clear();
    }
    
    
    void startTimeGamePressed(){
        osc->sendAction("/startTimeGame", nivel, timeCount);
        app->clear();
    }
    
    void startFruitGamePressed(){
        osc->sendAction("/startCountGame", nivel, timeCount);
        app->clear();
    }
};

