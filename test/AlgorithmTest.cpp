
#include <gtest/gtest.h>
#include "../src/Window.cpp"

TEST(Algorithm_Tests, BFS_TEST) {

    Window win = Window();

    win.addNode(Node(0, 100, 100, 10, 5, 1, sf::Color::White));
    win.addNode(Node(1, 200, 200, 10, 5, 1, sf::Color::White));
    win.addNode(Node(2, 300, 300, 10, 5, 1, sf::Color::White));
    win.addNode(Node(3, 400, 400, 10, 5, 1, sf::Color::White));
    win.addNode(Node(4, 500, 500, 10, 5, 1, sf::Color::White));

    win.edgeHandler(0, 1, true, sf::Color::White);
    win.edgeHandler(1, 2, true, sf::Color::White);
    win.edgeHandler(2, 3, true, sf::Color::White);
    win.edgeHandler(3, 4, true, sf::Color::White);

    ASSERT_TRUE(win.BFS(0, 4, 1, true));

    win.resetGraph(false);
    ASSERT_EQ(win.getGraph().getNodeMap().at(0).getPrev(), -1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(1).getPrev(), 0);
    ASSERT_EQ(win.getGraph().getNodeMap().at(2).getPrev(), 1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(3).getPrev(), 2);
    ASSERT_EQ(win.getGraph().getNodeMap().at(4).getPrev(), 3);

    win.resetGraph(true);
    ASSERT_EQ(win.getGraph().getNodeMap().at(0).getPrev(), -1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(1).getPrev(), -1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(2).getPrev(), -1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(3).getPrev(), -1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(4).getPrev(), -1);

    win.removeNode(2);
    ASSERT_FALSE(win.BFS(0, 4, 1, true));

}

TEST(Algorithm_Tests, DFS_TEST) {
    Window win = Window();

    win.addNode(Node(0, 100, 100, 10, 5, 1, sf::Color::White));
    win.addNode(Node(1, 200, 200, 10, 5, 1, sf::Color::White));
    win.addNode(Node(2, 300, 300, 10, 5, 1, sf::Color::White));
    win.addNode(Node(3, 400, 400, 10, 5, 1, sf::Color::White));
    win.addNode(Node(4, 500, 500, 10, 5, 1, sf::Color::White));
    win.addNode(Node(5, 600, 600, 10, 5, 1, sf::Color::White));

    win.edgeHandler(0, 1, true, sf::Color::White);
    win.edgeHandler(1, 2, true, sf::Color::White);
    win.edgeHandler(2, 3, true, sf::Color::White);
    win.edgeHandler(3, 4, true, sf::Color::White);
    win.edgeHandler(2,5, true, sf::Color::White);

    std::set<int> visited;
    ASSERT_TRUE(win.DFS(0, 0, 4, 1, visited, true));
    visited.clear();
    win.resetGraph(false);
    ASSERT_EQ(win.getGraph().getNodeMap().at(0).getPrev(), -1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(1).getPrev(), 0);
    ASSERT_EQ(win.getGraph().getNodeMap().at(2).getPrev(), 1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(3).getPrev(), 2);
    ASSERT_EQ(win.getGraph().getNodeMap().at(4).getPrev(), 3);
    ASSERT_EQ(win.getGraph().getNodeMap().at(5).getPrev(), -1);

    visited.clear();
    win.resetGraph(true);
    ASSERT_TRUE(win.DFS(0, 0, 5, 1, visited, true));
    ASSERT_EQ(win.getGraph().getNodeMap().at(0).getPrev(), -1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(1).getPrev(), 0);
    ASSERT_EQ(win.getGraph().getNodeMap().at(2).getPrev(), 1);
    ASSERT_EQ(win.getGraph().getNodeMap().at(3).getPrev(), 2);
    ASSERT_EQ(win.getGraph().getNodeMap().at(4).getPrev(), 3);
    ASSERT_EQ(win.getGraph().getNodeMap().at(5).getPrev(), 2);

    visited.clear();
    win.resetGraph(true);
    win.removeNode(2);
    ASSERT_FALSE(win.DFS(0, 0, 4, 1, visited, true));
}
