#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;
//Esta solo mostrara las intrucciones al jugador, de como jugar.
class class_intrucciones{
    public:
    void met_mostrarIntrucciones();
};
void class_intrucciones::met_mostrarIntrucciones(){
    cout << "\n|-----------------------------Intrucciones de como jugar-----------------------------|" << endl;
    cout << " " << endl;
    cout << "1. Para ganar, tu puntaje debe ser menor o igual a 21, pero mayor al del crupier." << endl;
    cout << " " << endl;
    cout << "2. Las cartas Q - K - J valen por 10 y la carta A vale por 11 siempre y cuando" << endl;
    cout << "   el puntaje no supere los 21, en todo caso valdra 1." << endl;
    cout << " " << endl;
    cout << "3. El crupier solo te mostrara una de las cartas de su mazo" << endl;
    cout << "   y tendras que adivinar si tu puntaje es mayor o menor al de el." << endl;
    cout << " " << endl;
    cout << "4. En todo caso de quedar en empate, tu apuesta seguira intacta, no" << endl;
    cout << "   perderas ni ganaras dinero." << endl;
    cout << " " << endl;
    cout << "5. Recuerda que puedes pedir mas cartas en todo caso de que tu puntaje" << endl;
    cout << "   sea menor, pero recuerda que las cartas son aleatorias a si que" << endl;
    cout << "   ten cuidado a la hora de pedir, ya que te pueden dar una carta" << endl;
    cout << "   que te deje el puntaje por encima de 21." << endl;
    cout << " " << endl;
    cout << "6. Si ganas tu apuesta se duplicara x2, pero si pierdes, perderas" << endl;
    cout << "   todo el dinero que apostastes" << endl;
    cout << " " << endl;
    cout << "|-------------------------------------------------------------------------------------|" << endl;
}
//Se encarga de recibir datos del jugador, como su nombre y la cantidad de dinero que desea apostar.
class class_jugador {
    private:
    string atr_nombre;
    int atr_dinero;
    public:
    string met_darNombre();
    int met_darDinero();
};
string class_jugador::met_darNombre(){
    cout << "Ingrese su nombre: ";
    cin >> atr_nombre;
    return atr_nombre;
}
int class_jugador::met_darDinero(){
    cout << "Ingrese el dinero que desea apostar: ";
    cin >> atr_dinero;
    return atr_dinero;
}
//Este tiene el proposito de darles un puntaje a las cartas que se generan en el mazo y tambien de sumar ese puntaje.
class class_valor_Carta {
private:
string atr_carta;
string atr_simbolo;

public:
class_valor_Carta(string atr_carta, string atr_simbolo);
string met_darCarta() const;
string met_darSimbolo() const;
int met_Puntaje() const;
};
class_valor_Carta::class_valor_Carta(string atr_carta, string atr_simbolo) : atr_carta(atr_carta), atr_simbolo(atr_simbolo) {}
string class_valor_Carta::met_darCarta() const {
    return atr_carta;
}
string class_valor_Carta::met_darSimbolo() const {
    return atr_simbolo;
}
int class_valor_Carta::met_Puntaje() const {
    if (atr_carta == "A") {
        return 11;
    } else if (atr_carta == "K" || atr_carta == "Q" || atr_carta == "J") {
        return 10;
    } else {
        return stoi(atr_carta);
    }
}
//se encargara de generar una carta aleatoria y añadirla al mazo.
class class_mazoCartas {
    private:
    vector<class_valor_Carta> atr_Cartas;
    random_device var_Random;
    mt19937 var_Generador;

    public:
    class_mazoCartas();
    class_valor_Carta met_repartirCarta();
};
class_mazoCartas::class_mazoCartas(): var_Generador(var_Random()){
    string atr_cartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    string atr_simbolos[] = {"♠", "♥", "♦", "♣"};

    for (const string& atr_carta : atr_cartas){
        for (const string& atr_simbolo : atr_simbolos){
            atr_Cartas.push_back(class_valor_Carta(atr_carta, atr_simbolo));
        }
    }
    shuffle(atr_Cartas.begin(), atr_Cartas.end(), var_Generador);
 }
