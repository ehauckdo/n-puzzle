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

void Tree::BFS(Board* objective){

}

void Tree::DFS(Board* objective){
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    std::vector<std::vector<int> > visited_states;
    std::vector<Node*> open_nodes;

    open_nodes.push_back(current);
    Node* found = NULL;

    while(open_nodes.size() > 0 && current != NULL){

        // check if current is the objective
        if(current->board == objective){
            std::cout << "Objective found! exiting...: " << std::endl;
            break;
        }

        // open current node
        Node* next = current;
        do{
            open_nodes.push_back(next->expand());
        }while(next->isfullyExpanded() == false);

        current = open_nodes.front();
        open_nodes.erase(open_nodes.begin());
        std::cout << "Size: " << open_nodes.size() << std::endl;

    }

    if(found != NULL){
        found->board->printBoard();
    }


    delete root_copy;

}
