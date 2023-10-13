#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_COMMAND_LEN 30

///CARS
#define CARSSIZE0 128       //For this project, 128 is perhaps the best option in terms of reallocs and total memory used
typedef struct cars_t {
	int *cars;		//array which contains (not in order) capacity of all cars
	int nCars;		//Number of cars effectively present in station
	int arrLen;		//length of array
	int maxCar;		//I precalculate the maximum present in array cars of capacity
	int nMax;		//number of max elements in cars 
} cars_t;
cars_t* initiazileCarsWithMax(int arr[], int nCars, int arrLen, int maxCar, int nMax);  //Use sema arr (with parameter size, len to create heap) and makes it a heap
int getMax_cars(cars_t *h);                         //gets max of heap (first el). returns 0 if heap empty
int deleteEl_cars(cars_t *h, int k);                //deletes and returns el specified, keeps it a heap. If heap empty or el not found, does nothing and returns -1
void insert_cars(cars_t *h, int k);                 //insert el in heap, keeping it a heap
void free_cars(cars_t *h);

///HIGHWAY
typedef struct highway_t {
    struct station_t *root;     //rbtree: root of rbtree
    struct station_t *nil;      //rbtree: nil element of rbtree
    struct station_t *head;     //list: head of list of stations (minimum id)
    struct station_t *tail;     //list: tail of list of stations (maximum id)
} highway_t;
typedef struct station_t {
    int id;                             //id of station: distance from beginning of highway
    struct station_t *p, *c[2];         //rbtree: parent, children (0 for left, 1 for right)
    int color;                          //rbtree: color of node (red or black)
    struct station_t *prev, *next;      //list: previous and next element on (asc ordered) list of stations
    struct station_t *reachedBy;        //used in BFS as a graph of reachability
    struct cars_t *cars;				//struct which contains array of cars (int of their capacities)
} station_t;
typedef struct pathNode_t {             //node of a simply linked list of pointers to stations, used to represent a path between two stations
    struct station_t *step;
    struct pathNode_t *next;
} pathNode_t;
highway_t* initializeEmptyHighway();                    //Creates a new empty hw (with empty tree, and head and tail = NULL)
void free_highway(highway_t *hw);   //frees all memory dynamically allocated (heaps for each station, each station itself and the only struct highway_t)
void free_path(pathNode_t *h);      //free list of pathNode_t
void printHighway(highway_t *hw);                       //Prints list of stations in order, printing also cars for each station
void printPath(FILE *fout, pathNode_t *h);              //Prints steps present in list of head h (i.e. prints a list of id of stations in order on path from start to end)
station_t* searchStation(highway_t *hw, int id);        //Searches node in rbtree, and if found it returns station linked, NULL otherwise
pathNode_t* insertHead_list(pathNode_t *h, station_t *step);
station_t* insertStationWithMax(highway_t *hw, int id, int cars[], int ncars, int nArr, int maxCar, int nMax);   //Inserts new station in rbtree and saves also right away next and prev (for list).
                                                                                    //The arr used for cars is the same of the parameter, with nArr elems (size of heap) among which the first ncars are significant (len of heap)
int deleteStation(highway_t *hw, int id);                   //deletes station with id (delete from rbtree and repair next/prev). Returns 0 if station is not fount, 1 otherwise
station_t* insertCar(highway_t *hw, int id, int car);       //Searches station with id, and if it's found it adds car to cars of station. Returns st found (NULL if not found)
station_t* deleteCar(highway_t *hw, int id, int car);       //Searches station with id, and if it's found it deletes car from cars. Returns st found if car is deleted, NULL if st is not found or car is not in cars of st
pathNode_t* planPath(highway_t *hw, int start, int end);    //Searches a path between stations with id start and end (to find), and returns head of list of pathNode_t. Returns NULL is start or end are not found, or a path doesn't exist
pathNode_t* planPathForward(highway_t *hw, station_t *start, int end);
pathNode_t* planPathBackward(highway_t *hw, station_t *start, int end);

