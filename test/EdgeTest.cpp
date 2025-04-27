
#include <gtest/gtest.h>
#include "../src/Edge.cpp"

TEST(Edge_Tests, Edge_Creation_Tests) {

    Edge unidirectional_edge = Edge(0, 1, false);
    Edge bidirectional_edge = Edge(2, 3, 4, true);

    ASSERT_EQ(unidirectional_edge.getSrc(), 0);
    ASSERT_EQ(unidirectional_edge.getDst(), 1);
    ASSERT_EQ(unidirectional_edge.getWeight(), 1);
    ASSERT_EQ(unidirectional_edge.isBidirectional(), false);

    ASSERT_EQ(bidirectional_edge.getSrc(), 2);
    ASSERT_EQ(bidirectional_edge.getDst(), 3);
    ASSERT_EQ(bidirectional_edge.getWeight(), 4);
    ASSERT_EQ(bidirectional_edge.isBidirectional(), true);

    unidirectional_edge.setSource(10);
    unidirectional_edge.setDestination(11);
    unidirectional_edge.setWeight(12);
    unidirectional_edge.setBidirectional(true);

    ASSERT_EQ(unidirectional_edge.getSrc(), 10);
    ASSERT_EQ(unidirectional_edge.getDst(), 11);
    ASSERT_EQ(unidirectional_edge.getWeight(), 12);
    ASSERT_EQ(unidirectional_edge.isBidirectional(), true);

}

TEST(Edge_Tests, Edge_Equality_Tests) {

    Edge edge1 = Edge(0, 1, false);
    Edge edge2 = Edge(0, 1 , false);

    ASSERT_EQ(edge1 == edge2, true);

    Edge edge3 = Edge(2, 3, false);

    ASSERT_EQ(edge1 == edge3, false);

    Edge edge4 = Edge(0, 1, 2, false);

    ASSERT_EQ(edge1 == edge4, false);

    Edge edge5 = Edge(0, 1, true);

    ASSERT_EQ(edge1 == edge5, false);
}
