#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include<string>
#include<stdlib.h>
#include <ga/GASimpleGA.h>
#include <ga/std_stream.h>
#include <ga/GARealGenome.h>

using namespace std;

void Leer();

string STRING;
string nodo;
int matAd[0][0];

int main(int argc, char **argv){

  for(int i=1; i<argc; i++) {
    if(strcmp(argv[i++],"seed") == 0)
      GARandomSeed((unsigned int)atoi(argv[i]));
  }

  Leer();

  int largoString = 0;
  int height   = 5;
  int popsize  = 30;
  int ngen     = 400;
  float pmut   = 0.001;
  float pcross = 0.9;

  GARealGenome genome(largoString,GARealAlleleSetArray &, Objective);

  GASimpleGA ga(genome);
  ga.populationSize(popsize);
  ga.nGenerations(ngen);
  ga.pMutation(pmut);
  ga.pCrossover(pcross);
  ga.evolve();

  cout << ga.statistics() << endl;

return 0;

}

void Leer(){

	char arch[40];
	char cadena[100];
	char a;
	//string STRING;
	//string nodo;
	cout<<"Ingrese nombre del archivo que desea utilizar: "<<endl;
	cin>>arch;
	bool bandera = true;
	ifstream fe (arch);
	int i=1;
	if(!fe)
	{
	  cout<<"El archivo definido no existe."<<endl;
	}else{
		while(!fe.eof()) {
			getline(fe,STRING);
			if(STRING[0]=='p'){
							
				nodo = STRING.substr(7,STRING.substr(7).find(" "));
				break;

			}
			
			STRING.clear();

			i=i+1;

		}

	}
	int nodos = atoi(nodo.c_str());
	cout << "Numero de nodos: " <<nodos << endl;
	//int matAd[nodos][nodos];
	for(int i = 0; i< nodos; i++){
		for(int j = 0; j<nodos;j++){
			matAd[i][j]=0;
			cout << matAd[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	while(!fe.eof()) {
		getline(fe,STRING);
		if(STRING[0]=='e'){
			int verticei = atoi((STRING.substr(2, 3)).c_str()) -1;
			int verticej = atoi((STRING.substr(2 + STRING.substr(2).find(" "), STRING.find("\n"))).c_str()) -1;
			//cout << i << " e " << verticei << " " << verticej << endl;
			matAd[verticei][verticej] = 1;
			matAd[verticej][verticei] = 1;

		}
		STRING.clear();
	}
	fe.close();
	for(int i = 0; i<nodos;i++){
		for(int j = 0;j<nodos;j++){
			cout << matAd[i][j] << " ";
		}
		cout << endl;
	}

}

float
Objective(GAGenome& g) {
  GARealGenome & genome = (GARealGenome &)g;
  float CantColores=0.0;
  
  
  //vaya a consultar a la matriz de adyacencia 
  //
  	int resultado = 0;
	int penalizados = 0;
	int arreglo[nodos];
	cout << "Arreglo: [ ";
	for (int i = 0; i <= nodos; ++i)
	{
		arreglo[i] = rand() % nodos + 1;
		cout << arreglo[i] << " ";
	}
	cout << "]" << endl;
	cout << "Inicio calculo Resultado: " << endl;
	for (int i = 0; i < nodos; ++i)
	{
		for (int j = 0; j < nodos; ++j)
		{
			if (i!=j) //no comparo al elemento en la misma posición
			{
				if (arreglo[i] == arreglo[j])
				{
					if (matAd[i][j]==0) //sin penalizacion el fitness sube 1000
					{
						resultado = resultado + 1000;
						cout << "Se le dio +1000 por vertice i:" << i+1 << " j:" << j+1 << endl;
					}
					else{ //con penalizacion el fitness sube 10
						resultado = resultado + 10;
						penalizados = penalizados+1;
						cout << "Se le dio   +10 por vertice i:" << i+1 << " j:" << j+1 << endl;
					}
				}
			}
		}
	}
	penalizados = penalizados/2;
	cout <<"Como el resultado entregado incluye ambos vertices iguales y el grafo es no dirigido, el resultado se divide a la mitad" << endl;
	resultado = resultado/2;
	cout << "Resultado: " << resultado << " con "<< penalizados << " penalizados" << endl;
	
	int listaColores[nodos];
	for (int i = 0; i <= nodos; ++i)
	{
		listaColores[i] = i+1;
	}
	int aux[nodos];
	for (int i = 0; i <=nodos; ++i)
	{
		aux[i] = arreglo[i];
	}
	int contadorColores = 0;
	//obtener cantidad de colores
	for (int i = 0; i <=nodos; ++i)
	{
		for (int j = 0; j <=nodos; ++j)
		{	//aca veremos lo de los colores en el listado colores
			if (aux[i]==listaColores[j])
			{
				contadorColores = contadorColores + 1;
				listaColores[j] = 0; //quitamos el color de la lista de colores si ya aparecio
				j=nodos;
			}
			
		}
	}
	cout << "Cantidad de colores: " << contadorColores << endl;

/*
  int count=0;
  for(int i=0; i<genome.width(); i++){
    for(int j=0; j<genome.height(); j++){
      if(genome.gene(i,j) == 0 && count%2 == 0)
	score += 1.0;
      if(genome.gene(i,j) == 1 && count%2 != 0)
	score += 1.0;
      count++;
    }
  }*/
  return resultado;
}
