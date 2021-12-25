#pragma once

#include "matrice.hpp"
#include <vector>
#include <cmath>

using namespace std;

class matriceCreuse : public matrice<double> {

    protected:
        double *mat;
        int lg;
        int nbNonNul;
    public:
        matriceCreuse(const int l=0, const int c=0) : matrice<double>(l,c) {
            if(this->nbElem<10){
                this->mat=nullptr;
                this->lg=0;
                this->nbNonNul=0;
            }
            else{
                this->lg=floor(0.1*this->nbElem);
                this->mat=new double[this->lg*3];
                this->nbNonNul=0;
            }
        }
        ~matriceCreuse(){
            cout << "delete matrice creuse" << endl;
            delete [] this->mat;
        }
        matriceCreuse(const matriceCreuse &mc){
            dupliquer(mc);
        }


        virtual const double get(const int i, const int j) const override {
            if(this->mat==nullptr || this->nbNonNul==0){
                return 0.0;
            }
            else{
                for(int a=1;a<=this->lg;a++){
                    if(this->mat[(a*3)+(2-3)-1]==i && this->mat[(a*3)+(3-3)-1]==j) {
                        return this->mat[(a*3)+(1-3)-1];
                    }
            }
            return 0.0;
            }
        }

        bool estPleine() const{
            return this->lg==this->nbNonNul;
        }

        virtual void  set(const int i, const int j, const double x) override{
            if(this->estPleine()){
                throw IndexInvalide("impossible d'ajouter un element non nul, matrice pleine i.e 10'%' des elements sont déjà non nuls");
            }
            else if(i>this->nbL || j>this->nbC)
            {
                throw IndexInvalide("erreur d'indice i ou j");            
            }
            else if(x!=0){
                this->nbNonNul=this->nbNonNul+1;
                this->mat[(this->nbNonNul*3)+(1-3)-1]=x;
                this->mat[(this->nbNonNul*3)+(2-3)-1]=i;
                this->mat[(this->nbNonNul*3)+(3-3)-1]=j;
            }

        }


        void dupliquer(const matriceCreuse &mc){
            this->nbC=mc.nbC;
            this->nbL=mc.nbL;
            this->nbElem=mc.nbElem;
            this->lg=mc.lg;
            this->nbNonNul=mc.nbNonNul;

            this->mat=new double[this->lg*3];
            for(int i=1;i<=this->lg;i++){
                for(int j=1;j<=3;j++){
                    this->set(i,j,mc.get(i,j));
                }
            }
        }
        
        virtual const string  toString() const override {
            ostringstream s;
			s<< " Matrice creuse " << this->nbL <<" x " <<this->nbC << " :" << endl;
            for(int i=1;i<=this->nbL;i++){
				s << "| ";
				for(int j=1;j<=this->nbC;j++){
					s << get(i,j) << " ";
				}
				s << "|";
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
            matrice<double> *m=new matriceCreuse(i2-i1+1,j2-j1+1);
            if(m->getNbElem()<10){
                for(int i=i1;i<=i2;i++){
                    for(int j=j1;j<=j2;j++){
                        if(this->get(i,j)!=0){
                            throw IndexInvalide("Une matrice creuse doit avoir 90'%' de ses elements à 0.0, or la sous matrice choisit ne respecte pas cette condition indice : ("+to_string(i)+","+to_string(j)+")");
                        }
                    }
                }
                return m;
            }
            else{
                int cpt=1;
                for(int i=i1,ii=1;i<=i2;i++,ii++){
                    for(int j=j1,jj=1;j<=j2;j++,jj++){
                        if(this->get(i,j)!=0){
                            if(cpt++>this->lg){
                                throw IndexInvalide("Impossible de creer une sous matrice creuse, la sous matrice contiendrait plus de 10'%' d'elements non nul");
                            }
                            m->set(ii,jj,this->get(i,j));
                        }
                    }
                }
                return m;
            }
            
        }

        virtual matrice<double>* fois(const matrice<double> &m) const {
            assert(this->nbC==m.getNbl());
            matrice<double> *md=new matriceCreuse(this->nbL, m.getNbc());
            if(this->lg==0){
                delete [] md; //a verifier
                return md;
            }
            else{
                double somme=0;
                for(int i=1;i<md->getNbl();i++){
                    for(int j=1;j<md->getNbc();j++){
                        if(this->get(i,j)!=0 && m.get(j,i)!=0){
                            for(int z=1;z<=this->nbC;z++){
                                somme=somme+this->get(i,z)*m.get(z,i); //pas opti
                            }
                        md->set(i,i,somme);
                        somme=0;
                        }
                    } 
                }
                return md;            
            }
        }

        virtual matrice<double>* addition(const matrice<double> &m) const {
            matrice<double> *md=new matriceCreuse(this->nbL, m.getNbc());
            if( !(this->nbC==m.getNbc()) || !(this->nbL==m.getNbl())  ){
                throw IndexInvalide("Les matrices doivent avoir le meme nombre de colonnes et de lignes i.e ");
            }
            /*else if(this->lg==0){
                md=&m;
                return md;              pas opti sans
            }*/                     
            else{
                int cpt=1;
                for(int i=1;i<md->getNbl();i++){
                    for(int j=1;j<md->getNbc();j++){
                        if(this->get(i,j)!=0 || m.get(j,i)!=0){
                            if(cpt++>this->lg){
                                throw IndexInvalide("L'addition de ces deux matrices engendrent une matrice creuse qui à plus de 10'%' de ces elements non nul, impossible");
                            }
                            md->set(i,j,this->get(i,j)+ m.get(j,i));
                        }

                    }
                }
                return md;
            }

        }

        virtual int const getnbNonNul() const{
            return this->nbNonNul;
        }

        virtual int const getlg() const{
            return this->lg;
        }


        virtual void randInit(){
            srand(time(nullptr));
            if(this->lg==0 && this->estPleine()){
                throw IndexInvalide("Impossible de faire une random initialisation la matrice creuse est deja pleine i.e 10'%' des elements differents de 0.0");
            }
            else{
                
                int nv=this->nbNonNul;
                /*cout<< "C THIS LG  " << this->lg << endl; test
                cout<< "C THIS NBNUL " << nv << endl;*/
                for(int i=nv;i<this->lg;i++){
                    int ligne=rand()%(this->nbL-0 + 1) + 0;
                    int colonne=rand()%(this->nbC-0 + 1) + 0;
                    this->set(ligne,colonne,rand()%(100-10 + 1) + 10);
                }
            }
        }

        virtual void setlg(const int x){
            this->lg=x;
        }

        virtual bool const estCreuse() const {
            return 1;
        }

        void toMatriceCreuse(const matrice<double> &md){
            this->nbElem=md.getNbElem();
            this->nbC=md.getNbc();
            this->nbL=md.getNbl();
            this->lg=floor(0.1*this->nbElem);
            this->mat=new double[this->lg];
            if(!(md.estCreuse())){
                throw IndexInvalide("Impossible de convertir la matrice double en matrice creuse, plus de 10'%' des elements de la matrice double sont non nuls ");
            }
            for(int i=1;i<= md.getNbl();i++){
                for(int j=1;j<=md.getNbc();j++){
                    if(md.get(i,j)!=0){
                       
                        this->set(i,j,md.get(i,j));
                    }
                }
            }
        }
        
        matriceCreuse& operator =(const matrice<double> &md){
            this->toMatriceCreuse(md);
            return *this;
            
        }
};
