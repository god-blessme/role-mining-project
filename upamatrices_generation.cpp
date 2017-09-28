#include<unistd.h>
#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vi >
#define sz(v) v.size()
#define pb push_back

int main()
{
	cout << "enter the no.of users: ";       //taking the inputs from user.
	int u,p;
	double density;
	cin >> u ;
	cout << "enter the no.of permissions: ";
	cin >> p;
	cout << "enter the density: ";
	cin >> density;
	int iter;
	cout << "the number of iterations: ";
	cin >> iter;
	//u = 50,p=50,density=0.05;
	ofstream outfile;


	//int iter = 5;
	srand(time(0));
	int k=1;
while(iter>0)
{

	outfile.open(to_string(u)+"_"+to_string(p)+"dataset"+to_string(k)+".txt");
outfile << u << " " << p << " " << density << endl;
	vvi upa(u,vi(p,0));

	for(int i=0;i<u;i++)
	{
		for(int j=0;j<p;j++)
		{

			double d = ((double) rand())/RAND_MAX;   //generating random number b/w 0 and 1.
			if(d<=density)                             // if the number is less than desnsity place 1 there.
			upa[i][j] = 1;
		}
	}
	for(int i=0;i<u;i++)             // checking whether each user has atleast one permission.
	{
		int flag = 0;
		for(int j=0;j<p;j++)
		{
			if(upa[i][j]==1)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)              // if user has 0 permissions and take some random number and place 1.
		{
			upa[i][rand()%p]=1;
		}

	}
	int cnt = 0;
	for(int i=0;i<u;i++)
	{
		for(int j=0;j<p;j++)
		{
			outfile << upa[i][j] << " ";
			if(upa[i][j]==1)
			cnt++;
		}
		outfile << endl;
	}
	outfile << endl << endl;
	cout << "The final density is : " << (double)cnt/(p*u) << endl;
//	usleep(20);
	iter--;
	k++;
	outfile.close();
}
return 0;
}
