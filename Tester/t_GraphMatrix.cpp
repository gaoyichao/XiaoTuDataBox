#include <gtest/gtest.h>

#include <GraphMatrix.hpp>

TEST(GraphMatrix, init)
{
    int no = 10;
    Graph<double, double> *graph;

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
    graph->add_edge(graph->nodes[0], graph->nodes[2], 2);
    graph->add_edge(graph->nodes[0], graph->nodes[3], 3);
    graph->add_edge(graph->nodes[4], graph->nodes[3], 4);
    graph->add_edge(graph->nodes[4], graph->nodes[5], 5);
    graph->add_edge(graph->nodes[6], graph->nodes[5], 6);
    graph->add_edge(graph->nodes[6], graph->nodes[7], 7);
    graph->add_edge(graph->nodes[6], graph->nodes[8], 8);
    graph->add_edge(graph->nodes[9], graph->nodes[8], 9);

    for (int i = 0; i < graph->num_edges(); i++) {
        std::cout << "[" << i << "]:" << *(graph->edges[i]) << std::endl;
    }

    GraphMatrix<double, double> *gmatrix = new GraphMatrix<double, double>(*graph);
    std::cout << *gmatrix << std::endl;

    graph->add_edge(graph->nodes[9], graph->nodes[0], 10);
    gmatrix->update();
    std::cout << *gmatrix << std::endl;

    delete graph;
    delete gmatrix;
}
