#include <iostream>
#include <string>
#include <vector>
using namespace std;

int verificar_n(string& n_ingresada);
bool lectura_polinomios(vector<string> &polinomio, int n);
bool verfica_monomio(const string &monomio);
bool verifica_conv_stod(const string &analisis);
void remover_espacios(string *str);
void remover_signo_multiplicacion(string* str);
void vector_de_monomios(vector<string> &polinomios_ingresado, vector<vector<string>> &polinomios_nuevo, int tam);
int calculo_max_grado (vector<vector<string>> &polinomios, int tam);
void vector_coeficientes (vector<vector<long double>> &polinomios_coeficientes, vector<vector<string>> &v_polinomio, int tam_v_poli);
void sumar(int& n, int& max_grado, vector<long double>& suma, vector<vector<long double>> &polinomios_coeficientes);
void imprimir_suma(int& max_grado, vector<long double>& suma);

int main(){
	
	vector<string> vpolinomios_ingresado;
	int n;
	string n_ingresada;
	
	//verificar que se ingrese un entero 
	do {
    	cout << "Introduzca la cantidad de polinomios a sumar: ";
        getline(cin, n_ingresada);
        n = verificar_n(n_ingresada);
    } while(n<=1);
	cout << endl;
	
	//se leen los polinomios y se verfica que se ingresen bien
	bool ingreso_polinomios_valido;
    do{
        ingreso_polinomios_valido = lectura_polinomios(vpolinomios_ingresado,n);
    } while (ingreso_polinomios_valido == false);
	
	//se agrega un signo + en caso que no haya en el primer termino
	for (int i=0; i<n; i++){
		if (vpolinomios_ingresado.at(i)[0] != '+' and vpolinomios_ingresado.at(i)[0] != '-') 
			vpolinomios_ingresado.at(i).insert(vpolinomios_ingresado.at(i).begin(), '+');	
	}
	
	//se crea un vector donde cada elemento es un vector de los monomios de cada polinomio
	vector<vector<string>> polinomios;
	vector_de_monomios(vpolinomios_ingresado,polinomios,n);

	//se obtiene el grado mayor de todos los polinomios
	int max_grado = calculo_max_grado(polinomios,n);

	//vector de coeficientes inicializados en cero y dimension de mayor grado +1 
	vector<vector<long double>> polinomios_coeficientes (n,vector<long double>(max_grado+1)); 
	
	//se agregan los coeficientes de cada polinomio dependiendo de su grado
	vector_coeficientes(polinomios_coeficientes, polinomios, n);
	
	//suma de los coeficientes
    vector<long double> suma(max_grado+1);
	sumar(n, max_grado, suma, polinomios_coeficientes);

	//Resultado
    imprimir_suma(max_grado, suma);
	

return 0;
}

int verificar_n(string& n_ingresada){
    int n;
    string aux = "";
    bool n_valida = true;
    for(int i=0; i < n_ingresada.length(); i++){
        if(isdigit(n_ingresada[i]))
            aux = aux + n_ingresada[i];
        else{
            cout << "Se ingreso incorrectamente la cantidad de polinomios a sumar (cant minima: 2)" << endl;
            n_valida = false;
            break;
        }            
    }
    if (n_valida == true)
        n = stoi(aux);
    else
        n=0;
    
    return n;
}

bool lectura_polinomios(vector<string> &polinomios, int n){
	bool ingreso_polinomios_valido = true;
    for (int i = 0; i < n; i++){
		cout << "Polinomio #" << i + 1 << ": ";
		string ingreso;
		getline(cin, ingreso);
		//se verfica que se ingrese bien el polinomio
/*		
		
		for (int k=0; k<ingreso.size(); k++){
		
			if (isdigit(ingreso[k])){		
				if (ingreso[k+1] == ' '){	
					for (int i = k+2; i<(ingreso.size()+1); i++){
						if ((ingreso[i] != ' ') and (ingreso[i] != '+') and (ingreso[i] != '-')){
							cout << "Debe ingresar correctamente los polinomios" << endl;
							ingreso_polinomios_valido = false;
							return ingreso_polinomios_valido;	
						}
						else if ((ingreso[i] == '+') or (ingreso[i] = '-'))
							break;
					}
				}
			}
			
			if (ingreso[k] == '+' or ingreso[k] == '-'){		
				if (ingreso[k+1] == ' '){		
					for (int i = k+2; i<(ingreso.size()+1); i++){
						if ((ingreso[i] != ' ') and (ingreso[i] != 'x') and !isdigit(ingreso[i])){
							cout << "Debe ingresar correctamente los polinomios" << endl;
							ingreso_polinomios_valido = false;
							return ingreso_polinomios_valido;	
						}
						else if ((ingreso[i] == 'x') or isdigit(ingreso[i]))
							break;
					}
				}
			}
		}
*/	
		remover_espacios(&ingreso);
		
	    for (auto c:ingreso){
		    if ((c!= '+') and (c!= '-') and (c!= 'x') and (c!= '*') and (c!= '.') and (int(c)<48 or int(c)>57)){
			    cout << "Debe ingresar correctamente los polinomios" << endl;
                ingreso_polinomios_valido = false;
			    return ingreso_polinomios_valido;
		    }		
	    }


        for (int k=0; k<ingreso.size(); k++){
            if ((ingreso[k]=='x') or (ingreso[k]=='+') or (ingreso[k]=='-') 
                or (ingreso[k]=='*') or (ingreso[k]=='.')){

                if (ingreso[k] == ingreso[k+1]){
                        cout << "Debe ingresar correctamente los polinomios" << endl;
                        ingreso_polinomios_valido = false;
                        return ingreso_polinomios_valido;
                }
            }
        }

        remover_signo_multiplicacion(&ingreso);

		polinomios.push_back(ingreso);
	}
    return ingreso_polinomios_valido;
}