///RBTREE UTILS
#define RED_RB 0
#define BLACK_RB 1
#define RIGHT_ROTATE 1
#define LEFT_ROTATE 0
highway_t* initializeEmptyRbtree_rbtree();                 //creates an empty rbtree (root=t.nil)
station_t* searchFromRoot_rbtree(highway_t *t, int k);                    //binary search from root, return rif to el with key k if is found, t->nil if is not found
station_t* searchFromNode_rbtree(highway_t *t, station_t *el, int k);      //binary search from node el, return rif to elem with key k if is found, t->nil if is not found
station_t* minFromNode_rbtree(highway_t *t, station_t *el);                //return minimum of node el. Special cases: t->nil if el is t->nil, node el if el is already minimum  (i.e. doesn't have left child)
station_t* maxFromNode_rbtree(highway_t *t, station_t *el);                //return maximum of node el. Special cases: t->nil if el is t->nil, node el if el is already maximum (i.e. doesn't have right child)
station_t* successor_rbtree(highway_t *t, station_t *el);                  //return successor of node el. Spacial cases: t->nil if el is t->nil or el is maximum (hence has no successor)
station_t* predecessor_rbtree(highway_t *t, station_t *el);                //return predecessor of node el. Spacial cases: t->nil if el is t->nil or el is minimum (hence has no predecessor)
station_t* rotate_rbtree(highway_t *t, station_t *x, int dir);        //rotate x in t with leftRotate (dir = 0) or rightRotate (dir = 1)
station_t* insert_rbtree(highway_t *t, int k);                        //Creates new node with key k and inserts in rbtree, repairing to keep it a rbtree. Return the inserted node. It node already exists returns nil
int deleteKey_rbtree(highway_t *t, int k);                            //Searches and deletes node with key k, repairing to keep it a rbtree. If k is not found, returns 0, 1 otherwise (delete successful)
int deleteNode_rbtree(highway_t *t, station_t *el);                   //Deletes node el, repairing to keep it a rbtree. If el is nil returns 0, 1 otherwise (delete successful)
void repairInsert_rbtree(highway_t *t, station_t *z);
void repairDelete_rbtree(highway_t *t, station_t *x);

///Function of Interface
void handleCommand(highway_t *hw, char comm[], FILE *in, FILE *out);
// This function handles things based on command string. Input and output needed to handle command are *in and *out. It does nothing if command is not handled

int main() {
    char comm[MAX_COMMAND_LEN];
    highway_t *hw;

    hw = initializeEmptyHighway();
    while(scanf("%s", comm)!=EOF) {
        handleCommand(hw, comm, stdin, stdout);
    }
    free_highway(hw);
    return 0;
}

///CARS
cars_t* initiazileCarsWithMax(int arr[], int nCars, int arrLen, int maxCar, int nMax) {
    cars_t *cars;
    cars = malloc(sizeof(cars_t));
    cars->cars = arr;
    cars->nCars = nCars;
    cars->arrLen = arrLen;
    cars->maxCar = maxCar;
    cars->nMax = nMax;
    return cars;
}
int getMax_cars(cars_t *h) {
    return (h->nCars!=0) ? h->maxCar : 0;
}
void insert_cars(cars_t *h, int k) {
    int newSize, *newArr;
    int i;

    if(h->nCars == h->arrLen) {
        newSize = h->arrLen * 2;
        newArr = malloc(newSize*sizeof(int));
        for(i=0 ; i<h->nCars ; i++)
            newArr[i] = h->cars[i];
        free(h->cars);
        h->cars = newArr;
        h->arrLen = newSize;
    }

    h->cars[h->nCars] = k;
    h->nCars++;
    if(k > h->maxCar) {
        h->maxCar = k;
        h->nMax = 1;
    } else if(k == h->maxCar)
        h->nMax++;
}
int deleteEl_cars(cars_t *h, int k) {
    int i;
    if(h->nCars==0 || k>h->maxCar)
    	return -1;

    if(k<h->maxCar || (k==h->maxCar && h->nMax>1)) {
    	for(i=0 ; i<h->nCars ; i++)
	        if(h->cars[i] == k)
	            break;
	    if(i == h->nCars)
	        return -1;
	    h->nCars--;
	    if(k==h->maxCar)
	    	h->nMax--;
	    for( ; i<h->nCars ; i++)
	    	h->cars[i] = h->cars[i+1];

    } else { //k == h->maxCar && h->nMax == 1
    	h->maxCar = INT_MIN;
    	h->nMax = 0;
    	h->nCars--;
    	for(i=0 ; h->cars[i]!=k ; i++)
    		if(h->cars[i]>h->maxCar) {
    			h->maxCar = h->cars[i];
    			h->nMax = 1;
    		} else if(h->cars[i] == h->maxCar)
    			h->nMax++;
	    for( ; i<h->nCars ; i++){
    		h->cars[i] = h->cars[i+1];
    		if(h->cars[i]>h->maxCar) {
    			h->maxCar = h->cars[i];
    			h->nMax = 1;
    		} else if(h->cars[i] == h->maxCar)
    			h->nMax++;
    	}
    }
    return k;
}
void free_cars(cars_t *h) {
    free(h->cars);
    free(h);
}

