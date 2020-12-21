#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>

using std::vector;
using std::min;
using std::make_pair;
using std::pair;
using std::ptrdiff_t;

class Block {
public:
	Block();
	Block(int x, int y, int w, int h);
	bool combine_to(const Block& other);
	inline void set_active(bool value) {
		this->active = active;
	}
	inline void operator=(const Block& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->w = rhs.w;
		this->h = rhs.h;
		this->active = rhs.active;
	}
private:
	bool active;
	int x, y;
	int w, h;
};

class Edge {
public:
	Edge(Block* first, Block* second);
	void calculate_valid();
	inline bool get_valid() {
		return this->valid;
	}
	inline bool operator==(const Edge& rhs) {
		// This checks if first and second are equal between pairs
		if (this->blocks == rhs.blocks) {
			return true;
		}
		// 1.first == 2.second and vice-versa is also equal since the graph isn't oriented
		else if (this->blocks.first == rhs.blocks.second && this->blocks.second == rhs.blocks.first) {
			return true;
		}
		return false;
	}
	inline Block* get_first() {
		return this->blocks.first;
	}
	inline Block* get_second() {
		return this->blocks.second;
	}
	inline void set_first(Block* block) {
		this->blocks.first = block;
	}
	inline void set_second(Block* block) {
		this->blocks.second = block;
	}
private:
	bool valid; // Cache the validity of this move so we don't have to recalculate every time we access the graph
	pair<Block*, Block*> blocks; // The order in the pair shouldn't matter
};

class Field {
public:
	Field(size_t n); // Initializes a field of size n*n
	Field(const Field& other);
	~Field();
	bool merge_edge(Edge& edge); // Basically performs the move => removes edge, merges blocks, merges overlapping edges
	vector<Edge> get_valid_edges(); // Basically returns every valid mode
private:
	void update_edge_validity(); // Updates the valid state for each edge
	Block* blocks; // Dynamic array of blocks, allocated when field is created, could technically be fixed at compile-time
	size_t blocks_size;
	vector<Edge> edges;
};