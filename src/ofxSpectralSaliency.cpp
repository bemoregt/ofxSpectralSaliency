#include "ofxSpectralSaliency.h"

using namespace ofxCv;
using namespace cv;

ofxSpectralSaliency::ofxSpectralSaliency() {
    // 기본값 설정
    gaussianSize = 9;
    kernelSize = 3;
}

ofxSpectralSaliency::~ofxSpectralSaliency() {
    // 소멸자
}

void ofxSpectralSaliency::computeSaliencyMap(const ofImage &input, ofImage &output) {
    cv::Mat img = toCv(input);
    
    // 이미지가 컬러인 경우 그레이스케일로 변환
    if (img.channels() > 1) {
        cv::cvtColor(img, img, CV_BGR2GRAY);
    }
    
    // 리사이즈 (이미지 너비가 256보다 크면)
    float ratio = 1.0;
    if (img.cols > 256) {
        ratio = 256.0 / img.cols;
        cv::resize(img, img, cv::Size(img.cols*ratio, img.rows*ratio));
    }
    
    // 푸리에 변환 준비
    cv::Mat planes[] = {cv::Mat_<float>(img), cv::Mat::zeros(img.size(), CV_32F)};
    cv::Mat complexImg;
    cv::merge(planes, 2, complexImg);
    cv::dft(complexImg, complexImg);
    
    cv::split(complexImg, planes);
    
    cv::Mat mag, logmag, smooth, spectralResidual;
    cv::Mat mag1;
    
    // 스펙트럼 진폭 계산 및 로그 변환
    cv::magnitude(planes[0], planes[1], mag);
    cv::log(mag, logmag);
    
    // 박스 필터 적용하여 스무딩
    cv::boxFilter(logmag, smooth, -1, cv::Size(kernelSize, kernelSize));
    
    // 스펙트럼 잔차 계산
    cv::subtract(logmag, smooth, spectralResidual);
    cv::exp(spectralResidual, spectralResidual);
    
    // 스펙트럼 잔차 적용
    planes[0] = planes[0].mul(spectralResidual) / mag;
    planes[1] = planes[1].mul(spectralResidual) / mag;
    
    // 역 푸리에 변환
    cv::merge(planes, 2, complexImg);
    cv::dft(complexImg, complexImg, cv::DFT_INVERSE | cv::DFT_SCALE);
    cv::split(complexImg, planes);
    cv::magnitude(planes[0], planes[1], mag);
    
    // 제곱 및 가우시안 블러 적용
    cv::multiply(mag, mag, mag);
    cv::GaussianBlur(mag, mag, cv::Size(gaussianSize, gaussianSize), 2.5, 2.5);
    
    // 정규화하여 출력 이미지 생성
    cv::normalize(mag, mag1, 255, 0, cv::NORM_MINMAX, CV_8U);
    toOf(mag1, output);
    output.update();
}

void ofxSpectralSaliency::setGaussianSize(int size) {
    // 가우시안 블러 크기는 항상 홀수여야 함
    if (size % 2 == 0) {
        size += 1;
    }
    gaussianSize = size;
}

void ofxSpectralSaliency::setKernelSize(int size) {
    // 커널 크기는 항상 홀수여야 함
    if (size % 2 == 0) {
        size += 1;
    }
    kernelSize = size;
}

int ofxSpectralSaliency::getGaussianSize() const {
    return gaussianSize;
}

int ofxSpectralSaliency::getKernelSize() const {
    return kernelSize;
}
