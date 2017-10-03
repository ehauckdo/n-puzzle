#include "tree.h"
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

ExecutionStats* Tree::backTracking(Board* objective){
    clock_t begin_time = clock();
    Node* current = new Node(NULL, root->board, -1);
    Node* root_copy = current;

    int expanded_nodes = 0;
    int visited_nodes = 0;

    std::vector<std::vector<int> > visited_states;
    visited_states.push_back(current->board->board);

    Node* found = NULL;

    while(current != NULL && current->board != objective){

        Node* next = current->expand();

        if(next != NULL){

            visited_nodes = visited_nodes + 1;

            if(next->parent->isAncestral(next->board)){
                continue;
            }
            else{
                if(next->board->board == objective->board){
                    found = next;
                    break;
                }
            }

            current = next;
        }

        else{
            Node *del = current;
            current = current->parent;
            for(int i = 0; i < 4; i ++){
                delete del->children[i];
                del->children[i] = NULL;
            }

            expanded_nodes = expanded_nodes + 1;

        }
    }

    ExecutionStats* stats = NULL;

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Branching factor: " << root_copy->getChildren(root_copy, 0) / (double)found->depth << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
        if(SHOW_PATH)
            printPath(found);
        stats = new ExecutionStats(found->depth,  expanded_nodes, visited_nodes,
        root_copy->getChildren(root_copy, 0) / (double)found->depth, 1000*float(clock()-begin_time)/CLOCKS_PER_SEC);
        stats->print();
    }

    delete root_copy;
    return stats;
}

void Tree::DFS(Board* objective, int limit){
    std::cout << "limit " << limit << std::endl;

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
        if(next->depth < limit){
            do{
                Node* child = next->expand();
                open_nodes.push_back(child);
            }while(next->isfullyExpanded() == false);

        expanded_nodes += 1;
        }
        else{
            //std::cout << "Limit reached at node " << next->id << std::endl;
        }

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Branching factor: " << root_copy->getChildren(root_copy, 0) / (double)found->depth << std::endl;
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
        do{
            Node* child = next->expand();
            open_nodes.push_back(child);
        }while(next->isfullyExpanded() == false);

        expanded_nodes += 1;

        open_nodes.erase(open_nodes.begin());

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Branching factor: " << root_copy->getChildren(root_copy, 0) / (double)found->depth << std::endl;
        std::cout << "Execution time: " << 1000*float(clock()-begin_time)/CLOCKS_PER_SEC << "ms"<< std::endl;
        if(SHOW_PATH)
            printPath(found);
    }

    delete root_copy;
}

void Tree::uniformCostSearch(Board* objective){
    BFS(objective);
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
            int i = 0;
            int initial_size = open_nodes.size();

            // insert ordered
            for(std::vector<Node*>::iterator it = open_nodes.begin(); it != open_nodes.end(); it++){
                if(child->board->getH2(objective) < (*it)->board->getH2(objective)){
                    open_nodes.insert(it, child);
                    break;
                }
                i += 1;
            }

            if(open_nodes.size() == initial_size){
                open_nodes.push_back(child);
            }

        }while(current->isfullyExpanded() == false);

        expanded_nodes = expanded_nodes + 1;

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Branching factor: " << root_copy->getChildren(root_copy, 0) / (double)found->depth << std::endl;
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
            child->value = new_child_value;

            // insert ordered
            for(std::vector<Node*>::iterator it = open_nodes.begin(); it != open_nodes.end(); it++){
                //int value = (*it)->board->getH2(objective) + getGvalue(*it, root_copy);
                if(new_child_value < (*it)->value){
                    open_nodes.insert(it, child);
                    break;
                }
                i += 1;
            }

            if(open_nodes.size() == initial_size){
                open_nodes.push_back(child);
            }

        }while(current->isfullyExpanded() == false);

        expanded_nodes = expanded_nodes + 1;

    }

    if(found != NULL){
        std::cout << "Depth of solution: " << found->depth << std::endl;
        std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
        std::cout << "Visited nodes: " << visited_nodes << std::endl;
        std::cout << "Branching factor: " << root_copy->getChildren(root_copy, 0) / (double)found->depth << std::endl;
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
            next->value = new_child_value;

            if(new_child_value <= bound){
                // good, keep expanding
                current = next;
            }

            else{
                // insert ordered
                int initial_size = discarded.size();
                int i = 0;

                for(std::vector<Node*>::iterator it = discarded.begin(); it != discarded.end(); it++){
                    if(new_child_value < (*it)->value){
                        discarded.insert(it, next);
                        break;
                    }
                    i += 1;
                }

                 if(discarded.size() == initial_size){
                    discarded.push_back(next);
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
        std::cout << "Branching factor: " << root_copy->getChildren(root_copy, 0) / (double)found->depth << std::endl;
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
        std::cout << util::getMoveSymbol(next->lastMove) << " ";
        path.pop_back();
    }
    std::cout << std::endl;
}
