///
///  @file Entity.cpp
///  @brief Anything and everything

#include "Entity.h"
using namespace kelp;

Entity::Entity(World * _world, std::string _tag)
{
    m_world = _world;
    m_tag = _tag;
    m_world->m_entities.push_back(this);
}
Entity::~Entity()
{
    for(int i = 0; i< m_components.size(); i++)
        delete m_components[i];
    m_components.clear();
}

void Entity::init()
{
    for(int i = 0; i< m_components.size(); i++)
        m_components[i]->init();
}

void Entity::update()
{
    for(int i = 0; i< m_components.size(); i++)
        m_components[i]->update();
}

void Entity::render()
{
    for(int i = 0; i< m_components.size(); i++)
        m_components[i]->render();
}

void Entity::addComponent(Component * io_c)
{
    io_c->m_owner = this;
    m_components.push_back(io_c);
}

