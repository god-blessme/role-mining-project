
/* the algorithm that is used in the program is mentioned in the research paper that we
have studied. If you have any doubts you can refert o subset enumeration data mining
research paper.*/
#include "combined_miner.h"
#include<bits/stdc++.h>
#include<unistd.h>
#include<time.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vi >
#define pb push_back
#define sz(v) v.size()
#define all(v) v.begin(),v.end()
#define ln(v) v.length()

void fastminer(vector<set<int> >& init_roles, set<set<int> >& intersected_roles, int p);
void completeminer(vector<set<int> >& init_roles, vector<set<int> >& set2, int p);

void do_mining(int complete, vector<int>& num_roles, vector<double>& exec_times)
{
	string paths[] = {"./50_50_0.05/50_50dataset","./50_100_0.05/50_100dataset","100_100_0.05/100_100dataset"};
	int no=1;
	//ofstream outfile("stats_output.txt",std::ofstream::out);
	int folds=1;
	while(folds<=3)
	{
		no = 1;
		while(no<=10)
		{

			ifstream infile(paths[folds-1]+to_string(no)+".txt");
			if(infile==NULL)
			{
				cout << "did not open file properly" << endl;
				return;
			}
			string str;
			getline(infile,str);
			stringstream ssp(str);
			int u,p;
			double density;
			ssp >> u >> p >> density;
			printf("%d %d %f\n",u,p,density);       // testing purpose.

			vvi upa(u,vi(p,0));
			int i=0;
			while(getline(infile,str))
			{
				int j=0;
				stringstream ss;
				ss << str;
				string temp;
				while(getline(ss,temp,' '))        // forming the upa matrix from the file.
				{
				upa[i][j] = stoi(temp);
				j++;

				}
				i++;

			}
			clock_t start = clock();
			set<int> P[u];
			for(i=0;i<u;i++)             // creating a set of permissions for each user.
			{
				for(int j=0;j<p;j++)
				{
					if(upa[i][j]==1)
					{
						//printf("%d %d\n",i,j);
						P[i].insert(j);
					}
				}
			}
			set<set<int> > init_sets;             // creating initial roles from array of set of permissions.
			for(i=0;i<u;i++)
			{
				//printf("size of %d is %lu\n",i,sz(P[i]));
				init_sets.insert(P[i]);
			}
			vector<set<int> > init_roles(all(init_sets));

			vi :: iterator it;
			set<set<int> > intersected_roles;
			vector<set<int> > set2(init_roles);

			if(complete)
			completeminer(init_roles,set2,p);
			else
			{
				fastminer(init_roles,intersected_roles,p);
				set2.clear();
				set2.insert(set2.begin(),all(intersected_roles));
			}

			cout << "final sets " << sz(set2) << endl;

			vector<set<int> > final_roles(all(set2));
			vi final_counts(sz(set2),0);
			vi generated_counts(sz(set2),0);
			for(i=0;i<sz(final_roles);i++)         // getting the final counts and generated counts.
			{
				for(int j=0;j<u;j++)
				{
					vi temp(p,0);
					it = set_difference(all(final_roles[i]),all(P[j]),temp.begin());
					temp.resize(it-temp.begin());
					if(P[j]==final_roles[i])
					{
						final_counts[i]++;
					}
					else if(temp.empty())
					{
						generated_counts[i]++;
					}
				}
			}
//cout << "haie \n";
/*for(i=0;i<sz(set2);i++)
cout << final_counts[i] << " ";
cout << endl;

for(i=0;i<sz(set2);i++)
cout << generated_counts[i] << " ";
cout << endl;*/
			double ticktick = (clock()-start)*1.0/CLOCKS_PER_SEC;
			num_roles.pb(sz(set2));
			exec_times.pb(ticktick);
			infile.close();
			no++;
		}
		folds++;
	}

	return;
}
void fastminer(vector<set<int> >& init_roles, set<set<int> >& intersected_roles, int p)
{
	vi :: iterator it;
		for(int i=0;i<sz(init_roles);i++)                //adding the intersection roles to the initial roles.
		{
			for(int j=i;j<sz(init_roles);j++)
			{
				vi temp(p,0);
				it = set_intersection(all(init_roles[i]),all(init_roles[j]),temp.begin());
				temp.resize(it-temp.begin());
				if(!temp.empty())
				{
					intersected_roles.insert(set<int>(all(temp)));
				}
			}
		}
}
void completeminer(vector<set<int> >& init_roles, vector<set<int> >& set2, int p)
{
	vi :: iterator it;
	set<set<int> > intersected_roles;
	for(int k=0;k<sz(init_roles)-1;k++)
	{
		//cout << "inter sets " << sz(set2) << endl;
		intersected_roles.clear();
		for(int i=0;i<sz(init_roles);i++)                //adding the intersection roles to the initial roles.
		{
			for(int j=0;j<sz(set2);j++)
			{
				vi temp(p,0);
				it = set_intersection(all(init_roles[i]),all(set2[j]),temp.begin());
				temp.resize(it-temp.begin());
				if(!temp.empty())
				{
					intersected_roles.insert(set<int>(all(temp)));
				}
			}
		}
		set2.clear();
		set2.insert(set2.begin(),all(intersected_roles));
	}
}
