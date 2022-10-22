#include <iostream>

using namespace std;

struct Result {
    int index;
    int value;
};

struct Result min_info(int* arr, int size) {
    Result a;
	int SmallestNumber = -1;
	int ind = 0;
	for (int i = 0; i < size; i ++ ) {
	    if (SmallestNumber == -1 && arr[i] >= 0) {
	        SmallestNumber = arr[i];
	        ind = i;
	        break;
	    }
	}
	for (int i = 0; i < size; i++) {
	    if (arr[i] < SmallestNumber && arr[i] >= 0){
	        SmallestNumber = arr[i];
	        ind = i;
	    }
	}
	a.index = ind;
	a.value = SmallestNumber;
	return a;
}

struct Result max_info(int* arr, int size) {
    Result a;
	int BiggestNumber = -1;
	int ind = 0;
	for (int i = 0; i < size; i ++ ) {
	    if (BiggestNumber == -1 && arr[i] >= 0) {
	        BiggestNumber = arr[i];
	        ind = i;
	        break;
	    }
	}
	for (int i = 0; i < size; i++) {
	    if (arr[i] > BiggestNumber && arr[i] >= 0){
	        BiggestNumber = arr[i];
	        ind = i;
	    }
	}
	a.index = ind;
	a.value = BiggestNumber;
	return a;
}


class MemoryManager {
  public:
    MemoryManager(int* blocks, int sizeBlocks, int* processes, int sizeProcesses) {
        blocks_ = new int[sizeBlocks];
        blocks_ = blocks;
        processes_ = new int[sizeProcesses];
        processes_ = processes;
        allocation = new bool[sizeProcesses];
        allocation_pos = new int[sizeProcesses];
        sizeb = sizeBlocks;
        sizep = sizeProcesses;
    }
    
    void reset() {
        for (int i = 0; i < sizep; i++) {
            allocation[i] = false;
            allocation_pos[i] = 0;
        }
    }
    
    void first_fit() {
        for (int i = 0; i < sizep; i++) {
            for (int j = 0; j < sizeb; j++) {
                if (processes_[i] <= blocks_[j]) {
                    blocks_[j] = blocks_[j] - processes_[i];
                    allocation[i] = true;
                    allocation_pos[i] = j;
                    break;
                }
            }
        }
        
        for (int i = 0; i < sizep; i++) {
            if (allocation[i] == false) {
                cout << "Process:" << i+1 << "     Allocated?:" << boolalpha << allocation[i] << "     Allocation Position: NONE" << endl;
            } else {
                cout << "Process:" << i+1 << "     Allocated?:" << boolalpha << allocation[i] << "     Allocation Position:" << allocation_pos[i]+1 << endl;
            }
        }
    }
    
    void best_fit() {
        int tmp[sizep][sizeb];
        Result a;
        for (int i = 0; i < sizep; i++) {
            for (int j = 0; j < sizeb; j++) {
                //cout << blocks_[j] << "   " << processes_[i] << endl;
                tmp[i][j] = blocks_[j] - processes_[i];
            }
            a = min_info(tmp[i], sizeb);
            if (a.value >= 0) {
                blocks_[a.index] = blocks_[a.index] - processes_[i];
                allocation[i] = true;
                allocation_pos[i] = a.index;
            } else {
                allocation[i] = false;
            }
        }
        for (int i = 0; i < sizep; i++) {
            if (allocation[i] == false) {
                cout << "Process:" << i+1 << "     Allocated?:" << boolalpha << allocation[i] << "     Allocation Position: NONE" << endl;
            } else {
                cout << "Process:" << i+1 << "     Allocated?:" << boolalpha << allocation[i] << "     Allocation Position:" << allocation_pos[i]+1 << endl;
            }
        }
        
    }
    
    void worst_fit() {
        int tmp[sizep][sizeb];
        Result a;
        for (int i = 0; i < sizep; i++) {
            for (int j = 0; j < sizeb; j++) {
                //cout << blocks_[j] << "   " << processes_[i] << endl;
                tmp[i][j] = blocks_[j] - processes_[i];
            }
            a = max_info(tmp[i], sizeb);
            if (a.value >= 0) {
                blocks_[a.index] = blocks_[a.index] - processes_[i];
                allocation[i] = true;
                allocation_pos[i] = a.index;
            } else {
                allocation[i] = false;
            }
        }
        for (int i = 0; i < sizep; i++) {
            if (allocation[i] == false) {
                cout << "Process:" << i+1 << "     Allocated?:" << boolalpha << allocation[i] << "     Allocation Position: NONE" << endl;
            } else {
                cout << "Process:" << i+1 << "     Allocated?:" << boolalpha << allocation[i] << "     Allocation Position:" << allocation_pos[i]+1 << endl;
            }
        }
        
    }
    
  private:
    int sizeb;
    int sizep;
    int* blocks_;
    int* processes_;
    bool* allocation;
    int* allocation_pos;
  
};

int main()
{
    int blocks[] = {100, 500, 200, 300, 600};
    int processes[] = {212, 417, 112, 426};
    MemoryManager mem(blocks, 5, processes, 4);
    mem.worst_fit();
    return 0;
}