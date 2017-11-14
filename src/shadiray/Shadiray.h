#ifndef SHADIRAY_H_
#define SHADIRAY_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <chrono>
#include <time.h>
#include <stdint.h>
#include <float.h>

#include "Plane.h"
#include "Ray.h"

namespace shad
{
#define BENCHMARK(o_timeElapsed, _expr) \
{\
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();\
            _expr;\
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();\
    std::chrono::microseconds time_span = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);\
    o_timeElapsed = time_span.count();\
}


#define NUM_SAMPLES 1000000
#define BENCHMARK_SAMPLE(o_timeElapsed0, _expr0) \
{\
        uint64_t tti0 = 0; \
        for(int i = 0 ;i < NUM_SAMPLES;i++)\
        {\
            uint64_t ti0 = 0;\
            BENCHMARK(ti0, _expr0);\
            tti0 = tti0 + ti0;\
        }\
        o_timeElapsed0 = tti0/NUM_SAMPLES;\
}

class Contact//intersect
{
public:
    bool e;//exists
    kep::Vector3 p;//position
    
    Contact(bool _exists = false, kep::Vector3 _position = kep::Vector3(0.0f, 0.0f, 0.0f));
    ~Contact();
    static Contact rayPlane(Ray _ray, Plane _plane);
};

;}


#endif // SHADIRAY_H_
