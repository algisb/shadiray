#ifndef SHAD_RAYCASTER_H_
#define SHAD_RAYCASTER_H_

#include "Component.h"
#include "component/RenderLine.h"
#include "component/Transform.h"
#include "Input.h"
#include "Contact.h"

namespace shad
{
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
};

#endif //SHAD_RAYCASTER_H_
