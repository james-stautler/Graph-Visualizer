
#include <gtest/gtest.h>
#include "../src/Edge.cpp"

TEST(Edge_Tests, Edge_Creation_Tests) {

    Edge unidirectional_edge = Edge(0, 1, false);
    Edge bidirectional_edge = Edge(2, 3, 4, true);

    ASSERT_EQ(unidirectional_edge.getSrc(), 0);
    ASSERT_EQ(unidirectional_edge.getDst(), 1);
    ASSERT_EQ(unidirectional_edge.getWeight(), 1);
    ASSERT_FALSE(unidirectional_edge.isBidirectional());

    ASSERT_EQ(bidirectional_edge.getSrc(), 2);
    ASSERT_EQ(bidirectional_edge.getDst(), 3);
    ASSERT_EQ(bidirectional_edge.getWeight(), 4);
    ASSERT_TRUE(bidirectional_edge.isBidirectional());

    unidirectional_edge.setSource(10);
    unidirectional_edge.setDestination(11);
    unidirectional_edge.setWeight(12);
    unidirectional_edge.setBidirectional(true);

    ASSERT_EQ(unidirectional_edge.getSrc(), 10);
    ASSERT_EQ(unidirectional_edge.getDst(), 11);
    ASSERT_EQ(unidirectional_edge.getWeight(), 12);
    ASSERT_TRUE(unidirectional_edge.isBidirectional());

}

TEST(Edge_Tests, Edge_Equality_Tests) {

    Edge edge1 = Edge(0, 1, false);
    Edge edge2 = Edge(0, 1 , false);

    ASSERT_TRUE(edge1 == edge2);

    Edge edge3 = Edge(2, 3, false);

    ASSERT_FALSE(edge1 == edge3);

    Edge edge4 = Edge(0, 1, 2, false);

    ASSERT_FALSE(edge1 == edge4);

    Edge edge5 = Edge(0, 1, true);

    ASSERT_FALSE(edge1 == edge5);
}