class_valor_Carta class_mazoCartas::met_repartirCarta(){
    class_valor_Carta obj_carta = atr_Cartas.back();
    atr_Cartas.pop_back();
    return obj_carta;
}
//Se encarga de generar la mano del juegador, como las cartas que optiene y el puntaje al que equivalen sus cartas.
class class_mano_jugador{
    private: 
    vector<class_valor_Carta> atr_Cartas;
    int atr_puntaje;
    int atr_numAses;

    public:
    void met_recibirCarta(class_valor_Carta atr_carta);
    void met_mostrarCartas();
    int met_calcularPuntaje(); 
};
void class_mano_jugador::met_recibirCarta(class_valor_Carta atr_carta){
    atr_Cartas.push_back(atr_carta);
}
void class_mano_jugador::met_mostrarCartas(){
    cout << "Cartas: " << endl;
    for (const auto& atr_carta: atr_Cartas){
        cout << atr_carta.met_darCarta() << atr_carta.met_darSimbolo() << endl;
    }
}
int class_mano_jugador::met_calcularPuntaje(){
    atr_puntaje = 0;
    atr_numAses = 0;

    for (const auto& atr_carta : atr_Cartas){
        atr_puntaje += atr_carta.met_Puntaje();
        if (atr_carta.met_darCarta() == "A"){
            atr_numAses++;
        }
    }
    while (var_puntaje > 21 && var_numAses > 0){
        atr_puntaje -= 10;
        atr_numAses--;
    }
    return atr_puntaje;
}
//Se encarga de generar la mano del crupier, tanto como sus cartas, la carta que mostrara, y el puntaje al que equivalen sus cartas.
class class_mano_crupier{
    private:
    vector<class_valor_Carta> atr_Cartas;
    int atr_puntaje;
    int atr_numAses;

