#ifndef SHAD_CONTACT_H_
#define SHAD_CONTACT_H_
#include "Ray.h"
#include "Triangle.h"
#include <vector>
#include "component/RenderLine.h"

namespace shad
{
    class Contact;
    typedef std::vector<Contact*> Contacts;
    
    class Contact
    {
    public:
        kep::Vector3 m_contact;
        Ray m_ray;
        Triangle m_triangle;
        
        Contact(kep::Vector3 _contact = kep::Vector3(), Ray _ray = Ray(), Triangle _triangle = Triangle());
        ~Contact();
        static void writeToLogFile(Contacts & _contacts);
        static void printToConsole(Contacts & _contacts);
        static void markContacts(Contacts & _contacts, kelp::Entity * _owner);
    };
    
    class Marker : public kelp::Component
    {
    public:
        const float m_size = 0.1f;
        kep::Vector3 m_point;
        kelp::RenderLine2 * m_line[3];
        static std::vector<Marker*> s_markers;
        Marker(kep::Vector3 _point = kep::Vector3());
        ~Marker();
        
        void init();
        void update();
        void render();
        
    };
    
};
#endif //SHAD_CONTACT_H_
