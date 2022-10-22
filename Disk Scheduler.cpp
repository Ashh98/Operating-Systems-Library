#include <iostream>

using namespace std;


class DiskScheduler {
  public:
  
  //This function sets the number of cylinders and the number of cylinder requests
    void ProblemSetting() {
        cout << "Please enter the requests size: ";
        cin >> reqsize;
        cout << "Please enter the cylinders size: ";
        cin >> cylsize;
        reqcylinders = new int[reqsize+1];
        
        //Generating a random series of requests such that duplicates are not allowed
        int num = 0;
        for (int i = 1; i <= reqsize; i++) {
            do {
                num = rand()%cylsize;
                for (int j = 1; j < i; j++) {
                    if (reqcylinders[j] == num) {
                        num = 0;
                        break;
                    }
                }
            } while (num == 0);
            reqcylinders[i] = num;
        }


        //Inserting a head cylinder such that it doesn't exist inside the generated series of requests
        num = -1;
        cout << "Please enter the head (from 0 to " << cylsize-1 << "): ";
        cin >> head;
        do {
            reqcylinders[0] = head;
            num = head;
            
            for (int j = 1; j < reqsize+1; j++) {
                if (reqcylinders[j] == num) {
                    num = -1;
                    cout << "Please enter a different head (from 0 to " << cylsize-1 << "): ";
                    cin >> head;
                    break;
                }
            }
        } while(num == -1);
    }
  
  
    //This function performs the FCFS algorithm
    void FCFS() {
        headmovements = 0;
        for (int i = 1; i <= reqsize; i++) {
            headmovements = headmovements + abs(reqcylinders[i] - reqcylinders[i-1]);
        }
        
        cout << "The total amount of head movement provided by FCFS is " << headmovements << endl;
    }
    
    
    //This function performs the SSTF algorithm
    void SSTF() {
        int tmp_reqcylinders[reqsize+1];
        int tmp_diff_forw[reqsize+1], tmp_diff_back[reqsize+1];
        int smallest_forw = cylsize;
        int smallest_back = cylsize;
        int min_indforw = 0;
        int min_indback = 0;
        int min_ind;
        int tmp_num;
        
        for (int i = 0; i <= reqsize; i++) {
            tmp_reqcylinders[i] = reqcylinders[i];
        }
        //Takes each element i of the series and checks the diff between it and all the rest elements
        //The element with the smallest difference is selected to be replaced next to element i
        for (int i = 0; i < reqsize; i++) {
            smallest_forw = cylsize;
            smallest_back = cylsize;
            for (int k = 0; k <= reqsize; k++) {
                tmp_diff_forw[k] = cylsize;
                tmp_diff_back[k] = cylsize;
            }
            
            for (int j = i+1; j <= reqsize; j++) {
                if (tmp_reqcylinders[j] > tmp_reqcylinders[i]) {
                    tmp_diff_forw[j] = abs(tmp_reqcylinders[j] - tmp_reqcylinders[i]);
                    if (smallest_forw > tmp_diff_forw[j]) {
                        smallest_forw = tmp_diff_forw[j];
                        min_indforw = j;
                    }
                } else {
                    tmp_diff_back[j] = abs(tmp_reqcylinders[j] - tmp_reqcylinders[i]);
                    if (smallest_back > tmp_diff_back[j]) {
                        smallest_back = tmp_diff_back[j];
                        min_indback = j;
                    }
                }
            }
            
            //If the difference between element i is the same for two other elements in the series
            //the bigger element is chosen to be replaced next to element i
            if (smallest_forw <= smallest_back) {
                min_ind = min_indforw;
            } else {
                min_ind = min_indback;
            }
            
            //cout << min_indforw << "  " << min_indback << endl;
            tmp_num = tmp_reqcylinders[i+1];
            tmp_reqcylinders[i+1] = tmp_reqcylinders[min_ind];
            tmp_reqcylinders[min_ind] = tmp_num;
            
            //cout << reqcylinders[i] << "  " << tmp_reqcylinders[i] << endl;
 
        }
        
        headmovements = 0;
        for (int i = 1; i <= reqsize; i++) {
            headmovements = headmovements + abs(tmp_reqcylinders[i] - tmp_reqcylinders[i-1]);
        }
        cout << "The total amount of head movement provided by SSTF is " << headmovements << endl;
    }
    
    
    //This function performs SCAN algorithm
    void SCAN(string direction) {
        int tmp_reqcylinders[reqsize+2];
        int nxt_ind;
        int tmp;
        int biggest;
        int smallest;
        int big_ind;
        int small_ind;
        
        for (int i = 0; i <= reqsize+1; i++) {
            tmp_reqcylinders[i] = reqcylinders[i];
        }
        
        if (direction == "inwards") {
            tmp_reqcylinders[reqsize+1] = 0;
            
            //Series is sorted descendingly according to elements smaller than the head
            for (int i = 1; i <= reqsize+1; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize+1; j++) {
                    if (tmp_reqcylinders[j] < tmp_reqcylinders[0] && tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
                
                if (biggest == -1) {
                    nxt_ind = i;
                    break;
                }
            }
            
            //Series is sorted ascendingly according to elements bigger than the head
            for (int i = nxt_ind; i < reqsize+1; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize+1; j++) {
                    if (tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                tmp_reqcylinders[small_ind] = tmp;
            }
            
        } else if (direction == "outwards") {
            tmp_reqcylinders[reqsize+1] = cylsize-1;
            
            //Series is sorted ascendingly according to elements bigger than the head
            for (int i = 1; i <= reqsize+1; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize+1; j++) {
                    if (tmp_reqcylinders[j] > tmp_reqcylinders[0] && tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                tmp_reqcylinders[small_ind] = tmp;
                
                if (smallest == cylsize) {
                    nxt_ind = i;
                    break;
                }
            }
            
            
            //Series is sorted descendingly according to elements smaller than the head
            for (int i = nxt_ind; i < reqsize+1; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize+1; j++) {
                    if (tmp_reqcylinders[j] < tmp_reqcylinders[nxt_ind-1] && tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
            }
        }
        
        headmovements = 0;
        for (int i = 1; i <= reqsize+1; i++) {
            headmovements = headmovements + abs(tmp_reqcylinders[i] - tmp_reqcylinders[i-1]);
        }

        if (direction == "inwards") {
            cout << "The total amount of head movement inwards provided by SCAN is " << headmovements << endl;
        } else if (direction == "outwards") {
            cout << "The total amount of head movement outwards provided by SCAN is " << headmovements << endl;
        }

    }

    //This function performs CSCAN algorithm
    void CSCAN(string direction) {
        int tmp_reqcylinders[reqsize+3];
        int nxt_ind;
        int tmp;
        int biggest;
        int smallest;
        int big_ind;
        int small_ind;
        
        for (int i = 0; i <= reqsize; i++) {
            tmp_reqcylinders[i] = reqcylinders[i];
        }
        
        tmp_reqcylinders[reqsize+1] = 0;
        tmp_reqcylinders[reqsize+2] = cylsize-1;
        
        if (direction == "inwards") {
            for (int i = 1; i <= reqsize+2; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize+2; j++) {
                    if (tmp_reqcylinders[j] < tmp_reqcylinders[0] && tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
                
                if (biggest == -1) {
                    nxt_ind = i;
                    break;
                }
            }
            
            for (int i = nxt_ind; i < reqsize+2; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize+2; j++) {
                    if (tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
            }
            
        } else if (direction == "outwards") {
            for (int i = 1; i <= reqsize+2; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize+2; j++) {
                    if (tmp_reqcylinders[j] > tmp_reqcylinders[0] && tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                tmp_reqcylinders[small_ind] = tmp;
                
                if (smallest == cylsize) {
                    nxt_ind = i;
                    break;
                }
            }

            for (int i = nxt_ind; i < reqsize+2; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize+2; j++) {
                    if (tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                tmp_reqcylinders[small_ind] = tmp;
            }
        }
        
        headmovements = 0;
        for (int i = 1; i <= reqsize+1; i++) {
            headmovements = headmovements + abs(tmp_reqcylinders[i] - tmp_reqcylinders[i-1]);
        }

        if (direction == "inwards") {
            cout << "The total amount of head movement inwards provided by CSCAN is " << headmovements << endl;
        } else if (direction == "outwards") {
            cout << "The total amount of head movement outwards provided by CSCAN is " << headmovements << endl;
        }

    }
    
    //This function performs LOOK algorithm
    void LOOK(string direction) {
        int tmp_reqcylinders[reqsize+1];
        int nxt_ind;
        int tmp;
        int biggest;
        int smallest;
        int big_ind;
        int small_ind;
        
        for (int i = 0; i <= reqsize; i++) {
            tmp_reqcylinders[i] = reqcylinders[i];
        }
        
        if (direction == "inwards") {
            for (int i = 1; i <= reqsize; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] < tmp_reqcylinders[0] && tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
                
                if (biggest == -1) {
                    nxt_ind = i;
                    break;
                }
            }
            
            for (int i = nxt_ind; i < reqsize; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                tmp_reqcylinders[small_ind] = tmp;
            }
            
        } else if (direction == "outwards") {
            for (int i = 1; i <= reqsize; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] > tmp_reqcylinders[0] && tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }

                if (smallest != cylsize) {
                    tmp = tmp_reqcylinders[i];
                    tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                    tmp_reqcylinders[small_ind] = tmp;
                } else if (smallest == cylsize) {
                    nxt_ind = i;
                    break;
                }
            }
            
            for (int i = nxt_ind; i < reqsize; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] < tmp_reqcylinders[nxt_ind-1] && tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
            }
        }
        
        headmovements = 0;
        for (int i = 1; i <= reqsize+1; i++) {
            headmovements = headmovements + abs(tmp_reqcylinders[i] - tmp_reqcylinders[i-1]);
        }
        if (direction == "inwards") {
            cout << "The total amount of head movement inwards provided by LOOK is " << headmovements << endl;
        } else if (direction == "outwards") {
            cout << "The total amount of head movement outwards provided by LOOK is " << headmovements << endl;
        }    
    }
    
    //This function performs CLOOK algorithm
    void CLOOK(string direction) {
        int tmp_reqcylinders[reqsize+1];
        int nxt_ind;
        int tmp;
        int biggest;
        int smallest;
        int big_ind;
        int small_ind;
        
        for (int i = 0; i <= reqsize; i++) {
            tmp_reqcylinders[i] = reqcylinders[i];
        }
        
        if (direction == "inwards") {
            for (int i = 1; i <= reqsize; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] < tmp_reqcylinders[0] && tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
                
                if (biggest == -1) {
                    nxt_ind = i;
                    break;
                }
            }
            
            for (int i = nxt_ind; i < reqsize; i++) {
                biggest = -1;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] > biggest) {
                        biggest = tmp_reqcylinders[j];
                        big_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[big_ind];
                tmp_reqcylinders[big_ind] = tmp;
            }
            
        } else if (direction == "outwards") {
            for (int i = 1; i <= reqsize; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] > tmp_reqcylinders[0] && tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }
                
                if (smallest != cylsize) {
                    tmp = tmp_reqcylinders[i];
                    tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                    tmp_reqcylinders[small_ind] = tmp;
                } else if (smallest == cylsize) {
                    nxt_ind = i;
                    break;
                }
            }


            for (int i = nxt_ind; i < reqsize; i++) {
                smallest = cylsize;
                for (int j = i; j <= reqsize; j++) {
                    if (tmp_reqcylinders[j] < smallest) {
                        smallest = tmp_reqcylinders[j];
                        small_ind = j;
                    }
                }
                tmp = tmp_reqcylinders[i];
                tmp_reqcylinders[i] = tmp_reqcylinders[small_ind];
                tmp_reqcylinders[small_ind] = tmp;
            }
        }

        headmovements = 0;
        for (int i = 1; i <= reqsize+1; i++) {
            headmovements = headmovements + abs(tmp_reqcylinders[i] - tmp_reqcylinders[i-1]);
        }
        
        if (direction == "inwards") {
            cout << "The total amount of head movement inwards provided by CLOOK is " << headmovements << endl;
        } else if (direction == "outwards") {
            cout << "The total amount of head movement outwards provided by CLOOK is " << headmovements << endl;
        }
        
    }
    
  private:
    int* reqcylinders;
    int head;
    int reqsize;
    int cylsize;
    int headmovements;
    
};

int main() {
    DiskScheduler x;
    
    x.ProblemSetting();
    x.FCFS();
    x.SSTF();
    x.SCAN("inwards");
    x.SCAN("outwards");
    x.CSCAN("inwards");
    x.CSCAN("outwards");
    x.LOOK("inwards");
    x.LOOK("outwards");
    x.CLOOK("inwards");
    x.CLOOK("outwards");

    return 0;
}