#include <iostream>
#include <vector>
using namespace std;

struct Slot
	{
		string name;
		int result;
		int ID;
		int num;
        int time;
	};
vector<Slot> slot_1;
class Heap
{
    public:
    vector<Slot> heap;
    void heapify_up(vector<Slot>& heap ,int index)
    {
        if (index == 0)
            return;
        int parent_index = (index - 1) / 2;
        if (heap[index].num < heap[parent_index].num)
        {
            swap(heap[index], heap[parent_index]);
            heapify_up(heap, parent_index);
        }
        else if(heap[index].num == heap[parent_index].num){
            if(heap[index].time < heap[parent_index].time){
                swap(heap[index], heap[parent_index]);
                heapify_up(heap, parent_index);
            }
        }
    }

    void heapify_down(vector<Slot> &heap, int i){
        int left_child_index = 2 * i + 1;
        int right_child_index = 2 * i + 2;
        int smallest = i;
        if(left_child_index< heap.size() && ((heap[left_child_index].num < heap[smallest].num) || ((heap[left_child_index].num == heap[smallest].num) && (heap[left_child_index].time < heap[smallest].time)))){
            smallest = left_child_index;
        }

        if(right_child_index < heap.size() && ((heap[right_child_index].num < heap[smallest].num) || ((heap[right_child_index].num == heap[smallest].num) && (heap[right_child_index].time < heap[smallest].time)))){
            smallest = right_child_index;
        }

        if(smallest != i){
            swap(heap[i], heap[smallest]);
            heapify_down(heap, smallest);
        }
    }

    void insert(vector<Slot> &heap, string name, int result, int ID, int num,  int time){
        Slot slot;
        slot.name = name;
        slot.result = result;
        slot.ID = ID;
        slot.num = num;
        slot.time = time;
        heap.push_back(slot);
        heapify_up(heap, heap.size() - 1);
    }

    void delete_value_heap_ID(vector<Slot> &heap, int ID){
        if (heap.empty()) return;
        int index = -1;
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].ID == ID) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return;
        }
        swap(heap[index], heap[heap.size()-1]);
        heap.pop_back();
        heapify_up(heap, index); 
        heapify_down(heap, index);  
    }

    void delete_value_heap(vector<Slot> &heap, string name){
        if (heap.empty()) return;
        int index = -1;
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].name == name) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return;
        }
        int left_child_index = 2 * index + 1;
        int right_child_index = 2 * index + 2;
        swap(heap[index], heap[heap.size()-1]);
        heap.pop_back();
        int parent = (index - 1) / 2;
        if(index > 0 && heap[index].num < heap[parent].num){
            heapify_up(heap, index); 
        }
        else if(index == 0 && (heap[index].num == heap[left_child_index].num || heap[index].num == heap[right_child_index].num)){
            heapify_down(heap, index);
        }
        else if(index > 0 && (heap[index].num == heap[left_child_index].num || heap[index].num == heap[right_child_index].num)){
            heapify_down(heap, index);
        }
		else if(index > 0 && heap[index].num == heap[parent].num){
			heapify_up(heap, index);
		}
        else{
            heapify_down(heap, index);
        }
    }

    void display_inorder(vector<Slot> &heap, int i)
    {
        if (i < heap.size())
        {
            display_inorder(heap, 2 * i + 1);
            cout << heap[i].name << " " << heap[i].result << " " << heap[i].ID << " " << heap[i].num << " " << heap[i].time << endl;
            display_inorder(heap, 2 * i + 2);
        }
    }
};

int main()
{
    Heap order_dish;
    int time = 1;
    slot_1.push_back({"a", 5, 1, 4, time});
    order_dish.insert(order_dish.heap, slot_1[0].name, slot_1[0].result, slot_1[0].ID, slot_1[0].num, slot_1[0].time);
    
    for (int i = 0; i < slot_1.size(); i++)
    {
        time = slot_1[i].time;
        time++;
    }
    slot_1.push_back({"b", 3, 2, 1, time});
    order_dish.insert(order_dish.heap, slot_1[1].name, slot_1[1].result, slot_1[1].ID, slot_1[1].num, slot_1[1].time);
    for (int i = 0; i < slot_1.size(); i++)
    {
        time = slot_1[i].time;
        time++;
    }
    slot_1.push_back({"c", 2, 3, 1, time});
    order_dish.insert(order_dish.heap, slot_1[2].name, slot_1[2].result, slot_1[2].ID, slot_1[2].num, slot_1[2].time);
    for (int i = 0; i < slot_1.size(); i++)
    {
        time = slot_1[i].time;
        time++;
    }
    slot_1.push_back({"d", 1, 4, 1, time});
    order_dish.insert(order_dish.heap, slot_1[3].name, slot_1[3].result, slot_1[3].ID, slot_1[3].num, slot_1[3].time);
    slot_1[1].num++;


    order_dish.delete_value_heap(order_dish.heap, slot_1[1].name);
    order_dish.insert(order_dish.heap, slot_1[1].name, slot_1[1].result, slot_1[1].ID, slot_1[1].num, slot_1[1].time);
    // for (int i = 0; i < order_dish.heap.size(); i++)
    // {
    //     cout << order_dish.heap[i].name << " " << order_dish.heap[i].num << " " << order_dish.heap[i].time << endl;
    // }

    order_dish.display_inorder(order_dish.heap, 0);
    return 0;
}