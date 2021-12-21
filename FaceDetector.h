//
// Created by dl on 19-7-19.
//

#ifndef FACE_DETECTOR_H
#define FACE_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <string>
#include <stack>
#include "net.h"
#include <chrono>
using namespace std::chrono;

struct Point{
    float _x;
    float _y;
};

struct bbox{
    float x1;
    float y1;
    float x2;
    float y2;
    float s;
    Point point[5];
};

struct box{
    float cx;
    float cy;
    float sx;
    float sy;
};

class Detector
{

public:
    Detector();

    void Init(const std::string &model_param, const std::string &model_bin);

    Detector(const std::string &model_param, const std::string &model_bin);

    inline void Release();

    void nms(std::vector<bbox> &input_boxes, float NMS_THRESH);

    void Detect(cv::Mat& bgr, std::vector<bbox>& boxes);

    void create_anchor(std::vector<box> &anchor, int w, int h);

    void create_anchor_retinaface(std::vector<box> &anchor, int w, int h);

    inline void SetDefaultParams();

    static inline bool cmp(bbox a, bbox b);

    ~Detector();

public:
    float _nms;
    float _threshold;
    float _mean_val[3];
    bool _retinaface;

    ncnn::Net *Net;
};
#endif //
