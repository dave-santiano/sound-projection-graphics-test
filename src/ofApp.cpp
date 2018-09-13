#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    isAboveThreshold = false;

    //sound stuff
    int bufferSize = 256;
    ofSoundStreamSettings settings;
    left.assign(bufferSize, 0.0f);
    right.assign(bufferSize, 0.0f);
    settings.setApi(ofSoundDevice::Api::MS_DS);
    settings.setInListener(this);
    settings.sampleRate = 48000;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    smoothedVolume = 0.0f;

    soundPlayer.load("star_theme.mp3");
    soundPlayer.setLoop(true);
    soundPlayer.play();
    soundPlayer.setPaused(true);

    //graphics stuff
    img.loadImage("afgGirl.jpg");
    img.resize(133.33, 200);
    imgPixels = img.getPixels();
    ofBackground(200, 50, 50);
}

//--------------------------------------------------------------
void ofApp::update() {



}

//--------------------------------------------------------------
void ofApp::draw() {

    if (smoothedVolume > 1.0) {
        ofBackground(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
        if (isAboveThreshold == false) {
            soundPlayer.setPaused(false);
            isAboveThreshold = true;
        }
    }
    else if (smoothedVolume < 1.0 && isAboveThreshold == true) {
        soundPlayer.setPaused(true);
        isAboveThreshold = false;
    }

    width = img.getWidth();
    height = img.getHeight();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor colorAtXY = img.getColor(x, y);
            if (colorAtXY.getBrightness() > 80) {
                int newX = (x / width) * 533.33;
                int newY = (y / height) * 800;
                ofSetColor(smoothedVolume * 255, 50, 50);
                ofDrawRectangle(newX, newY, smoothedVolume, smoothedVolume);

            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}


//Audio in function
void ofApp::audioIn(ofSoundBuffer& input) {
    float measuredVolume = 0.0f;
    for (size_t i = 0; i < input.getNumFrames(); i++) {
        left[i] = input[i * 2];
        right[i] = input[i * 2 + 1];

        measuredVolume += left[i] * left[i];
        measuredVolume += right[i] * right[i];
    }

    measuredVolume = sqrt(measuredVolume);

    smoothedVolume *= 0.93;
    smoothedVolume += 0.07 * measuredVolume;

}