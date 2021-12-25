#include "matrice.hpp"
#include "matriceDouble.hpp"
#include <cstdlib>
#include "IndexInvalide.hpp"
#include "matriceCreuse.hpp"

using namespace std;

int main(){
	
	//main ds
	matriceDouble m1(3,6,1);
	cout << "m1 : " << m1 << endl;
	matriceDouble m2=m1;
	try{
	cout <<"sous matrice de m2 : " << *m2.subMat(1,2,1,3) << endl;
	}
	catch(const IndexInvalide &e){
		cerr << e.what() << endl;
	}
	
	//main projet

	matriceCreuse mc1=matriceCreuse(10,10);
	matriceCreuse mc2=matriceCreuse(10,10);

	matriceDouble md1=matriceDouble(3,3);
	matriceDouble md2=matriceDouble(3,3);
	matriceDouble md3=matriceDouble(10,10);
	
	md1.randInit();
	md2.randInit();

	matrice<double> *matc1=new matriceCreuse(10,10);
	matrice<double> *matc2=new matriceCreuse(10,10);

	matrice<double> *matd1= new matriceDouble(3,3);
	matrice<double> *matd2= new matriceDouble(3,3);
	matrice<double> *matd3=new matriceDouble(3,3);

	matd1->randInit();
	matd2->randInit();

	try{
		srand(time(nullptr));
		//matc1->randInit(); //erreur? init trop ?
		matc1->set(1,3,5);
		matc2->randInit();

		cout <<"avec matrice double " <<endl;

		cout <<"md1 : " << md1 << endl;
		cout <<"md2 : " << md2 << endl;
		cout << "sous matrice de md1 : " << *md1.subMat(1,2,1,2) << endl;
		cout << "additiond de md1 et md2 : " << md1+md2 << endl;
		cout << "multiplication de md1 et md2 : " << md1*md2 << endl;
		cout << "Matrice md1 creuse ? : " << md1.estCreuse() << endl;
		cout << "Matrice md2 creuse ? : " << md2.estCreuse() << endl;
		cout<<endl;
		cout<<endl;
		cout << "avec matrice creuse " << endl;

		mc1.set(1,1,3);
		mc2.set(1,1,3);
		cout <<"mc1 : " <<mc1 <<endl;
		cout <<"mc2 : " <<mc2 <<endl;
		cout << "sous matrice de mc1 : " << *mc1.subMat(1,10,1,2) << endl;
		cout << "addition de mc1 et mc2 : " << mc1+mc2 << endl;
		mc1.randInit();
		mc2.randInit();
		cout << "multiplication de mc1 et mc2 : " << mc1*mc2 << endl;
		cout << "Matrice mc1 creuse ? : " << mc1.estCreuse() << endl;
		cout << "Matrice mc2 creuse ? : " << mc2.estCreuse() << endl;
		cout<<endl;
		cout<<"Avec matrice<double> de matrice double" << endl;

		cout<<"matd1 : "<< *matd1 << endl;
		cout<<"matd2 : "<< *matd2 << endl;
		cout <<"sous matrice de matd1 : "<< *(matd1->subMat(1,3,1,3))<<endl;
		cout << "addition de matd1 et matd2 : " << (*matd1)+(*matd2) << endl;
		cout<< "multiplication de matd1 et matd2 : "<< (*matd1)*(*matd2) <<endl;
		cout << "Matrice matd1 creuse ? : " << matd1->estCreuse() << endl;
		cout << "Matrice matd2 creuse ? : " << matd2->estCreuse() << endl;
		cout<<endl;
		cout<<"Avec matrice<double> de matrice creuse" << endl;
	

		
		cout<<"matc1 : "<< *matc1 << endl;
		cout<<"matc2 : "<< *matc2 << endl;
		cout << "addition de matc1 et matc2 : " << (*matc1)+(*matc2) << endl;
		cout<< "multiplication de matc1 et matc2 : "<< (*matc1)*(*matc2) <<endl;
		cout << "Matrice matd1 creuse ? : " << matc1->estCreuse() << endl;
		cout << "Matrice matd2 creuse ? : " << matc2->estCreuse() << endl;


		cout <<"Les conversions"<<endl;
		cout<<endl;
		cout<<"Conversion matrice<double>" <<endl;
		matrice<double> *matc5=matd1; //conversion 1
		cout<<"convrsion double to creuse avec allocation" <<endl;
		cout<<"matd1 : "<<*matd1<<endl;
		cout<<"matc5=matd1 : "<<*matc5<<endl;
		cout<<endl;

		cout<<"convrsion creuse to double avec allocation" <<endl;

		matrice<double> *matd4=matc5;
		cout<<"matc5 : "<<*matc5<<endl;
		cout<<"matd4=matc5 : "<<*matd4<<endl;
		cout<<endl;

		cout<<"conversion creuse to double" <<endl;
		matriceDouble md2;
		md2.operator=(mc1); 
		cout <<"mc1 : " <<mc1 <<endl;
		cout <<"md2=mc1 : " <<md2 <<endl;
		cout<<endl;
		cout<<"conversion double to creuse" <<endl;
		md3.set(1,1,3);
		matriceCreuse mc3;
		mc3=md3; 
		cout <<"md3 : " <<md3 <<endl;
		cout <<"mc3=md3 : " <<mc3 <<endl;

		


	}
	catch(const IndexInvalide &e){
		cerr << e.what() << endl;
	}

	delete matc1;
	delete matc2;
	delete matd1;
	delete matd2;
	delete matd3;
	

	return EXIT_SUCCESS;
}
