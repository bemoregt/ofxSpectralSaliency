#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofxSpectralSaliency {
public:
    ofxSpectralSaliency();
    ~ofxSpectralSaliency();
    
    // 현저성 맵 계산
    void computeSaliencyMap(const ofImage &input, ofImage &output);
    
    // 매개변수 설정
    void setGaussianSize(int size);
    void setKernelSize(int size);
    
    // 매개변수 획득
    int getGaussianSize() const;
    int getKernelSize() const;
    
private:
    int gaussianSize;
    int kernelSize;
};
