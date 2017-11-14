#include "RenderLine.h"
#include "Camera.h"

using namespace kelp;
std::vector<kep::Vector3> RenderLine::m_verticies = std::vector<kep::Vector3>();

RenderLine::RenderLine(kep::Vector3 _p0, kep::Vector3 _p1)
{
    m_p0 = _p0;
    m_p1 = _p1;
}
RenderLine::~RenderLine()
{
    
}

void RenderLine::renderLines(Shader * _shader, Camera * _rc)
{
    GLuint vao = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    int _numVertices = m_verticies.size();

    //totalVertex = totalVertex + _numVertices;
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &m_verticies[0], GL_DYNAMIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);


    glUseProgram(_shader->m_shaderLocation);
    kep::Matrix4 m4;
    glUniformMatrix4fv(_shader->m_shaderModelMatLocation, 1, 
                       GL_FALSE, &m4.d[0][0]);
    glUniformMatrix4fv(_shader->m_shaderViewMatLocation, 1, 
                       GL_FALSE, &_rc->m_viewMat.d[0][0]);
    glUniformMatrix4fv(_shader->m_shaderProjMatLocation, 1, 
                       GL_FALSE, &_rc->m_projectionMat.d[0][0]);
    
    // Tell OpenGL to draw it
    // Must specify the type of geometry to draw and the number of vertices
    glDrawArrays(GL_LINES, 0, _numVertices);
    // Unbind VAO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    m_verticies.clear();
}

void RenderLine::init()
{
    
}
void RenderLine::update()
{
    m_verticies.push_back(m_p0);
    m_verticies.push_back(m_p1);
}
void RenderLine::render()
{
    
}
