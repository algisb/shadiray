#ifndef INPUTCONTROLLER_H_
#define INPUTCONTROLLER_H_
#include "Input.h"
#include "Component.h"
#include "Transform.h"
#include "Time.h"


namespace kelp
{
    class InputController : public Component
    {
    public:
        InputController();
        ~InputController();
        void init();
        void update();
        
    };
};


#endif // INPUTCONTROLLER_H_
