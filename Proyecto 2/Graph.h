
#include <iostream>
#include "VectorJ.h"
#include "Queue.h"
#include "Stack.h"
#include <string>

/*
* @class Graph
* @atribute root: raiz del grafo
* @brief grafo que almacena nodos en un vector
* @class GNode: nodo del grafo, utiiza un VectorJ de nodos para los hijos
* @atribute data: dato del nodo insertado
* @atribute visited: regresa los nodos visitados empezando desde root
*/
template<class T>
class Graph {
private:
    class GNode {
    private:
        T data;
        bool visited = false;
        bool deQueue = false;
        bool smell = true;
        int level = 0;
        int cost = 0;
        int path= 0;
        
        VectorJ<GNode*> children;
        VectorJ<int>dist;
        VectorJ<int> costs;
        GNode* parent;
    public:
        GNode() {}
        GNode(T d) {
            data = d;
        }
        friend class Graph;
    };

public:
    GNode* root = nullptr;
    int nodeCount = 0;
    int infinite = 9999;
    Graph() {}
    Graph(T data);
    Graph(Graph& gr2);
    void insert(T parent, T newData, int c);
    void print();
    static void setVisitedFalse(Queue<GNode*> qV);
    void deleteNode(T parent, T data);
    void iterativeDFS(T data);
    int dijkstra(T src, T goal);
    int heuristic(GNode* src, GNode* goal);
    int aStar(T src, T goal);
    //int intersect(bool a, bool b);
    bool biderectionalBFS(T data1, T data2);
    static std::string GetAroma(int i) {
        if (i < 4) {
            return "Huele mal. Por aqui no\n";
        }
        else if (i < 7) {
            return "Huele normal. Avanzando\n";
        }
        else {
            return "Huele bien. Avanzando\n";
        }
    }

    static GNode* HBHambre(GNode* begin) {
        std::cout << "Buscando comida\n";
        begin->visited = true;
        begin->deQueue = false;
        Queue<GNode*> q;
        q.push(begin);
        Queue<GNode*> qVisited;
        GNode* tmp = q.front();
        qVisited.push(tmp);
        while (tmp->children.size()) {
            for (int i = 0; i < tmp->children.size(); i++) {
                if (!tmp->children[i]->visited) {
                    tmp->children[i]->visited = true;
                    std::cout << GetAroma(tmp->children[i]->data);
                    if (tmp->children[i]->data > 3) {
                        if (tmp->children[i]->data == 10) {
                            setVisitedFalse(qVisited);
                            std::cout << "Se encontro la comida\n";
                            return tmp->children[i];
                        }
                        q.push(tmp->children[i]);
                        qVisited.push(tmp->children[i]);
                    }
                }

            }
            q.pop();
            tmp = q.front();
        }
        setVisitedFalse(qVisited);
        std::cout << "No se encontro la comida\n";
        return nullptr;
    }
    static GNode* HBHambreMemoria(GNode* begin) {
        std::cout << "Buscando comida\n";
        begin->visited = true;
        begin->deQueue = false;
        Queue<GNode*> q;
        q.push(begin);
        Queue<GNode*> qVisited;
        GNode* tmp = q.front();
        qVisited.push(tmp);
        GNode* lastNode = nullptr;
        while (tmp->children.size()) {
            for (int i = 0; i < tmp->children.size(); i++) {
                if (tmp->children[i]->smell) {
                    tmp->children[i]->visited = true;
                    std::cout << GetAroma(tmp->children[i]->data);
                    if (tmp->children[i]->data > 3) {
                        q.push(tmp->children[i]);
                        qVisited.push(tmp->children[i]);
                        if (tmp->children[i]->data == 10) {
                            setVisitedFalse(qVisited);
                            std::cout << "Se encontro el la comida\n";
                            return tmp->children[i];
                        }
                    }
                    else {
                        tmp->children[i]->smell = false;
                        if (tmp->children.size()-1 == i) {
                            q.push(lastNode);
                        }
                    }
                    
                }

            }
            lastNode = q.back();
            q.pop();
            tmp = q.front();
        }
        setVisitedFalse(qVisited);
        std::cout << "No se encontro la comida\n";
        return nullptr;
    }

    void start();
    
