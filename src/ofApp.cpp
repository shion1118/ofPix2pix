#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetColor(255);
    ofBackground(0);
    ofSetVerticalSync(true);
    
    p2p.setup("graph_l2s.pb", "test_img.png", input_range, output_range);
    palette.setup("palette.txt");
    fbo.allocate(p2p.INPUT_SIZE, p2p.INPUT_SIZE, GL_RGB);
    img_input.allocate(p2p.INPUT_SIZE, p2p.INPUT_SIZE, OF_IMAGE_COLOR);
    img_output.allocate(p2p.OUTPUT_SIZE, p2p.OUTPUT_SIZE, OF_IMAGE_COLOR);
    
    fbo.begin();
    p2p.get_test_img().draw(0, 0, fbo.getWidth(), fbo.getHeight());
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.readToPixels(img_input.getPixels());
    
    // draw input/output image
    drawImage(img_input);
    drawImage(img_output, img_input.getWidth(), 0);
    
    // draw color palette
    palette.draw(0, 300);
    
    // draw message
    drawMessage(550, 20);
}

void ofApp::drawImage(ofImage img, int x, int y) {
    ofSetColor(255);
    ofFill();
    img.draw(x, y);
    
    // Outline
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(1);
    ofDrawRectangle(x, y, img.getWidth(), img.getHeight());
}

void ofApp::drawMessage(int x, int y) {
    stringstream str;
    str << ofGetFrameRate() << endl;
    str << endl;
    str << "SPACE : run pix2pix " << endl;
    str << "b/n   : change draw color " << endl;
    str << endl;
    
    ofSetColor(255);
    ofDrawBitmapString(str.str(), x, y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'b':
            palette.previous_palette();
            break;
        case 'n':
            palette.next_palette();
            break;
        case ' ':
            p2p.run(img_input, img_output);
            break;
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
    fbo.begin();
    ofSetColor(palette.get_current_color());
    ofFill();
    ofDrawCircle(x, y, 8.f);
    ofSetLineWidth(16.f);
    ofDrawLine(x, y, ofGetPreviousMouseX(), ofGetPreviousMouseY());
    fbo.end();
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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
