#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H

#include "Graph.h"
#include <vector>
#include <stack>
#include <queue>
#include <math.h>
#include "PriorityQueue.h"

class mycomparison
{
    public:
      mycomparison() {}
      bool operator() (const std::pair<double,int>& lhs, const std::pair<double,int>&rhs) const {return (lhs.first>rhs.first);}
};


class GraphSearch
{
    public:

        GraphSearch(SparseDirectedGraph* graph, int source, int target, int search):m_Graph(graph),m_iSource(source),m_iTarget(target),m_bFound(false),
                    m_Visited(m_Graph->Size(), unvisited),m_Route(m_Graph->Size(), no_parent_assigned),
                    m_CostToThisNode(m_Graph->Size(),-1),m_FCost(m_Graph->Size(),-1)
        {
            switch(search)
            {
                case 0:
                   Search(true);
                break;

                case 1:
                   Search(false);
                break;

                case 2:
                   SearchD();
                break;
            }

        }
        virtual ~GraphSearch() {}

        bool Found() {return m_bFound;}
        std::vector<int> Route() {return m_Route;};
        SparseDirectedGraph* GetGraph() { return m_Graph;};

    protected:

    private:

        enum {visited, unvisited, no_parent_assigned=-1};
        SparseDirectedGraph* m_Graph; //a reference to the graph to be searched
        std::vector<int> m_Visited; //this records the indexes of all the nodes that are visited
        std::vector<int> m_Route; //this holds the route taken to the target.
        int m_iSource; //the source and target node indices
        int m_iTarget;
        bool m_bFound; //true if a path to the target has been found

        std::vector<double> m_CostToThisNode; //minimal cost to go to a specific node
        std::vector<double> m_FCost;

        //this method performs the DFS search
        void Search(bool bDFS)
        {
            //create a std stack of pointers to edges
            std::list<GraphEdge*> list;

            //create a dummy edge and put on the stack
            GraphEdge Dummy(m_iSource, m_iSource,0);
            list.push_back(&Dummy);

            //while there are edges on the stack keep searching
            while (!list.empty())
            {
                //grab the next edge
                GraphEdge* Next = list.back();

                //remove the edge from the stack
                list.pop_back();

                if(m_Visited[Next->To()]!=visited){

                //make a note of the parent of the node this edge points to
                m_Route[Next->To()] = Next->From();

                //and mark it visited
                m_Visited[Next->To()] = visited;

                //if the target has been found the method can return success
                if (Next->To() == m_iTarget)
                    m_bFound=true;

                //push the edges leading from the node this edge points to onto
                //the stack (provided the edge does not point to a previously
                //visited node)
                for (std::list<GraphEdge*>::iterator it=m_Graph->GetEdge(Next->To())->begin(); it != m_Graph->GetEdge(Next->To())->end(); ++it)
                    if( m_Visited.at((*it)->To())!=visited)
                        {
                            if(!bDFS)
                                {list.push_front(*it);}
                            else {list.push_back(*it);}

                        }
            }}//while
        }

        void SearchD()
        {
            //create an indexed priority queue that sorts smallest to largest
            //(front to back). Note that the maximum number of elements the iPQ
            //may contain is Size(). This is because no node can be represented
            // on the queue more than once.
            IndexedPriorityQLow<double> pq(m_CostToThisNode, m_Graph->Size());
            //std::priority_queue<std::pair<double,int>,std::vector<std::pair<double,int> >,mycomparison> pq;

            //put the source node on the queue
            pq.insert(m_iSource);
            //pq.push(std::pair<double,int> (-1,m_iSource));
            m_Visited[m_iSource]=m_iSource;

            //while the queue is not empty
            while(!pq.empty())
            {
                //get the lowest cost node from the queue. Don't forget, the return value
                //is a *node index*, not the node itself. This node is the node not already
                //on the SPT that is the closest to the source node
                int NextClosestNode = pq.Pop();
                //int NextClosestNode = pq.top().second;
                //pq.pop();

                //move this edge from the search frontier to the shortest path tree
                m_Route[NextClosestNode] = m_Visited[NextClosestNode];

                //if the target has been found exit
                if (NextClosestNode == m_iTarget)
                    m_bFound=true;

                for (std::list<GraphEdge*>::iterator it=m_Graph->GetEdge(NextClosestNode)->begin(); it != m_Graph->GetEdge(NextClosestNode)->end(); ++it)
                //now to relax the edges. For each edge connected to the next closest node
                {
                    //calculate the heuristic cost from this node to the target (H)
                    double x= (m_iTarget%20)-((*it)->To()%20);
                    double y= (m_iTarget/20)-((*it)->To()/20);
                    double HCost = abs(x)+abs(y);//heuristic::Calculate(m_Graph, m_iTarget, pE->To());

                    //the total cost to the node this edge points to is the cost to the
                    //current node plus the cost of the edge connecting them.
                    double NewCost = m_CostToThisNode[NextClosestNode] + (*it)->Cost();

                    //if this edge has never been on the frontier make a note of the cost
                    //to reach the node it points to, then add the edge to the frontier
                    //and the destination node to the PQ.
                    if (m_Visited[(*it)->To()] == unvisited)
                    {
                        m_FCost[(*it)->To()] = NewCost + HCost;
                        m_CostToThisNode[(*it)->To()] = NewCost;

                        pq.insert((*it)->To());
                        //pq.push(std::pair<double,int> (NewCost + HCost,(*it)->To()));
                        m_Visited[(*it)->To()] = (*it)->From();
                    }

                    //else test to see if the cost to reach the destination node via the
                    //current node is cheaper than the cheapest cost found so far. If
                    //this path is cheaper we assign the new cost to the destination
                    //node, update its entry in the PQ to reflect the change, and add the
                    //edge to the frontier
                    else if ( (NewCost < m_CostToThisNode[(*it)->To()]) && (m_Route[(*it)->To()] == -1) )
                    {
                        m_FCost[(*it)->To()] = NewCost + HCost;
                        m_CostToThisNode[(*it)->To()] = NewCost;

                        //because the cost is less than it was previously, the PQ must be
                        //resorted to account for this.
                       // pq.ChangePriority((*it)->To());
                        m_Visited[(*it)->To()] = (*it)->From();
                    }

                }
            }
        }
};

#endif // GRAPHSEARCH_H