    /*
    * @param data: dato del nodo a buscar
    * @brief busca un nodo a travez de BFS (amplitud)
    * @return regresa el nodo si lo encuentra, de lo contrario pone a sus hijos como visitados = falso
    */
    GNode* NBFS(T data) {
        root->visited = true;
        root->deQueue = false;
        Queue<GNode*> q;
        q.push(root);
        Queue<GNode*> qVisited;
        GNode* tmp = q.front();
        while (tmp) {
            if (tmp->data == data) {
                setVisitedFalse(qVisited);
                tmp->deQueue = true;
                //tmp->visited = true;
                return tmp;
            }
            else {
                for (int i = 0; i < tmp->children.size(); i++) {
                    if (!tmp->children[i]->visited) {
                        tmp->children[i]->visited = true;
                        tmp->children[i]->path = infinite;
                        
                        q.push(tmp->children[i]);
                        qVisited.push(tmp->children[i]);
                    }

                }
                q.pop();
                tmp = q.front();
            }
        }
        setVisitedFalse(qVisited);
        return nullptr;
    }

    /*
    * @param data: dato del nodo a buscar
    * @brief busca un nodo a travez de DFS (profundidad)
    * @return regresa el nodo si lo encuentra, de lo contrario pone a sus hijos como visitados = falso
    */
    GNode* NDFS(T data) {
        root->visited = true;
        Stack<GNode*> s;
        s.push(root);
        Queue<GNode*> qVisited;
        GNode* tmp = s.front();
        while (tmp) {
            
            if (tmp->data == data) {
                setVisitedFalse(qVisited);
                //tmp->visited = true;
                
                return tmp;
            }
            else {
                s.pop();
                
                for (int i = 0; i < tmp->children.size(); i++) {
                    if (!tmp->children[i]->visited) {
                        tmp->children[i]->visited = true;
                        s.push(tmp->children[i]);
                        qVisited.push(tmp->children[i]);
                        
                    }
                    //cout << tmp->children[i]->data << endl;
                }
                tmp = s.front();
            }
        }
        setVisitedFalse(qVisited);
        return nullptr;
    }
    GNode* limitedDFS(T data, int depth) {
        
        Stack<GNode*> s;
        s.push(root);
        root->visited = true;
        root->level = 0;
        Queue<GNode*> qVisited;
        GNode* tmp = s.front();
        int counter = 0;
        while (tmp) {

            if (tmp->data == data) {
                if (tmp->level <= depth) {
                    setVisitedFalse(qVisited);
                    
                    return tmp;
                }
                else {
                    cout << "muy poca profundidad" << endl;
                    break;
                }
                //break;
            }

            else {
                s.pop();
                if (depth >= 0) {
                    for (int i = 0; i < tmp->children.size(); i++) {
                        if (!tmp->children[i]->visited) {
                            tmp->children[i]->visited = true;
                            
                            tmp->children[i]->level = tmp->level + 1;
                            cout << " " << tmp->children[i]->data << " esta en el nivel -->" << tmp->children[i]->level << endl;
                            s.push(tmp->children[i]);
                            qVisited.push(tmp->children[i]);
                        }
                    }
                    tmp = s.front();
                }
            }
        }
        setVisitedFalse(qVisited);
        return nullptr;
    }

    GNode* iterariveDFS(T data) {
        GNode* r = nullptr;
        int profundidad = 1;
        while (true) {

            r = limitedDFS(data,profundidad);
            if(r)
                if (r->data == data) {
                    return r;
                }
            profundidad++;
        }
    }

    T getMaxHillClimping() {
        T data = 0;
        T lastData = 0;
        GNode* r = nullptr;
        int nCheck = 0;
        while (true) {

            r = NDFS(data);
            if (r) {
                nCheck = 0;
                lastData = r->data;
            }
            else {
                nCheck++;
                if (nCheck > nodeCount) {
                    return lastData;
                }
            }
            data++;
        }
    }
};
/*
*                    grafo creado
*                  6-—7——1—---———2
*                   \  \/| \____ |
*                    \ /\|      \|
*                     4--5-------3
*                         \     /
*                          \   /
*                           \ /
*                            8
*
*/

/*
* @param data: root del arbol
*/
template <class T>
Graph<T>::Graph(T d) {
    nodeCount = 1;
    root = new GNode(d);
}
/*
* @brief imprime el grafo, cada nodo con sus hijos
*/
template <class T>
void Graph<T>::print() {
    if (!root) {
        return;
    }
    //cout << nodeCount << endl;
    Queue<GNode*> q;
    Queue<GNode*> qVisited;
    q.push(root);
    int counter = 0;
    while (q.front())
    {
        GNode* tmp = q.front();
        cout << tmp->data << "{";
        auto vectorTmp = tmp->children;
        for (int i = 0; i < tmp->children.size(); i++) {
            if (!vectorTmp[i]->visited) {
                q.push(vectorTmp[i]);
                qVisited.push(vectorTmp[i]);
                vectorTmp[i]->visited = true;
                for (int i = 2; i < tmp->children.size() - 1; i++)
                    cout << ",";
                
            }
            cout << vectorTmp[i]->data << ",";
            
        }
        for (int i = 0; i < tmp->costs.size(); i++) {
            cout << tmp->costs[i];
        }
        q.pop();
        cout << "}\n";
    }
    setVisitedFalse(qVisited);
}
/*
* @param qV: Queue que almacena nodos.
* @brief setea a los nodos como visitados = falso
*/
template<class T>
void Graph<T>::setVisitedFalse(Queue<GNode*> qV) {
    while (qV.front()) {
        qV.front()->visited = false;
        qV.pop();
    }
}
/*
* @param parent: dato del nodo al que se le va a insertar
* @param newData: dato del nodo a insertar
* @brief inserta un nodo en el parent si este existe y si existe el param newData lo declara como el nuevo hijo
*/
template <class T>
void Graph<T>::insert(T parent, T newData, int c) {

    GNode* tmp = NBFS(parent);
    if (tmp) {
        GNode* tmp2 = NBFS(newData);
        if (tmp2) {
            tmp->children.push_back(tmp2);
            tmp->costs.push_back(c);
        }
        else {
            tmp->children.push_back(new GNode(newData));
            tmp->costs.push_back(c);
            nodeCount++;
        } 
    }
}

