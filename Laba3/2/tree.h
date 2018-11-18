#ifndef TREE_H
#define TREE_H
#pragma once

#include <utility>
#include "uniq_ptr.h"

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

		UniqPtr<TreeNode> left;
		UniqPtr<TreeNode> rigth;
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

		void erase(int key)
		{
			auto& p = Find(key);
			if (p.Empty()) return;
			UniqPtr<TreeNode> left = std::move(p->left);
			p = std::move(p->rigth);
			if ( !left.Empty() )
			{
				Find(p, left->data.first) = std::move(left);
			}
			--count_;
		}

	private:
		const UniqPtr<TreeNode> & Find(int key) const
		{
			return Find(root_, key);
		}
		UniqPtr<TreeNode> & Find(int key)
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
		UniqPtr<TreeNode> root_;
	};
}

#endif
