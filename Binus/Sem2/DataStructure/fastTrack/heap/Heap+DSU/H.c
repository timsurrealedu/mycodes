#include<stdio.h>
#include<string.h>

struct Data {
	char c;
	int freq;
};

struct Data HEAP[100];
int size = 0;

void swap(int u, int v) {
	struct Data temp = HEAP[u];
	HEAP[u] = HEAP[v];
	HEAP[v] = temp;
}

int isHigher(int u, int v) {
	if (HEAP[u].freq > HEAP[v].freq) return 1;
	if (HEAP[u].freq < HEAP[v].freq) return 0;
	return HEAP[u].c > HEAP[v].c;
}

void push(struct Data val) {
	size++;
	HEAP[size] = val;
	
	int cur = size;
	while (cur != 1 && isHigher(cur, cur / 2)) {
		swap(cur / 2, cur);
		cur /= 2;
	}
}

void pop() {
	HEAP[1] = HEAP[size];
	size--;
	
	int cur = 1;
	while (cur * 2 <= size) {
		struct Data maks = HEAP[cur];
		int idx = cur;
		
		if (isHigher(cur * 2, idx)) {
			maks = HEAP[cur * 2];
			idx = cur * 2;
		}
		
		if (cur * 2 + 1 <= size && isHigher(cur * 2 + 1, idx)) {
			maks = HEAP[cur * 2 + 1];
			idx = cur * 2 + 1;
		}
		
		if (idx == cur) break;
		swap(idx, cur);
		cur = idx;
	}
}

struct Data top() {
	return HEAP[1];
}

int main() {
	int K;
	char S[105];
	int freq[30] = {0};
	
	scanf("%d %s", &K, S);
	int N = strlen(S);
	int i;
	for (i = 0; i < N; i++) {
		freq[S[i] - 'A']++;
	}
	
	for (i = 0; i < 26; i++) {
		if (freq[i] > 0) {
			struct Data newData;
			newData.c = i + 'A';
			newData.freq = freq[i];
			push(newData);
		}
	}
	
	for (i = 0; i < K; i++) {
		if (size == 0) break;
		struct Data cur = top();
		pop();
		printf("%c %d\n", cur.c, cur.freq);
	}
	return 0;
}