/*
* @param parent: parent del dato a eliminar
* @param data: dato a eliminar
* @brief elimina un dato del nodo parent
*/
template<class T>
void Graph<T>::deleteNode(T parent, T data) {
    GNode* tmp = NBFS(parent);
    if (tmp) {
        GNode* tmp2 = NBFS(data);
        if (tmp2) {
            tmp->children.erase(tmp2);
        }
    }
}
template<class T>
void Graph<T>::iterativeDFS(T data) {
    root->visited = true;
    Stack<GNode*> s;
    s.push(root);
    Queue<GNode*> qVisited;
    GNode* tmp = s.front();
    while (tmp) {
        if (tmp->data == data) {
            setVisitedFalse(qVisited);
            //return tmp;
        }
        else {
            s.pop();
            for (int i = 0; i < tmp->children.size(); i++) {
                if (!tmp->children[i]->visited) {
                    tmp->children[i]->visited = true;
                    s.push(tmp->children[i]);
                    qVisited.push(tmp->children[i]);
                }
            }
            tmp = s.front();
        }
    }
    setVisitedFalse(qVisited);
    //return nullptr;
}


 template <class T>
 bool Graph<T>::biderectionalBFS(T data1, T data2) {
     GNode* src = NBFS(data1);
     GNode* goal = NBFS(data2); 
     //goal->visited = true;
     Queue<GNode*> q1;
     q1.push(src);
     src->visited = true;
     Queue<GNode*> q2;
     q2.push(goal);
     
     Queue<GNode*> qVisited1;
     Queue<GNode*> qVisited2;
     int intersect = -1;
     if (src == nullptr || goal == nullptr) {
         return false;
     }
     while (q1.getSize() > 0 && q2.getSize() > 0) {
         GNode* tmp = q1.front();
         GNode* tmp2 = q2.front();
         for (int i = 0; i < tmp->children.size(); i++) {
             if (!tmp->children[i]->visited) {
                 tmp->children[i]->visited = true;
                 tmp->children[i]->path = infinite;

                 q1.push(tmp->children[i]);
                 qVisited1.push(tmp->children[i]);
             }

         }
         q1.pop();
         tmp = q1.front();
         for (int i = 0; i < tmp2->children.size(); i++) {
             if (!tmp2->children[i]->visited) {
                 tmp2->children[i]->visited = true;
                 tmp2->children[i]->path = infinite;

                 q2.push(tmp2->children[i]);
                 qVisited2.push(tmp2->children[i]);
             }

         }
         q2.pop();
         tmp2 = q2.front();
        
         for (int i = 0; i < nodeCount; i++) {
             
             if (tmp->visited && tmp2->visited) {
                 intersect = i;
                 setVisitedFalse(qVisited1);
                 setVisitedFalse(qVisited2);
                 cout << intersect << endl;
                 return true;
             }
             else
             {
                 return false;
             }
             
         }
     }
     setVisitedFalse(qVisited1);
     setVisitedFalse(qVisited2);
     return false;
     
 }

 /*
* @param src: dato del nodo de inicio
* @param goal: dato del nodo final
* @brief elige el camino mas economico hacia el objetivo, inicializando al inicio con un costo de 0 y
* los demas en infinito.
*/
 template <class T>
 int Graph<T>::dijkstra(T src, T goal) {
     GNode* start = NBFS(src);
     GNode* end = NBFS(goal);
     //cout << end->data;
     Queue<GNode*> q;
     start->parent = nullptr;
     start->path = 0;
     start->visited = true;
     q.push(start);
     Queue<GNode*> qVisited;
     
     while (q.getSize()>0) {
         GNode* tmp = q.front();
        
         if (tmp->data == end->data) {
             
             setVisitedFalse(qVisited);
             
             cout << tmp->data << " camino mas corto desde " << start->data << " tiene valor de " << tmp->path << endl;
             
             return tmp->path;
         }
         else {
             
             for (int i = 0; i < tmp->children.size(); i++) {
                 
                 if (!tmp->children[i]->visited && (tmp->path + tmp->costs[i] < tmp->children[i]->path)) {
                     
                     tmp->children[i]->visited = true;
                     tmp->children[i]->path = tmp->path + tmp->costs[i];
                     tmp->children[i]->parent = tmp;
                     
                     cout << tmp->children[i]->data << " es hijo de: " << tmp->children[i]->parent->data <<" con valor de "<< tmp->costs[i] << endl;
                     q.push(tmp->children[i]);
                     qVisited.push(tmp->children[i]);
                     qVisited.push(tmp);
                 }
             }
             q.pop();
             tmp = q.front();
         }
     }
     setVisitedFalse(qVisited);
     
 }

 template <class T>
 int Graph<T>::heuristic(GNode* src, GNode* goal) {
     
 }
 template <class T>
 int Graph<T>::aStar(T src, T goal) {
     GNode* start = NBFS(src);
     GNode* end = NBFS(goal);
     //cout << end->data;
     Queue<GNode*> q;
     start->parent = nullptr;
     start->path = 0;
     start->visited = true;
     q.push(start);
     Queue<GNode*> qVisited;

     while (q.getSize() > 0) {
         GNode* tmp = q.front();

         if (tmp->data == end->data) {

             setVisitedFalse(qVisited);

             cout << tmp->data << " camino mas corto desde " << start->data << " tiene valor de " << tmp->path << endl;

             return tmp->path;
         }
         else {

             for (int i = 0; i < tmp->children.size(); i++) {

                 if (!tmp->children[i]->visited && (tmp->path + tmp->costs[i] < tmp->children[i]->path)) {

                     tmp->children[i]->visited = true;
                     tmp->children[i]->path = tmp->path + heuristic(tmp->children[i], end);
                     tmp->children[i]->parent = tmp;

                     cout << tmp->children[i]->data << " es hijo de: " << tmp->children[i]->parent->data << " con valor de " << tmp->costs[i] << endl;
                     q.push(tmp->children[i]);
                     qVisited.push(tmp->children[i]);
                     qVisited.push(tmp);
                 }
             }
             q.pop();
             tmp = q.front();
         }
     }
     setVisitedFalse(qVisited);

 }
