#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // GUI 설정
    gui.setup("Saliency Parameters");
    gui.add(gaussianSlider.setup("Gaussian Size", 9, 3, 31));
    gui.add(kernelSlider.setup("Kernel Size", 3, 3, 15));
    
    // 기본 이미지 로드 (예제 이미지 포함 필요)
    filePath = "images/sample.jpg";
    inputImage.load(filePath);
    
    if (!inputImage.isAllocated()) {
        ofLogError() << "Failed to load sample image. Using default image...";
        // 이미지 로드 실패시 기본 이미지 생성
        inputImage.allocate(512, 512, OF_IMAGE_COLOR);
        inputImage.setColor(ofColor::white);
        inputImage.update();
    }
    
    // 출력 이미지를 입력 이미지와 같은 크기로 할당
    outputImage.allocate(inputImage.getWidth(), inputImage.getHeight(), OF_IMAGE_COLOR);
    
    // 초기 현저성 맵 계산
    saliency.computeSaliencyMap(inputImage, outputImage);
    
    needUpdate = false;
}

//--------------------------------------------------------------
void ofApp::update() {
    // 슬라이더 값이 변경되었거나 업데이트가 필요한 경우
    if (gaussianSlider.getValue() != saliency.getGaussianSize() || 
        kernelSlider.getValue() != saliency.getKernelSize() || 
        needUpdate) {
        
        // 애드온 매개변수 업데이트
        saliency.setGaussianSize(gaussianSlider);
        saliency.setKernelSize(kernelSlider);
        
        // 현저성 맵 다시 계산
        saliency.computeSaliencyMap(inputImage, outputImage);
        
        needUpdate = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255, 255, 255);
    
    // 원본 이미지 그리기
    inputImage.draw(0, 0, 512, 512);
    
    // 현저성 맵 그리기
    outputImage.draw(512, 0, 512, 512);
    
    // 파일 이름 표시
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 0, 200, 20);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("File: " + ofFilePath::getFileName(filePath), 10, 15);
    
    // GUI 그리기
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 's') {
        // 결과 이미지 저장
        string filename = "saliency_" + ofGetTimestampString() + ".png";
        outputImage.save(filename);
        ofLogNotice() << "Image saved: " << filename;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    if (dragInfo.files.size() > 0) {
        // 드래그된 파일 중 첫 번째 파일 로드
        filePath = dragInfo.files[0];
        inputImage.load(filePath);
        
        if (inputImage.isAllocated()) {
            // 윈도우 타이틀 업데이트
            ofSetWindowTitle(ofFilePath::getFileName(filePath));
            
            // 현저성 맵 계산 플래그 설정
            needUpdate = true;
        }
    }
}
