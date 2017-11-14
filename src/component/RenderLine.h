
#ifndef RENDERLINE_H_
#define RENDERLINE_H_
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Config.h"
#include "kep/Core.h"
namespace kelp
{
    class Camera;
    class RenderLine : public Component
    {
    public:
        kep::Vector3 m_p0;
        kep::Vector3 m_p1;
        static std::vector<kep::Vector3> m_verticies;
        
        RenderLine(kep::Vector3 _p0, kep::Vector3 _p1);
        ~RenderLine();
        static void renderLines(Shader * _shader, Camera * _rc);
        
        void init();
        void update();
        void render();
    };
};

#endif // RENDERLINE_H_
