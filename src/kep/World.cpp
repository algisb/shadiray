#include "World.h"
using namespace kep;

World::World()
{
    m_fReg = new ForceRegistry();
    
    m_gGen = new Gravity(Vector3(0.0f, -9.81f, 0.0f));
    m_ldGen = new LinearDrag(0.1f, 0.001f);
    m_adGen = new AngularDrag(0.5, 0.1f);
}
void World::update(real _duration)
{
    m_fReg->updateForces(_duration);
    for(int i = 0; i < m_rigidBody.size(); i++)
    {
        m_rigidBody[i]->integrate(_duration);
    }
}
void World::addRigidBody(RigidBody * _rigidBody)
{
    m_fReg->add(_rigidBody, m_gGen);
    m_fReg->add(_rigidBody, m_ldGen);
    m_fReg->add(_rigidBody, m_adGen);
    m_rigidBody.push_back(_rigidBody);
}
