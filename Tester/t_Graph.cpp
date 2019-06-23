#include <gtest/gtest.h>

#include <GEdge.hpp>
#include <GNode.hpp>
#include <Graph.hpp>

TEST(GNode, init)
{
    GNode<double, double> node;

    node.key = 0.1;
    node = 1.2;
    EXPECT_EQ(1.2, node.key);

    double value = node;
    EXPECT_EQ(1.2, value);

    double &value2 = node;
    value2 = 3.3;
    EXPECT_EQ(3.3, node);

    GNode<double, double> const node1(3.1);
    double const &value3 = node1;
    EXPECT_EQ(3.1, value3);
}

TEST(GEdge, init)
{
    GEdge<double, double> edge;

    edge.key = 0.1;
    edge = 1.2;
    EXPECT_EQ(1.2, edge.key);

    double value = edge;
    EXPECT_EQ(1.2, value);

    double &value2 = edge;
    value2 = 3.3;
    EXPECT_EQ(3.3, edge);

    GEdge<double, double> const edge1(3.1);
    double const &value3 = edge1;
    EXPECT_EQ(3.1, value3);
}

TEST(Graph, init)
{
    int no = 10;
    Graph<double, double> *graph;
    
    graph = new Graph<double, double>;
    EXPECT_EQ(0, graph->num_nodes());
    EXPECT_EQ(0, graph->num_edges());
    for (int i = 0; i < no; i++)
        graph->add_node(i + 0.1);
    for (int i = 0; i < no; i++)
        EXPECT_EQ(i + 0.1, graph->nodes[i]->key);
    delete graph;

    graph = new Graph<double, double>(no);
    EXPECT_EQ(no, graph->num_nodes());
    EXPECT_EQ(0, graph->num_edges());
    for (int i = 0; i < no; i++) {
        *(graph->nodes[i]) = i + 0.1;
        EXPECT_EQ(i + 0.1, graph->nodes[i]->key);
        EXPECT_EQ(0, graph->nodes[i]->degree_out());
        EXPECT_EQ(0, graph->nodes[i]->degree_in());
    }

    graph->add_edge(graph->nodes[0], graph->nodes[1], 1);
    EXPECT_EQ(1, graph->num_edges());
    EXPECT_EQ(1, graph->nodes[0]->degree_out());
    EXPECT_EQ(1, graph->nodes[1]->degree_in());
    EXPECT_EQ(1, graph->edges[0]->key);

    graph->remove_edge(graph->edges[0]);
    EXPECT_EQ(0, graph->num_edges());
    EXPECT_EQ(0, graph->nodes[0]->degree_out());
    EXPECT_EQ(0, graph->nodes[1]->degree_in());
 
    graph->add_edge(graph->nodes[2], graph->nodes[1], 1);
    EXPECT_EQ(1, graph->num_edges());
    EXPECT_EQ(1, graph->nodes[2]->degree_out());
    EXPECT_EQ(1, graph->nodes[1]->degree_in());
    EXPECT_EQ(1, graph->edges[0]->key);

    graph->remove_node(graph->nodes[2]);
    EXPECT_EQ(no - 1, graph->num_nodes());
    EXPECT_EQ(0, graph->num_edges());
    EXPECT_EQ(0, graph->nodes[1]->degree_in());


    delete graph;
}


