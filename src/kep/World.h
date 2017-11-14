#pragma once
#include "RigidBody.h"
#include "ForceGenerator.h"
namespace kep
{
    class World
    {
    public:
        std::vector<RigidBody*> m_rigidBody;
        ForceRegistry * m_fReg;
        Gravity * m_gGen;
        LinearDrag * m_ldGen;
        AngularDrag * m_adGen;
        
        World();
        void update(real _duration);
        void addRigidBody(RigidBody * _rigidBody);
    };
}
