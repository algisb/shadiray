///
///  @file World_0.cpp
///  @brief holds all the entities that get created also loads assets and other shared objects

#include "World_0.h"
#include <Core.h>

using namespace kelp;

World_0::World_0(Core * _core) : World(_core)
{

    
    Entity * refEntity = NULL;
    //////////////////////CAM/////////////////////////
    refEntity = new Entity(this, "camera");//TODO: allow it so this can insted be another entity acting as a root node(scenegraph)
    refEntity->addComponent(new Transform(
                                          kep::Vector3(0.0f, 0.0f, 20.0f),
                                          kep::Quaternion(), 
                                          kep::Vector3(1.0f, 1.0f, .0f)
                                         ));
    refEntity->addComponent(
                            new Camera(kep::Vector3(0.0f, 1.0f, 0.0f),
                            kep::perspectiveProjection(
                                45.0f, 
                                Config::s_windowWidth, 
                                Config::s_windowHeight, 
                                1.0f, 
                                1000.0f).transpose(),
                                true
                            ));
    
    
    refEntity = new Entity(this, "Directional Light");
    refEntity->addComponent(new LightDirectional(m_core->m_shaderDefault, 0.5f, kep::Vector3(0.0f,0.0f,0.0f), kep::Vector3(1.0f, 1.0f, 1.0f)));
    
    refEntity = new Entity(this, "Point Light");
    refEntity->addComponent(new Transform(
                                        kep::Vector3(2.0f, 4.0f, -10.0f),
                                        kep::Quaternion(), 
                                        kep::Vector3(0.2f, 0.2f, 0.2f)
                                        ));
    refEntity->addComponent(new LightPoint(m_core->m_shaderDefault, 10.0f, kep::Vector3(0.0f, 0.0f, 0.0f)));
    refEntity->addComponent(new Render(m_core->m_sphereMesh, m_core->m_shaderMinimal, RenderMode::SOLID));
    
    //m_renderCamera = empty[0]->getComponent<Camera>();/////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    
    
    refEntity = new Entity(this, "ray caster");
    refEntity->addComponent(new Transform(
                                          kep::Vector3(0.0f, 0.0f, 0.0f),
                                          kep::Quaternion(), 
                                          kep::Vector3(0.1f, 0.1f, 0.1f)
                                         ));
    
    refEntity->addComponent(new shad::RayCaster(256, 256, 2.0f, 100.0f, 0.01f));
    refEntity->addComponent(new Render(m_core->m_sphereMesh, m_core->m_shaderMinimal, RenderMode::SOLID, kep::Vector3(0.0f, 0.0f, 1.0f)));
    
   //////////////////////////////////////////////////////////////////////////////////////////// 
    
    
    refEntity = new Entity(this, "high poly");
    refEntity->addComponent(new Transform(
                                          kep::Vector3(0.0f, 0.0f, -30.0f),
                                          kep::Quaternion(), 
                                          kep::Vector3(1.0f, 1.0f, 1.0f)
                                         ));
    refEntity->addComponent(new Render(m_core->m_highPolyMesh, m_core->m_shaderDefault, RenderMode::SOLID));
    
    
    refEntity = new Entity(this, "plane");
    refEntity->addComponent(new Transform(
                                          kep::Vector3(0.0f, 0.0f, -20.0f),
                                          kep::Quaternion(kep::Vector3(1,0,0), -90.0f), 
                                          kep::Vector3(10.0f, 1.0f, 10.0f)
                                         ));
    //refEntity->addComponent(new shad::RayReciever());
    refEntity->addComponent(new Render(m_core->m_plane, m_core->m_shaderDefault, RenderMode::SOLID));
    
    refEntity = new Entity(this, "plane");
    refEntity->addComponent(new Transform(
                                          kep::Vector3(0.0f, -10.0f, -10.0f),
                                          kep::Quaternion(kep::Vector3(1,0,0), 0.0f), 
                                          kep::Vector3(10.0f, 1.0f, 10.0f)
                                         ));
    //refEntity->addComponent(new shad::RayReciever());
    refEntity->addComponent(new Render(m_core->m_plane, m_core->m_shaderDefault, RenderMode::SOLID));
    
    

    
    refEntity = new Entity(this, "monkey");
    refEntity->addComponent(new Transform(
                                          kep::Vector3(5.0f, -5.0f, -10.0f),
                                          kep::Quaternion(), 
                                          kep::Vector3(1.0f, 1.0f, 1.0f)
                                         ));
    refEntity->addComponent(new shad::RayReciever());
    refEntity->addComponent(new Render(m_core->m_monkeyMesh, m_core->m_shaderDefault, RenderMode::SOLID));
    
    refEntity = new Entity(this, "cube");
    refEntity->addComponent(new Transform(
                                          kep::Vector3(-5.0f, -5.0f, -10.0f),
                                          kep::Quaternion(), 
                                          kep::Vector3(1.0f, 1.0f, 1.0f)
                                         ));
    refEntity->addComponent(new shad::RayReciever());
    refEntity->addComponent(new Render(m_core->m_cubeMesh, m_core->m_shaderDefault, RenderMode::SOLID));

    
}
World_0::~World_0()
{
    
}

void World_0::updateV()
{
    //empty[0]->getComponent<Transform>()->dump();
}
