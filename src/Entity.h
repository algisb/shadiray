#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include <string>
#include "Component.h"
#include "World.h"

namespace kelp
{
    class World;
    class Component;
    class Entity
    {
    public:
        World * m_world;
        std::string m_tag;
        std::vector<Component*> m_components;

        Entity(World * _world, std::string _tag);
        ~Entity();
        void init();
        void update();
        void render();
        void addComponent(Component * io_c);
        template<typename ComponentType> ComponentType * getComponent()
        {
            for (int i = 0; i < this->m_components.size(); i++)
            {
                ComponentType * tempComp = dynamic_cast<ComponentType*>(this->m_components[i]);
                if (tempComp != NULL)
                {
                    return tempComp;
                }
            }
            return NULL;
        }
    };
    
};
#endif // ENTITY_H_
