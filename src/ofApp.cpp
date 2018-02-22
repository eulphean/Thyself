#include "ofApp.h"


void ofApp::setup()
{
    ofBackground(0);

    int height = ofGetHeight();
    int width = ofGetWidth();
    grabber.setup(width, height);
    
    // Setup box 2d.
    box2d.init();
    box2d.setGravity(0, 10);
    //box2d.createBounds(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    box2d.createGround();
    box2d.setFPS(60);
  
    circlesUpdated = false;
}

void ofApp::update()
{
    grabber.update();
    box2d.update();

    if (grabber.isFrameNew())
    {
        // Do something if and only if the frame is new and unique.
        // Copy camera pixels to our pixels.
        pixels = grabber.getPixels();

        // Upload pixels to a texture on the graphics card so we can draw it.
        texture.loadData(pixels);
      
        // Clear circles and create new circles till size is increasing.
        if (circleSize <= maxCircleSize) {
          // Empty circles array.
          circles.clear();
          
          // Create Box 2D objects.
          for (int y = 0; y < pixels.getHeight(); y = y + circleSize) {
            for (int x = 0; x < pixels.getWidth(); x = x + circleSize) {
              auto circle = std::make_shared<ofxBox2dCircle>();
              circle -> setPhysics(0, 0, 0);
              circle -> setup(box2d.getWorld(), x, y, circleSize/2);
              circles.push_back(circle);
            }
          }
        }
      
        // Size has reached the threshold. Clear the circles and add physics to
        // these circles now.
        if (circleSize > maxCircleSize && !circlesUpdated) {
          // Clear the circles
          circles.clear();
          
          // Create new circles with new physics properties.
          for (int y = 0; y < pixels.getHeight(); y = y + circleSize) {
            for (int x = 0; x < pixels.getWidth(); x = x + circleSize) {
              auto circle = std::make_shared<ofxBox2dCircle>();
              circle -> setPhysics(0.5, 0.2, 0.1);
              circle -> setup(box2d.getWorld(), x, y, circleSize/2);
              circles.push_back(circle);
            }
          }
          
          circlesUpdated = true;
        }
      
        // Clear any circle that is out of bound.
        clearCirclesOutOfBound();
    }
}

void ofApp::draw()
{
  ofPushMatrix();
    ofTranslate(pixels.getWidth(), 0);
    ofScale(-1, 1, 1);
  
    // Draw regular circles.
    for (auto circle: circles) {
        int x = (circle -> getPosition()).x;
        int y = (circle -> getPosition()).y;
        ofSetColor(pixels.getColor(x, y));
        circle -> draw();
    }
  ofPopMatrix();
}

void ofApp::keyPressed(int key) {
    if (key == OF_KEY_UP) {
      circleSize++;
    } else if (key == OF_KEY_DOWN) {
      circleSize--;
    }
}

void ofApp::clearCirclesOutOfBound() {
    // Remove any circles that fall out of the screen
    ofRemove(circles, [&](std::shared_ptr<ofxBox2dCircle> circle){
        auto rect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
        return !rect.inside(circle -> getPosition());
    });
}










