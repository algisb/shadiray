#ifndef SHAD_RAYRECIEVER_H_
#define SHAD_RAYRECIEVER_H_
#include "Component.h"
#include "Triangle.h"
#include "Plane.h"
#include "Ray.h"
#include "component/RenderLine.h"
#include "component/Transform.h"
#include "component/Render.h"
#include "Input.h"
namespace shad 
{
    class RayReciever : public kelp::Component //any set of trinagles appearing in the ray cast scene
    {
    public:
        //kelp::RenderLine * rline[3];
        
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
        void updateR();
    };  
};

#endif //SHAD_RAYRECIEVER_H_
