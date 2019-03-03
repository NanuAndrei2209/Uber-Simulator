// Copyright [2018] <Nanu Andrei 313CA>

#ifndef LISTGRAPH_H__
#define LISTGRAPH_H__
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include "Hashtable.h"

template <typename T>struct Node {
    std::vector<T> neighbors;
};

template <typename T>class ListGraph {
 public:
    std::vector<Node<T>> nodes;
    int size;
    explicit ListGraph(int size) {
        this->size = size;
        nodes.resize(size);
    }

    ~ListGraph() {}

    void addEdge(T src, T dst) {
        nodes[src].neighbors.push_back(dst);
    }
    void removeEdge(T src, T dst) {
        for (auto it = nodes[src].neighbors.begin();
            it != nodes[src].neighbors.end(); ++it) {
            if (*it == dst) {
                nodes[src].neighbors.erase(it);
                break;
            }
        }
    }
    bool hasEdge(T src, T dst) {
        for (auto it = nodes[src].neighbors.begin();
            it != nodes[src].neighbors.end(); ++it) {
            if (*it == dst) {
                return true;
            }
        }
        return false;
    }
    std::vector<T> getNeighbors(T node) {
        return nodes[node].neighbors;
    }

    bool is_Path(int source, int dest) {
        std::vector<bool> vis(size, false);
        vis[source] = true;
        std::queue<T> q;
        q.push(source);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto it = nodes[v].neighbors.begin();
                it != nodes[v].neighbors.end(); it++) {
                    if (vis[*it] == false) {
                        vis[*it] = true;
                        q.push(*it);
                    }
            }
        }
        if (vis[dest]) {
          return true;
        }
        return false;
    }
    int distance(int source, int dest) {
      if (source == dest) {
        return 0;
      }
      std::vector<bool> vis(size, false);
      vis[source] = true;
      std::queue<T> q;
      q.push(source);
      std::vector<int> dist(size, 0);
      while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(auto it = nodes[v].neighbors.begin();
            it != nodes[v].neighbors.end(); ++it) {
                if (vis[*it] == false) {
                  vis[*it] = true;
                  q.push(*it);
                  dist[*it] = dist[v] + 1;
                }
        }
      }
      if (!vis[dest]) {
        return -1;
      }
      return dist[dest];
    }
    int getSize() {
        return size;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << i << "-";
            for (auto it = nodes[i].neighbors.begin();
                    it != nodes[i].neighbors.end(); it++) {
                std::cout << " " << *it;
            }
            std::cout << std::endl;
        }
    }
    int destination(Hashtable<std::string, int> *hash, ListGraph<int> *listT,
      std::string start, std::string end) {
      // returneaza nodul destinatie, chiar daca end poate nu este accesibil
      if (is_Path(hash->get(start), hash->get(end))) {
        return hash->get(end);
      }
      if (listT->nodes[hash->get(end)].neighbors.size() == 0) {
        return -1;
      }
      int nodDestinatie;
      int min = 1000000;
      for (unsigned int i = 0; i < listT->nodes[hash->get(end)].neighbors.size(); ++i) {
        if (is_Path(hash->get(start), listT->nodes[hash->get(end)].neighbors[i])) {
          if (min > distance(hash->get(start),
          listT->nodes[hash->get(end)].neighbors[i])) {
            min = distance(hash->get(start),
            listT->nodes[hash->get(end)].neighbors[i]);
            nodDestinatie = listT->nodes[hash->get(end)].neighbors[i];
          }
        }
      }
      return nodDestinatie;
    }
};

#endif  // __LISTGRAPH_H__
