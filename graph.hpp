#pragma once
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>

namespace strukdat
{

  template <typename VertexType>
  class graph
  {
    using list_type = std::unordered_set<VertexType>;
    using adj_list_type = std::unordered_map<VertexType, list_type>;

    graph() {}

    void add_vertex(const VertexType &val)
    {
      _adj_list.insert(std::make_pair(val, list_type()));
    }

    void remove_vertex(const VertexType &val)
    {
     
      if (_adj_list.find(val) == _adj_list.end())
      {
        return;
      }
      _adj_list.erase(val);
      for (int i = 1; i < _adj_list.size(); ++i)
      {
        if (_adj_list.find(val) != _adj_list.end())
        {
          _adj_list.erase(val);
        }
      }
    }

    void add_edge(const VertexType &val1, const VertexType val2)
    {
     
      if (_adj_list.at(val1).find(val2) == _adj_list.at(val1).end())
        _adj_list.at(val1).insert(val2);
      if (_adj_list.at(val2).find(val1) == _adj_list.at(val2).end())
        _adj_list.at(val2).insert(val1);
    }

    void remove_edge(const VertexType &val1, const VertexType &val2)
    {
     
      if (_adj_list.at(val1).find(val2) != _adj_list.at(val1).end())
        _adj_list.at(val1).erase(val2);
      if (_adj_list.at(val2).find(val1) != _adj_list.at(val2).end())
        _adj_list.at(val2).erase(val1);
    }

    size_t order() const
    {
     
      return _adj_list.size();
    }

    bool is_edge(const VertexType &val1, const VertexType &val2) const
    {
     
      return (_adj_list.at(val1).find(val2) != _adj_list.at(val1).end() && _adj_list.at(val2).find(val1) != _adj_list.at(val2).end());
    }

    void bfs(const VertexType &root,
             std::function<void(const VertexType &)> func) const
    {
     
      std::unordered_map<VertexType, bool> visited;
      for (auto &it : _adj_list)
      {
        visited.insert(std::make_pair(it.first, false));
      }
      std::queue<VertexType> q;
      visited[root] = true;
      q.push(root);
      while (!q.empty())
      {
        VertexType temp = q.front();
        func(temp);
        q.pop();
        for (auto it : _adj_list.at(temp))
        {
          if (!visited[it])
          {
            visited[it] = true;
            q.push(it);
          }
        }
      }
    }

    void dfs(const VertexType &root,
             std::function<void(const VertexType &)> func) const
    {
     
      std::unordered_map<VertexType, bool> visited;
      for (auto &it : _adj_list)
      {
        visited.insert(std::make_pair(it.first, false));
      }
      std::stack<VertexType> s;
      s.push(root);
      while (!s.empty())
      {
        VertexType temp = s.top();
        s.pop();
        if (!visited[temp])
        {
          func(temp);
          visited[temp] = true;
        }
        for (auto &it : _adj_list.at(temp))
        {
          if (!visited[it])
          {
            s.push(it);
          }
        }
      }
    }

    adj_list_type _adj_list;
  };
} 
