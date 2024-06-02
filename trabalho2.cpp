#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

class Grafo {
private:
    unordered_map<char, vector<char>> addList; // um tipo de map que deixa vc somente dizer que tipo de dado vai entrar, tbm deixa vc colocar vetores
                                                                                                                                    // dentro dele
    unordered_map<char, vector<pair<char, int>>> addList3; // msm coisa, só que o vetor possui 2 campos, vertice destino, e o peso
    //unordered_map<string, vector<string>> addList_EX2;

public:
    // Função para adiciona uma aresta ao grafo
    void addAresta(char de, char para) {
        if(de != para){ // se a aresta origem for diferente da destino faça:
            addList[de].push_back(para); // o "de" está entrando na primeira parte do "unordered_map" (no caso, no primeiro char) enquanto que para 
                                    // add o char "para" na variavel "vector", é necessario usar o "push_back", além de tbm fazer a conecção do grafo     
        }else{} // se não, n faça nada
    }                                      

    // Printa o grafo
    void printGrafo() {
        for (auto it = addList.begin(); it != addList.end(); it++) { // criando uma variavel "it", e percorrendo todas as arestas do grafo
            cout << it->first << " -> "; // printando o "de cá"
            for (char v : it->second) { // criando uma varivel "v" e já tribuiindo o valor de "pra lá" nela, enq tiver uma variavel em "lá", o código roda
                cout << v << " "; // printando o "pra lá"
            }
            cout << endl;
            cout << endl;
        }
    }

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------

    void addAresta3(char de, char para, int peso) {
        addList3[de].push_back({para, peso});
    }

    // Imprime o grafo
    void printGrafo3() {
        for (auto& par : addList3) {
            cout << par.first << " -> ";
            for (auto& vizinho : par.second) {
                cout << "(" << vizinho.first << ", " << vizinho.second << ") ";
            }
            cout << endl;
        }
    }

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------

    void bfs(char origem) {
        unordered_set<char> visitados;
        queue<char> fila;

        fila.push(origem);
        visitados.insert(origem);

        while (!fila.empty()) {
            char verticeAtual = fila.front();
            fila.pop();

            cout << verticeAtual << " ";

            for (const char& vizinho : addList[verticeAtual]) {
                if (visitados.find(vizinho) == visitados.end()) {
                    fila.push(vizinho);
                    visitados.insert(vizinho);
                }
            }
        }
    }
};

int main() {

    Grafo grafo;

    //EX: grafo.addAresta('aresta origem', 'aresta destino');

    cout << "GRAFO 1";
    cout << endl;

    grafo.addAresta('a', 'b');
    grafo.addAresta('a', 'e');
    grafo.addAresta('b', 'f');
    grafo.addAresta('e', 'f');
    grafo.addAresta('e', 'i');
    grafo.addAresta('i', 'f');
    grafo.addAresta('f', 'c');
    grafo.addAresta('f', 'g');
    grafo.addAresta('f', 'j');
    grafo.addAresta('c', 'g');
    grafo.addAresta('c', 'h');
    grafo.addAresta('c', 'd');
    grafo.addAresta('d', 'h');
    grafo.addAresta('d', 'g');
    grafo.addAresta('g', 'h');
    grafo.addAresta('g', 'l');
    grafo.addAresta('j', 'k');
    grafo.addAresta('g', 'k');
    grafo.addAresta('k', 'l');
    grafo.addAresta('h', 'l');

    grafo.printGrafo();

    cout << endl;
    cout << endl;

    // Realizando a busca em largura a partir do vértice "a"
    cout << "Busca em largura a partir do vertice 'b': ";
    grafo.bfs('b');
    cout << endl;
    
    cout << "----------------------------------------------------------------------";
    cout << endl;

    

    /*cout << "----------------------------------------------------------------------";
    cout << endl;

    cout << "GRAFO 2";
    cout << endl;
    cout << endl;

    grafo.addAresta('a', 'b');
    grafo.addAresta('a', 'e');
    grafo.addAresta('a', 'f');
    grafo.addAresta('b', 'e');
    grafo.addAresta('f', 'e');
    grafo.addAresta('b', 'c');
    grafo.addAresta('e', 'g');
    grafo.addAresta('f', 'h');
    grafo.addAresta('c', 'd');
    grafo.addAresta('g', 'h');
    grafo.addAresta('g', 'c');
    grafo.addAresta('h', 'd');

    grafo.printGrafo();*/

    /*cout << "----------------------------------------------------------------------";
    cout << endl;

    cout << "GRAFO 3";
    cout << endl;
    cout << endl;

    grafo.addAresta3('x', 'z', 12);
    grafo.addAresta3('x', 'v', 30);
    grafo.addAresta3('v', 'z', 35);
    grafo.addAresta3('v', 'r', 17);
    grafo.addAresta3('v', 'u', 15);
    grafo.addAresta3('u', 'r', 15);
    grafo.addAresta3('u', 's', 10);
    grafo.addAresta3('u', 't', 5);
    grafo.addAresta3('z', 'r', 25);
    grafo.addAresta3('z', 's', 20);
    grafo.addAresta3('r', 's', 7);
    grafo.addAresta3('s', 't', 12);

    grafo.printGrafo3();

    cout << "----------------------------------------------------------------------";
    cout << endl;*/


}
