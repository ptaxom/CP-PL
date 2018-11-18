#include <stdexcept>
#include "tree.h"

namespace tree
{
	int destroy_count = 0;

	Tree::Tree(std::initializer_list<std::pair<int, int>>&& list)
	{
		for (auto& item : list)
		{
			SetValue(item.first, item.second);
		}
	}
	void Tree::SetValue(int key, int value)
	{
		auto& ptr = Find(key);
		if (!ptr.Empty())
		{
			ptr->data.second = value;
		}
		else
		{
			ptr = new TreeNode(key, value);
			++count_;
		}
	}
	int & Tree::operator[](int key)
	{
		auto& ptr = Find(key);
		if (ptr.Empty())
		{
			ptr = new TreeNode(key);
			++count_;
		}
		return ptr->data.second;
	}
	int & Tree::at(int key)
	{
		auto& ptr = Find(key);
		if (ptr.Empty()) throw std::range_error("Invalid key");
		return ptr->data.second;
	}
	int Tree::at(int key) const
	{
		auto& ptr = Find(key);
		if (ptr.Empty()) throw std::range_error("Invalid key");
		return ptr->data.second;
	}
}

