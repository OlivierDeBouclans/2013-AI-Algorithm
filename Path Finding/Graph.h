
/**----------------------------------------------------------------------
// @Class: Graph
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 3/11/13
//
// @Description: Graph representation class. Construct a sparse graph model
// with adjacency list (not matrix), to use with graph with a few connections
// between each nodes. This class has been created for path finding purposes.
// The nodes are represented with their index. If a node is deleted, its index
// is simply overlook, not actualy deleted. This is not suited for dynamic graph
// with multiple nodes adding or deleting.
//----------------------------------------------------------------------**/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>

/**----------------------------------------------------------------------
// @Class: Node
// @Description: Basic node representation.For more specific node just
// inherit this class.The node class don't check if the given index is valide
//----------------------------------------------------------------------**/
class GraphNode
{
    public:
        //Constructor
        GraphNode():m_iIndex(-1) {}
        GraphNode(int val):m_iIndex(val) {}

        //Destructor
        virtual ~GraphNode() {}

        //Get
        int Index() { return m_iIndex; }

        //Set
        void SetIndex(int val) { m_iIndex = val; }

    protected:
        int m_iIndex; //Index of the node (-1 is invalide)
};

/**----------------------------------------------------------------------
// @Class: Edge
// @Description: Basic edge representation.For more specific edge just
// inherit this class.
//----------------------------------------------------------------------**/
class GraphEdge
{
    public:
        //Constructor
        GraphEdge(int from, int to, double cost):m_iFrom(from),m_iTo(to),m_dCost(cost) {}
        GraphEdge(int from, int to):m_iFrom(from),m_iTo(to),m_dCost(1.0) {}
        GraphEdge():m_iFrom(-1),m_iTo(-1),m_dCost(1.0) {}
        //Destructor
        virtual ~GraphEdge() {}

        //Get
        double Cost() { return m_dCost; }
        int    From() { return m_iFrom; }
        int    To()   { return m_iTo;   }

        //Set
        double SetCost(double val)   { m_dCost = val; }
        int    SetFrom(int val)      { m_iFrom = val; }
        int    SetTo(int val)        { m_iTo   = val; }

    protected:
        int    m_iFrom; //Starting node's index
        int    m_iTo;   //Arriving node's index
        double m_dCost; //Edge's cost
};

/**----------------------------------------------------------------------
// @Class: Sparse graph
// @Description: Directed Graph representation using adjacency list.
//----------------------------------------------------------------------**/
class SparseDirectedGraph
{
    public:
    //Constructor
    SparseDirectedGraph():m_iNextNodeIndex(0) {}

   //Destructor
    ~SparseDirectedGraph()
    {
       //Delete all edge
       for (std::vector<std::list<GraphEdge*> >::iterator it=m_Edges.begin(); it != m_Edges.end(); it++)
            {
                for (std::list<GraphEdge*>::iterator itt=(*it).begin(); itt != (*it).end(); itt++)
                    delete (*itt);
                (*it).clear();
            }
        m_Edges.clear();

        //Delete all node
        for (std::vector<GraphNode*>::iterator it=m_Nodes.begin(); it != m_Nodes.end(); it++)
            delete (*it);
        m_Nodes.clear();
    }

    //Get
    int                    Size()                 { return m_iNextNodeIndex; } //returns the number of (active + inactive) nodes present in the graph
    GraphNode*             GetNode(int idx)       { return m_Nodes.at(idx);  } //return the node of given index (as the m_node vector is ordered by index)
    std::list<GraphEdge*>* GetEdge(int idx)       { return &m_Edges.at(idx); } //return the list of edges leaving from a given node

    GraphEdge*             GetEdge(int from, int to)                           //return the edge connecting 2 given nodes
    {
        for (std::list<GraphEdge*>::iterator it=m_Edges.at(from).begin(); it != m_Edges.at(from).end(); it++)
            if((*it)->To()==to)
                return (*it);

        std::cout << "No edge from " << from << " to " << to << "found" << std::endl;
        exit(1);
    }

    /**Other functions**/
    //Adds a node to the graph
    void AddNode(GraphNode *node)
    {
        node->SetIndex(m_iNextNodeIndex);
        m_Nodes.push_back(node);
        m_Edges.push_back(std::list<GraphEdge*>());

        m_iNextNodeIndex++;
    }

    //removes a node by setting its index to -1
    void RemoveNode(int idx) { m_Nodes.at(idx)->SetIndex(-1);}

    //Adds an edge to the graph
    void AddEdge(GraphEdge *edge) { m_Edges.at(edge->From()).push_front(edge); }

    //Remove an edge
    void RemoveEdge(int from, int to)
    {
        for (std::list<GraphEdge*>::iterator it=m_Edges.at(from).begin(); it != m_Edges.at(from).end(); it++)
            if((*it)->To()==to)
            {
                delete (*it);
                m_Edges.at(from).erase(it);
                break;
            }
    }

    private:
        //vector of the nodes within the graph; contain all the nodes added, even after being deleted
        std::vector<GraphNode*> m_Nodes;

        //adjacency list (sorted by node index); m_Edges.at(i) contain all the edge coming from the node of index i;
        //contain an empty adjacency list for deleted nodes
        std::vector<std::list<GraphEdge*> >  m_Edges;

        int m_iNextNodeIndex;  //index for the next node to add (therefore correspond to the size of m_Edges and m_Nodes)
};

#endif // GRAPH_H
