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

void Contact::writeToLogFile(Contacts & _contacts)
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
    file = fopen ("contactLog.txt", "w");
    fwrite (buffer.c_str() , sizeof(char), buffer.size(), file);
    fclose (file);
}

void Contact::printToConsole(Contacts & _contacts)
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

void Contact::markContacts(shad::Contacts& _contacts, kelp::Entity * _owner)
{

    for(uint64_t i = 0; i<_contacts.size(); i++)
    {
        uint64_t reqSize = i+1;
        if(Marker::s_markers.size()<reqSize)
        {
            Marker * m = new Marker(_contacts[i]->m_contact);
            m->m_owner = _owner;
            _owner->m_lateComponents.push_back(m);
        }
        else
        {
            Marker::s_markers[i]->m_point = _contacts[i]->m_contact;
            Marker::s_markers[i]->m_line[0]->m_enabled = true;
            Marker::s_markers[i]->m_line[1]->m_enabled = true;
            Marker::s_markers[i]->m_line[2]->m_enabled = true;
        }
        

    }
}
void Contact::clearMarkers()
{
    for(uint64_t i = 0; i<Marker::s_markers.size(); i++)//disable markers incase we have more then required
    {
        Marker::s_markers[i]->m_line[0]->m_enabled = false;
        Marker::s_markers[i]->m_line[1]->m_enabled = false;
        Marker::s_markers[i]->m_line[2]->m_enabled = false;
    }
}


std::vector<Marker*> Marker::s_markers = std::vector<Marker*>();

Marker::Marker(kep::Vector3 _point)
{
    m_point = _point;
    s_markers.push_back(this);
}
Marker::~Marker()
{
}
void Marker::init()
{
    m_line[0] = new kelp::RenderLine2(m_point + kep::Vector3(m_size, 0.0f, 0.0f),m_point + kep::Vector3(-m_size, 0.0f, 0.0f));
    m_line[1] = new kelp::RenderLine2(m_point + kep::Vector3(0.0f, m_size, 0.0f),m_point + kep::Vector3(0.0f, -m_size, 0.0f));
    m_line[2] = new kelp::RenderLine2(m_point + kep::Vector3(0.0f, 0.0f, m_size),m_point + kep::Vector3(0.0f, 0.0f, -m_size));
    for(int i = 0; i<3;i++)
    {
        m_line[i]->m_owner = m_owner;
        m_owner->m_lateComponents.push_back(m_line[i]);
    }
    //dont need to delete as RenderLine2 is a component which gets deleted at the end automatically
}

void Marker::update()
{
    m_line[0]->m_p0 = m_point + kep::Vector3(m_size, 0.0f, 0.0f);
    m_line[0]->m_p1 = m_point + kep::Vector3(-m_size, 0.0f, 0.0f);
    
    m_line[1]->m_p0 = m_point + kep::Vector3(0.0f, m_size, 0.0f);
    m_line[1]->m_p1 = m_point + kep::Vector3(0.0f, -m_size, 0.0f);
    
    m_line[2]->m_p0 = m_point + kep::Vector3(0.0f, 0.0f, m_size);
    m_line[2]->m_p1 = m_point + kep::Vector3(0.0f, 0.0f, -m_size);
}

void Marker::render()
{
    
}







