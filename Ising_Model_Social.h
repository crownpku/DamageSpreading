#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <list>
#include <queue>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

#define AgentNum 100
#define maxstep 100 //run for maxstep runs
#define updatenum 20 //for each step, updatenum sites will be updated
#define AIndex 50
//#define BIndex 60
#define roundnum 100
double KbT;
//Critical: 2.269

/*States of the nodes*/
vector< bool > Matrix;
vector< bool > MatrixDamagedA;
//vector< bool > MatrixDamagedB;
//vector< bool > MatrixDamagedAB;

/*Topology of the nodes*/
vector< vector<double> > Topology;


class IsingModel
{
public:
	IsingModel(void);
	virtual ~IsingModel(void);

public:

	void evolve (vector< bool > & Matrix, vector< bool > & MatrixDamagedAB,const vector<vector<double> > Topology );
		//& MatrixDamagedA, vector< vector<bool> > & MatrixDamagedB, vector< vector<bool> > & MatrixDamagedAB);
	double HammingDist (const vector  <bool>  Matrix1, const vector <bool > Matrix2);
	int Hamiltonian (int index, const vector<bool> Matrix, const vector< vector<double> > Topology);
	void flip (int index, vector< bool > & Matrix, const vector< vector<double> > Topology, double randomnum );

private:

private:
	

};

