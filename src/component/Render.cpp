///
///  @file World.cpp
///  @brief draws entity to the frame buffer

#include "Render.h"
#include "Camera.h"


using namespace kelp;

Render::Render(Mesh * _mesh, Shader * _shader, RenderMode _renderMode) : Component()
{
    m_mesh = _mesh;
    m_shader = _shader;
    m_renderMode = _renderMode;

}
Render::~Render()
{
    
}

void Render::init()
{
    m_transform = m_owner->getComponent<Transform>();


}
void Render::update()
{
    m_transform->m_orientation.normalize();
    m_modelMat.setOrientationAndPos(m_transform->m_orientation, m_transform->m_position);
    m_modelMat = m_modelMat * kep::Matrix4(m_transform->m_scale.x, 0.0f, 0.0f, 0.0f,
                                           0.0f, m_transform->m_scale.y, 0.0f, 0.0f,
                                           0.0f, 0.0f, m_transform->m_scale.z, 0.0f,
                                           0.0f, 0.0f, 0.0f, 1.0f);
    m_modelMat = m_modelMat.transpose();
    
    Camera * rc = m_owner->m_world->m_renderCamera;
    m_viewMat = rc->m_viewMat;
    m_projectionMat = rc->m_projectionMat;
}
void Render::render()
{
    glUseProgram(m_shader->m_shaderLocation);

    glUniformMatrix4fv(m_shader->m_shaderModelMatLocation, 1, 
                       GL_FALSE, &m_modelMat.d[0][0]);
    glUniformMatrix4fv(m_shader->m_shaderViewMatLocation, 1, 
                       GL_FALSE, &m_viewMat.d[0][0]);
    glUniformMatrix4fv(m_shader->m_shaderProjMatLocation, 1, 
                       GL_FALSE, &m_projectionMat.d[0][0]);
    glUniform3fv(m_shader->m_shaderColourLocation, 1, kep::Vector3(1.0f, 0.0f, 0.0f).data);

    switch(m_renderMode)
    {
        case RenderMode::SOLID:
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            break;
        
        case RenderMode::WIRE:
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            break;
    }
    glBindVertexArray( m_mesh->m_vao );
    glDrawArrays(GL_TRIANGLES, 0, m_mesh->m_numVertices);
    glBindVertexArray( 0 );

}
