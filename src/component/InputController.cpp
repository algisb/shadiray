///
///  @file InputController.cpp
///  @brief attaches player related input to any entity
#include "InputController.h"
#include "Camera.h"

using namespace kelp;

InputController::InputController() : Component()
{
    
    
}

InputController::~InputController()
{
    
}

void InputController::init()
{
    
}
void InputController::update()
{
    Camera * rc = m_owner->m_world->m_renderCamera;
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_W, Input::Keyboard::KeyboardAction::HELD))
    {
        rc->m_transform->m_position +=  (rc->m_front*Time::s_deltaT) * 10.0f;
    }
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_S, Input::Keyboard::KeyboardAction::HELD))
    {
        rc->m_transform->m_position +=  (rc->m_front*Time::s_deltaT) * -10.0f;
    }
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_A, Input::Keyboard::KeyboardAction::HELD))
    {
        rc->m_transform->m_position += (rc->m_left*Time::s_deltaT) * 10.0f;
    }
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_D, Input::Keyboard::KeyboardAction::HELD))
    {
        rc->m_transform->m_position += (rc->m_left*Time::s_deltaT) * -10.0f;
    }
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_E, Input::Keyboard::KeyboardAction::HELD))
    {
        rc->m_transform->m_position += (rc->m_up*Time::s_deltaT) * 10.0f;
    }
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_C, Input::Keyboard::KeyboardAction::HELD))
    {
        rc->m_transform->m_position += (rc->m_up*Time::s_deltaT) * -10.0f;
    }
    
    
    
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_LEFT, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        
        kep::Quaternion q;
        q.setEuler(rc->m_up, -1.0f);
        rc->m_transform->m_orientation *= q;
    }
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_RIGHT, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        
        kep::Quaternion q;
        q.setEuler(rc->m_up, 1.0f);
        rc->m_transform->m_orientation *= q;
    }
    
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_UP, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        
        kep::Quaternion q;
        q.setEuler(rc->m_left, -1.0f);
        rc->m_transform->m_orientation *= q;
    }
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_DOWN, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        
        kep::Quaternion q;
        q.setEuler(rc->m_left, 1.0f);
        rc->m_transform->m_orientation *= q;
    }
    
}
