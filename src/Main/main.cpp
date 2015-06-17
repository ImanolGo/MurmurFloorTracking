#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "MurmurFloorTrackingApp.h"


//========================================================================
int main( ){

    ofAppGlutWindow window;
    ofSetupOpenGL(&window,1280, 1024, OF_WINDOW);
    ofRunApp( new MurmurFloorTrackingApp());

}
