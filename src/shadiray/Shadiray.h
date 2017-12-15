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
            return 0;
        
        float t = nu/de;// 1 flops
        if(t < 0.0f)
            return 0;
        
        *o_point = _ray->s + (_ray->d*t);//6 flops
        return 1;
    }

    inline int rayTriangleBForce(Ray * _ray, Triangle * _triangle, kep::Vector3 * o_point)//77 total flops
    {
        Plane plane(_triangle->p[0], _triangle->n);
        if(rayPlane(_ray, &plane, o_point) == 0)//17 flops
            return 0;
        //edge 0
        kep::Vector3 ab = _triangle->p[1] - _triangle->p[0];//3 flops
        kep::Vector3 aq = *o_point - _triangle->p[0];//3 flops
        kep::Vector3 c = kep::cross(ab,aq);//9 flops
        float d = kep::dot(c, _triangle->n);//5 flops
        
        if(d < 0)
            return 0;
        //edge 1
        ab = _triangle->p[2] - _triangle->p[1];//3 flops
        aq = *o_point - _triangle->p[1];//3 flops
        c = kep::cross(ab,aq);//9 flops
        d = kep::dot(c, _triangle->n);//5 flops
        if(d < 0)
            return 0;
        //edge 2
        ab = _triangle->p[0] - _triangle->p[2];//3 flops
        aq = *o_point - _triangle->p[2];//3 flops
        c = kep::cross(ab,aq);//9 flops
        d = kep::dot(c, _triangle->n);//5 flops
        if(d < 0)
            return 0;    
        
        return 1;
        
        //         kep::Vector3 ab, aq, c;
//         float d;
//         
//         for(int i = 0; i<3; ++i)
//         {
//             int i0 = i+1;
//             if(i0 > 2)
//                 i0 = 0;
//             ab = _triangle->p[i0] - _triangle->p[i];//3 flops
//             aq = *o_point - _triangle->p[i];//3 flops
//             c = kep::cross(ab,aq);//9 flops
//             d = kep::dot(c, _triangle->n);//5 flops
//             if(d < 0)
//                 return 0;
//             
//         }
    }
    
    inline int rayTriangleBary(Ray * _ray, Triangle * _triangle,  kep::Vector3 * o_point)// total 63 flops
    {
        Plane plane(_triangle->p[0], _triangle->n);
        if(rayPlane(_ray, &plane, o_point)==0)//17 flops
            return 0;
        
        kep::Vector3 v0, v1, v2;
        float dot00, dot01, dot02, dot11, dot12, invDenom, u, v;
        
        v0 = _triangle->p[1] - _triangle->p[0];//3 flops

        v1 = _triangle->p[2] - _triangle->p[0];//3 flops

        v2 = *o_point - _triangle->p[0];// 3 flops
        
        dot00 = kep::dot(v0, v0);// 5 flops

        dot01 = kep::dot(v0, v1);// 5 flops

        dot02 = kep::dot(v0, v2);// 5 flops

        dot11 = kep::dot(v1, v1);// 5 flops

        dot12 = kep::dot(v1, v2);// 5 flops

        // Compute barycentric coordinates
        invDenom = 1 / (dot00 * dot11 - dot01 * dot01); // 4 flops
        u = (dot11 * dot02 - dot01 * dot12) * invDenom; // 4 flops
        v = (dot00 * dot12 - dot01 * dot02) * invDenom; // 4 flops


        // Check if point is in triangle

        if ((u >= 0.0f) && (v >= 0.0f) && (u <= 1.0f) && (v <= 1.0f) && (u + v <= 1.0f))
            return 1;
        else
            return 0;
    }

    
    inline int rayTriangleMT97(Ray * _ray, Triangle * _triangle,  kep::Vector3 * o_point)// 64 flops
    {
        kep::Vector3 edge1, edge2, pvec, tvec, qvec;
        float det, inv_det, u, v, w, t;
        edge1 = _triangle->p[1] - _triangle->p[0];// 3 flops
        edge2 = _triangle->p[2] - _triangle->p[0];// 3 flops
        
        pvec  = kep::cross(_ray->d, edge2);// 9 flops
        
        det = kep::dot(edge1, pvec);// 5 flops
        if(det == 0.0f)
            return 0;
        
        inv_det = 1.0f/det;// 1 flops
        
        tvec = _ray->s - _triangle->p[0];// 3 flops
        
        u = kep::dot(tvec, pvec) * inv_det;// 8 flops
        if(u < 0.0f || u > 1.0f)
            return 0;
        
        qvec = kep::cross(tvec, edge1);//9 flops
        
        v = kep::dot(_ray->d, qvec) * inv_det;// 8 flops
        if(v < 0.0f || v > 1.0f)
            return 0;
        
        w = u + v;//1 flop
        if(w < 0.0f || w > 1.0f)
            return 0;
        
        t = kep::dot(edge2, qvec) * inv_det;// 8 flops
        if(t < 0.0f)
            return 0;
        *o_point = _ray->s + _ray->d * t; // 6 flops
        return 1;;
    }

};


#endif // SHADIRAY_H_
