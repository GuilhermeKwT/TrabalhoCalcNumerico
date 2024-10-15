#include <iostream>
#include <cmath>

using namespace std;

double func(double x){
    return (pow(x, 3) - 9 * x + 3);
}

double func2(double x){
    return ((pow(x, 3)/9) + (1.0/3.0));
}


double metodoBisseccao(double intervalo[], long double precisao, int it){
    double a = intervalo[0], b = intervalo[1];
    int k = 0;
    double meio, finicio, fmeio;
    if (fabs(b - a) < precisao){
        meio = (a + b) / 2;
    }
    else {
        while (k < it && fabs(b - a) > precisao){
            k++;
            finicio = func(a);
            meio = (a + b) / 2; 
            fmeio = func(meio);
            if (finicio * fmeio < 0){
                b = meio;
            }
            else {
                a = meio;
            }
        }
    }
    cout << "Numero de iteracoes: " << k << endl;
    return meio;
}


double metodoMIL(double x0, double precisao, int it){
    int k = 0;
    double xAnt = 0, x = x0;
    while (abs(func(x)) > precisao && k < it && abs(x - xAnt) > precisao){
        k++;
        xAnt = x;
        x = func2(x);
    }
    cout << "Numero de iteracoes: " << k << endl;
    return x;
}


double derivada(double x){
    return (4 * pow(x, 3) - 6 * pow(x, 2) + 2);
}

double metodoNewton(double x0, double precisao, int it){
    int k = 0;
    double x = x0;
    while (fabs(func(x)) > precisao && k < it){
        k++;
        x = x - (func(x)/derivada(x));
    }
    cout << "Numero de iteracoes: " << k << endl;
    return x;
}


double metodoSecante(double x0, double x1, double precisao, int it){
    int k = 0; 
    double x;
    if (fabs(func(x0)) < precisao){
        return x0;
    }
    else {
        while (fabs(func(x1)) > precisao && fabs(x1 - x0) > precisao && k < it){
            k++;
            x = x1 - ((func(x1) * (x1 - x0)) / (func(x1) - func(x0)));
            x0 = x1;
            x1 = x;
            cout << x0 << "  " << x1 << "  " << x << endl;
        }
    }
    cout << "Numero de iteracoes: " << k << endl;
    return x1;
}


double metodoRegulaFalsi(double intervalo[], double precisao1, double precisao2, int it){
    double a = intervalo[0], b = intervalo[1];
    int k = 0;
    double M, x = a;
    if (fabs(b - a) < precisao1){
        return a;
    }
    if (fabs(func(a)) < precisao2 || fabs(func(b)) < precisao2){
        return a;
    }
    while (fabs(func(x)) > precisao2 && k < it){
        k++;
        M = func(a);
        x = (a * func(b) - b * func(a)) / (func(b) - func(a));
        if (M * func(x) > 0){
            a = x;
        }
        else {
            b = x;
        }
        if (fabs(b - a) < precisao1){
            return a;
        }
    }
    cout << "Numero de iteracoes: " << k << endl;
    return x;
}

//1 - Bisseccao, 2 - MIL, 3 - Newton, 4 - Secante, 5 - Regula-Falsi
double inicializaMetodo(int escolha){
    double raiz, x0, x1, intervalo[2], precisao1, precisao2;
    int it;
    switch(escolha){
        case 1:
            cout << "Digite o intervalo que se deseja utilizar:" << endl;
            cin >> intervalo[0] >> intervalo[1];
            cout << "Digite a precisao solicitada:" << endl;
            cin >> precisao1;
            cout << "Digite o numero maximo de iteracoes" << endl;
            cin >> it;

            raiz = metodoBisseccao(intervalo, precisao1, it);
            break;
        case 2:
            cout << "Digite o valor inicial:" << endl;
            cin >> x0;
            cout << "Digite a precisao solicitada:" << endl;
            cin >> precisao1;
            cout << "Digite o numero maximo de iteracoes" << endl;
            cin >> it;

            raiz = metodoMIL(x0, precisao1, it);
            break;
        case 3:
            cout << "Digite o valor inicial:" << endl;
            cin >> x0;
            cout << "Digite a precisao solicitada:" << endl;
            cin >> precisao1;
            cout << "Digite o numero maximo de iteracoes" << endl;
            cin >> it;

            raiz = metodoNewton(x0, precisao1, it);
            break;
        case 4:
            cout << "Digite o primeiro valor inicial:" << endl;
            cin >> x0;
            cout << "Digite o segundo valor inicial:" << endl;
            cin >> x1;
            cout << "Digite a precisao solicitada:" << endl;
            cin >> precisao1;
            cout << "Digite o numero maximo de iteracoes" << endl;
            cin >> it;

            raiz = metodoSecante(x0, x1, precisao1, it);
            break;
        case 5:
            cout << "Digite o intervalo que se deseja utilizar:" << endl;
            cin >> intervalo[0] >> intervalo[1];
            cout << "Digite a primeira precisao solicitada:" << endl;
            cin >> precisao1;
            cout << "Digite a segunda precisao solicitada:" << endl;
            cin >> precisao2;
            cout << "Digite o numero maximo de iteracoes" << endl;
            cin >> it;

            raiz = metodoRegulaFalsi(intervalo, precisao1, precisao2, it);
            break;
    }

    return raiz;
}

int main(){
    int selecao;
    cout << "Digite qual metodo e desejado:" << endl
         << "1 - Bisseccao" << endl
         << "2 - MIL" << endl
         << "3 - Newton" << endl
         << "4 - Secante" << endl
         << "5 - Regula-Falsi" << endl;
    cin >> selecao;
    cout << "Raiz: " << inicializaMetodo(selecao) << endl;

    return 0;
}