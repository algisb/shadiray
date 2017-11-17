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

#include "Component.h"
#include "Triangle.h"
#include "Plane.h"
#include "Ray.h"
#include "component/RenderLine.h"
#include "component/Transform.h"
#include "component/Render.h"


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
        static Contact rayTriangle(Ray _ray, Triangle _triangle);
    };
    
    class RayCaster : public kelp::Component // Equivelent to a camera for regular rendering
    {
    public:
        kep::Vector3 m_up;  
        kep::Vector3 m_front;
        kep::Vector3 m_left;
        
        kelp::Transform * m_transform;
        float m_maxRayLength;
        Ray ray;
        kelp::RenderLine * rline;
        RayCaster();
        ~RayCaster();
        
        void init();
        void update();
        void render();
        
    };
    class RayReciever : public kelp::Component //any set of trinagles appearing in the ray cast scene
    {
    public:
        kelp::RenderLine * rline[3];
        
        static std::vector<RayReciever*> s_rayRecievers;
        kelp::Mesh * m_mesh;
        kelp::Transform * m_transform;
        int m_numTriangles;
        Triangle * m_triangles;
        Triangle * m_tTriangles; // trasformed triangles
        RayReciever();
        ~RayReciever();
        
        void init();
        void update();
        void render();
    };

};


#endif // SHADIRAY_H_