///RBTREE UTILS
highway_t* initializeEmptyRbtree_rbtree() {
    highway_t *t;
    t = malloc(sizeof(highway_t));
    t->nil = malloc(sizeof(station_t));
    t->nil->p = t->nil->c[0] = t->nil->c[1] = t->nil;
    t->nil->color = RED_RB;
    t->root = t->nil;
    return t;
}
station_t* searchFromRoot_rbtree(highway_t *t, int k) {
    return searchFromNode_rbtree(t, t->root, k);
}
station_t* searchFromNode_rbtree(highway_t *t, station_t *el, int k) {
    int child;
    if(el==t->nil || el->id == k)
        return el;
    child = (el->id > k) ? 0 : 1;
    return searchFromNode_rbtree(t, el->c[child], k);
}
station_t* minFromNode_rbtree(highway_t *t, station_t *el) {
    station_t *curr;
    curr = el;
    if(curr == t->nil)
        return curr;
    while(curr->c[0] != t->nil)
        curr = curr->c[0];
    return curr;
}
station_t* maxFromNode_rbtree(highway_t *t, station_t *el) {
    station_t *curr;
    curr = el;
    if(curr == t->nil)
        return curr;
    while(curr->c[1] != t->nil)
        curr = curr->c[1];
    return curr;
}
station_t* successor_rbtree(highway_t *t, station_t *el) {
    station_t *parent;
    if(el == t->nil)
        return el;
    if(el->c[1] != t->nil)
        return minFromNode_rbtree(t, el->c[1]);
    parent = el->p;
    while(parent!=t->nil && el==parent->c[1]) {
        el = parent;
        parent = parent->p;
    }
    return parent;
}
station_t* predecessor_rbtree(highway_t *t, station_t *el) {
    station_t *parent;
    if(el == t->nil)
        return el;
    if(el->c[0] != t->nil)
        return maxFromNode_rbtree(t, el->c[0]);
    parent = el->p;
    while(parent!=t->nil && el==parent->c[0]) {
        el = parent;
        parent = parent->p;
    }
    return parent;
}
station_t* rotate_rbtree(highway_t *t, station_t *x, int dir) {
    if(x->c[1-dir] == t->nil)
        return x;
    station_t *y, *parent;
    int child;

    y = x->c[1-dir];
    parent = x->p;
    y->p = parent;
    if(parent != t->nil)  {
        child = (parent->c[0]==x) ? 0 : 1;
        parent->c[child] = y;
    }
    x->c[1-dir] = y->c[dir];
    if(y->c[dir] != t->nil)
        y->c[dir]->p = x;
    y->c[dir] = x;
    x->p = y;
    if(x==t->root)
        t->root = y;

    return y;
}
station_t* insert_rbtree(highway_t *t, int k) {
    /* insert as a bst */
    station_t *prev, *curr;
    int child;

    prev = t->nil;
    curr = t->root;
    while(curr != t->nil) {
        if(curr->id == k)           //if node is already in rbtree, returns nil
            return t->nil;
        child = (curr->id > k) ? 0 : 1;
        prev = curr;
        curr = curr->c[child];
    }

    curr = malloc(sizeof(station_t));
    curr->color = RED_RB;
    curr->id = k;
    curr->c[0] = curr->c[1] = t->nil;
    curr->p = prev;
    if(prev!=t->nil)
        prev->c[child] = curr;
    else
        t->root = curr;

    repairInsert_rbtree(t, curr);
    return curr;
}
void repairInsert_rbtree(highway_t *t, station_t *z) {
    station_t *x, *xp, *y;
    int childx, childz;     //0 if x is left child of xp, 1 if is right child. Same for z as x's child

    if(t->root == z) {         //case: z is root, must become black and enough
        z->color = BLACK_RB;
        return;
    }
    if(z->p->color == BLACK_RB)    //case: z is not root, hence has a parent, and it's black --> z can remain red
        return;

    /* here we know el has a parent (is not root) and it's red
     * Hence z has also a dad, as its parent is red and cannot be root
     * We name x = z's parent, xp = x's parent, y = z's uncle = x's sibling (if there's)
     * Oss: only y can be t->nil */
    x = z->p;
    xp = x->p;
    childx = (xp->c[0] == x) ? 0 : 1;
    childz = (x->c[0] == z) ? 0 : 1;
    y = xp->c[1-childx];

    if(y->color==RED_RB) {     //case 1: there's uncle y and is red
        x->color = BLACK_RB;
        y->color = BLACK_RB;
        xp->color = RED_RB;
        repairInsert_rbtree(t, xp);
        return;
    }

    // Now we know y must be black (maybe is t->nil, we don't bother)
    if(childx!=childz) {
        /* case 2: uncle y is black, z and x are one right child and the other left child.
         * We can rotate in one dir x, and swap roles of x, z in order to find case 3 */
        if(childx == 0)     //then z is right child, we must rotate x as left_rotate
            x = rotate_rbtree(t, x, LEFT_ROTATE);
        else                //contraty of before
            x = rotate_rbtree(t, x, RIGHT_ROTATE);
        z = x->c[childx];
    }

    //case 3: now we are z and x are both right or left child, and uncle y is black
    x->color = BLACK_RB;
    xp->color = RED_RB;
    if(childx == 0)
        rotate_rbtree(t, xp, RIGHT_ROTATE);
    else
        rotate_rbtree(t, xp, LEFT_ROTATE);
}
int deleteKey_rbtree(highway_t *t, int k) {
    return deleteNode_rbtree(t, searchFromRoot_rbtree(t, k));
}
int deleteNode_rbtree(highway_t *t, station_t *el) {
    station_t *parent, *succ, *replaced;
    station_t *nil = t->nil;
    int child, child2;
    int toRepair = 0;
    if(el == t->nil)
        return 0;

    if(el->c[0]==nil && el->c[1]==nil) {        // case 1: no children (actually both children = nil)
        parent = el->p;
        if(parent == nil)     //el is root, and there's nothing else
            t->root = nil;       //free of el is done in the end
        else {
            child = (parent->c[0] == el) ? 0 : 1;
            parent->c[child] = nil;
            if(el->color == BLACK_RB) {
                nil->p = parent;        //momentarily, if I will have to call repairDelete, nil's parent is set to the deleted node's parent
                replaced = nil;
                toRepair = 1;
            }
        }
    }
    else if(!(el->c[0]!=nil && el->c[1]!=nil)) {       // case 2: only 1 child
        /* if it has only 1 child, it must be 1 red child for black heights, and el must be black */
        child = (el->c[0]!=nil) ? 0 : 1;
        parent = el->p;
        if(parent != nil){
            child2 = (parent->c[0] == el) ? 0 : 1;
            parent->c[child2] = el->c[child];
        } else
            t->root = el->c[child];
        el->c[child]->p = parent;
        el->c[child]->color = BLACK_RB;
        toRepair = 0;
    }
    else {               // case 3: both children
        succ = successor_rbtree(t, el);
        succ->c[0] = el->c[0];
        el->c[0]->p = succ;
        if(succ->color == BLACK_RB) {
            toRepair = 1;
            replaced = succ->c[1];
        }
        succ->color = el->color;
        if(el->c[1] != succ) {
            /* if succ is not directly right child of el, it must be a left child of some other node in right subtree of el
             * hence its right subtree (possibly nil) can be assigned as left subtree of that parent
             * and the right child of succ now must become the previous right child of el
             * In any case, right child of succ is the element which replaces succ */
            succ->p->c[0] = succ->c[1];
            if(toRepair || succ->c[1] != nil)       //momentarily even if succ->c[1] is nil, its parent is set to succ's parent
                succ->c[1]->p = succ->p;
            succ->c[1] = el->c[1];
            el->c[1]->p = succ;
        } else if(toRepair)
            succ->c[1]->p = succ;       //if succ->c[1] is nil, its parent is momentarily set to succ
        parent = el->p;
        succ->p = parent;
        if(parent != nil) {
            child = (parent->c[0] == el) ? 0 : 1;
            parent->c[child] = succ;
        } else
            t->root = succ;
    }

    free(el);
    if(toRepair) {
        repairDelete_rbtree(t, replaced);
    }
    return 1;
}
void repairDelete_rbtree(highway_t *t, station_t *x) {
    station_t *xp, *w;
    int temp, child;

    xp = x->p;
    child = (xp->c[0] == x) ? 0 : 1;
    if(x == t->nil)
        t->nil->p = t->nil;

    if(x->color == RED_RB) {        //Case 0: x is red (it can't be nil)
        x->color = BLACK_RB;
        return;
    }

    w = xp->c[1-child];
    if(w->color == RED_RB) {
        /* Case 1: x now is black, and its sibling w is red --> xp must be black
         * it is normalized is one of case 2, 3, 4, as in the end x has a black sibling*/
        temp = xp->color;
        xp->color = w->color;
        w->color = temp;
        rotate_rbtree(t, xp, child);
        w = xp->c[1-child];
    }

    if(w->c[0]->color==BLACK_RB && w->c[1]->color==BLACK_RB) {      //case 2: x B, sibling w B, w's children both B
        w->color = RED_RB;
        repairDelete_rbtree(t, xp);
        return;
    } else {
        if(w->c[1-child]->color==BLACK_RB) {        //case 3: x B, sibling w B, w's child oppositi to x is B, the other is R
            /* it is normalized to case 4 */
            temp = w->c[child]->color;
            w->c[child]->color = w->color;
            w->color = temp;
            rotate_rbtree(t, w, 1-child);
            w = xp->c[1-child];
        }

        //case 4: x B, sibling w B, w's child opposite to x R (xp and the other child of w can be whatever they want)
        w->c[1-child]->color = BLACK_RB;
        temp = w->color;
        w->color = xp->color;
        xp->color = temp;
        rotate_rbtree(t, xp, child);
        return;
    }
}