void remover_espacios(string *str) {
	string str_sin_espacios = "";
	for (int i = 0; i < str->length(); i++) {
   		if ((*str)[i] != ' ') {
    		str_sin_espacios = str_sin_espacios + (*str)[i];
    	}
  	}
  *str = str_sin_espacios;
}

void remover_signo_multiplicacion(string* str) {
    string str_sin_espacios = "";
    for (int i = 0; i < str->length(); i++) {
        if ((*str)[i] != '*') {
            str_sin_espacios = str_sin_espacios + (*str)[i];
        }
    }
    *str = str_sin_espacios;
}

void vector_de_monomios(vector<string> &polinomios_ingresado, vector<vector<string>> &polinomios_nuevo, int tam){
	string monomio;
	vector<string> monomios;
	
	for (int i=0; i<tam; i++){
		for (auto c:polinomios_ingresado.at(i)){	
			if (c=='+' or c=='-' and !monomio.empty()){
	            monomios.push_back(monomio);
	            monomio.clear();
				}
			monomio += c;
		}
		if (!monomio.empty()){
			monomios.push_back(monomio);
			monomio.clear();
		}
		polinomios_nuevo.push_back(monomios);
		monomios.clear();
	}

}

int calculo_max_grado (vector<vector<string>> &polinomios, int tam){
	int max_grado;
	for (int k = 0; k < tam; k++) {
		for (int j = 0; j < polinomios.at(k).size(); j++){
		    for (int i = 0; i < polinomios.at(k).at(j).length(); i++) {
		    	if (polinomios.at(k).at(j)[i] == 'x') {
		        // if 'x' is found, check the number after it
		        	string temp = "0";
			        while (i+1 < polinomios.at(k).at(j).size()) {
			          	if (isdigit(polinomios.at(k).at(j)[i+1]))	
							temp += polinomios.at(k).at(j)[i+1]; // if the next character is a digit, add it to the temp string
			        	else
							break; // if the next character is not a digit, break the loop	
						i++;
			        }
			        if (temp == "0") //si no cambio el valor	
						temp = "1";
					else if (temp == "00")
						temp = "0";
			        // convert the temp string to an integer and update the highest number
			        int num = stoi(temp);
			        if (num > max_grado)			   
			        	max_grado = num;
			    }
		    }
	    }
	}
	return max_grado;
}

void vector_coeficientes (vector<vector<long double>> &polinomios_coeficientes, vector<vector<string>> &v_polinomio, int tam_v_poli){
	
    for(int k=0; k<tam_v_poli; k++){ //numero de vectores 
    	for (int q=0; q< v_polinomio.at(k).size(); q++){	// filas de cada vector 
            string temp = "0"; // Si no hay x, el grado es 0
            for (int i=0; i<v_polinomio.at(k).at(q).size(); i++){ //elementos de las filas de cada vector
            //Posicion del coeficiente o el grado de cada monomio
                if(v_polinomio.at(k).at(q)[i] == 'x'){
                // if 'x' is found, check the number after it
                    for(int j=i+1; j<v_polinomio.at(k).at(q).size(); j++){
                        if(isdigit(v_polinomio.at(k).at(q)[j])){
                            // if the next character is a digit, add it to the temp string
                            temp += v_polinomio.at(k).at(q)[j];
                        }
                    }
                    if(temp == "0") // si x no tiene exponente, su grado es 1
                    	temp = '1';
                    else if (temp == "00")
						temp = "0";
                }
            }
            int posicion = stoi(temp);
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ahora identificar el elemento que se encuentra antes que la x
            string aux = "";
            for (int z=0; z<v_polinomio.at(k).at(q).size(); z++){            	
                if (v_polinomio.at(k).at(q)[z] == 'x'){
                    break;
                }
                else 
                	aux += v_polinomio.at(k).at(q)[z];                       
            }
            if (aux == "+")						////////////////  Agregue estas dos lineas para solucionar el errod del stod
            	aux = "1";   
			else if (aux == "-")
				aux = "-1";    
			else if (aux == "")
				aux = "0";
           /////////////////
            long double coef = stold(aux);
            polinomios_coeficientes.at(k).at(posicion) = coef;
		}
        // despues de aqui se reinica la posicion y coef
    }
}
	
bool verifica_conv_stod(const string &analisis){
	size_t caract_procesados;
    stod(analisis, &caract_procesados);
    if (caract_procesados != analisis.size()) return false;
	else return true;	
}

void sumar(int& n, int& max_grado, vector<long double>& suma, vector<vector<long double>> &polinomios_coeficientes){
    for(int j=0; j< max_grado+1 ;j++){
    	long double auxi = 0.0;
        for(int k=0; k<n; k++){
            auxi = auxi + polinomios_coeficientes.at(k).at(j);
        }
        suma.at(j) = auxi;
    }
}

void imprimir_suma(int& max_grado, vector<long double>& suma) {
    cout << endl << "El polinomio suma es de grado "<< max_grado <<":" <<endl;
    for (int i = max_grado; i >= 0; i--) {
        if (suma.at(i) != 0) {
            if (suma.at(i) < 0)
                cout << " - ";
            else if (i != max_grado)
                cout << " + ";

            cout << abs(suma.at(i));

            if (i == 1)
                cout << "*x";
            else if (i != 0)
                cout << "*x^" << i;
        }
    }
}

