
#include "../src/Graph.cpp"
#include <gtest/gtest.h>

TEST(Graph_Tests, Graph_Creation_Tests) {
    Graph graph = Graph();

    Node node1 = Node(1, 10, 10, 10, 5, 1, sf::Color::White);
    Node node2 = Node(2, 20, 20, 10, 5, 1, sf::Color::White);
    Node node3 = Node(3, 30, 30, 10, 5, 1, sf::Color::White);
    Node node4 = Node(4, 40, 40, 10, 5, 1, sf::Color::White);
    Node node5 = Node(5, 50, 50, 10, 5, 1, sf::Color::White);

    graph.addNode(node1);
    graph.addNode(node2);
    graph.addNode(node3);
    graph.addNode(node4);
    graph.addNode(node5);

    ASSERT_TRUE(graph.getNodeMap().at(1) == node1);
    ASSERT_TRUE(graph.getNodeMap().at(2) == node2);
    ASSERT_TRUE(graph.getNodeMap().at(3) == node3);
    ASSERT_TRUE(graph.getNodeMap().at(4) == node4);
    ASSERT_TRUE(graph.getNodeMap().at(5) == node5);
    ASSERT_TRUE(graph.getNodeMap().size() == 5);

    graph.removeNode(2);
    graph.removeNode(1);

    ASSERT_EQ(graph.getNodeMap().size(), 3);
}

TEST(Graph_Tests, Graph_Edges_Tests) {
    Graph graph = Graph();

    Node node1 = Node(1, 10, 10, 10, 5, 1, sf::Color::White);
    Node node2 = Node(2, 20, 20, 10, 5, 1, sf::Color::White);
    Node node3 = Node(3, 30, 30, 10, 5, 1, sf::Color::White);
    Node node4 = Node(4, 40, 40, 10, 5, 1, sf::Color::White);
    Node node5 = Node(5, 50, 50, 10, 5, 1, sf::Color::White);

    graph.addNode(node1);
    graph.addNode(node2);
    graph.addNode(node3);
    graph.addNode(node4);
    graph.addNode(node5);

    ASSERT_TRUE(graph.addEdge(1, 2, true, sf::Color::White));
    ASSERT_EQ(graph.getEdges().size(), 2);
    ASSERT_EQ(graph.getAdjMap().at(1).size(), 1);
    ASSERT_EQ(graph.getAdjMap().at(2).size(), 1);
    ASSERT_TRUE(graph.checkIfEdgeExists(1, 2));
    ASSERT_FALSE(graph.checkIfEdgeExists(1, 5));

    graph.addEdge(3, 2, false, sf::Color::White);
    ASSERT_EQ(graph.getEdges().size(), 3);
    ASSERT_EQ(graph.getAdjMap().at(2).size(), 1);
    ASSERT_EQ(graph.getAdjMap().at(3).size(), 1);

    graph.addEdge(4, 2, false, sf::Color::White);
    graph.addEdge(5, 2, true, sf::Color::White);
    ASSERT_EQ(graph.getEdges().size(), 6);
    ASSERT_EQ(graph.getAdjMap().at(2).size(), 2);

    graph.removeNode(2);
    ASSERT_EQ(graph.getAdjMap().at(3).size(), 0);
    graph.addEdge(1, 3, true, sf::Color::White);
    ASSERT_EQ(graph.getEdges().size(), 2);
    ASSERT_EQ(graph.getAdjMap().at(3).size(), 1);
    ASSERT_EQ(graph.getAdjMap().find(2), graph.getAdjMap().end());
    graph.addNode(node2);

    graph.removeEdge(1, 3);
    ASSERT_EQ(graph.getEdges().size(), 0);

    graph.addEdge(1, 2, true, sf::Color::White);
    ASSERT_EQ(graph.getEdges().size(), 2);
    graph.removeEdge(2, 1);
    ASSERT_EQ(graph.getEdges().size(), 0);
}