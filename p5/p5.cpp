/* Project 5 by Andy Hansen
 * 5/1/20
 *
 * This is a simple program that takes 2 files containing nodes and edges of a map, and outputs various
 * traversals of the graph
 */


#define _DEBUG_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class MyNode
{
public:
    MyNode(char ID, int delay)
        : _id(ID), _delay(delay)
    {
        #ifdef _DEBUG_
            std::cout << "Node constructor called with ID " << ID << " and delay " << delay << std::endl;
        #endif
    }
    int Delay()
    {
        return _delay;
    }
    char ID()
    {
        return _id;
    }

private:
    char _id;
    int _delay;
};

class MyEdge
{
public:
    MyEdge(MyNode* origin, MyNode* destination, int length, int speed)
        : _length(length), _speed(speed)
    {
        _origin = origin;
        _destination = destination;

        #ifdef _DEBUG_
            std::cout << "Edge constructor called from " << origin->ID() << " to " << destination->ID() << " with length " << length << " and speed " << speed << std::endl;
        #endif
    }
    char OriginID()
    {
        return _origin->ID();
    }
    char DestinationID()
    {
        return _destination->ID();
    }
    int Length()
    {
        return _length;
    }
    int Speed()
    {
        return _speed;
    }

private:
    MyNode* _origin;
    MyNode* _destination;

    int _length = 0;
    int _speed = 0;
};

class MyGraph
{
public:
    MyGraph()
    {
        #ifdef _DEBUG_
            std::cout << "Graph constructor called." << std::endl;
        #endif
    }
    void Graph(std::string nodeFile, std::string edgeFile)
    {
        BuildNodes(nodeFile);
        PrintNodes();

        BuildEdges(edgeFile);
        PrintEdges();

        ShortestDistance();
        ShortestDelay();
        ShortestTravel();
        ShortestTime();
        FewestHops();
    }

private:
    bool _edgesRead = false;
    bool _nodesRead = false;

    MyNode* _nodes[5000];
    int _nodeCount = 0;

    MyEdge* _edges[5000];
    int _edgeCount = 0;

    void BuildNodes(std::string nodeFile)
    {
        #ifdef _DEBUG_
            std::cout << "Function BuildNodes() called." << std::endl;
        #endif

        std::fstream file;
        std::string tmp, line;

        file.open(nodeFile);

        if(!file.is_open())
        {
            Warn("Node file could not be opened.");
            return;
        }

        while( getline(file, line) )
        {
            char letter;
            int delay;

            std::sscanf(line.c_str(), "%c %d", &letter, &delay);

            MyNode* node = new MyNode(letter, delay);

            _nodes[_nodeCount] = node;
            _nodeCount++;
                    
            #ifdef _DEBUG_
                std::cout << "\tBuild created node " << letter << " with delay " << delay << std::endl;
            #endif
        }

        _nodesRead = true;
    }

    void BuildEdges(std::string edgeFile)
    {
        #ifdef _DEBUG_
            std::cout << "Function BuildEdges() called." << std::endl;
        #endif

        std::fstream file;
        std::string tmp, line;

        file.open(edgeFile);

        if(!file.is_open())
        {
            Warn("Edge file could not be opened.");
            return;
        }

        while( getline(file, line) )
        {
            char origin, destination;
            int length, speed;

            std::sscanf(line.c_str(), "%c %c %d %d", &origin, &destination, &length, &speed);

            MyEdge* edge = new MyEdge(Locate(origin), Locate(destination), length, speed);

            _edges[_edgeCount] = edge;
            _edgeCount++;

                    
            #ifdef _DEBUG_
                std::cout << "\tBuild created edge from " << origin << " to " << destination << " with length " << length << " and speed " << speed << std::endl;
            #endif
        }
    }

    void ShortestDistance()
    {

    }
    void ShortestDelay()
    {

    }
    void ShortestTravel()
    {

    }
    void ShortestTime()
    {

    }
    void FewestHops()
    {

    }

    MyNode* Locate(char ID)
    {
        for(int i = 0; i < _nodeCount; i++)
        {
            if(_nodes[i]->ID() == ID) return _nodes[i];
        }
        return NULL;
    }

    void PrintNodes()
    {
        for(int i = 0; i < _nodeCount; i++)
        {
            std::cout << _nodes[i]->ID() << '\t' << _nodes[i]->Delay() << std::endl;
        }
        return;
    }

    void PrintEdges()
    {
        for(int i = 0; i < _edgeCount; i++)
        {
            std::cout << _edges[i]->OriginID() << '\t' <<_edges[i]->DestinationID() << '\t' << _edges[i]->Length() << '\t' << _edges[i]->Speed() << std::endl;
        }
        return;
    }

    void Warn(std::string message)
    {
        std::cout << message << std::endl;
        return;
    }
};

int main(int argc, char** argv)
{
    MyGraph* g = new MyGraph();
    g->Graph(std::string(argv[1]), std::string(argv[2]));

    return 0;
}