    public:
    void met_recibirCartaCRUP(class_valor_Carta atr_carta);
    void met_mostrarCartaCRUP();
    int met_valorCartaCRUP();
};
void class_mano_crupier::met_recibirCartaCRUP(class_valor_Carta atr_carta){
    atr_Cartas.push_back(atr_carta);
}
void class_mano_crupier::met_mostrarCartaCRUP(){
    cout <<"Carta del crupier: ";
    //cout << atr_Cartas[0].met_darCarta() << atr_Cartas[0].met_darSimbolo() << endl;
    for (const auto& atr_carta: atr_Cartas){
        cout << atr_carta.met_darCarta() << atr_carta.met_darSimbolo() << endl;
    }
}
int class_mano_crupier::met_valorCartaCRUP(){
    atr_puntaje = 0;
    atr_numAses = 0;

    for (const auto& atr_carta : atr_Cartas){
        atr_puntaje += atr_carta.met_Puntaje();
        if (atr_carta.met_darCarta() == "A"){
            atr_numAses++;
        }
    }

    while (atr_puntaje > 21 && atr_numAses > 0){
        atr_puntaje -= 10;
        atr_numAses--;
    }

    return atr_puntaje;
}
//Se encargara de mostrar el menu de las decisiones y la opcion para introducir los datos de entrada.
class class_decisiones_menu {
    public:
    void met_mostrar_menu();
    string met_opcion_decision();
};
void class_decisiones_menu::met_mostrar_menu()
{ 
    cout << "Seleccione una opción: " << endl;
    cout << "(1) Jugar Mano" << endl;
    cout << "(2) Pedir una Carta" << endl;
    cout << "(3) Aumentar Apuesta" << endl;
    cout << "(4) Dejar Apuesta" << endl;
}
string class_decisiones_menu::met_opcion_decision()
{
    string atr_opcion;
    cin >> atr_opcion;
    return atr_opcion;
}
//Esta clase se encargara de realizar las ultimas opciones, que pueda decidir el jugador, tanto como pedir otra carta, aumentar su apuesta y o dejar la apuesta.
class class_decisiones{
    public:
    int atr_dineroMas;
    class_valor_Carta met_Pedir_Carta();
    int met_Aumentar_Apuesta();
    void met_Dejar_Apuesta();
};
class_valor_Carta class_decisiones::met_Pedir_Carta(){
    class_mazoCartas obj_mazo;
    return obj_mazo.met_repartirCarta();
}
int class_decisiones::met_Aumentar_Apuesta(){
    cout << "Introduzca la cantidad de dinero que quiere agregar: ";
    cin >> atr_dineroMas;
    return atr_dineroMas;
}
void class_decisiones::met_Dejar_Apuesta(){
    cout << " " << endl;
    cout << "Has abandonaste la apuesta" << endl;
    cout << "Volviendo al menu principal..." << endl;
    cout << " " << endl;
}
//Esta es la clase principal, donde se iniciara todo el juego, aqui se mostrara las mano tanto del Jugador como del crupier y la "mesa de juego".
class class_juego_inicio{
    public:
    int atr_puntajeJugador;
    int atr_puntajeCrupier;
    int atr_dineroJugador;
    string atr_nombreJugador;
    int atr_apuesta_total = 0;
    string atr_opcion;
    void met_juego_inicio();
};
void class_juego_inicio::met_juego_inicio(){
    class_jugador obj_Jugador;
    class_mazoCartas obj_mazo;
    class_mano_jugador obj_manoJugador;
    class_mano_crupier obj_manoCrupier;
    class_decisiones_menu obj_menu;
    class_decisiones obj_decision;

    class_valor_Carta obj_carta1 = obj_mazo.met_repartirCarta();
    class_valor_Carta obj_carta2 = obj_mazo.met_repartirCarta();
    obj_manoJugador.met_recibirCarta(obj_carta1);
    obj_manoJugador.met_recibirCarta(obj_carta2);

    class_valor_Carta obj_cartaCrupier1 = obj_mazo.met_repartirCarta();
    class_valor_Carta obj_cartaCrupier2 = obj_mazo.met_repartirCarta();
    obj_manoCrupier.met_recibirCartaCRUP(obj_cartaCrupier1);
    obj_manoCrupier.met_recibirCartaCRUP(obj_cartaCrupier2);

    atr_puntajeCrupier = obj_manoCrupier.met_valorCartaCRUP();

    atr_nombreJugador = obj_Jugador.met_darNombre();
    atr_dineroJugador = obj_Jugador.met_darDinero();

    do {
    atr_puntajeJugador = obj_manoJugador.met_calcularPuntaje();
    cout << "\n|---------------------Mesa de Juego---------------------|" << endl;    
    cout << "Jugador: " << atr_nombreJugador << endl;

    obj_manoJugador.met_mostrarCartas();
    cout << " " << endl;
    cout << "Puntaje de Cartas: " << atr_puntajeJugador << endl;
    cout << "Apuesta: $" << atr_dineroJugador << endl;
    cout << " " << endl;
    obj_manoCrupier.met_mostrarCartaCRUP();
    cout << "Puntaje de Cartas: " << atr_puntajeCrupier << endl;
    cout << "|--------------------------------------------------------|" << endl;
    obj_menu.met_mostrar_menu();
    atr_opcion = obj_menu.met_opcion_decision();
    cout << "\n|-------------------------------------------------------|" << endl;
    if (atr_opcion == "1"){
        if (atr_puntajeJugador <= 21 && atr_puntajeJugador > atr_puntajeCrupier){
            atr_apuesta_total = atr_dineroJugador * 2;
            cout << " " << endl;
            cout << "Felicidades has ganado con un puntaje mayor al del crupier" << endl;
            cout << "Dinero Total: $" << atr_apuesta_total << endl;
            cout << " " << endl;
            cout << "Volviendo al menu principal..." << endl;
            cout << " " << endl;
            break;
        }
        if (atr_puntajeJugador <= 21 && atr_puntajeJugador < atr_puntajeCrupier){
            atr_apuesta_total = atr_dineroJugador * 0;
            cout << " " << endl;
            cout << "Has perdido con un puntaje menor al del crupier" << endl;
            cout << "Dinero Total: $" << atr_apuesta_total << endl;
            cout << " " << endl;
            cout << "Volviendo al menu principal..." << endl;
            cout << " " << endl;
            break;
        }
        if (atr_puntajeJugador > 21 && atr_puntajeJugador > atr_puntajeCrupier){
            atr_apuesta_total = atr_dineroJugador * 0;
            cout << " " << endl;
            cout << "Has perdido por tener un puntaje mayor a 21" << endl;
            cout << "Dinero Total: $" << atr_apuesta_total << endl;
            cout << " " << endl;
            cout << "Volviendo al menu principal..." << endl;
            cout << " " << endl;
            break;
        }
        if (atr_puntajeJugador > 21 && atr_puntajeJugador < atr_puntajeCrupier){
            atr_apuesta_total = atr_dineroJugador * 0;
            cout << " " << endl;
            cout << "Has perdido por tener un puntaje mayor a 21" << endl;
            cout << "Volviendo al menu principal..." << endl;
            cout << "Dinero Total: $" << atr_apuesta_total << endl;
            cout << " " << endl;
            cout << " " << endl;
            break;
        }
        if (atr_puntajeJugador <= 21 && atr_puntajeJugador == atr_puntajeCrupier){
            atr_apuesta_total = atr_dineroJugador;
            cout << " " << endl;
            cout << "Has empatado por tener un puntaje igual al de crupier" << endl;
            cout << "Dinero Total: $" << atr_apuesta_total << endl;
            cout << " " << endl;
            cout << "Volviendo al menu principal..." << endl;
            cout << " " << endl;
            break;
        }
    }
    else if (atr_opcion == "2"){
        class_valor_Carta obj_carta_dar = obj_decision.met_Pedir_Carta();
        obj_manoJugador.met_recibirCarta(obj_carta_dar);
        atr_puntajeJugador = obj_manoJugador.met_calcularPuntaje();
    }
    else if (atr_opcion == "3"){
    atr_dineroJugador += obj_decision.met_Aumentar_Apuesta(); 
    }
    else if (atr_opcion == "4"){
    obj_decision.met_Dejar_Apuesta();
    break;
    }
    else if (atr_opcion != "1" || atr_opcion != "2" || atr_opcion != "3" || atr_opcion != "4"){
    cout << "Por favor elija la opcion correcta..." << endl;
    }
    } while (atr_opcion != "4");
}
//Esta tiene como fin, mostrar las opciones a elegir en el menu y la opcion de entrada de datos para elegir la opcion deseada.
class class_menu {
    public:
    void met_mostrar();
    int met_leer_opcion();
};
void class_menu::met_mostrar()
{ 
    cout << "\n|------Bienvenido al Juego de Black Jack------|" << endl;
    cout << "Seleccione una opción:" << endl;
    cout << "(1) Jugar" << endl;
    cout << "(2) Instrucciones" << endl;
    cout << "(3) Salir" << endl;
}
int class_menu::met_leer_opcion()
{
    int atr_opcion;
    cin >> atr_opcion;
    return atr_opcion;
}
//Sera la encargada de ejecutar el juego, comenzando con el menu principal, dando 3 opciones a elegir.
class class_ejecutar_juego {
    public:
    int atr_opcion;
    void met_ejecutar();
};
void class_ejecutar_juego::met_ejecutar(){
    class_intrucciones obj_mostrarINS;
    class_menu obj_menu;
    do {
        obj_menu.met_mostrar();
        atr_opcion = obj_menu.met_leer_opcion();

        switch (atr_opcion){
            case 1: {
                class_juego_inicio obj_mostrarMano;
                obj_mostrarMano.met_juego_inicio();
                break;
            }
            case 2: 
                obj_mostrarINS.met_mostrarIntrucciones();
                break;
            
            case 3:
                cout << " " << endl;
                cout << "Saliendo del juego..." << endl;
                break;
            default:
                cout << " " << endl;
                cout << "Opción equivocada, intente de nuevo" << endl;
                cout << " " << endl;
                break;
        }
    } while (atr_opcion != 3);
}
//En el main solo se encuentra la clase de ejecutar el juego.
int main (){
    class_ejecutar_juego obj_ejecutar;
    obj_ejecutar.met_ejecutar();
    return 0;
}