#include "Ising_Model_Social.h"


IsingModel::IsingModel(void)
{
}
IsingModel::~IsingModel(void)
{
}

double IsingModel::HammingDist(const vector  <bool>  Matrix1, const vector  <bool>  Matrix2){
	int i;
	double distance=0.;
	for (i=0; i<AgentNum; i++){
		if (Matrix1[i] != Matrix2[i])
			distance = distance +1;
	}
	distance = double (distance/(AgentNum) );
	return distance;
}

int IsingModel::Hamiltonian (int index, vector<bool> Matrix, vector< vector<double> > Topology){
	int Hamiltonian = 0;
	for (int i=0; i<AgentNum; i++){
		if (Topology[index][i]!=0 ) 
			Hamiltonian = Hamiltonian + int (Matrix[index]==Matrix[i])*2 -1;
	}
	return Hamiltonian;
}

void IsingModel::flip (int index, vector< bool > & Matrix, const vector< vector<double> > Topology, double randomnum ){
	int energybefore, energyafter;
	energybefore = this->Hamiltonian(index, Matrix, Topology);
	Matrix [index] = !Matrix[index];
	energyafter = this->Hamiltonian(index, Matrix, Topology);
	if (energyafter>energybefore) {
		if (   randomnum > exp( double(energybefore - energyafter)/KbT ) ) Matrix [index] = !Matrix[index];
	}
}
/*Envolve one step*/
void IsingModel::evolve(vector< bool > & Matrix, vector< bool > & MatrixDamagedA, const vector< vector<double> > Topology )
	//& MatrixDamagedA, vector< vector<bool> >  & MatrixDamagedB, vector< vector<bool> > & MatrixDamagedAB)
{
	int i;
	int index;
	double randomnum;
	for (i=0; i<updatenum; i++){
		index = int ( (double)(rand()%32767)/(double)32767 * AgentNum );
		randomnum = (double)(rand()%32767)/(double)32767;
		/*Matrix*/
		this->flip (index, Matrix, Topology, randomnum);
		/*MatrixDamagedA*/
		//	if (row != Aposix || column != Aposiy) this->flip (row, column, MatrixDamagedA, randomnum);
		/*MatrixDamagedB*/
		//	if (row != Bposix || column != Bposiy) this->flip (row, column, MatrixDamagedB, randomnum);
		/*MatrixDamagedAB*/
		if ( index!=AIndex  ) this->flip (index, MatrixDamagedA, Topology, randomnum);
	}

}





int main(){
	
	
	string OutputFile="Ising_CritiTempSmallRange_RegularTriangular.txt";
	string InputFile = "RegularTriangular.txt";
	ofstream fout;
	ifstream fin;
	fout.open(OutputFile.c_str());
	fin.open(InputFile.c_str());
	
	
	int i,j,k;
	/*Intialization of the topology*/
	for (i=0; i<AgentNum; i++){
		Topology.push_back(vector<double>(AgentNum) );
		Matrix.push_back(0);
		MatrixDamagedA.push_back(0);
	}
	
	for (i=0; i<AgentNum; i++){
		for(j=0; j<AgentNum; j++){
			fin>>k;
			Topology[i][j]=k;
		}
	}
	
	IsingModel crown;
	
			for(KbT=0.1; KbT<3.1; KbT = KbT + 0.1){
				cout<<"KbT = "<<KbT<<endl;
				double Damage = 0.;
				for (k=0; k<roundnum; k++){
					for (i=0; i<AgentNum; i++){
						if (double (rand() )/32767.>0.5) 
						{
							Matrix[i]=0;
							MatrixDamagedA[i]=0;
							//				MatrixDamagedB[i]=0;
							//MatrixDamagedAB[i]=0;
						}
						else
						{
							Matrix[i]=1;
							MatrixDamagedA[i]=1;
							//MatrixDamagedB[i]=1;
							//MatrixDamagedAB[i]=1;
						}
					}

					MatrixDamagedA[AIndex]=1;
					//MatrixDamagedB[Bposix][Bposiy]=0;
					//MatrixDamagedAB[AIndex]=1;
					//MatrixDamagedAB[BIndex]=0;
					for (i=0; i<maxstep; i++){
						//cout<<i<<endl;
						crown.evolve(Matrix, MatrixDamagedA, Topology);
						//, MatrixDamagedB, MatrixDamagedAB);


					}
					Damage = Damage + crown.HammingDist(Matrix, MatrixDamagedA); 
				}
				Damage = Damage / roundnum;
				fout<<KbT<<" "<<Damage<<endl;
			}

	return 0;
}
