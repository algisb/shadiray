///
///  @file World.cpp
///  @brief draws entity to the frame buffer

#include "Render.h"
#include "Camera.h"


using namespace kelp;

Render::Render(Mesh * _mesh, Shader * _shader, RenderMode _renderMode, kep::Vector3 _colour) : Component()
{
    m_mesh = _mesh;
    m_shader = _shader;
    m_renderMode = _renderMode;
    m_colour = _colour;

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
}
void Render::render()
{
    
    glUseProgram(m_shader->m_shaderLocation);

    glUniformMatrix4fv(m_shader->m_shaderModelMatLocation, 1, 
                       GL_FALSE, &(m_transform->m_modelMat.transpose().d[0][0]));
    
    Camera * rc = m_owner->m_world->m_renderCamera;
    glUniformMatrix4fv(m_shader->m_shaderViewMatLocation, 1, 
                       GL_FALSE, &rc->m_viewMat.d[0][0]);
    glUniformMatrix4fv(m_shader->m_shaderProjMatLocation, 1, 
                       GL_FALSE, &rc->m_projectionMat.d[0][0]);
    glUniform3fv(m_shader->m_shaderColourLocation, 1, m_colour.data);

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
