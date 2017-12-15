#include "Subdiv.h"
using namespace kelp;

Subdiv::Subdiv(float * _vertexSoup, uint64_t _numVertex)
{
    std::vector<Vertex> vTmp;
    std::vector<Triangle> tTmp;
    //extract verticies
    allocToLocalStructure(_vertexSoup, _numVertex, &vTmp, &tTmp);
    indexVerticies(&tTmp);
    genEdges();
    //genVertexNeighbours(&tTmp);

    
    printf("v num: %d \n", m_v.size());
    printf("t num: %d \n", m_t.size());
    printf("e num; %d \n", m_e.size());
    //m_t[0]->dumpVertexLocs();
    //m_t[1]->dumpVertexLocs();
    
}

Subdiv::~Subdiv()
{
    for(uint64_t i = 0; i < m_v.size(); i++)
        delete m_v[i];
    m_v.clear();
    for(uint64_t i = 0; i < m_t.size(); i++)
        delete m_t[i];
    m_t.clear();
    for(uint64_t i = 0; i < m_e.size(); i++)
        delete m_e[i];
    m_e.clear();
}

void Subdiv::allocToLocalStructure(float * _vertexSoup, uint64_t _numVertex, std::vector<Vertex> * _v, std::vector<Triangle> * _t)
{
    for(uint64_t i = 0; i < _numVertex*3; i=i+3)
    {
        Vertex tmpV;
        tmpV.position = kep::Vector3(_vertexSoup[i+0], _vertexSoup[i+1], _vertexSoup[i+2]);
        _v->push_back(tmpV);
    }
    
    for(uint64_t i = 0; i < _v->size(); i=i+3)
    {
        Triangle tmpT;
        tmpT.edge[0] = NULL;
        tmpT.edge[1] = NULL;
        tmpT.edge[2] = NULL;
        for(int j = 0; j<3;j++)
            tmpT.vertex[j] = &(*_v)[i+j];
        _t->push_back(tmpT);
    }
}
void Subdiv::indexVerticies(std::vector<Triangle> * _t)
{
    for(uint64_t i = 0; i < _t->size(); i++)//each tri
    {
        Triangle * tmpT = new Triangle();
        for(int j = 0; j<3;j++)//each vert
        {
            bool exist = false;
            //check if vertex already exists
            for(uint64_t k = 0; k < m_v.size(); k++)
            {
                if((*_t)[i].vertex[j]->position == m_v[k]->position)
                {
                    printf("reused: \n");
                    m_v[k]->dumpLoc();
                    tmpT->vertex[j] = (m_v)[k];
                    exist = true;
                    break;
                }
            }
            if(!exist)
            {
                Vertex * v = new Vertex();
                v->position = (*_t)[i].vertex[j]->position;
                tmpT->vertex[j] = v;
                m_v.push_back(v);
                
                printf("added:\n");
                //m_v[m_v.size()-1].dumpLoc();
            }
        }
        m_t.push_back(tmpT);
    }  
}
int Subdiv::genEdges()
{
    for(uint64_t i = 0; i < m_t.size(); i++)//each tri
    {
        for(unsigned j =0; j<3; j++)//each triangle edge
        {
            unsigned i0 = j;
            unsigned i1 = j+1;
            if(i1 > 2)
                i1 = 0;
            
            //our edge data
            Vertex * v0 = m_t[i]->vertex[i0];
            Vertex * v1 = m_t[i]->vertex[i1];
            
            //check if the edge already exits
            bool exists = false;
            for(unsigned k = 0; k< m_e.size(); k++)
            {
                if((m_e[k]->vertex[0] == v0 && m_e[k]->vertex[1] == v1) || (m_e[k]->vertex[1] == v0 && m_e[k]->vertex[0] == v1))//edge exists
                {
                    //printf("shared edge\n");
                    exists = true;
                    //check if the edge's neighbours arn't full
                    if(m_e[k]->neighbourTriangle[0] != NULL && m_e[k]->neighbourTriangle[1] != NULL)
                    {
                        printf("subdiv ERROR: mesh contains an edge with more than 2 neighbour triangles\n");//gtfo
                        return 1;
                    }
                    //hook the triangle to the edge
                    if(m_e[k]->neighbourTriangle[0] == NULL)
                        m_e[k]->neighbourTriangle[0] = m_t[i];
                    else
                        m_e[k]->neighbourTriangle[1] = m_t[i];
                    
                    //hook the edge to the triangle
                    m_t[i]->edge[j] = m_e[k];
                    break;//and we're done
                }
            }
            
            if(exists)//edge exists so nothing left to do 
            {
                continue;
            }
            else //edge does not exist so we need to create it
            {
                Edge * e = new Edge();
                //hook the triangle to the edge
                e->neighbourTriangle[0] = m_t[i];//hook the triangle to the edge
                e->neighbourTriangle[1] = NULL;
                e->vertex[0] = v0;
                e->vertex[1] = v1;
                m_t[i]->edge[j] = e;
                m_e.push_back(e);
                //hook the edge to the triangle
            }
        }
    }
    return 0;//jolly good
}


void Subdiv::genVertexNeighbours(std::vector<Triangle>* _t)
{
    
}


