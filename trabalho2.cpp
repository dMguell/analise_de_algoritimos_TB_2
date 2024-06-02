#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

class Grafo {
private:
    unordered_map<char, vector<char>> addList1; // um tipo de map que deixa vc somente dizer que tipo de dado vai entrar, tbm deixa vc colocar vetores
                                                                                                                                    // dentro dele
    unordered_map<char, vector<char>> addList2; // msmc coisa que o 1                                                                                                                                   
    unordered_map<char, vector<pair<char, int>>> addList3; // msm coisa que o 1 e 2, só que o vetor possui 2 campos, vertice destino, e o peso

public:
    // Função para adiciona uma aresta ao grafo
    void addAresta1(char de, char para) {

        if(de != para){ // se a aresta origem for diferente da destino faça:

            addList1[de].push_back(para); // o "de" está entrando na primeira parte do "unordered_map" (no caso, no primeiro char) enquanto que para 
                                    // add o char "para" na variavel "vector", é necessario usar o "push_back", além de tbm fazer a conecção do grafo
            addList1[para].push_back(de); // por se tratar de um grafo não ordenado, é necessário fazer o processo inverso para cada vertice

        }else{} // se não, n faça nada
    }                                      

    // Printa o grafo
    void printGrafo1() {

        for (auto it = addList1.begin(); it != addList1.end(); it++) { // criando uma variavel "it", e percorrendo todas as arestas do grafo

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

    void addAresta2(char de, char para) {

        if(de != para){// se a aresta origem for diferente da destino faça:

            addList2[de].push_back(para); // por se tratar de um grafo orientado, não tem necessidade de fazer os dois caminhos para os vertices

        }else{}
    }

    // Printa o grafo
    void printGrafo2() {

        for (auto it = addList2.begin(); it != addList2.end(); it++) { // criando uma variavel "it", e percorrendo todas as arestas do grafo

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

        if(de != para){ // se a aresta origem for diferente da destino faça:

            addList3[de].push_back({para, peso}); // por se tratar de um grafo não ordenado, são feita duas variaveis, uma pra ida e uma para volta
            addList3[para].push_back({de, peso});

        }else{}
    }

    // Imprime o grafo
    void printGrafo3() {

        for (auto aaa : addList3) { // for que já diz q aaa é igual ao mapa

            cout << aaa.first << " -> "; // printando o primeiro campo do mapa (no caso o "de cá")

            for (auto vizinho : aaa.second) { // for que já diz q vizinho é igual ao segundo campo de aaa (no caso o "pra lá" e peso)

                cout << "(" << vizinho.first << ", " << vizinho.second << ") "; // pritando separadamento o "pra lá" juntamente com peso da aresta

            }

            cout << endl;
        }
    }

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------

    // função para a busca em largura
    void buscaL(char inicio) {

        queue<char> q; // fila vazia do c++ para armazenar os vertices que vão ser visitados
        unordered_set<char> visitado; // msm coisa que o unordered_map, só que tipo um vetor

        q.push(inicio); // variavel diciona o vertice inicial a fila e o marca como visitado
        visitado.insert(inicio);

        while (!q.empty()) { // enquanto a fila não estiver vazia faça:
            
            char current = q.front(); // pegar o vertice da frente da fila
            cout << current << " ";
            q.pop();

            //---------------------------------------------------------------------

            // bloco referente aos vizinhos do vertice atual
            for (char vizinho : addList1[current]) {
                
                if (visitado.find(vizinho) == visitado.end()) { // se o vizinho não foi visitado faça:
                
                    q.push(vizinho); // marcar o vertice visinho visitado como visitado
                    visitado.insert(vizinho);

                }
            }
        }
    };

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------

    // função para a busca em profundidade
    void buscaP(char start, unordered_set<char>& visited) {
    stack<char> stack; // pilha vazia do c++ para armazenar os vertices que vão ser visitados
    stack.push(start); // variavel diciona o vertice inicial a fila e o marca como visitado

        while (!stack.empty()) { // enquanto a fila não estiver vazia faça:
            char current = stack.top();
            stack.pop();

            if (visited.find(current) == visited.end()) {
                cout << current << " ";
                visited.insert(current);

                for (char neighbor : addList2[current]) {
                    if (visited.find(neighbor) == visited.end()) {
                        stack.push(neighbor);
                    }
                }
            }
        }
    }

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------

    void menorcaminho(char origem, char destino) {
    unordered_map<char, int> distancia;
    unordered_map<char, char> anterior;
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    
    for (auto& par : addList3) {
        distancia[par.first] = INT_MAX;
        anterior[par.first] = 0;
    }
    
    distancia[origem] = 0;
    pq.push({0, origem});
    
    while (!pq.empty()) {
        char u = pq.top().second;
        pq.pop();
        
        for (auto& vizinho : addList3[u]) {
            char v = vizinho.first;
            int peso = vizinho.second;
            
            if (distancia[v] > distancia[u] + peso) {
                distancia[v] = distancia[u] + peso;
                anterior[v] = u;
                pq.push({distancia[v], v});
            }
        }
    }
    
    if (distancia[destino] == INT_MAX) {
        cout << "Não há caminho entre " << origem << " e " << destino << endl;
    } else {
        vector<char> caminho;
        for (char v = destino; v != 0; v = anterior[v]) {
            caminho.push_back(v);
        }
        cout << "Menor caminho entre " << origem << " e " << destino << ": ";
        for (int i = caminho.size() - 1; i >= 0; i--) {
            cout << caminho[i];
            if (i > 0) {
                cout << " -> ";
            }
        }
        cout << endl;
        
        cout << "Arestas:" << endl;
        for (int i = caminho.size() - 1; i > 0; i--) {
            char u = caminho[i];
            char v = caminho[i - 1];
            for (auto& aresta : addList3[u]) {
                if (aresta.first == v) {
                    cout << u << " - " << v << " (" << aresta.second << ")" << endl;
                    break;
                }
            }
        }
    }
}

};

int main() {

    Grafo grafo;

    //EX: grafo.addAresta('aresta origem', 'aresta destino');

    /*cout << "----------------------------------------------------------------------";
    cout << endl;

    cout << "GRAFO 1";
    cout << endl;
    cout << endl;

    grafo.addAresta1('a', 'b');
    grafo.addAresta1('a', 'e');
    grafo.addAresta1('b', 'f');
    grafo.addAresta1('e', 'f');
    grafo.addAresta1('e', 'i');
    grafo.addAresta1('i', 'f');
    grafo.addAresta1('f', 'c');
    grafo.addAresta1('f', 'g');
    grafo.addAresta1('f', 'j');
    grafo.addAresta1('c', 'g');
    grafo.addAresta1('c', 'h');
    grafo.addAresta1('c', 'd');
    grafo.addAresta1('d', 'h');
    grafo.addAresta1('d', 'g');
    grafo.addAresta1('g', 'h');
    grafo.addAresta1('g', 'l');
    grafo.addAresta1('j', 'k');
    grafo.addAresta1('g', 'k');
    grafo.addAresta1('k', 'l');
    grafo.addAresta1('h', 'l');

    grafo.printGrafo1();

    cout << endl;

    cout << "Busca em largura partindo de 'b': ";
    grafo.buscaL('b'); // altere o vertice inical aq
    cout << endl;
    
    cout << "----------------------------------------------------------------------";
    cout << endl;*/

    /*cout << "----------------------------------------------------------------------";
    cout << endl;

    cout << "GRAFO 2";
    cout << endl;
    cout << endl;

    grafo.addAresta2('a', 'b');
    grafo.addAresta2('a', 'e');
    grafo.addAresta2('a', 'f');
    grafo.addAresta2('b', 'e');
    grafo.addAresta2('f', 'e');
    grafo.addAresta2('b', 'c');
    grafo.addAresta2('e', 'g');
    grafo.addAresta2('e', 'd');
    grafo.addAresta2('f', 'h');
    grafo.addAresta2('c', 'd');
    grafo.addAresta2('g', 'h');
    grafo.addAresta2('g', 'c');
    grafo.addAresta2('h', 'd');

    grafo.printGrafo2();

    unordered_set<char> visited;

    cout << "Busca em profundidade partindo de 'a': ";
    grafo.buscaP('a', visited); // altere o vertice inical aq
    cout << endl;*/

    cout << "----------------------------------------------------------------------";
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

    cout << endl;
    cout << endl;

    grafo.menorcaminho('x', 't');
    cout << endl;

    cout << "----------------------------------------------------------------------";
    cout << endl;

}
