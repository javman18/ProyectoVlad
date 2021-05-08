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
        VectorJ<GNode*> children;
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
    Graph() {}
    Graph(T data);
    Graph(Graph& gr2);
    void insert(T parent, T newData);
    void print();
    void setVisitedFalse(Queue<GNode*> qV);
    void deleteNode(T parent, T data);
    void iterativeDFS(T data);
    bool limitedDFS(T data, int depth);
    //int intersect(bool a, bool b);
    bool biderectionalBFS(T data1, T data2);
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
                }
                tmp = s.front();
            }
        }
        setVisitedFalse(qVisited);
        return nullptr;
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
    cout << nodeCount << endl;
    Queue<GNode*> q;
    Queue<GNode*> qVisited;
    q.push(root);
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
void Graph<T>::insert(T parent, T newData) {

    GNode* tmp = NBFS(parent);
    if (tmp) {
        GNode* tmp2 = NBFS(newData);
        if (tmp2) {
            tmp->children.push_back(tmp2);
        }
        else {
            tmp->children.push_back(new GNode(newData));
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

template<class T>
bool Graph<T>::limitedDFS(T data, int depth) {
    root->visited = true;
    Stack<GNode*> s;
    s.push(root);
    Queue<GNode*> qVisited;
    
    //float depth = 0;
    //float limit = 2;
    GNode* tmp = s.front();
    while (s.getSize()>0) {
        if (depth >= 0) {
            
            //cout << tmp->data << endl;
            if (tmp->data == data) {
                setVisitedFalse(qVisited);
                cout << "se encontro" << endl;
                cout << depth << endl;
                return true;
                //break;
            }
            else {
                s.pop();
                for (int i = 0; i < tmp->children.size(); i++) {
                    if (!tmp->children[i]->visited) {
                        tmp->children[i]->visited = true;
                        s.push(tmp->children[i]);
                        qVisited.push(tmp->children[i]);
                        
                    }
                    limitedDFS(data, depth-1);
                    
                }
                
                tmp = s.front();
            }
            
        }
        else {
            //cout << depth << endl;
            cout << "no se encontro" << endl;
            return false;
        }
            
    }
    setVisitedFalse(qVisited);
    return false;
}

 template <class T>
 bool Graph<T>::biderectionalBFS(T data1, T data2) {
     GNode* src = NBFS(data1);
     GNode* goal = NBFS(data2);
     Queue<GNode*> q1;
     q1.push(src);
     src->visited = true;
     Queue<GNode*> q2;
     q2.push(goal);
     goal->visited = true;
     Queue<GNode*> qVisited1;
     Queue<GNode*> qVisited2;
     GNode* intersectNode = nullptr;
     if (src == nullptr || goal == nullptr) {
         return false;
     }
     while (q1.getSize() > 0 && q2.getSize() >0) {
         GNode* tmp1 = q1.front();
         GNode* tmp2 = q2.front();
         cout << tmp1->data << endl;
         if (tmp1->visited && tmp2->visited) {
             //cout << tmp2->data << endl;
             //cout << intersect << endl;
             return true;
         }
         
         
         //if (tmp1->visited && tmp2->visited) {
         //    setVisitedFalse(qVisited1);
         //    setVisitedFalse(qVisited2);
         //    cout << "encontrado: " << tmp1->data << endl;
         //    cout << "encontrado: " << tmp2->data << endl;
         //    
         //    return;
         //    //break;
         //}
         //else {
         //    for (int i = 0; i < tmp1->children.size(); i++) {
         //        if (!tmp1->children[i]->visited) {
         //            tmp1->children[i]->visited = true;
         //            q1.push(tmp1->children[i]);
         //            qVisited1.push(tmp1->children[i]);
         //        }

         //    }
         //    q1.pop();
         //    tmp1 = q1.front();
         //    for (int i = 0; i < tmp2->children.size(); i++) {
         //        if (!tmp2->children[i]->visited) {
         //            tmp2->children[i]->visited = true;
         //            q2.push(tmp2->children[i]);
         //            qVisited2.push(tmp2->children[i]);
         //        }

         //    }
         //    q2.pop();
         //    tmp2 = q2.front();
         //}
     }
     return false;
     //cout << "queue 1: "<<q1.front()->data << endl;
     //cout << "queue 2: "<<q2.front()->data << endl;
 }

/**
* @brief inicia las funciones
*/
template <class T>
void Graph<T>::start() {
    insert(5, 8);
    insert(8, 4);
    insert(4, 2);
    insert(3, 2);
    /*insert(8, 3);
    
    insert(2, 1);
    insert(1, 7);
    insert(7, 8);
    insert(8, 4);
    insert(4, 1);
    insert(5, 7);
    insert(4, 5);
    insert(1, 3);
    insert(5, 3);
    insert(1, 5);*/
    
    //deleteNode(3,2);
    //deleteNode(7, 6);
    
    /*if (NDFS(4)) {
        cout << "si esta\n";
    }
    else {
        cout << "nohay\n";
    }*/
    print();
    
    //limitedDFS(7, 3);
    if (NBFS(7)) {
        cout << "si esta\n";
    }
    else {
        cout << "nohay\n";
    }
    if (biderectionalBFS(5, 2)) {
        cout << "hay camino" << endl;
    }
    else {
        cout << "no hay camino" << endl;
    }
    
}



