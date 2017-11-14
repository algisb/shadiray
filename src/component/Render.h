#ifndef RENDER_H_
#define RENDER_H_
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Config.h"
#include "kep/Core.h"
namespace kelp
{
    enum RenderMode
    {
        SOLID = 0,
        WIRE
    };
    class Render : public Component
    {
    public:

        Mesh * m_mesh;
        Shader * m_shader;
        Transform * m_transform;
        
        RenderMode m_renderMode;
        
        kep::Matrix4 m_modelMat;
        kep::Matrix4 m_viewMat;
        kep::Matrix4 m_projectionMat;
        

        
        Render(Mesh* _mesh, Shader* _shader, RenderMode _renderMode);
        ~Render();
        void init();
        void update();
        void render();
    };
};

#endif // RENDER_H_
