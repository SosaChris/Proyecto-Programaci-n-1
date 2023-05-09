#include <iostream>
#include <string>
#include <vector>

using namespace std;


void remover_espacios(string* str);

struct tPolinomio {
  int grado;
  vector<double> coef;
};

int main() {
    
    vector<string> vpolinomios_ingresado;
    int n;

    cout << "Introduzca la cantidad de polinomios a sumar: ";
    cin >> n;
    cin.ignore();
    cout << endl;

    // Ingreso de polinomios
    for (int i = 0; i < n; i++) {
        cout << "Polinomio #" << i+1 << ": ";
        string ingreso;
        getline(cin, ingreso);
        vpolinomios_ingresado.push_back(ingreso);
    }

    // Eliminacion de espacios
    for (int i = 0; i < n; i++) {
        remover_espacios(&vpolinomios_ingresado[i]);
        //out << "String #" << i+1 << " without spaces: " << vpolinomios_ingresado[i] << endl; //// Borrar cuando hayamos acabado el proyecto
    }


    // Cada fila del vector es separada por los elementos
  string elemento;
  vector<string> v_polinomio[n];  

    for (int j = 0; j<n; j++) {
      //string* polinomio_analisis = &vpolinomios_ingresado[j];
      string polinomio_analisis = vpolinomios_ingresado[j];

      for (int i = 0; i < polinomio_analisis.length(); i++) {

        if (polinomio_analisis[i] != '+' and polinomio_analisis[i] != '-')
          elemento = elemento + polinomio_analisis[i];

        else if (elemento != "") {
          v_polinomio[j].push_back(elemento);
          elemento = "";
        }
      }
      if (elemento != "")
        v_polinomio[j].push_back(elemento);
        elemento = "";

  // Agregar el signo de cada elemento  
    int q=0;
    char signo = ' ';
    for (int k = 0 ; k < polinomio_analisis.length(); k++) {
    
      if (polinomio_analisis[k] == '+')
        signo = '+';
      else if (polinomio_analisis[k] == '-')
        signo = '-';
      

      if (polinomio_analisis[k] == 'x' ) {
          if(signo=='-'){
          v_polinomio[j][q].insert(0, 1, signo);
          q++;
        }
        else 
          q++;      
      }

    }
    if(signo=='-')  v_polinomio[j][q].insert(0, 1, signo);
  }

///////////////////////////////////////////////////////////////////////////////////

    tPolinomio p[n];
// Identificar el grado
//GPT: How to detect the highest number that is after the letter x in the next string: {2x3 + 3x2 + 1}

  for(int k=0; k<n; k++){
    int max_grado = 0;
    for (int i=0; i<vpolinomios_ingresado[k].length(); i++){
//////
        if(vpolinomios_ingresado[k][i] == 'x'){
            // if 'x' is found, check the number after it
            string temp = "0";
            for(int j=i+1; j<vpolinomios_ingresado[k].length(); j++){
                if(isdigit(vpolinomios_ingresado[k][j])){
                    // if the next character is a digit, add it to the temp string
                    temp = temp + vpolinomios_ingresado[k][j];
                }
                else
                    break; // if the next character is not a digit, break the loop
                
            }

        if(temp == "0")
            temp = "1";
        
            // convert the temp string to an integer and update the highest number
            int num = atoi(temp.c_str());
            if(num > max_grado){
                max_grado = num;
            }
        }
        p[k].grado = max_grado;
        
    }
  }

//    cout << "Max grado:" << p[0].grado <<endl;
//    cout << "Max grado: " << p[1].grado <<endl;
////////////////////////////////

  //Inicializar los vectores de los coeficientes con el tamanio del max_grado
    for(int i = 0; i < n; i++){
        p[i].coef.resize(p[i].grado + 1); // add one to include the constant term
    }


  // Llenar el vector de los coeficientes



// cout << v_polinomio[0][0];

//cout << v_polinomio[0].size();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for(int k=0; k<n; k++){ //numero de vectores 
        for (int q=0; q < v_polinomio[k].size();q++){   // filas de cada vector 
      
            int posicion;
            string temp = "0"; // Si no hay x, el grado es 0
            for (int i=0; i<v_polinomio[k][q].size(); i++){ //elementos de las filas de cada vector
            //Posicion del coeficiente o el grado de cada elemento
            
            
            
                if(v_polinomio[k][q][i] == 'x'){
                // if 'x' is found, check the number after it
            

                    for(int j=i+1; j<v_polinomio[k][q].size(); j++){

                        if(isdigit(v_polinomio[k][q][j])){
                            // if the next character is a digit, add it to the temp string
                            temp = temp + v_polinomio[k][q][j];
                        }
                    
                    }
                    if(temp == "0") // si x no tiene exponente, su grado es 1
                        temp = '1';
                }

            }
            posicion = atoi(temp.c_str());
            ////cout << "Elemento " << q << " posicion: " << posicion <<endl;  /// Borrar
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ahora identificar el elemento que se encuentra antes que la x
        
            int coef;
            string aux = "0";
            for (int z=0; z<v_polinomio[k][q].size(); z++){

                
                if(v_polinomio[k][q][z] == 'x'){
                    if (aux == "0")
                        aux = "1";
                    break;
                }
                else if (isdigit(v_polinomio[k][q][z])){
                //else if ((v_polinomio[k][q][z])){
                    aux = aux + v_polinomio[k][q][z];
                }
                                
            }



            coef = atoi(aux.c_str());
            ////cout << "Elemento " << q << " coef: " << coef <<endl;  /// Borrar
            p[k].coef[posicion] = coef;


        // despues de aqui se reinica la posicion y coef
        }
   }


//////////////////////////////////////
    //Suma de los coeficientes

    /*Identificar cual es el mayor grado de todos los polinomios
    Con este grado vamos a crear un vector resultante de las sumas*/
        
    int max_grad =-1;// condicion para que siempre entre en el loop
    int aux;
    for(int k=0; k<n; k++){
        aux = p[k].grado;
        if (aux > max_grad)
        max_grad = aux;

    }
    
//cout << "grado mas grande: " << max_grad;

    vector<double> suma(max_grad+1);
    int auxi = 0;
    

    for(int j=0; j< max_grad+1 ;j++){   //p[k].coef.size()
        for(int k=0; k<n; k++){
            auxi = auxi + p[k].coef[j];
        }
        suma[j] = auxi;
        auxi = 0;
    }

    cout << "Resultado: " << suma[0] << " + " << suma[1] << "x  + " << suma[2] << "x^2";


    return 0;
}

void remover_espacios(string* str) {
    string str_sin_espacios = "";
    for (int i = 0; i < str->length(); i++) {
        if ((*str)[i] != ' ') {
            str_sin_espacios = str_sin_espacios + (*str)[i];
        }
    }
    *str = str_sin_espacios;
}