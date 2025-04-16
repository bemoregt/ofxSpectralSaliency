#pragma once

#include "ofMain.h"
#include "ofxSpectralSaliency.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    ofxSpectralSaliency saliency;  // 현저성 맵 애드온
    
    ofImage inputImage;            // 입력 이미지
    ofImage outputImage;           // 출력 이미지
    
    ofxPanel gui;                  // GUI 패널
    ofxIntSlider gaussianSlider;   // 가우시안 크기 슬라이더
    ofxIntSlider kernelSlider;     // 커널 크기 슬라이더
    
    bool needUpdate;               // 업데이트 필요 여부 플래그
    string filePath;               // 현재 파일 경로
};
