#ifndef WORLD_0_H
#define WORLD_0_H

#include "World.h"
#include "Shader.h"
#include "Mesh.h"
#include "component/Transform.h"
#include "component/InputController.h"
#include "component/Render.h"
#include "component/Camera.h"
#include "component/Light.h"
#include "component/RenderLine.h"
#include "shadiray/Shadiray.h"

namespace kelp
{
    class World_0 : public World
    {
    public:
        Entity * empty[10];
        shad::Ray ray;
        shad::Plane plane;
        
        World_0(Core * _core);
        ~World_0();
        void updateV();
    };
    
};


#endif // WORLD_0_H
