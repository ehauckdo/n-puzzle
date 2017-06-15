#include "tree.h"
#include <cstddef>
#include <util.h>
#include <iostream>
#include <time.h>

#define SHOW_PATH 1


Tree::Tree(Board* b){
    root = new Node(NULL, b, -1);
}

Tree::~Tree(){
    delete root;
}


void Tree::backTracking(Board* objective){
    clock_t begin_time = clock();
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;
    int i = 0;

    int expanded_nodes = 0;
    int visited_nodes = 0;

    std::vector<std::vector<int> > visited_states;
    visited_states.push_back(current->board->board);

    Node* found = NULL;

    while(current != NULL && current->board != objective){

        Node* next = current->expand();

        if(next != NULL){

            visited_nodes = visited_nodes + 1;

            if(util::contains(visited_states, next->board->board)){
                //std::cout << "Already in history. Continuing...: " << std::endl;
               continue;
            }
            else{
                if(next->board->board == objective->board){
                    //std::cout << "Objective found! exiting...: " << std::endl;
                    found = next;
                    break;
                }
                else{
                    //std::cout << "New state! saving...: " << std::endl;
                    visited_states.push_back(next->board->board);
                    std::cout << "Number of states: " << visited_states.size() << std::endl;
                }
            }
            current = next;
        }

        else{
            //std::cout << "Curret null" << std::endl;
            Node *del = current;
            current = current->parent;
            std::cout << "Returning to parent (id:"<< current->id<<")" << std::endl;
            // Node fully expanded, so free any children before returning to parent
            for(int i = 0; i < 4; i ++){
                delete del->children[i];
                del->children[i] = NULL;
            }

            expanded_nodes = expanded_nodes + 1;

        }
    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
        if(SHOW_PATH)
            printPath(found);
    }

    delete root_copy;

}

void Tree::DFS(Board* objective){
    clock_t begin_time = clock();
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    int expanded_nodes = 0;
    int visited_nodes = 0;

    std::vector<std::vector<int> > visited_states;
    std::vector<Node*> open_nodes;

    open_nodes.push_back(current);
    Node* found = NULL;

    while(open_nodes.size() > 0 && current != NULL){

        current = open_nodes.back();
        open_nodes.pop_back();

        visited_nodes = visited_nodes + 1;

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

        expanded_nodes += 1;

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
         if(SHOW_PATH)
            printPath(found);
    }

    delete root_copy;

}

void Tree::BFS(Board* objective){
    clock_t begin_time = clock();
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    int expanded_nodes = 0;
    int visited_nodes = 0;

    std::vector<std::vector<int> > visited_states;
    std::vector<Node*> open_nodes;

    open_nodes.push_back(current);
    Node* found = NULL;

    while(open_nodes.size() > 0 && current != NULL){

        current = open_nodes.front();
        visited_nodes = visited_nodes + 1;

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

        expanded_nodes += 1;

        open_nodes.erase(open_nodes.begin());

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
        if(SHOW_PATH)
            printPath(found);
    }

    delete root_copy;

}

void Tree::uniformCostSearch(Board* objective){
    DFS(objective);
}

void Tree::greedySearch(Board* objective){
    clock_t begin_time = clock();
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    int expanded_nodes = 0;
    int visited_nodes = 0;

    std::vector<Node*> open_nodes;

    open_nodes.push_back(current);
    Node* found = NULL;

    while(open_nodes.size() > 0 && current != NULL){

        current = open_nodes.front();
        open_nodes.erase(open_nodes.begin());

        visited_nodes = visited_nodes + 1;

        // check if current is the objective
        if(current->board->board == objective->board){
            std::cout << "Objective found! exiting...: " << std::endl;
            found = current;
            break;
        }

        do{
            Node* child = current->expand();
            //std::cout << "H2 of child: " << child->board->getH2(objective) << std::endl;
            int i = 0;
            int initial_size = open_nodes.size();

            // insert ordered
            for(std::vector<Node*>::iterator it = open_nodes.begin(); it != open_nodes.end(); it++){
                if(child->board->getH2(objective) < (*it)->board->getH2(objective)){
                    open_nodes.insert(it, child);
                    //std::cout << "Inserted at "<< i <<"position" << std::endl;
                    break;
                }
                i += 1;
            }

            if(open_nodes.size() == initial_size){
                open_nodes.push_back(child);
                //std::cout << "Inserted at last position" << std::endl;
            }

        }while(current->isfullyExpanded() == false);

        expanded_nodes = expanded_nodes + 1;

        //std::cout << "size " << open_nodes.size() << std::endl;

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
        if(SHOW_PATH)
            printPath(found);
    }

    open_nodes.clear();
    delete root_copy;
}

int getGvalue(Node* node, Node* root){
    Node *traverser = node;
    int g = 0;
    while(traverser != root){
        traverser = traverser->parent;
        g = g + 1;
    }
    return g;
}

