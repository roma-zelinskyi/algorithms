/**
 *  Project Data Structure
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <memory>
#include <optional>
#include <stdexcept>
#include <unordered_map>

namespace zee {

template<class _Key>
concept IterableKey = requires(_Key key)
{
    typename _Key::iterator::value_type;
    key.begin();
    key.end();
};

template<IterableKey _Key, class _Value>
class Trie
{
    struct Node
    {
        Node()
            : value{std::nullopt}
            , paths{}
        {
            paths.reserve(5);
        }

        std::optional<_Value> value;
        std::unordered_map<typename _Key::iterator::value_type, std::shared_ptr<Node>> paths;
    };

public:
    Trie()
        : _root{std::make_shared<Node>()}
    {
    }

    void insert(const _Key& key, const _Value& value)
    {
        auto node = _root;
        for (auto& it : key) {
            if (!node->paths.contains(it))
                node->paths[it] = std::make_shared<Node>();

            node = node->paths.at(it);
        }
        node->value = value;
    }

    bool contains(const _Key& key)
    {
        auto node = _root;
        for (const auto& it : key) {
            if (!node->paths.contains(it))
                return false;

            node = node->paths.at(it);
        }

        return true;
    }

    void erase(const _Key& key)
    {
        eraseRec(_root, key.begin(), key.end());
    }

private:
    void eraseRec(
        std::shared_ptr<Node> cur,
        _Key::const_iterator it,
        const _Key::const_iterator& end)
    {
        if (it == end)
            return;

        if (!cur->paths.contains(*it))
            throw std::invalid_argument{"No such key exist."};

        auto next = cur->paths.at(*it);
        eraseRec(next, std::next(it), end);

        if (next->paths.empty())
            cur->paths.erase(*it);
        else if (std::next(it) == end)
            next->value.reset();
    }

private:
    std::shared_ptr<Node> _root;
};

} // namespace zee
