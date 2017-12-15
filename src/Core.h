//      .--..--..--..--..--..--.
//    .' \  (`._   (_)      ---\------------<<<//END ME
//  .'    |  '._)         (_)  |
//  \ _.')\      .----..---.   /
//  |(_.'  |    /    .-\-.  \  |
//  \     0|    |   ( O| O) | o|
//   |  _  |  .--.____.'._.-.  |
//   \ (_) | o         -` .-`  |
//    |    \   |`-._ _ _ _ _\ /
//    \    |   |  `. |_||_|   |     KELP ENGINE
//    | o  |    \_      \     |     -.   .-.
//    |.-.  \     `--..-'   O |     `.`-' .'
//  _.'  .' |     `-.-'      /-.__   ' .-'
//.' `-.` '.|='=.='=.='=.='=|._/_ `-'.'
//`-._  `.  |________/\_____|    `-.'
//   .'   ).| '=' '='\/ '=' |
//   `._.`  '---------------'
//           //___\   //___\
//             ||       ||
//             ||_.-.   ||_.-.
//            (_.--__) (_.--__)
#ifndef CORE_KELP_H_
#define CORE_KELP_H_

#include "GL/glew.h"
#include "Config.h"
#include "Input.h"
#include "Time.h"

#include "World.h"
#include "Entity.h"
#include "component/Transform.h"
#include "kep/Core.h"
#include "world/World_0.h"
#include "Subdiv.h"

//Fore initialising worlds
namespace kelp
{
    class Core
    {
    public:
 //       MeshLoad * m_cityMesh;
        MeshLoad * m_plane;
        Subdiv * m_planeSubdiv;
        MeshLoad * m_sphereMesh;
        MeshLoad * m_cubeMesh;
        MeshLoad * m_highPolyMesh;
        MeshLoad * m_monkeyMesh;
        
        MeshLoad * m_externalMesh;
        
        ShaderMin * m_shaderMinimal;
        ShaderDefault * m_shaderDefault;
        
        World * m_world;
        Core(int _argc, char ** _argv);
        ~Core();
        void update();
    };
};
#endif // CORE_KELP_H_

