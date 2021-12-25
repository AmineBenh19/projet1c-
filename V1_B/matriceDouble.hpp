#pragma once

#include "matrice.hpp"
#include "IndexInvalide.hpp"


#include <sstream>
#include <cassert>

using namespace std;

class matriceDouble : public matrice<double> {
	protected:
		double *mat;
	public:

        ~matriceDouble(){
			cout<<"delete doublemat"<<endl;
           delete [] this->mat;
        }


		matriceDouble(const int l=0, const int c=0, const int v=0.0) : matrice<double>(l,c) {
			this->mat=new double[this->nbElem];
            for(int i=0;i<this->nbElem;i++){
                this->mat[i]=v;
            }
		}

        matriceDouble(const matriceDouble &md){
            dupliquer(md);
        }   
    
         
        void dupliquer(const matriceDouble &md){
            this->nbC=md.nbC;
            this->nbL=md.nbL;
            this->nbElem=md.nbElem;
            this->mat=new double[this->nbElem];
            for(int i=1;i<=md.nbL;i++){
                for(int j=1;j<=md.nbC;j++){
                    this->set(i,j,md.get(i,j));
                    }
                }
        }

       
        virtual const double get(const int i, const int j) const override {
			assert(i>=1 && j >= 1 && i<=this->nbL && j<=this->nbC);
            return this->mat[(i*this->nbC)+(j-this->nbC)-1];
        }
        
        virtual void  set(const int i, const int j, const double x) override{
			assert(i>=1 && j >= 1 && i<=this->nbL && j<=this->nbC);
            this->mat[(i*this->nbC)+(j-this->nbC)-1]=x;
        }

        virtual const string  toString() const override {
            ostringstream s;
			s<< " Matrice double " << this->nbL <<" x " <<this->nbC << " :" << endl;
            for(int i=1;i<=this->nbL;i++){
				s << " |  ";
				for(int j=1;j<=this->nbC;j++){
					s << get(i,j) <<" ";
				}
				s << " |";
				s<< endl;
			}
            return s.str();
        }
	
       
        
         virtual matrice<double>* subMat(const int i1,const int i2, const int j1, const int j2){
            if(!(i1 <= i2 && j1 <= j2)){
                if(!(i1 <= i2)){
                    throw IndexInvalide("Erreur d'indice pour la sous matrice : i1=" + to_string(i1) + " > i2=" + to_string(i2));
                }
                else if (j1 <= j2)
                {
                   throw IndexInvalide("Erreur d'indice pour la sous matrice : " + to_string(j1) + " > " + to_string(j2));
                }
                else{
                    throw IndexInvalide("Erreur d'indice pour la sous matrice : " + to_string(i1) + " > " + to_string(i2) + " et " + to_string(j1) + " > " + to_string(j2));
                    }

            }
            matrice<double> *m=new matriceDouble(i2-i1+1,j2-j1+1);
            for(int i=i1,ii=1;i<=i2;i++,ii++){
                for(int j=j1,jj=1;j<=j2;j++,jj++){
                    m->set(ii,jj,this->get(i,j));
                    }
                }
            return m;

        }
        virtual matrice<double>* fois(const matrice<double> &m) const {
            if(!(this->nbC==m.getNbl())){
                throw IndexInvalide(to_string(this->nbC)+"et "+to_string(m.getNbl())+" doivent etre egaux !");
            }

            matrice<double> *md=new matriceDouble(this->nbL, m.getNbc());
            double somme=0;
            for(int i=1;i<=this->nbL;i++){
                
                for(int j=1;j<=this->nbC;j++){
                    for(int z=1;z<=this->nbC;z++){
                        somme=this->get(i,z)*m.get(z,i)+somme;
                    }
                    md->set(i,j,somme);
                    somme=0;
                }
            }
            return md;
        }

        virtual matrice<double>* addition(const matrice<double> &m) const {
            if( !(this->nbC==m.getNbc()) || !(this->nbL==m.getNbl())  ){
                throw IndexInvalide("Les matrices doivent avoir le meme nombre de colonnes et de lignes i.e ");
            }
            else{
                matrice<double> *md=new matriceDouble(this->nbL, m.getNbc());
                for(int i=1;i<=this->nbL;i++){
                    for(int j=1;j<=this->nbC;j++){
                        md->set(i,j,this->get(i,j)+m.get(i,j));
                    }
                }
               return md;
            }
        }

        virtual void randInit() {
            srand(time(nullptr));
             for(int i=1;i<=this->nbL;i++){
                for(int j=1;j<=this->nbC;j++){
                    this->set(i,j,rand()%(100-10 + 1) + 10);
                }
            }
        }

        virtual bool const estCreuse() const{
            int cpt=0;
             for(int i=1;i<=this->nbL;i++){
                for(int j=1;j<=this->nbC;j++){
                    if(this->get(i,j)!=0){
                        if(++cpt>floor(0.10*this->nbElem)){
                            return 0;
                        }
                    }
                }
            }
            return 1;
        }

        void toMatriceDouble(const matrice<double> &mc){
            this->nbElem=mc.getNbElem();
            this->nbC=mc.getNbc();
            this->nbL=mc.getNbl();
            this->mat=new double[this->nbElem];
            for(int i=1;i<= mc.getNbl();i++){
                for(int j=1;j<=mc.getNbc();j++){
                    this->set(i,j,mc.get(i,j));
                }
            }
        }

        matriceDouble& operator =(const matrice<double> &mc){
            this->toMatriceDouble(mc);
            return *this;
        }
};
