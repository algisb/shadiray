#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "Entity.h"


//Made up of entities
namespace kelp
{
    class Core;
    class Component;
    
    class Entity;
    class Camera;
    class Light;
    class World
    {
    public:
        bool m_init;
        Core * m_core;
        Camera * m_renderCamera;
        std::vector<Light*> m_lights;
        std::vector<Entity*> m_entities;
        World(Core * _core);
        virtual ~World()=0;
        virtual void updateV()=0;
        void update();
    };
};
#endif // WORLD_H_
