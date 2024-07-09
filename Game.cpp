#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <set>'
#include <unordered_set>
using namespace std;



class Solution {
private:
	void Insert(string word, string beginWord,  vector<string> &vec, map<string, vector<string>>& my_map, vector<vector<string>> &ans) {
		vector<string>::iterator it;
		vec.insert(vec.begin(), word);
		

		if (word  == beginWord) {
			ans.push_back(vec);
			it = vec.begin();
			vec.erase(it);
			return;
			
		}
		for (auto a : my_map[word]) { 
			Insert(a, beginWord, vec, my_map, ans);
		}
		it = vec.begin();
		
		vec.erase(it);


	}
public:
	vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
		map<string, int> graph;

		queue<string>q;
		q.push(beginWord);
		int vec_size = wordList.size();

		map<string, bool> vis;


		map<string, bool> visited;
		
		for (int i = 0; i < vec_size; ++i) {
			visited[wordList[i]] = false;
			vis[wordList[i]] = false;
			graph[wordList[i]] = 1e9;
		}
		graph[beginWord] = 1, vis[beginWord] = false;
		graph[endWord] = 1e9, vis[endWord] = false;

		visited[beginWord] = false;
		visited[endWord] = false;
		
		map<string, vector<string>> my_map;
		

		while (!q.empty()) {
			string word = q.front();
			

			int u_dist = graph[word];
			
			if (word != endWord) vis[word] = true;



			q.pop();
			for (auto a : wordList) {
				if (!vis[a]) {
					int counter = 0;
					

					for (char& b : a) {
						int index = &b - &a[0];
						if (word[index] != b) {
							counter++;
						}
					}
					
					if (counter == 1) {
						int v_dist = graph[a];
						if (u_dist + 1 < v_dist || u_dist +1 == v_dist) {
							my_map[a].push_back(word);
							graph[a] = u_dist +1;
							if (!visited[a]) {
								q.push(a);
								visited[a] = true;

							}
							
							
						}
						

					}
				}

			}
			
			


		}
		
		vector<vector<string>> ans;
		vector<string> vec;
		Insert(endWord, beginWord, vec, my_map, ans);
		return ans;
	}

};





int main() {
	Solution solu;
	vector<string> wordList_2 = { "ted","tex","red","tax","tad","den","rex","pee" };
	
	vector<vector<string>> ans = solu.findSequences("red", "tax", wordList_2);

	for (auto a : ans) {
		for (auto b : a) {
			cout << b << " ";
		}
		cout << endl;
	}

	
	
}