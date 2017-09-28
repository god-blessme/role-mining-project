#include "combined_miner.h"
#include<bits/stdc++.h>
#include<unistd.h>
#include<time.h>

using namespace std;
void do_output(ofstream& outfile, vector<int>& num_roles, vector<double>& exec_times);

int main(int argc, char* argv[])
{
	for(int i=0;i<2;i++)
	{
		vector<int> num_roles;
		vector<double> exec_times;
		cout << "printing the " << i << " miner\n";
		do_mining(1-i,num_roles,exec_times);
		ofstream outfile("stats_output.txt",std::ofstream::out|std::ofstream::app);
		outfile << "0 - complete miner    1 - fast miner\n";
		outfile << "printing the " << i << " Miner\n";
		do_output(outfile,num_roles,exec_times);
		outfile.close();
	}

	return 0;
}
void do_output(ofstream& outfile, vector<int>& num_roles, vector<double>& exec_times)
{
	double sum =0;
	for(int i=0;i<30;i++)
	{
		sum = sum+exec_times[i];
		outfile << num_roles[i] << " " << exec_times[i]<< endl;
		if(i%10==9)
		{
			switch(i/10)
			{
				case 0: sort(num_roles.begin(),num_roles.begin()+10);
				case 1: sort(num_roles.begin()+10,num_roles.begin()+20);
				case 2: sort(num_roles.begin()+20,num_roles.end());
			}
			outfile << "mean of roles is " << (num_roles[i-4]+num_roles[i-5])/2 << endl;
			outfile << "average execution time is " << sum/10 << endl;
			sum = 0;
			outfile << "----------------------------------------" << endl;
		}
	}
}