///HIGHWAY
highway_t* initializeEmptyHighway() {
    highway_t *hw;
    hw = initializeEmptyRbtree_rbtree();
    hw->head = hw->tail = NULL;
    return hw;
}
void free_highway(highway_t *hw) {
    station_t *curr, *prev;
    curr = hw->tail;
    while(curr) {
        prev = curr->prev;
        free_cars(curr->cars);
        free(curr);
        curr = prev;
    }
    free(hw->nil);
    free(hw);
}
void free_path(pathNode_t *h) {
    pathNode_t *curr, *next;
    curr = h;
    while(curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}
void printHighway(highway_t *hw) {
    station_t *el;
    int i;
    el = hw->head;
    printf("HIGHWAY BEGINNING\n");
    fflush(stdout);
    while(el) {
        printf("\tStation %d \t- cars: ", el->id);
        for(i=0 ; i<el->cars->nCars ; i++)
            printf("%d ", el->cars->cars[i]);
        printf("\n");
        fflush(stdout);
        el = el->next;
    }
    printf("HIGHWAY ENDING\n");
    fflush(stdout);
}
void printPath(FILE *fout, pathNode_t *h) {
    if(h)
        fprintf(fout, "%d", h->step->id);
    h = h->next;
    while(h) {
        fprintf(fout, " %d", h->step->id);
        h = h->next;
    }
    fprintf(fout, "\n");
}
station_t* searchStation(highway_t *hw, int id) {
    station_t *st = searchFromRoot_rbtree(hw, id);
    if(st == hw->nil)
        return NULL;
    return st;
}
pathNode_t* insertHead_list(pathNode_t *h, station_t *step) {
    pathNode_t *newEl;
    newEl = malloc(sizeof(pathNode_t));
    newEl->step = step;
    newEl->next = h;    //it is ok even if h is NULL
    return newEl;
}
station_t* insertStationWithMax(highway_t *hw, int id, int cars[], int ncars, int nArr, int maxCar, int nMax) {
    station_t *st, *prev, *next;
    st = insert_rbtree(hw, id);
    if(st == hw->nil)
        return NULL;
    st->cars = initiazileCarsWithMax(cars, ncars, nArr, maxCar, nMax);
    prev = predecessor_rbtree(hw, st);
    if(prev != hw->nil) {       //there is a previous el (st is not first el in list)
        next = prev->next;      //In this case, it doesn't need to call also successor, and the successor we look for is the succossor of prev
        st->prev = prev;
        prev->next = st;
    } else {
        next = successor_rbtree(hw, st);
        if(next == hw->nil)
            next = NULL;
        hw->head = st;
        st->prev = NULL;
    }
    if(next) {      //same with next element
        st->next = next;
        next->prev = st;
    } else {
        hw->tail = st;
        st->next = NULL;
    }
    return st;
}
int deleteStation(highway_t *hw, int id) {
    station_t *st;
    st = searchStation(hw, id);
    if(!st)
        return 0;

    if(st->prev)
        st->prev->next = st->next;
    else    //st is the first el, hence I must change head
        hw->head = st->next;
    if(st->next)
        st->next->prev = st->prev;
    else    //idem, but for tail
        hw->tail = st->prev;
    free_cars(st->cars);
    deleteNode_rbtree(hw, st);
    return 1;
}
station_t* insertCar(highway_t *hw, int id, int car) {
    station_t *st;
    st = searchStation(hw, id);
    if(st)
        insert_cars(st->cars, car);
    return st;
}
station_t* deleteCar(highway_t *hw, int id, int car) {
    station_t *st;
    int res;
    st = searchStation(hw, id);
    if(st) {
        res = deleteEl_cars(st->cars, car);
        if(res<0)
            return NULL;
    }
    return st;
}
pathNode_t* planPath(highway_t *hw, int start, int end) {
    /*
     * In this function I look for start station, and check if it is found
     * If it is found, I check if end == start --> in this case, I return directly right path
     * Otherwise, I search a path (and contextually I check if end station exists)
     * More or less is a BFS on a graph of reachability of nodes, forward or backward
     * The adjacents vertices are found at runtime using max capacity information from max of heap cars
     * In the meantime, I sign for each node after start the node from wich the current node is reached
     *    Hence in the end from node end I can rewind path by exploiting reachedBy field of stations
     * The bfs is done by visiting stations in ascending order.
     *      Minimality of path rule is assured by bfs itself
     *      Ambiguity rule is assured by fact that bfs is done in ascending order, hence reachedBy field is always set to the nearest to the beginning of highway station which can reach that station
     */
    station_t *stStart;
    pathNode_t *path = NULL;
    stStart = searchStation(hw, start);
    if(!stStart)
        return NULL;
    if(start == end) {
        path = insertHead_list(path, stStart);      //Problem specifies that I must insert only once the station if they are equal
        return path;
    }

    //now I'm sure station with id start exists, and it's different from end station. But I don't know if end station exists
    return (start<end) ? planPathForward(hw, stStart, end) : planPathBackward(hw, stStart, end);
}
pathNode_t* planPathForward(highway_t *hw, station_t *start, int end) {
    station_t *st, *reach, *maxReached;
    pathNode_t *path = NULL;
    int currMax, isReached;
    /*
     * st: main iterator which starts from start and continues til end is found (or I understand that a path doesn't exist)
     * maxReached: It is in every instant the farthest station from start which is reached by someone in bfs (hence reachedBy is set)
     * reach: in iteration with station st, reach is an iterator which visits reachable station starting from maxReach (til currMax)
     * currMax: in iteration with station st, currMax indicates farthest distance which can be reached (with car with max capacity)
     * isReached: flag to check if path has been found
     */

    maxReached = start; //maxReached initialized with start (visit not yet started)
    isReached = 0;
    st = start;
    while(!isReached && st->id<=maxReached->id) {          //bfs continues til end is found (isReached=1) or no other station can be reached (st->id<=maxReached->id, so I surpassed maxReached)
        currMax = st->id + getMax_cars(st->cars);       //set currMax by retriving max capacity from cars in st

        reach = maxReached->next;
        while(reach && reach->id<=currMax) {     //Checks all reachable (by st) stations starting from maxReached (in fact I don't have to start from st, as station before maxReached are already visited and don't need to be updated)
            reach->reachedBy = st;
            if (reach->id == end) {              //I check right away if end is reached. In this case I set isReached to 1 and exit
                isReached = 1;
                break;  //this break makes me exit from internal while, and in the next check of external while isReached is 1, so I definitively exit
            }
            //If I get here, reach is not end but it's reached by st, heance I update maxReached
            maxReached = reach;
            reach = reach->next;
        }

        // I must update st only if end has not been found
        if(!isReached) {
            if (currMax >= end)     //I got beyond end station (currMax>=end) but I didn't find end --> end station doesn't exist. I break (and I keep isReached=0)
                break;
            st = st->next;
        }
    }
    if(!isReached)          //If I exit loop with isReached==0, end doesn't exist or a path to it doesn't exist
        return NULL;

    //Now I know end exists and a path from start to end has been found; it can be retrieved by following the field reachedBy from end to start
    //From end to start the path is flipped --> to reverse order, I insert into list of pathNode_t from head of list
    //As from planPath I know that start != end, I don't bother about the corner case start==end
    st = reach;
    while(st != start) {
        path = insertHead_list(path, st);
        st = st->reachedBy;
    }
    path = insertHead_list(path, start);  //I exited because st = start, hence start is missing
    return path;
}
pathNode_t* planPathBackward(highway_t *hw, station_t *start, int end) {
    /* Similar to planPathForward, I do a bfs from start to end (with start > end)
     * To follow ambiguity rule, For each level of graph of reachability, I start from lowest station of level to highest
     * This way visit isn't done in descending/ascending order (on contrary of planPathForward, which does bfs in ascending order)
     *      Visit is level by level, and each level has visit in ascending order
     */
    station_t *st, *reach, *startLevel, *endLevel, *maxReached;
    pathNode_t *path = NULL;
    int currMax, isReached;
    /*
     * st: main iterator which starts from start and continues til end is found (or I understand that a path doesn't exist)
     * maxReached: It is in every instant the farthest station from start which is reached by someone in bfs (hence reachedBy is set)
     * reach: in iteration with station st, reach is an iterator which visits reachable station starting from maxReach (til currMax)
     * currMax: in iteration with station st, currMax indicates farthest distance which can be reached (with car with max capacity)
     * isReached: flag to check if path has been found
     * startLevel / endLevel: In every instant, they are the station at the beginning and end of a level of graph of reachability, with station in level in ascending order
     *      So in every instant it should be startLevel->id < endLevel->id
     *      if we reach beginning of highway, it may become startLevel->id > endLevel->id --> in that case we know that we don't have to search a path anylonger
     */

    //First initialize of startLevel and endLevel, by checking which stations are reachably from start
    isReached = 0;
    endLevel = start->prev;
    reach = endLevel;
    if(!reach)          //start is first station, this means that end station (!= start) cannot exist
        return NULL;
    currMax = start->id - getMax_cars(start->cars);
    while(reach && reach->id>=currMax) {
        reach->reachedBy = start;       //In the mean time of inizializing start/endLevel, I also set this stations as reached by start
        if(reach->id == end) {          //I must check also in this first initializing if end is reached
            isReached = 1;
            break;
        }
        reach = reach->prev;
    }

    if(!isReached) {    //Now I must continue only if I haven't already found end
        if(!reach || currMax<=end)     //I didn't find end, but either I got to the beginning of highway (!reach as it is head of list) or currMax is less than end ( I surpassed end) --> end station doesn't exist
            return NULL;

        //Now I start looking for a path. The stations reached by start are already set, so maxReached is startLevel (lowest visited)
        startLevel = reach->next;
        maxReached = startLevel;
        st = startLevel;
        while(!isReached && startLevel->id<=endLevel->id) {
            currMax = st->id - getMax_cars(st->cars);   //set currMax by retriving max capacity from cars in st
            reach = maxReached->prev;
            while(reach && reach->id>=currMax) {    //Checks all reachable (by st) stations starting from maxReached (in fact I don't have to start from st, as station before maxReached are already visited and don't need to be updated)
                reach->reachedBy = st;
                if(reach->id == end) {      //The first time I reach end, as bfs is done in ascending order for each level, st is already the right station that reaches end in path --> I set isReached on 1 and break
                    isReached = 1;
                    break;
                }
                //If I get here, reach is not end but it's reached by st, heance I update maxReached
                maxReached = reach;
                reach = reach->prev;
            }

            //I must check is I reached endLevel and update st and only if end has not been found
            if(!isReached) {
                if (currMax <= end)      //I got beyond end station (currMax>=end) but I didn't find end --> end station doesn't exist. I break (and I keep isReached=0)
                    break;

                /* if st==endLevel, I reached end of level in bfs, so I must update also endLevel and startLevel, and in this case st must be set to startLevel
                 * Otherwise I normally go to next station in ascending order */
                if (st == endLevel) {        //Oss: if st = NULL, the end of level is reached
                    //Now the limits of next level are definitively given by old startLevel and actual maxReached
                    endLevel = startLevel->prev;
                    startLevel = maxReached;        //hence if no other station can be reached, maxReached is kept to last startLevel --> startLevel doesn't change, while endLevel changes into startLevel->prev, so endlevel->id < startLevel->id
                    st = startLevel;
                } else
                    st = st->next;
            }
        }
        if(!isReached)      //If I exit loop with isReached==0, end doesn't exist or a path to it doesn't exist
            return NULL;
    }

    //Now I know end exists and a path from start to end has been found; it can be retrieved by following the field reachedBy from end to start
    //From end to start the path is flipped --> to reverse order, I insert into list of pathNode_t from head of list
    //As from planPath I know that start != end, I don't bother about the corner case start==end
    st = reach;
    while(st != start) {
        path = insertHead_list(path, st);
        st = st->reachedBy;
    }
    path = insertHead_list(path, start);  //I exited because st = start, hence start is missing
    return path;
}

void handleCommand(highway_t *hw, char comm[], FILE *in, FILE *out) {
    int ncars, nArr, id, start, end;
    int *cars, car, maxCar, nMax, i, res;
    pathNode_t *path;
    station_t *st;

    //aggiungi-stazione
    if(comm[0]=='a' && comm[9]=='s') {
        if(fscanf(in, "%d %d", &id, &ncars) < 0)
            return;
        nArr = CARSSIZE0;
        while(ncars > nArr)
            nArr *= 2;
        cars = malloc(sizeof(int)*nArr);
        maxCar = INT_MIN;
        nMax = 0;
        for(i=0 ; i<ncars ; i++){
            if(fscanf(in, "%d", &cars[i]) < 0)
                return;
            if(cars[i] > maxCar) {
                maxCar = cars[i];
                nMax = 1;
            } else if (cars[i] == maxCar)
                nMax++;       
        }
        st = insertStationWithMax(hw, id, cars, ncars, nArr, maxCar, nMax);
        if(st)
            fprintf(out, "aggiunta\n");
        else {
            fprintf(out, "non aggiunta\n");
            free(cars);
        }
    }

    //demolischi-stazione
    else if(comm[0]=='d') {
        if(fscanf(in, "%d", &id) < 0)
            return;
        res = deleteStation(hw, id);
        if(res)
            fprintf(out, "demolita\n");
        else
            fprintf(out, "non demolita\n");
    }

    //aggiungi-auto
    else if(comm[0]=='a' && comm[9]=='a') {
        if(fscanf(in, "%d %d", &id, &car) < 0)
            return;
        st = insertCar(hw, id, car);
        if(st)
            fprintf(out, "aggiunta\n");
        else
            fprintf(out, "non aggiunta\n");
    }

    //rottama-auto
    else if(comm[0]=='r') {
        if(fscanf(in, "%d %d", &id, &car) < 0)
            return;
        st = deleteCar(hw, id, car);
        if(st)
            fprintf(out, "rottamata\n");
        else
            fprintf(out, "non rottamata\n");
    }

    //pianifica-percorso
    else if(comm[0]=='p') {
        if(fscanf(in, "%d %d", &start, &end) < 0)
            return;
        path = planPath(hw, start, end);
        if(path) {
            printPath(out, path);
            free_path(path);
        } else
            fprintf(out, "nessun percorso\n");
    }
}