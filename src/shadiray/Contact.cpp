#include "Contact.h"
#include <string>
using namespace shad;

Contact::Contact(kep::Vector3 _contact, shad::Ray _ray, shad::Triangle _triangle)
{
    m_contact = _contact;
    m_ray = _ray;
    m_triangle = _triangle;
}
Contact::~Contact()
{
}

void Contact::writeToLogFile(std::vector<Contact*> & _contacts)
{
    std::string buffer;
    char tmpBuff[256];
    sprintf(tmpBuff, "");
    
    
    for(uint64_t i = 0; i<_contacts.size(); i++)
    {
        Contact * c = _contacts[i];
        sprintf(tmpBuff, "Contact %llu \n", i);
        buffer += tmpBuff;
        sprintf(tmpBuff, "    point: %.3f %.3f %.3f \n", c->m_contact.data[0], c->m_contact.data[1], c->m_contact.data[2]);
        buffer += tmpBuff;
        sprintf(tmpBuff, "    ray:\n");
        buffer += tmpBuff;
        sprintf(tmpBuff, "        source: %.3f %.3f %.3f\n", c->m_ray.s.data[0], c->m_ray.s.data[1], c->m_ray.s.data[2]);
        buffer += tmpBuff;
        sprintf(tmpBuff, "        direction: %.3f %.3f %.3f \n", c->m_ray.d.data[0], c->m_ray.d.data[1], c->m_ray.d.data[2]);
        buffer += tmpBuff;
        sprintf(tmpBuff, "    triangle:\n");
        buffer += tmpBuff;
        for(int j = 0; j<3; j++)
        {
            sprintf(tmpBuff, "        point%d: %.3f %.3f %.3f\n", j, c->m_triangle.p[j].data[0], c->m_triangle.p[j].data[1], c->m_triangle.p[j].data[2]);
            buffer += tmpBuff;
        }
        sprintf(tmpBuff, "        normal: %.3f %.3f %.3f\n", c->m_triangle.n.data[0], c->m_triangle.n.data[1], c->m_triangle.n.data[2]);
        buffer += tmpBuff;
        sprintf(tmpBuff,"\n");
        buffer += tmpBuff;
    }
    
    
    FILE * file;
    file = fopen ("contact.log", "w");
    fwrite (buffer.c_str() , sizeof(char), buffer.size(), file);
    fclose (file);
}

void Contact::printToConsole(std::vector<Contact *> & _contacts)
{
    for(uint64_t i = 0; i<_contacts.size(); i++)
    {
        Contact * c = _contacts[i];
        printf("Contact %llu \n", i);
        printf("    point: %.3f %.3f %.3f \n", c->m_contact.data[0], c->m_contact.data[1], c->m_contact.data[2]);
        printf("    ray:\n");
        printf("        source: %.3f %.3f %.3f\n", c->m_ray.s.data[0], c->m_ray.s.data[1], c->m_ray.s.data[2]);
        printf("        direction: %.3f %.3f %.3f \n", c->m_ray.d.data[0], c->m_ray.d.data[1], c->m_ray.d.data[2]);
        printf("    triangle:\n");
        for(int j = 0; j<3; j++)
            printf("        point%d: %.3f %.3f %.3f\n", j, c->m_triangle.p[j].data[0], c->m_triangle.p[j].data[1], c->m_triangle.p[j].data[2]);
        printf("        normal: %.3f %.3f %.3f\n", c->m_triangle.n.data[0], c->m_triangle.n.data[1], c->m_triangle.n.data[2]);
        printf("\n");
    }
}



