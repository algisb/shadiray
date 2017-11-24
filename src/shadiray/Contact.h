#ifndef SHAD_CONTACT_H_
#define SHAD_CONTACT_H_
#include "Ray.h"
#include "Triangle.h"
#include <vector>
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
    };
    
};
#endif //SHAD_CONTACT_H_
