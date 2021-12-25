#pragma once


using namespace std;

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <random>
#include <ctime>


template <typename T>

class matrice {
	protected:
		int nbElem;
        int nbL;
		int nbC;
		
	public:
		matrice(const int l=0, const int c=0) : nbL(l),nbC(c) {
			this->nbElem=l*c;
			}
		
		void dupliquer(const matrice &m){
			this->nbElem=m.nbElem;
			this->nbC=m.nbC;
			this->nbL=m.nbL;
		}
		matrice(const matrice &m){
			dupliquer(m);		
		}
		virtual ~matrice(){
			cout<<"delete mat"<<endl;
        }
		
		virtual const T get(const int i, const int j) const =0;
		virtual void    set(const int i, const int j,const T x)=0;
		virtual void    randInit()=0;

		
		virtual const string toString() const=0;
		
		friend ostream &operator<<(ostream &s, const matrice<T> &m){
			return s<< m.toString();
		}
		
		virtual T operator()(const int i,const int j)  const {
			return 	this->get(i,j);
		}
		virtual matrice<T>* subMat(const int i1,const int i2, const int j1, const int j2)=0;

		virtual matrice<T>* fois(const matrice<T> &m) const=0;
		virtual matrice<T>* addition(const matrice<T> &m) const=0;
		
		matrice<T>& operator * (const matrice<T> &m) {
			matrice<T> *resultat=fois(m);
			return *resultat;
		}
		
		matrice<T>& operator + (const matrice<T> &m){
			matrice<T> *resultat=addition(m);
			return *resultat;
		}

		matrice<T>& operator =(const matrice<T> &m){
			this->dupliquer(m);
			return *this;
		}

		virtual int const getNbc() const{
            		return this->nbC;
       	 	}
       		virtual int const getNbl() const{
            		return this->nbL;
		}
		virtual int const getNbElem() const{
			return this->nbElem;
		}

		virtual bool const estCreuse() const=0;
			
			
			
			
};

