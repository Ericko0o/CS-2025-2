#include <iostream>
#include <assert.h> // Buena practica meterlo en todo lado, para verificar y frenar erroes

struct Node
{
    Node(int x){ v = x; next = 0; }
    int v;
    Node* next;
};

class CForwardList
{
public:
    CForwardList();
    ~CForwardList();
    void push_back(int x);
    void push_front(int x);
    void pop_back();
    void pop_front();
    int& operator[](int i);
    void print();
private:
    Node* head;
    int nelem;
};

CForwardList::CForwardList()
{
    head = 0;
    nelem = 0;
}

CForwardList::~CForwardList()
{
    Node* p = head; // Puntero auxiliar
    while ( p ) // Mientras p no sea null
    {
        p = p->next; // Avanzamos p al siguiente
        delete head; // Borramos el nodo actual
        head = p; // head apunta al siguiente
    }
}


void CForwardList::push_back(int x)
{
    Node* n = new Node(x);
    Node** q;
    for ( q = &head; *q != 0; q = &( (*q)->next ) );
    *q = n;
}


/*void CForwardList::push_back(int x)
{
    Node* n = new Node(x);
    Node** q = &head;
    while ( *q != 0 )
        q = &( (*q)->next );
    *q = n;
}*/

/*void CForwardList::push_back(int x)
{
    Node* n = new Node(x);
    if ( head == 0 )
    {    head = n;  }
    else
    {
        Node* p = head;
        while( p )
        {
            if ( p->next == 0 )
                p->next = n;
        }
    }
}*/


void CForwardList::push_front(int x)
{
    Node* n = new Node(x); // Creamos nodo
    n->next = head; 
    head = n;
    nelem++;
}

void CForwardList::pop_back() //
{ 
    //Puntero doble, para que q se posicione en el siguiente dle ultimo
    Node** q;
    for ( q = &head; *q != 0 && (*q)-> next !=0; q = &( (*q)->next ) );
    delete *q; // Borramos el ultimo nodo
    *q = 0; // El siguiente del penultimo es null
}

void CForwardList::pop_front()
{
    Node* n = head; // Apuntando el
    head = head->next; // Movemos head al siguiente nodo
    delete n; // Borramos el nodo inicial
}

int& CForwardList::operator[](int i)
{
    assert( i < nelem);
    Node* p = head; // Apuntamos al inicio
    for ( int j = 0; j < i; j++)
        p = p->next;
    return p->v; // Devolvemos el valor del nodo
}

void CForwardList::print()
{
    Node* p;
    for ( p = head; p != 0; p = p->next )
        std::cout<<p->v<<" ";
    std::cout<<"\n";
}

int main()
{
    CForwardList fl;
    fl.push_back(8);
    fl.push_back(6);
    fl.push_back(3);
    fl.push_back(7);
    fl.print();
    fl[2] = 1; // Corchete 20, expand
    fl.print();
}


// Actualizar numero de elementos
