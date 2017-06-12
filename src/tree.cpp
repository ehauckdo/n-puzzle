#include "tree.h"
#include <cstddef>
#include <util.h>
#include <iostream>

Tree::Tree(Board* b){
    root = new Node(NULL, b, -1);
}

Tree::~Tree(){
    delete root;
}


void Tree::backTracking(Board* objective){
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    std::vector<std::vector<int> > visited_states;
    visited_states.push_back(current->board->board);

    Node* found = NULL;

    while(current != NULL && current->board != objective){

        Node* next = current->expand();
        //next->board->printBoard();
        //return;
        if(next != NULL){
            //std::cout << "Testing state (id:"<< next->id<<"): " << std::endl;
            //next->board->printBoard();
            if(util::contains(visited_states, next->board->board)){
                 //std::cout << "Already in history. Continuing...: " << std::endl;
               continue;
            }
            else{
                if(next->board->board == objective->board){
                    std::cout << "Objective found! exiting...: " << std::endl;
                    found = next;
                    break;
                }
                else{
                    //std::cout << "New state! saving...: " << std::endl;
                    visited_states.push_back(next->board->board);
                    //std::cout << "Number of states: " << visited_states.size() << std::endl;
                }
            }
            current = next;
        }

        else{
            current = current->parent;
            //std::cout << "No more expansions! Returning to parent (id:"<< current->id<<")" << std::endl;
        }
    }

    if(found != NULL){
        found->board->printBoard();
    }


    delete root_copy;

}

void Tree::DFS(Board* objective){
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    std::vector<std::vector<int> > visited_states;
    std::vector<Node*> open_nodes;

    open_nodes.push_back(current);
    Node* found = NULL;

    while(open_nodes.size() > 0 && current != NULL){

        current = open_nodes.back();
        open_nodes.pop_back();

         if(current->board->board == objective->board){
            std::cout << "Objective found! exiting...: " << std::endl;
            found = current;
            break;
        }

        Node* next = current;
        //std::cout << "Current: " << std::endl;
        //next->board->printBoard();
        //std::cout << std::endl;
        do{
            Node* child = next->expand();
            open_nodes.push_back(child);
            //std::cout << "Inserting: " << std::endl;
            //child->board->printBoard();
        }while(next->isfullyExpanded() == false);

    }

    if(found != NULL){
        found->board->printBoard();
    }

    delete root_copy;

}

void Tree::BFS(Board* objective){
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    std::vector<std::vector<int> > visited_states;
    std::vector<Node*> open_nodes;

    open_nodes.push_back(current);
    Node* found = NULL;

    while(open_nodes.size() > 0 && current != NULL){

        current = open_nodes.front();

        // check if current is the objective
        if(current->board->board == objective->board){
            std::cout << "Objective found! exiting...: " << std::endl;
            found = current;
            break;
        }


        Node* next = current;
        //std::cout << "Current: " << std::endl;
        //next->board->printBoard();
        //std::cout << std::endl;
        // open current node
        do{
            Node* child = next->expand();
            open_nodes.push_back(child);
            //std::cout << "Inserting: " << std::endl;
            //child->board->printBoard();
        }while(next->isfullyExpanded() == false);

        open_nodes.erase(open_nodes.begin());

    }

    if(found != NULL){
        found->board->printBoard();
    }

    delete root_copy;

}

void Tree::uniformCostSearch(Board* objective){

}

void Tree::greedySearch(Board* objective){

}

void Tree::aStar(Board* objective){

}

void Tree::idaStar(Board* objective){

}
