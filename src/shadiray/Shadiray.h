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
#include "Triangle.h"
#include "Plane.h"
#include "Ray.h"
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


        


    inline int rayPlane(Ray * _ray, Plane * _plane, kep::Vector3 * o_point)//total 17 flops
    {
        float nu = kep::dot((_plane->p - _ray->s), _plane->n);//5 flops
        float de = kep::dot(_ray->d, _plane->n);//5 flops
        if(de == 0.0f)
            return 1;
        
        float t = nu/de;// 1 flops
        if(t < 0.0f)
            return 1;
        
        *o_point = _ray->s + (_ray->d*t);//6 flops
        return 0;
    }

    inline int rayTriangle(Ray * _ray, Triangle * _triangle, kep::Vector3 * o_point)//77 total flops
    {
        Plane plane(_triangle->p[0], _triangle->n);
        if(rayPlane(_ray, &plane, o_point) == 1)//17 flops
            return 1;
        
        //edge 0
        kep::Vector3 ab = _triangle->p[1] - _triangle->p[0];//3 flops
        kep::Vector3 aq = *o_point - _triangle->p[0];//3 flops
        kep::Vector3 c = kep::cross(ab,aq);//9 flops
        float d = kep::dot(c, _triangle->n);//5 flops
        if(d < 0)
            return 1;
        //edge 1
        ab = _triangle->p[2] - _triangle->p[1];//3 flops
        aq = *o_point - _triangle->p[1];//3 flops
        c = kep::cross(ab,aq);//9 flops
        d = kep::dot(c, _triangle->n);//5 flops
        if(d < 0)
            return 1;
        //edge 2
        ab = _triangle->p[0] - _triangle->p[2];//3 flops
        aq = *o_point - _triangle->p[2];//3 flops
        c = kep::cross(ab,aq);//9 flops
        d = kep::dot(c, _triangle->n);//5 flops
        if(d < 0)
            return 1;    
        
        return 0;
    }
    
    inline int pointInTriangle(kep::Vector3 * _point, Triangle * _triangle) // total 46 flops
    {
        kep::Vector3 v0 = _triangle->p[1] - _triangle->p[0];//3 flops

        kep::Vector3 v1 = _triangle->p[2] - _triangle->p[0];//3 flops

        kep::Vector3 v2 = *_point - _triangle->p[0];// 3 flops
        float dot00 = kep::dot(v0, v0);// 5 flops

        float dot01 = kep::dot(v0, v1);// 5 flops

        float dot02 = kep::dot(v0, v2);// 5 flops

        float dot11 = kep::dot(v1, v1);// 5 flops

        float dot12 = kep::dot(v1, v2);// 5 flops

        // Compute barycentric coordinates
        float invDenom = 1 / (dot00 * dot11 - dot01 * dot01); // 4 flops
        float u = (dot11 * dot02 - dot01 * dot12) * invDenom; // 4 flops
        float v = (dot00 * dot12 - dot01 * dot02) * invDenom; // 4 flops


        // Check if point is in triangle

        if ((u >= 0) && (v >= 0) && (u <= 1) && (v <= 1) && (u + v <= 1))
            return 0;
        else
            return 1;
        
    }
    
    inline int rayTriangle0(Ray * _ray, Triangle * _triangle,  kep::Vector3 * o_point)// total 63 flops
    {
        Plane plane(_triangle->p[0], _triangle->n);
        if(rayPlane(_ray, &plane, o_point)==1)//17 flops
            return 1;
        
        if(pointInTriangle(o_point, _triangle) == 0) //46 flops
            return 0;
        else
            return 1;
    }

//     Contact Contact::rayTriangle1(Ray _ray, Triangle _triangle)
//     {
// 
//         return Contact();
//     }
    



};


#endif // SHADIRAY_H_
