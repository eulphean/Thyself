#pragma once


#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
  
    // Helper methods.
    void clearCirclesOutOfBound();
  
    // Grabber stuff.
    ofVideoGrabber grabber;
    ofPixels pixels;
    ofTexture texture;
  
    // Physics engine.
    ofxBox2d box2d;
    vector<std::shared_ptr<ofxBox2dCircle>> circles;
  
    // Incrementer and circleSize.
    int circleSize = 6;
    const int maxCircleSize = 15;
  
    // Checks to keep track of updated box2d object.
    bool circlesUpdated;
};
