#include <iostream>
using namespace std;

// Container linked list
struct Container{
    int id;
    int weight;
    int assignedTruck;
    Container* next;

    Container(int i, int w){
        id = i;
        weight = w;
        assignedTruck = -1;
        next = NULL;
    }
};
//Inserting the containers at the at the tail
void insertContainer(Container* &head, int id, int weight){
    Container *newNode = new Container(id, weight);
    //if the container that we are inserting is the firt container
    if(head == NULL){
        head = newNode;
        return;
    }

    Container * temp = head;
    while(temp ->next != NULL){
        temp = temp->next;
    }
    temp ->next = newNode; 
}
//Creating a truck queue
struct Truck{
    int id;
    int capacity;
    int remaining;
    Truck* next;

    Truck(int i, int c){
        id = i;
        capacity = c;
        remaining = c;
        next = NULL;
    }
};
class TruckQueue{
private:
    Truck *rear;
    Truck *front;
//Cponstructor
public:
    TruckQueue(){
        rear = front = NULL;
    }
//Adding truck to the queue
    void enqueue(int id, int capacity){
     Truck * newTruck = new Truck(id, capacity);
    if(front == NULL){
        front =rear = newTruck;
      }
      else{
        rear ->next = newTruck;
        rear = newTruck;
      }
    }
      //returning front truck
      Truck* getFront(){
        return front;
      }
};

//Calculating remaining total capacity
int totalRemainingCapacity(Truck *truck){
    int total = 0;

    while(truck!= NULL){
        total += truck->remaining;
        truck = truck->next;
    }
    return total;
}
//Backtracking

bool backtrack(Container* current, Truck*truck, int remainingWeight){
    //base case
    if(current == NULL){
        return true;
    }
    if(truck == NULL){
        return false;
    }

    //pruning 
    //checking total remaining capacity
    int availableCapacity = totalRemainingCapacity(truck);
    if(remainingWeight > availableCapacity){
        return false;
    }

    //Assigning current container to the currect truck
    if(current->weight <= truck->remaining){
        //choose it
            current->assignedTruck = truck->id;
            truck->remaining -= current->weight;
            //Exploring
            if(backtrack(current->next, truck, remainingWeight - current->weight)){
                return true;
            }
            //backtracking
            truck->remaining += current->weight;
             current->assignedTruck = -1;
}


// Pruning
return backtrack(current, truck->next, remainingWeight);
}

// PRINT FINAL ASSIGNMENTS
void printAssignments(Container* head, Truck* truck){
while (truck != NULL)
{
cout << "\nTruck " << truck->id << " (Capacity: " << truck->capacity << " tons)\n";
    int totalWeight = 0;
    bool found = false;

    Container* temp = head;

    while (temp != NULL)
    {
        if (temp->assignedTruck == truck->id)
        {
            cout << "Container ID: " << temp->id
                 << " | Weight: " << temp->weight << " tons\n";

            totalWeight += temp->weight;
            found = true;
        }

        temp = temp->next;
    }

    if (!found)
    {
        cout << "No containers assigned.\n";
    }

    cout << "Total Loaded Weight: " << totalWeight << " tons\n";
    cout << "Remaining Capacity: " << truck->remaining << " tons\n";
    truck = truck->next;
}

}

// 6. MAIN FUNCTION

int main()
{
Container* head = NULL;
TruckQueue trucks;
int numberOfContainers;
int numberOfTrucks;
int totalWeight = 0;
// INPUT CONTAINERS

cout << "Enter number of containers: ";
cin >> numberOfContainers;

for (int i = 0; i < numberOfContainers; i++)
{
    int id;
    int weight;

    cout << "Enter container ID and weight: ";
    cin >> id >> weight;

    if (weight <= 0)
    {
        cout << "Weight must be positive.\n";
        return 0;
    }
    insertContainer(head, id, weight);
    totalWeight += weight;
}

// INPUT TRUCKS
cout << "\nEnter number of trucks: ";
cin >> numberOfTrucks;

for (int i = 0; i < numberOfTrucks; i++)
{
    int capacity;

    cout << "Enter capacity of Truck "
         << i + 1 << ": ";
    cin >> capacity;
    if (capacity <= 0)
    {
        cout << "Capacity must be positive.\n";
        return 0;
    }
    trucks.enqueue(i + 1, capacity);
}


// RUN BACKTRACKING

bool result = backtrack(head, trucks.getFront(),totalWeight);

// Displaying result
if (result)
{
    cout << "\nAll containers successfully loaded!\n";
    printAssignments(head, trucks.getFront());
}
else
{
    cout << "\nInsufficient truck capacity.\n";
}
return 0;

}

