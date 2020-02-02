#include <iostream>
using namespace std;


struct Przedszkolak {
string name;
int group;
Przedszkolak* next;
};

struct List {
    Przedszkolak* head;
};

//void init(List* &list){
//    Przedszkolak* n = new Przedszkolak;
//
//    n->name = "";
//    n->group = 0;
//    n->next = NULL;
//    list->head = n;
//}

void add(List* list, string name, int group){
    Przedszkolak* n = new Przedszkolak;  // tworzy nowy element listy

    //wypelniamy danymi
    n->name = name;
    n->group = group;

    //UWAGA dodajemy do przodu
    n->next = list->head;
    list->head = n;

}
bool exists(List* list, string name){
    // imie to unikalny atrybut w tym przypadku
    Przedszkolak* current = list->head;

    while(current != NULL) {
        if(current->name == name){
            return true;
        }
        current = current->next;
    }
    return false;
}
void delete_przedszkolaczka(List* list, string name){
    // imie to unikalny atrybut w tym przypadku
    Przedszkolak* current = list->head;
    Przedszkolak* tmp = list->head;

    //PAMIETAJ O ZWALNIANIU PAMIECI
    //PRZYPADEK JESLI USUWAMY PIERWSZY ELEMENT LISTY
    if(list->head->name == name) {
        list->head = current->next;
        delete current;
        return;
    }
    while(current != NULL) {
        
        if(current->name == name) {
            tmp->next = current->next;
            delete current;
        }
        tmp = current;
        current = current->next;
        
    }

}
void set_to_group(List* list, List* t[]){
    Przedszkolak* current = list->head;
    
    for(int i=0; i<=9; i++){
        t[i] = new List();
    }

    while (current != NULL)
    {
        add(t[current->group], current->name, current->group);
        current = current->next;
    }
}

List* rewrite(List* t[10], List* list){
    Przedszkolak* current = NULL;

    int i = 0;
    while(current == NULL && i<10){
     current = t[i]->head;
    }
    List* returned = t[i];
    for(; i<9; i++){
        while(current->next != NULL){
            current = current->next;
        }
        Przedszkolak* nodeHead = t[i+1]->head;
        while(nodeHead == NULL && i<9){
            i++;
            nodeHead = t[i+1]->head;
        }
        current->next = nodeHead;
    }
    return returned;
}

void show(List* list){
    Przedszkolak* tmp = list->head;

    while(tmp!=NULL){
        cout<<tmp->name<<" - "<<tmp->group<<endl;
        tmp = tmp->next;
    }

}
List* reverse(List* list, List* reversedList){
    Przedszkolak* tmp = list->head;
    
    while(tmp != NULL) {
        add(reversedList,tmp->name,tmp->group);
        tmp = tmp->next;
    }
    return reversedList;
}
int main(){

    List* list = new List;
//    init(list);
    //list.head = NULL;
    List* t[10];

    add(list,"Czarek",1);
    add(list,"Basia",3);
    add(list,"Marysia",1);
    show(list);

    set_to_group(list,t);
    show(t[1]);
    show(t[2]);
    show(t[3]);

    list = rewrite(t,list);
    show(list);

    cout<<"czy jest Marysia? "<<exists(list,"Marysia")<<endl;

    delete_przedszkolaczka(list, "Marysia");
    show(list);
    cout<<"czy jest Marysia? "<<exists(list,"Marysia")<<endl;
    
    List* reversedList = new List;
    //reversedList->head = NULL;
    reversedList = reverse(list, reversedList);
    show(reversedList);
    return 0;
}
