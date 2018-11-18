#ifndef TREE_H
#define TREE_H
#pragma once

#include <utility>
#include "smart_ptr.h"

namespace tree
{
	extern int destroy_count;

	struct TreeNode
	{
		TreeNode()
		{}
		TreeNode(int key, int value = 0) :
			data(key,value)
		{};

		~TreeNode()
		{
			++destroy_count;
		}

		std::pair<int, int> data = {0,0};

		SmartPtr<TreeNode> left;
		SmartPtr<TreeNode> rigth;
	};

	class Tree
	{
	public:
		Tree() : 
			count_{0}
		{}
		Tree(std::initializer_list<std::pair<int, int>>&& list);
		
		void SetValue(int key, int value);
		int& operator[](int key);
		int& at(int key);
		int at(int key) const;

		int size() const
		{
			return count_;
		}
		bool empty() const
		{
			return count_ == 0;
		}

		int& root()
		{
			if (root_.Empty())throw std::range_error("Getting value from empty tree");
			return (*root_).data.first;
		}
		int root() const
		{
			if (root_.Empty())throw std::range_error("Getting value from empty tree");
			return (*root_).data.first;
		}


	private:
		const SmartPtr<TreeNode> & Find(int key) const
		{
			return Find(root_, key);
		}
		SmartPtr<TreeNode> & Find(int key)
		{
			return Find(root_, key);
		}
		template<typename Ptr>
		static Ptr& Find(Ptr& root, int key)
		{
			if (root.Empty()) return root;
			if (root->data.first == key) return root;
			if (key > root->data.first) return Find(root->rigth,key);
			return Find(root->left,key);
		}

		int count_;
		SmartPtr<TreeNode> root_;
	};
}

#endif