/**
* @brief inicia las funciones
*/
template <class T>
void Graph<T>::start() {
    insert(5, 8, 4);
    insert(8, 4, 3);
    insert(4, 2, 5);
    insert(5, 4, 8);
    insert(5, 9, 5);
    insert(9, 7, 7);
    insert(2, 9, 6);
    insert(7, 1, 2);
    insert(1, 6, 2);
    insert(6, 4, 8);
    insert(7, 10, 6);
    insert(5, 7, 6);
    insert(1, 10, 1);
    insert(8, 7, 5);
    //insert(2, 7, 1);
    
    
    print();
    
    cout << "BREATH FIRST SEARCH" << endl;
    GNode* BFS = NBFS(2);
    if (BFS) {
        cout << "si esta " <<BFS->data<< endl;
    }
    else {
        cout << "no esta" << endl;
    }

    cout << "DEEP FIRST SEARCH" << endl;
    GNode* DFS = NDFS(10);
    if (DFS) {
        cout << "si esta " << DFS->data << endl;
    }
    else {
        cout << "no esta" << endl;
    }

    cout << "LIMITED SEARCH" << endl;
    if (limitedDFS(6,1)) {
        cout << "si esta" << endl;
    }
    else {
        cout << "no esta" << endl;
    }
    
    cout << "BIDIRECTIONAL SEARCH" << endl;
    if (biderectionalBFS(6,2)) {
        cout << "hay camino" << endl;
    }
    else {
        cout << "no hay camino" << endl;
    }

    cout << "DIJKSTRA" << endl;
    cout<<dijkstra(4, 7)<<endl;
    //dijkstra(4, 2);
    
    cout << "ITERATIVE SEARCH" << endl;
    GNode* p = iterariveDFS(10);
    cout << p->data << " encontrado.\n" << endl;

    cout << "HEURISTIC SEARCH NORMAL" << endl;
    HBHambre(root);
    cout << "HEURISTIC SEARCH MEMORY 1" << endl;
    HBHambreMemoria(root);
    cout << "HEURISTIC SEARCH MEMORY 2" << endl;
    HBHambreMemoria(root);

    cout << "HILLCLIMPING" << endl;
    cout << getMaxHillClimping() << endl;

}



