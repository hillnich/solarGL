#include "ofApp.h"
#define PI 3.141592653589793

//--------------------------------------------------------------
void ofApp::setup(){

    // Set up basic parameters and options
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);

    backward = false;
    forward = true;
    pause = false;
    rotate = false;
    perlin = false;

    center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

    ofEnableDepthTest();
    ofDisableArbTex();

    // Load my shaders and font
    solarShader.load("solar.vs","solar.fs");
    meShader.load("me.vs", "me.fs");
    font.loadFont("verdana.ttf", 12, false);
	
    // Create the Sun
    scale = 10.0;
    oscale = scale;
    sun.rot = 0.0;
    sun.rot_rate = 0.074;
    sun.radius = 90.0;
    sun.tex.loadImage("sun.jpg");
    sun.sphere.set(sun.radius, 100);

    // Create the earth
    earth.rot = 0.0;
    earth.rot_rate = 2.0 * .5;
    earth.orbit = 0.0;
    earth.orbit_rate = 0.005 * 5;
    earth.radius = 50;
    earth.tex.loadImage("earth.jpg");
    earth.sphere.set(earth.radius, 100);

    // Create the moon
    moon.rot = 90.0;
    moon.rot_rate = 0.07;
    moon.orbit = 0.0;
    moon.orbit_rate = 0.07;
    moon.radius = 25;
    moon.tex.loadImage("moon.jpg");
    moon.sphere.set(moon.radius, 100);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (!pause) {

	if (sun.rot > 360.) sun.rot = 0.0f;		    
	if (earth.rot > 360.) earth.rot = 0.0f;
	if (moon.rot > 360.) moon.rot = 0.0f;
	if (earth.orbit > 360.) earth.orbit = 0.0f;
	if (moon.orbit > 360.) moon.orbit = 0.0f;
	
	if (forward) {
	   
	    sun.rot += sun.rot_rate * scale;

	    earth.rot += earth.rot_rate * scale;
	    earth.orbit += earth.orbit_rate * scale;
	    
	    moon.rot += moon.rot_rate * scale;
	    moon.orbit += moon.orbit_rate * scale;
	}
	
	if (backward) {
	    
	    sun.rot -= sun.rot_rate * scale;
	    
	    earth.rot -= earth.rot_rate * scale;
	    earth.orbit -= earth.orbit_rate * scale;
	    
	    moon.rot -= moon.rot_rate * scale;
	    moon.orbit -= moon.orbit_rate * scale;
	}
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Add explanative text
    font.drawString("Right arrow - Forward motion/Fast-forward", 10, 20);
    font.drawString("Left arrow  - Backward motion/Rewind", 10, 40);
    font.drawString("Spacebar    - Pause", 10, 60);
    font.drawString("'r'         - Rotate to view North Pole", 10, 80);
    font.drawString("'s'         - Slow down movement", 10, 100);
    font.drawString("'p'         - Toggle solar Perlin noise", 10, 120);		    
    
    // Move everything to the center and rotate
    // my view if need be
    ofPushMatrix();
    ofTranslate(center);
    if (rotate) {
	ofRotate(90.0, -1.0, 0.0, 0.0);
    }
    
    // Turn on my solar shader
    sun.tex.getTextureReference().bind();
    solarShader.begin();
    solarShader.setUniform1f("time", ofGetFrameNum() * .01);
    solarShader.setUniform1i("perlin", perlin);
    
    // Rotate the Sun and draw it
    ofPushMatrix();
    ofRotate(sun.rot, 0.0, 1.0, 0.0);
    sun.sphere.draw();
    ofPopMatrix();

    // With sun drawn, turn on its light and off its shader
    solarShader.end();
    sun.tex.getTextureReference().unbind();

    // Now turn on my moon/earth shader and pass it
    // the light position
    meShader.begin();
    lightPos[0] = -cos(earth.orbit * PI/180.);
    lightPos[1] = 0.0f;
    lightPos[2] = sin(earth.orbit * PI/180.);
    meShader.setUniform3fv("lightPos", lightPos);
    
    // Rotate and translate my earth
    ofPushMatrix();
    ofRotate(earth.orbit, 0.0, 1.0, 0.0);
    ofTranslate(325, 0, 0);

    // Rotate and translate my moon
    ofPushMatrix();
    ofRotate(moon.orbit-earth.orbit, 0.0, 1.0, 0.0);
    ofTranslate(90, 0, 0);
    ofRotate(-moon.orbit, 0.0, 1.0, 0.0);
    ofRotate(moon.rot, 0.09, 0.99, 0.0);
    moon.tex.getTextureReference().bind();
    moon.sphere.draw();
    moon.tex.unbind(); 
    ofPopMatrix();

    // And rotate my earth
    ofPushMatrix();
    ofRotate(-earth.orbit, 0.0, 1.0, 0.0);
    ofRotate(earth.rot, 0.39, 0.92, 0.0); 
    earth.tex.getTextureReference().bind();
    earth.sphere.draw();
    earth.tex.unbind();
    ofPopMatrix();
    ofPopMatrix();
    ofPopMatrix();

    // Turn of moon/earth shader
    meShader.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT) {

	if (backward && !pause) {
	    scale *= 2.0;
	}
	else {
	    scale = oscale;
	}

	pause = false;
	backward = true;
	forward = false;

    }
    if (key == OF_KEY_RIGHT) {

	if (forward && !pause) {
	    scale *= 2.0;
	}

	
	if (!forward) {
	    scale = oscale;
	}

	pause = false;
	backward = false;
	forward = true;
    }

    if (key == ' ') {
	pause = !pause;
    }

    if (key == 's') {
	if (!pause) {
	    scale *= .5;
	}
    }

    if (key == 'r') {
	rotate = !rotate;
    }

    if (key == 'p') {
	perlin = !perlin;
    }

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
