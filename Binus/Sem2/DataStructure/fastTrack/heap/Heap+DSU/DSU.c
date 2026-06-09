#include<stdio.h>

int parent[100];
int size[100];

int root(int u) {
	if (parent[u] == u) return u;
	return parent[u] = root(parent[u]);
}

void combine(int u, int v) {
	int ru = root(u), rv = root(v);
	if (ru != rv) {
		if (size[ru] < size[rv]) {
			parent[ru] = rv;
			size[rv] += size[ru];
		} 
		else {
			parent[rv] = ru;
			size[ru] += size[rv];
		}
	}
}

int main() {
	for (int i = 0; i < 100; i++) {
		parent[i] = i;
		size[i]	= 1;
	}
	return 0;
}
