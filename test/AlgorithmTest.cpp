
#include <gtest/gtest.h>
#include "../src/Window.cpp"

TEST(Algorithm_Tests, BFS_TEST) {

    //const sf::Font font("../assets/swansea.ttf");
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
