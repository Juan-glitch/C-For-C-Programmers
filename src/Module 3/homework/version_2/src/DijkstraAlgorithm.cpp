#include "DijkstraAlgorithm.h"

using namespace std;

Point::Point() = default;

Point::Point(char n, float d) : node(n), distance(d) {}

/**
 * @brief Class representing a point (node) in a graph.
 *
 * A Point holds a node identifier and the current accumulated distance (cost) to get there.
 */
class Point
{
public:
    char node;      ///< Identifier of the node.
    float distance; ///< Distance from the starting node.

    /**
     * @brief Default constructor.
     *
     * Creates a Point with a blank node (' ') and zero distance.
     */
    Point() : node(' '), distance(0.0) {}

    /**
     * @brief Parameterized constructor.
     *
     * @param n The identifier of the node.
     * @param d The distance (cost) associated with this node.
     */
    Point(char n, float d) : node(n), distance(d) {}

    /**
     * @brief Overloads the addition operator.
     *
     * Although not essential for Dijkstra, this operator lets you add the distances of two points.
     * @param other Another Point object.
     * @return A new Point with the same node and the sum of the distances.
     */
    Point operator+(const Point &other) const
    {
        return Point(node, distance + other.distance);
    }

    /**
     * @brief Overloaded input operator.
     *
     * Allows formatted input for a Point.
     * @param is Input stream.
     * @param p Point object to fill.
     * @return Reference to the input stream.
     */
    friend istream &operator>>(istream &is, Point &p)
    {
        cout << "Enter the node (character): ";
        is >> p.node;
        cout << "Enter the distance (floating point number): ";
        is >> p.distance;
        return is;
    }

    /**
     * @brief Overloaded output operator.
     *
     * Allows formatted output of a Point.
     * @param os Output stream.
     * @param p Point object to print.
     * @return Reference to the output stream.
     */
    friend ostream &operator<<(ostream &os, const Point &p)
    {
        os << "Node: " << p.node << ", Distance: " << p.distance;
        return os;
    }
};