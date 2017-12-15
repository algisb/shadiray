#ifndef SUBDIV_H_
#define SUBDIV_H_
#include "kep/Core.h"
#include <vector>
namespace kelp
{
    struct Vertex
    {
        kep::Vector3 position;
        std::vector<Vertex *> neighbours;//verticies that connect to this vertex
        inline void dump()
        {
            printf("vertex pos: ");
            position.dump();
            printf("    neighbouring vertices:\n");
            for(int i = 0; i<neighbours.size(); i++)
            {
                neighbours[i]->dump();
            }
        }
        inline void dumpLoc()
        {
            printf("vertex locs: \n");
            printf("    %llu\n", this);
        }
    };
    struct Triangle;
    struct Edge
    {
        Vertex * vertex[2];//verticies that make up the edge
        Triangle * neighbourTriangle[2];// triangles that share the edge
        Edge()
        {
            for(unsigned i = 0; i<2; i++)
            {
                vertex[i] = NULL;
                neighbourTriangle[i] = NULL;   
            }
        }
    };
    struct Triangle
    {
        
        Vertex * vertex[3];
        Edge * edge[3];
        
        Triangle()
        {
            for(unsigned i = 0; i<3; i++)
            {
                vertex[i] = NULL;
                edge[i] = NULL;
            }
        }
        inline void dumpVertexLocs()
        {
            printf("triangle vertex locs: \n");
            for(unsigned i = 0; i<3; i++)
                printf("    %llu\n",vertex[i]);
                
        }
    };
    
    class Subdiv
    {
    public:
        std::vector<Vertex*> m_v;
        std::vector<Triangle*> m_t;
        std::vector<Edge*> m_e;
        Subdiv(float * _vertexSoup, uint64_t _numVertex);
        ~Subdiv();
        void allocToLocalStructure(float * _vertexSoup, uint64_t _numVertex, std::vector<Vertex> * _v, std::vector<Triangle> * _t);
        void indexVerticies(std::vector<Triangle> * _t);
        int genEdges();
        void genVertexNeighbours(std::vector<Triangle> * _t);
        
    };
};
#endif //SUBDIV_H_
