/**
 *  Project Data Structure
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <memory>
#include <optional>
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
        auto node = _root;
        auto curNode = std::shared_ptr<Node>{nullptr};

        for (const auto& it : key) {
            if (!node->paths.contains(it))
                return;

            curNode = node->paths.at(it);

            if (curNode->paths.empty()) {
                node->paths.erase(it);
                return;
            }

            node = curNode;
        }

        if (curNode)
            curNode->value.reset();
    }

private:
    std::shared_ptr<Node> _root;
};

} // namespace zee
