/*
 * Dictionary.cpp
 *
 * Copyright (c) 2009 Jonathan Beck All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdlib.h>
#include <plist/Dictionary.h>

namespace PList
{

Dictionary::Dictionary(Node* parent) : Structure(PLIST_DICT, parent)
{
}

Dictionary::Dictionary(plist_t node, Node* parent) : Structure(parent)
{
    _node = node;
    plist_dict_iter it = NULL;

    char* key = NULL;
    plist_t subnode = NULL;
    plist_dict_new_iter(_node, &it);
    plist_dict_next_item(_node, it, &key, &subnode);
    while (subnode)
    {
        _map[std::string(key)] = Node::FromPlist(subnode, this);

        subnode = NULL;
        free(key);
        key = NULL;
        plist_dict_next_item(_node, it, &key, &subnode);
    }
    free(it);
}

Dictionary::Dictionary(PList::Dictionary& d) : Structure()
{
    for (Dictionary::iterator it = _map.begin(); it != _map.end(); it++)
    {
        plist_free(it->second->GetPlist());
        delete it->second;
    }
    _map.clear();

    _node = plist_copy(d.GetPlist());
    plist_dict_iter it = NULL;

    char* key = NULL;
    plist_t subnode = NULL;
    plist_dict_new_iter(_node, &it);
    plist_dict_next_item(_node, it, &key, &subnode);
    while (subnode)
    {
        _map[std::string(key)] = Node::FromPlist(subnode, this);

        subnode = NULL;
        free(key);
        key = NULL;
        plist_dict_next_item(_node, it, &key, &subnode);
    }
    free(it);
}

Dictionary& Dictionary::operator=(PList::Dictionary& d)
{
    for (Dictionary::iterator it = _map.begin(); it != _map.end(); it++)
    {
        plist_free(it->second->GetPlist());
        delete it->second;
    }
    _map.clear();

    _node = plist_copy(d.GetPlist());
    plist_dict_iter it = NULL;

    char* key = NULL;
    plist_t subnode = NULL;
    plist_dict_new_iter(_node, &it);
    plist_dict_next_item(_node, it, &key, &subnode);
    while (subnode && key)
    {
        _map[std::string(key)] = Node::FromPlist(subnode, this);

        subnode = NULL;
        free(key);
        key = NULL;
        plist_dict_next_item(_node, it, &key, &subnode);
    }
    free(it);
    return *this;
}

Dictionary::~Dictionary()
{
    for (Dictionary::iterator it = _map.begin(); it != _map.end(); it++)
    {
        delete it->second;
    }
    _map.clear();
}

Node* Dictionary::Clone()
{
    return new Dictionary(*this);
}

Node* Dictionary::operator[](const std::string& key)
{
    return _map[key];
}

Dictionary::iterator Dictionary::Begin()
{
    return _map.begin();
}

Dictionary::iterator Dictionary::End()
{
    return _map.end();
}

Dictionary::iterator Dictionary::Find(const std::string& key)
{
    return _map.find(key);
}

Dictionary::iterator Dictionary::Insert(const std::string& key, Node* node)
{
    if (node)
    {
        Node* clone = node->Clone();
        if (clone != NULL)
        {
            UpdateNodeParent(clone);
            plist_dict_insert_item(_node, key.c_str(), clone->GetPlist());
            delete _map[key];
            _map[key] = clone;
            return _map.find(key);
        }
    }
    return iterator(NULL);
}

void Dictionary::Remove(Node* node)
{
    if (node)
    {
        char* key = NULL;
        plist_dict_get_item_key(node->GetPlist(), &key);
        plist_dict_remove_item(_node, key);
        std::string skey = key;
        free(key);
        _map.erase(skey);
        delete node;
    }
}

void Dictionary::Remove(const std::string& key)
{
    plist_dict_remove_item(_node, key.c_str());
    delete _map[key];
    _map.erase(key);
}

std::string Dictionary::GetNodeKey(Node* node)
{
    for (iterator it = _map.begin(); it != _map.end(); ++it)
    {
        if (it->second == node)
            return it->first;
    }
    return "";
}

};
