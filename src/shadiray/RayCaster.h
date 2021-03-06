#ifndef SHAD_RAYCASTER_H_
#define SHAD_RAYCASTER_H_

#include "Component.h"
#include "component/RenderLine.h"
#include "component/Transform.h"
#include "Input.h"
#include "Ray.h"
#include "Triangle.h"

namespace shad
{
    class RayCaster : public kelp::Component // Equivelent to a camera for regular rendering
    {
    public:
        kep::Vector3 m_up;  
        kep::Vector3 m_front;
        kep::Vector3 m_left;
        
        kelp::Transform * m_transform;
        float m_nearPlane;
        float m_farPlane;
        
        int m_width;
        int m_height;
        float m_raySpread;
        
        Ray ** m_rays;
        kelp::RenderLine ** m_rLines;
        
        Ray m_viewCone[4];//rays descrbing the viewcone
        kelp::RenderLine * m_vcLines[12];//used for drawing viewcone
        
        kep::Vector3 m_box[8];
        kelp::RenderLine * m_bLines[12];
        
        
        RayCaster(int _width, int _height, float _nearPlane, float _farPlane, float _raySpread);
        ~RayCaster();
        
        void init();
        void update();
        void render();
        
        void initRays();
        void updateRays(int (*_testFunc)(Ray *, Triangle *,  kep::Vector3 * ), int _type);
        void raycastCone(int (*_testFunc)(Ray *, Triangle *,  kep::Vector3 * ));//each ray against every triangle, better for raytracing
        
        void initViewCone();
        void updateViewCone();
        
        void raycastBox(int (*_testFunc)(Ray *, Triangle *,  kep::Vector3 * ));
        
        void initBoxVolume();
        
    };  
};

#endif //SHAD_RAYCASTER_H_