void Tree::aStar(Board* objective){
    clock_t begin_time = clock();
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    int expanded_nodes = 0;
    int visited_nodes = 0;

    //std::cout << "ROOT:" << std::endl;
    //root_copy->board->printBoard();
    //std::cout << std::endl;

    std::vector<Node*> open_nodes;

    open_nodes.push_back(current);
    Node* found = NULL;

    while(open_nodes.size() > 0 && current != NULL){

        current = open_nodes.front();
        open_nodes.erase(open_nodes.begin());

        visited_nodes = visited_nodes + 1;

        // check if current is the objective
        if(current->board->board == objective->board){
            std::cout << "Objective found! exiting...: " << std::endl;
            found = current;
            break;
        }

        do{
            Node* child = current->expand();

            int i = 0;
            int initial_size = open_nodes.size();

            int new_child_value = child->board->getH2(objective) + getGvalue(child, root_copy);
            //std::cout << "F(x) + g(x) of child: " << child->board->getH2(objective) << " + " << getGvalue(child, root_copy) << std::endl;
            //child->board->printBoard();
            //std::cout << std::endl;

            // insert ordered
            for(std::vector<Node*>::iterator it = open_nodes.begin(); it != open_nodes.end(); it++){
                int value = (*it)->board->getH2(objective) + getGvalue(*it, root_copy);
                if(new_child_value < value){
                    open_nodes.insert(it, child);
                    //std::cout << "Inserted at "<< i <<" position" << std::endl;
                    break;
                }
                i += 1;
            }

            if(open_nodes.size() == initial_size){
                open_nodes.push_back(child);
                //std::cout << "Inserted at last position" << std::endl;
            }

        }while(current->isfullyExpanded() == false);

        expanded_nodes = expanded_nodes + 1;

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
        if(SHOW_PATH)
            printPath(found);
    }

    open_nodes.clear();
    delete root_copy;
}



void Tree::idaStar(Board* objective){
    clock_t begin_time = clock();
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    int expanded_nodes = 0;
    int visited_nodes = 0;

    //std::cout << "Initial bound: " << bound << std::endl;
    std::vector<int> old_bounds;
    std::vector<Node*> discarded;

    int bound = current->board->getH2(objective);
    old_bounds.push_back(bound);

    Node* found = NULL;

    while(found == NULL){

        Node* next = current->expand();

        if(next != NULL){

            visited_nodes = visited_nodes + 1;

            if(next->board->board == objective->board){
                std::cout << "Objective found! exiting...: " << std::endl;
                found = next;
                break;
            }

            int new_child_value = next->board->getH2(objective) + getGvalue(next, root_copy);

            if(new_child_value <= bound){
                // good, keep expanding
                current = next;
                //std::cout << "Lower than bound, keep expanding" << std::endl;
            }

            else{
                // insert ordered
                int initial_size = discarded.size();
                int i = 0;
                //std::cout << "F(x) + g(x) of child: " << next->board->getH2(objective) << " + " << getGvalue(next, root_copy) << std::endl;

                for(std::vector<Node*>::iterator it = discarded.begin(); it != discarded.end(); it++){
                    int value = (*it)->board->getH2(objective) + getGvalue(*it, root_copy);
                    if(new_child_value < value){
                        discarded.insert(it, next);
                        //std::cout << "Inserted at "<< i <<" position" << std::endl;
                        break;
                    }
                    i += 1;
                }

                 if(discarded.size() == initial_size){
                    discarded.push_back(next);
                    //std::cout << "Inserted at last position" << std::endl;
                }

                current = next->parent;
            }
        }
        else{
            // check if the current node is not the root node
            if(current->parent != NULL){
                current = current->parent;
                expanded_nodes = expanded_nodes + 1;
            }
            // if it is the root node, we need to update the bound
            else{
                if(discarded.size() > 0){
                    bound = discarded[0]->board->getH2(objective) + getGvalue(discarded[0], root_copy);
                    old_bounds.push_back(bound);
                    //std::cout << "New Bound(" << discarded[0]->id <<"): " << discarded[0]->board->getH2(objective) << " + " << getGvalue(discarded[0], root_copy) << std::endl;
                    discarded.clear();
                    delete root_copy;
                    current = new Node(NULL, root->board, -1);
                    root_copy = current;
                }
                else{
                    break;
                }
            }
        }

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
        std::cout << "Old bounds: ";
        for(std::vector<int>::iterator it = old_bounds.begin(); it != old_bounds.end(); it++)
            std::cout << *it << " ";
        std::cout << std::endl;
        if(SHOW_PATH)
            printPath(found);
    }

    delete root_copy;

}

void Tree::printPath(Node* leaf){

    Node* traverser = leaf;
    std::vector<Node*> path;

    while(traverser->parent != NULL){
        path.push_back(traverser);
        traverser = traverser->parent;
    }

    while(path.size() > 0){
        Node* next = path.back();
        std::cout << "Move " << next->depth << ":" << util::getMoveName(next->lastMove) << std::endl;
        path.pop_back();
    }

}
