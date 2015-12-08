#include "assets.h"

Assets::Assets():BaseAssets(){}

Assets* Assets::instance = 0;

Assets* Assets::getInstance(){
    if (instance == 0){
        instance = new Assets();
        instance->loadAssets();
    }
    return instance;
};