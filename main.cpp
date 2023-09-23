#include <iostream>
#include <random>
#include <string.h>

using namespace std;

const int GRAPH_NODES = 5;
const int GRAPH_MAX_WEIGHT = 20;
const int GRAPH_MIN_WEIGHT = 0;


int generate_random_number(int min, int max){
    random_device rd;
    uniform_int_distribution<int> dist(min,max);
    return dist(rd);
}

class Adjacency_matrix{
    int** graph = new int*[GRAPH_NODES];
    int number_of_edges;
    int total_possible_number_of_edges;
    bool **isVisited = new bool*[GRAPH_NODES];

public:

    int ** getGraph(){
        return graph;
    }

    explicit Adjacency_matrix(char* type){

        total_possible_number_of_edges = GRAPH_NODES*(GRAPH_NODES - 1)/2;
        if (strcmp(type, "dense") == 0){

            number_of_edges = total_possible_number_of_edges*95/100;
            cout<<"Creating a dense Graph with "<<number_of_edges<< " number of edges"<<endl;
        }
        else if(strcmp(type, "sparse") == 0){
            number_of_edges = total_possible_number_of_edges*50/100;
            cout<<"Creating a sparse Graph with "<<number_of_edges<< " number of edges"<<endl;
        }else{
            cout<<"ERROR: Unknown graph type";
        }

        //setting edge weights
        for(int i=0; i<GRAPH_NODES;i++){
            graph[i] = new int[GRAPH_NODES];
            for (int j = 0; j < GRAPH_NODES; ++j) {
                graph[i][j] = generate_random_number(GRAPH_MIN_WEIGHT, GRAPH_MAX_WEIGHT);
            }
        }

        //removing self edges
        for (int i = 0; i < GRAPH_NODES; ++i) {
            graph[i][i] = -1;
        }


        //making the graph undirected
        for (int i = 0; i < GRAPH_NODES; ++i) {
            for (int j = 0; j < GRAPH_NODES; ++j) {
                if (i==j){
                    break;
                }
                graph[j][i] = graph[i][j];
            }
        }



        //making the graph sparse or dense
        for(int i=0; i<GRAPH_NODES;i++){
            isVisited[i] = new bool[GRAPH_NODES];
            for (int j = 0; j < GRAPH_NODES; ++j) {
                isVisited[i][j] = false;
            }
        }

        int removed_edges = 0;
        while(removed_edges != (total_possible_number_of_edges - number_of_edges)){
            int i = generate_random_number(0, GRAPH_NODES-1);
            if (i<=0){
                continue;
            }
            int j = generate_random_number(0, i-1);
            if (!isVisited[i][j]){
                removed_edges++;
                isVisited[i][j] = true;
                graph[i][j] = -1;
                graph[j][i] = -1;
            }

        }


    }

    void print_graph(){
        for (int i = 0; i < GRAPH_NODES; ++i) {
            for (int j = 0; j < GRAPH_NODES; ++j) {
                cout<<graph[i][j]<<"\t";
            }
            cout<<endl;
        }
    }

};



class Graph_node{
    int weight;
    Graph_node * next;

public:
    explicit Graph_node(int w){
        this->next = nullptr;
        this->weight = w;
    }

    void set_next(Graph_node * next_node){
        this->next = next_node;
    }

    Graph_node* get_next(){
        return this->next;
    }

    int get_weight(){
        return this->weight;
    }
};

class Adjacency_List{
    vector<Graph_node> graph;

public:
    Adjacency_List(int **graph_m, int number_of_columns, int number_of_rows){
        cout<<endl<<endl<<endl;
        for (int i = 0; i < number_of_rows; ++i) {
           Graph_node new_node(0);
            graph.push_back(new_node);
        }

        for (int i = 0; i < GRAPH_NODES; ++i) {
            for (int j = 0; j < GRAPH_NODES; ++j) {
                if(graph_m[i][j] != -1){
                    Graph_node* new_node = new Graph_node(graph_m[i][j]);
                    Graph_node * tmp = & graph[i];
                    while(tmp->get_next() != nullptr){
                        tmp = tmp->get_next();
                    }
                    tmp->set_next(new_node);
                }
            }
//            print_list(&graph[i]);

        }
        print_graph();
    }

    void add_edge(Graph_node * source, Graph_node * new_node){
        Graph_node *tmp = source;
        while(tmp->get_next() != nullptr){
            tmp = tmp->get_next();
        }
        tmp->set_next(new_node);
        tmp->get_next()->set_next(nullptr);
    }



    void print_graph(){
        for (int i = 0; i < GRAPH_NODES; ++i) {
            Graph_node * tmp = graph[i].get_next();
            while(tmp != nullptr){
                cout<<tmp->get_weight()<< "\t";
                tmp = tmp->get_next();
            }
            cout<<endl;
        }
    }

//    void print_list(Graph_node * source){
//        Graph_node *tmp = source;
//        while(tmp != nullptr){
//            cout<<tmp->get_weight()<<"\t";
//            tmp = tmp->get_next();
//        }
//
//        cout<<endl<<"line printed"<<endl;
//
//    }



};

int main() {
    Adjacency_matrix graph((char *)"dense");
    graph.print_graph();
    Adjacency_List graph_l(graph.getGraph(), GRAPH_NODES, GRAPH_NODES);
//    graph_l.print_graph();
    return 0;
}
