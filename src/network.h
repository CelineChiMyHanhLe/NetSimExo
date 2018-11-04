#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <map>

/*!
  This is a network of nodes with bidirectional links: if <b>(a, b)</b> is a link then <b>(b, a)</b> is also a link.

  Each node supports a *double* value, and the list of nodes is in fact defined by the list of their values.
 */

class Network {

public:
    Network() {}

/*! 
    Resizes the list of nodes (\ref values) and also resets all values.
    After this function is called \ref values has size *n* and contains random numbers (normal distribution, mean=0, sd=1).
 */
    void resize(const size_t &n);
/*! 
  Adds a bidirectional link between two nodes
  @param[in] a,b the indexes if the two nodes 
  @param[out] success the link was succesfully inserted (true if both nodes exist and the link did not exist yet)
 */
    bool add_link(const size_t& a, const size_t& b);
/*! Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes (randomly chosen),
  where *degree(n)* is Poisson-distributed.

  All previous links are erased first.
  @param[in] mean_deg the average of the Poisson distribution,
  @param[out] number of links created.
 */
    size_t random_connect(const double& mean);
/*! Resets node values with a vector of *n* new values.
  If the current size is *s* and *n<s* then only the first *n* values are changed.
  If *n>s* then only *s* values are used. 
  The internal \ref values vector keeps the same size.

  @param[in] vector of new node values,
  @param[out] number of nodes succesfully reset.
 */
    size_t set_values(const std::vector<double>& vec);
/*! Number of nodes */
    size_t size() const;
/*! Degree (number of links) of node no *n* */
    size_t degree(const size_t &_n) const;
/*! Value of node no *n* */
    double value(const size_t &_n) const;
/*! All node values in descending order.
    \ref values is left unchanged by this operation.
 */
    std::vector<double> sorted_values() const;
/*! All neighbors (linked) nodes of node no *n* */
    std::vector<size_t> neighbors(const size_t& nb) const;
    
    ///return true if the two vectors v1 and v2 have the same size
    bool same_size(const std::vector<double> v1, const std::vector<double> v2) const;

private:
    std::vector<double> values;
    std::multimap<size_t, size_t> links;

};

#endif
