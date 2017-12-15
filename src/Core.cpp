///
///  @file Core.cpp
///  @brief core engine components really generic, can be reused in multiple worlds

#include "Core.h"


using namespace kelp;

Core::Core(int _argc, char ** _argv)
{
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    ///////////////////////////////////////
    //MeshGen * meshGen = new MeshGen();
    //meshGen->addTri(kep::Vector3(-2.0,0,0), kep::Vector3(2.0f,0,0), kep::Vector3(0,3.0f,0));
    //meshGen->gen();
    
    
    
    m_plane = new MeshLoad("./models/plane.obj", "./models/");
    m_planeSubdiv = new Subdiv(m_plane->m_dataV, m_plane->m_numVertices);
    
    m_sphereMesh = new MeshLoad("./models/sphereUV.obj", "./models/");
    m_cubeMesh = new MeshLoad("./models/cube.obj", "./models/");
    m_highPolyMesh = new MeshLoad("./models/peps.obj", "./models/");
    m_monkeyMesh = new MeshLoad("./models/monkey.obj", "./models/");
    if(_argc > 1)
        m_externalMesh = new MeshLoad(_argv[1], "./models/");
    else
        m_externalMesh = NULL;
    
    m_shaderMinimal = new ShaderMin();
    m_shaderDefault = new ShaderDefault();
    
    m_world = new World_0(this);
}
Core::~Core()
{
    delete m_plane;
    delete m_planeSubdiv;
    delete m_sphereMesh;
    delete m_cubeMesh;
    delete m_highPolyMesh;
    delete m_monkeyMesh;
    if(m_externalMesh != NULL)
        delete m_externalMesh;
    
    delete m_shaderMinimal;
    delete m_shaderDefault;
    delete m_world;
}

void Core::update()
{
    //printf("fps: %d \n", Time::s_frameRate);
    //printf("deltaT: %f \n", kelp::Time::s_deltaT);
    //Input::printKeyList();
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //render to the original buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    //update worlds (includes rendering)
    m_world->update();
}
