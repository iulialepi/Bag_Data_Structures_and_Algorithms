#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

//kompl: o max n pasi, theta exact n pasi, omega cel putin n pasi

//kompl: worst, best, avg:theta(1)
Bag::Bag() {
	this->nrElems = 0;
	this->cap=15;
	this->vector = new int[cap]{0};
	this->min = INT_MAX;     // de ce nu this->min = new Telem? nu folosesc deloc telemu?
	this->max = 0;

}
	/*
	if(capacity <= 0){
		throw exception();
	}
	this->cap=capacity    faza asta cu capacity nu cred ca ne trebuie ca ii numa din exemplu de la fixed cap map
	*/

//kompl: worst = theta(n) wenn wir im <min gehen und das ist das schlechste, 
//best = theta(1) weil wir inden 1ten if reingehen und nur dort, 
//avg:theta(1)
void Bag::add(TElem elem) {
	/*
	//check if it is full        cred ca asta era in exemplu  pentru ca era fixed capacity
	if(this->nrElems == this->cap){
		throw exception();
	}
	*/

	if (this->nrElems == 0) {
		this->vector[0]++;
		this->min = elem;
		this->max = elem;
		this->nrElems++;
	}
	else {
		//also wir werden drei if Konditionen haben. 1 wenn elem < min, 2 wenn elem > min, 3 wenn elem im existierenden Interwall ist

		//wir ueberpr jedes mal ob der Maximum sich aendert

		if (elem > this->max) {
			int oldMax = this->max;
			this->max = elem;

			//wir wollen ueberpruefen ob die neue Ziffer "elem" im aktuellen Array reinpasst

			int checkCap = this->max - this->min + 1;
			if (checkCap > cap) {
				//wenn nicht, verdoppeln wir den Array

				int* vectorNew = new int[this->cap * 2]{ 0 };

				for (int index = 0; index < this->nrElems; index++) {
					vectorNew[index] = vector[index];
				}
				this->cap = this->cap * 2;

				//nachdem wir den Array verdoppelt haben geben wir den neuen Array zuruck zu dem alten 
				this->vector = vectorNew;

				//wir deallokieren den copy array      
				delete[] vectorNew;
			}

			this->nrElems += this->max-oldMax;         //wir berechnen die aktuelle Nummer der Elemente

			//wir inkrementieren die nrOcc der Ziffer elem
			this->vector[elem - this->min]++;              //aici elem ii teoretic acelasi nr cu this->max;
		}

		//wir ueberpr jedes mal ob der Minimum sich aendert
		else if (elem < this->min) {
			int oldMin = this->min; 
			this->min = elem;

			//wir wollen ueberpruefen ob die neue Ziffer "elem" im aktuellen Array reinpasst

			int checkCap = this->max - this->min + 1;
			if (checkCap > cap) {
				//wenn nicht, verdoppeln wir den Array
				/*
				int* vectorNew;
				this->nrElems = this->nrElems +;
				vectorNew = new int[nrElems + 1];
				for (int index = 0; index < nrElems + 1; index++)
					vectorNew[index] = this->vector[index];
				this->vector = vectorNew;
				delete[] vectorNew;
				*/
				int* vectorNew = new int[this->cap * 2]{ 0 };

				for (int index = 0; index < this->cap; index++) {
					vectorNew[index] = vector[index];
				}
				this->cap = this->cap * 2;

				//nachdem wir den Array verdoppelt haben geben wir den neuen Array zuruck zu dem alten 
				this->vector = vectorNew;

				//wir deallokieren den copy array      
				delete[] vectorNew;
			}

			//this->nrElems=this->max - this->min + 1;         //wir berechnen die aktuelle Nummer der Elemente

			int steps = oldMin - this->min;
		
			
			for (int index = this->max - oldMin + steps; index >= steps; index--) {
				//wir muessen alle elemente nach rechts schieben 'steps' mal
				this->vector[index] = this->vector[index - steps];
			}

			for (int index = steps-1; index > 0; index--) {
				this->vector[index] = 0;
			}
			
			this->vector[0]=1;     
			this->nrElems = this->nrElems + steps;


			/*
			int* vectorNew = new int[this->cap]();

			vectorNew[0] = 1;

			for (int index = 1; index < steps; index++) {
				vectorNew[index] = 0;    
			}
			
			for (int index = steps; index < this->max- oldMin + steps; index++) {
				vectorNew[index] =vector[index];
			}
			//wir geben den neuen Array zuruck zu dem alten 
			this->vector = vectorNew;

			//wir deallokieren den copy array      
			delete[] vectorNew;

			*/

			

		}

		//wenn es nicht groesser als max oder kleiner als min ist, dann koennen wir direkt den wert des elems inkremetieren

		else if (elem >= this->min && elem <= this->max) {
			if (elem == this->min) {
				this->vector[0]++;
			}
			else {
				if (elem == this->max) {
					this->vector[this->max - this->min]++;
				}
				else {
					this->vector[elem - this->min]++; 
					//this->nrElems++;   numaru de elemente nu cred ca se schimba
				}
			}
			
		}

	}
}

