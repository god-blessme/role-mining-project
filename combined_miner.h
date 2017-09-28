#ifndef COMBINED_H
#define COMBINED_H
#include<bits/stdc++.h>
using namespace std;

void fastminer(vector<set<int> >& init_roles, set<set<int> >& intersected_roles, int p);
void completeminer(vector<set<int> >& init_roles, vector<set<int> >& set2, int p);

void do_mining(int complete, vector<int>& num_roles, vector<double>& exec_times);

#endif
