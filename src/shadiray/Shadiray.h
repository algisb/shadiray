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


//#include "shadiray/RayCaster.h"
//#include "shadiray/RayReciever.h"

namespace shad
{
#define EXEC_TIMER(o_timeElapsed, _expr) \
{\
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();\
            _expr;\
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();\
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);\
    o_timeElapsed = time_span.count();\
}


#define NUM_SAMPLES 10000
#define EXEC_TIMER_SAMPLE(o_timeElapsed0, _expr0) \
{\
        double tti0 = 0.0f; \
        for(int i = 0 ;i < NUM_SAMPLES;i++)\
        {\
            double ti0 = 0.0f;\
            EXEC_TIMER(ti0, _expr0);\
            tti0 = tti0 + ti0;\
        }\
        o_timeElapsed0 = tti0/(double)NUM_SAMPLES;\
}


    



};


#endif // SHADIRAY_H_