//wir haben diese Funktion um den Array zu sehen und Sachen zu ueberpruefen
//Kompl: theta(nrElems) weil wir genau nrelems Schritte machen
void Bag::print() {
	for (int i = 0; i < this->nrElems;i++) {
		std::cout << this->vector[i];
		std::cout << "  ";
	}
}

//Kompl: best:theta(1) weil wir nichts loeschen
//worst: theta(log nrelem) weil es genau nrelems Schritte immer macht
//avg: o(log nrelem) weil nicht immer wie bei worst 
bool Bag::remove(TElem elem) {

	//cred ca un remove inseamna doar sa ii setam valoarea 0
	//dar exceptiile sunt cand este minimul si maximul deoarece trebuie sa schimbam valorile lor

	if (elem == this->min) {
		//cautam urmatorul minim
		for (int index = 1; index <= this->nrElems; index++) {
			std::cout << index;
			if (vector[index] != 0) {

				int oldMin = this->min;
				this->min =this->min+index;
				int* vectorNew;
				this->nrElems = this->nrElems-index;
				vectorNew = new int[nrElems-1];
				for (int index = 0; index < nrElems-1; index++){
					vectorNew[index] = this->vector[this->min-oldMin];
			}
				this->vector = vectorNew;
				delete[] vectorNew;
				
				return true;
			}
		}
	}
	if (elem == this->max) {
		//cautam urm maxim
		int nr = 0;          //folosim acest nr ca sa stim cu cat decrementam nrElems
		for (int index = this->max-this->min; index >= 0; index--) {
			nr++;
			if (vector[index] != 0) {
				this->max = index + this->min;
				this->nrElems -= nr;

				return true;
			}
		}
	}
	if (elem > this->max || elem < this->min) {
		return false;   //pentru ca nu exista deci nu il putem sterge
	}
	if (vector[elem - this->min] == 0) {
		return false;   //pentru ca nu exista in interval
	}
	if (vector[elem - this->min] != 0) {
		this->vector[elem - this->min] = this->vector[elem - this->min] - 1;  //vrem sa stergem doar o aparitie
		return true;
	}

}

//alle kompl:theta(1)
bool Bag::search(TElem elem) const {

	if (elem > this->max) {
		return false;
	}
	if (elem < this->min) {
		return false;
	}
	if (this->vector[elem - this->min] == 0) {         //elem - min ne da pozitia
		return false;
	}

	return true; 

	//return false daca nu apare return true cand apare
}

//alle kompl:theta(1)
int Bag::nrOccurrences(TElem elem) const {
	return this->vector[elem-this->min]; 
}

//kompl:theta(nrElems) weil immer
int Bag::size() const {
	int elementsInBag=0;
	//return this->nrElems; NUUU... pentru ca size inseamna cate elemente am in bag nu cate pozitii... deci adun numerele din bag de la occ
	for (int i = 0;i <= this->nrElems;i++) {
		elementsInBag += this->vector[i];
	}
	return elementsInBag;
}

//alle kompl:theta(1)
bool Bag::isEmpty() const {
	if(this->nrElems==0){
		return true;
	}
	return false;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	delete[] this->vector;
}


