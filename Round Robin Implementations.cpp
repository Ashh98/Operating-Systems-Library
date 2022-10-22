#include <iostream>
#include <vector>
using namespace std;

class RoundRobin {
    public:
    
    void ProblemSetting() {
        cout << "Please enter the number of processes: ";
        cin >> nproc;
        
        proc = new int(nproc);
        procburst = new int(nproc);
        
        cout << "Please enter the burst time for each process" << endl;
        for (int i = 0; i < nproc; i++) {
            cout << "P" << i+1 << ": ";
            cin >> procburst[i];
            proc[i] = i+1;
        }
        
        //cout << "Please enter the time quantum: ";
        //cin >> tq;
    }
    
    void ClassicalRR() {
        vector<int> start;
        vector<int> end;
        vector<int> proc_no;
        int tmp_procburst[nproc];
        for (int i = 0; i < nproc; i++) {
            tmp_procburst[i] = procburst[i];
        }
        
        
        int done;
        int c = 0;
        while (done != 0) {
            done = 0;
            
            if (c == 0 && tmp_procburst[c] != 0) {
                if (tmp_procburst[c] <= tq) {
                    start.push_back(0);
                    end.push_back(tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(c);
                } else {
                    start.push_back(0);
                    end.push_back(tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(c);
                }
            } else if (c != 0 && tmp_procburst[c] != 0) {
                if (tmp_procburst[c] <= tq) {
                    start.push_back(end.back());
                    end.push_back(end.back() + tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(c);
                } else {
                    start.push_back(end.back());
                    end.push_back(end.back() + tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(c);
                }
            }
            
            for (int i = 0; i < nproc; i++) {
                if (tmp_procburst[i] != 0) {
                    done = 1;
                    //cout << tmp_procburst[i] << endl;
                }
                //cout << tmp_procburst[i] << "  ";
                //if (i == nproc-1) { cout << c << "\n"; }
            }
            
            if (c == nproc-1) {
                c = 0;
            } else {
                c++;
            }
        }
        
        WaitingTime(proc_no, start, end);

    }
    
    void AbdulrahimRR() {
        vector<int> start;
        vector<int> end;
        vector<int> proc_no;
        int tmp_procburst[nproc];
        for (int i = 0; i < nproc; i++) {
            tmp_procburst[i] = procburst[i];
        }
        
        
        int done;
        int c = 0;
        while (done != 0) {
            done = 0;
            
            if (c == 0 && tmp_procburst[c] != 0) {
                if (tmp_procburst[c] <= tq) {
                    start.push_back(0);
                    end.push_back(tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(c);
                } else {
                    start.push_back(0);
                    end.push_back(tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(c);
                    if (tmp_procburst[c] <= tq/2) {
                        start.push_back(end.back());
                        end.push_back(end.back() + tmp_procburst[c]);
                        tmp_procburst[c] = 0;
                        proc_no.push_back(c);
                    }
                }
            } else if (c != 0 && tmp_procburst[c] != 0) {
                if (tmp_procburst[c] <= tq) {
                    start.push_back(end.back());
                    end.push_back(end.back() + tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(c);
                } else {
                    start.push_back(end.back());
                    end.push_back(end.back() + tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(c);
                    if (tmp_procburst[c] <= tq/2) {
                        start.push_back(end.back());
                        end.push_back(end.back() + tmp_procburst[c]);
                        tmp_procburst[c] = 0;
                        proc_no.push_back(c);
                    }
                }
            }
            
            for (int i = 0; i < nproc; i++) {
                if (tmp_procburst[i] != 0) {
                    done = 1;
                    cout << tmp_procburst[i] << endl;
                }
                cout << tmp_procburst[i] << "  ";
                if (i == nproc-1) { cout << c << "\n"; }
            }
            
            if (c == nproc-1) {
                c = 0;
            } else {
                c++;
            }
        }
        
        WaitingTime(proc_no, start, end);

    }
 
    void MishraRR() {
        vector<int> start;
        vector<int> end;
        vector<int> proc_no;
        int tmp_procburst[nproc];
        int tmp_procno[nproc];
        for (int i = 0; i < nproc; i++) {
            tmp_procburst[i] = procburst[i];
            tmp_procno[i] = i;
        }
        
        int smallest;
        int ind;
        int tmp;
        int tmp1;
        for (int i = 0; i < nproc; i++) {
            smallest = tmp_procburst[i];
            for (int j = i; j < nproc; j++) {
                if (tmp_procburst[j] <= smallest) {
                    smallest = tmp_procburst[j];
                    ind = j;
                }
            }
            tmp = tmp_procburst[ind];
            tmp1 = tmp_procno[ind];
            tmp_procburst[ind] = tmp_procburst[i];
            tmp_procno[ind] = tmp_procno[i];
            tmp_procburst[i] = tmp;
            tmp_procno[i] = tmp1;
        }
        
        
        int done;
        int c = 0;
        //int fullround = 0;
        while (done != 0) {
            done = 0;
            if (c == 0 && tmp_procburst[c] != 0) {
                tq = tmp_procburst[c];
                if (tmp_procburst[c] <= tq) {
                    start.push_back(0);
                    end.push_back(tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(tmp_procno[c]);
                } else {
                    start.push_back(0);
                    end.push_back(tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(tmp_procno[c]);
                }
            } else if (c != 0 && tmp_procburst[c] != 0) {
                if (tmp_procburst[c] <= tq) {
                    start.push_back(end.back());
                    end.push_back(end.back() + tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(tmp_procno[c]);
                } else {
                    start.push_back(end.back());
                    end.push_back(end.back() + tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(tmp_procno[c]);
                }
            }
            
            for (int i = 0; i < nproc; i++) {
                if (tmp_procburst[i] != 0) {
                    done = 1;
                    //cout << tmp_procburst[i] << endl;
                }
                cout << tmp_procburst[i] << "  ";
                if (i == nproc-1) { cout << c << "\n"; }
            }
            
            if (c == nproc-1) {
                c = 0;
                //fullround++;
                //tq = tmp_procburst[fullround];
                for (int i = 0; i < nproc; i++) {
                    if (tmp_procburst[i] > 0) {
                        tq = tmp_procburst[i];
                        break;
                    }
                }
            } else {
                c++;
            }
        }
        
        WaitingTime(proc_no, start, end);

    }
    
    void MishraMODRR() {
        vector<int> start;
        vector<int> end;
        vector<int> proc_no;
        int tmp_procburst[nproc];
        int tmp_procno[nproc];
        for (int i = 0; i < nproc; i++) {
            tmp_procburst[i] = procburst[i];
            tmp_procno[i] = i;
        }
        
        int smallest;
        int ind;
        int tmp;
        int tmp1;
        for (int i = 0; i < nproc; i++) {
            smallest = tmp_procburst[i];
            for (int j = i; j < nproc; j++) {
                if (tmp_procburst[j] <= smallest) {
                    smallest = tmp_procburst[j];
                    ind = j;
                }
            }
            tmp = tmp_procburst[ind];
            tmp1 = tmp_procno[ind];
            tmp_procburst[ind] = tmp_procburst[i];
            tmp_procno[ind] = tmp_procno[i];
            tmp_procburst[i] = tmp;
            tmp_procno[i] = tmp1;
        }
        
        
        int done;
        int c = 0;
        int fullround = 0;
        while (done != 0) {
            done = 0;
            if (c == 0 && tmp_procburst[c] != 0) {
                tq = tmp_procburst[c];
                if (tmp_procburst[c] <= tq) {
                    start.push_back(0);
                    end.push_back(tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(tmp_procno[c]);
                } else {
                    start.push_back(0);
                    end.push_back(tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(tmp_procno[c]);
                    if (tmp_procburst[c] <= tq/2) {
                        start.push_back(end.back());
                        end.push_back(end.back() + tmp_procburst[c]);
                        tmp_procburst[c] = 0;
                        proc_no.push_back(tmp_procno[c]);
                    }
                }
            } else if (c != 0 && tmp_procburst[c] != 0) {
                if (tmp_procburst[c] <= tq) {
                    start.push_back(end.back());
                    end.push_back(end.back() + tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(tmp_procno[c]);
                } else {
                    start.push_back(end.back());
                    end.push_back(end.back() + tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(tmp_procno[c]);
                    if (tmp_procburst[c] <= tq/2) {
                        start.push_back(end.back());
                        end.push_back(end.back() + tmp_procburst[c]);
                        tmp_procburst[c] = 0;
                        proc_no.push_back(tmp_procno[c]);
                    }
                }
            }
            
            for (int i = 0; i < nproc; i++) {
                if (tmp_procburst[i] != 0) {
                    done = 1;
                    //cout << tmp_procburst[i] << endl;
                }
                //cout << tmp_procburst[i] << "  ";
                //if (i == nproc-1) { cout << c << "\n"; }
            }
            
            if (c == nproc-1) {
                c = 0;
                fullround++;
                tq = tmp_procburst[fullround];
            } else {
                c++;
            }
        }
        
        WaitingTime(proc_no, start, end);

    }
    
    void NayakRR() {
        vector<int> start;
        vector<int> end;
        vector<int> proc_no;
        int tmp_procburst[nproc];
        int tmp_procno[nproc];
        for (int i = 0; i < nproc; i++) {
            tmp_procburst[i] = procburst[i];
            tmp_procno[i] = i;
        }
        
        int smallest;
        int ind;
        int tmp;
        int tmp1;
        for (int i = 0; i < nproc; i++) {
            smallest = tmp_procburst[i];
            for (int j = i; j < nproc; j++) {
                if (tmp_procburst[j] <= smallest) {
                    smallest = tmp_procburst[j];
                    ind = j;
                }
            }
            tmp = tmp_procburst[ind];
            tmp1 = tmp_procno[ind];
            tmp_procburst[ind] = tmp_procburst[i];
            tmp_procno[ind] = tmp_procno[i];
            tmp_procburst[i] = tmp;
            tmp_procno[i] = tmp1;
        }
        
        
        int done;
        int c = 0;
        int k = 0;
        int fullround = 0;
        while (done != 0) {
            done = 0;

            if (c == 0 && tmp_procburst[c] != 0) {
                if (nproc % 2 == 0) {
                    tq = (tmp_procburst[((nproc+1)/2) - 1] + tmp_procburst[nproc - 1])/2;
                } else {
                    tq = (tmp_procburst[(nproc/2) - 1]+tmp_procburst[nproc/2]+tmp_procburst[nproc-1])/2;
                }
                if (tmp_procburst[c] <= tq) {
                    start.push_back(0);
                    end.push_back(tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(tmp_procno[c]);
                } else {
                    start.push_back(0);
                    end.push_back(tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(tmp_procno[c]);
                }
            } else if (c != 0 && tmp_procburst[c] != 0) {
                if (tmp_procburst[c] <= tq) {
                    start.push_back(end.back());
                    end.push_back(end.back() + tmp_procburst[c]);
                    tmp_procburst[c] = 0;
                    proc_no.push_back(tmp_procno[c]);
                } else {
                    start.push_back(end.back());
                    end.push_back(end.back() + tq);
                    tmp_procburst[c] = tmp_procburst[c] - tq;
                    proc_no.push_back(tmp_procno[c]);
                }
            }
            
            for (int i = 0; i < nproc; i++) {
                if (tmp_procburst[i] != 0) {
                    done = 1;
                    //cout << tmp_procburst[i] << endl;
                }
                cout << tmp_procburst[i] << "  ";
                if (i == nproc-1) { cout << c << "\n"; }
            }
            
            if (c == nproc-1) {
                c = 0;
                k = 0;
                for (int i = 0; i < nproc; i++) {
                    if (tmp_procburst[i] > 0) {
                        k = i;
                        cout << k << endl;
                        break;
                    }
                }
                if ( (nproc-k) % 2 == 0) {
                    tq = (tmp_procburst[((nproc-k+1)/2) + k] + tmp_procburst[nproc - 1])/2;
                } else {
                    tq = (tmp_procburst[(nproc-k/2) - 1 + k]+tmp_procburst[(nproc-k/2) + k]+tmp_procburst[nproc-1])/2;
                }
            } else {
                c++;
            }
        }
        
        //WaitingTime(proc_no, start, end);

    }
    
    private:
        int nproc;
        int* proc;
        int* procburst;
        int tq;
        
        void WaitingTime(vector<int> proc_no, vector<int> start, vector<int> end) {
            int wt[nproc];
            int avg_wt = 0;
            for (int i = 0; i < nproc; i++) { wt[i] = 0; }
            int first_att;
            int tmp;
            
            for (int i = 0; i < nproc; i++) {
                first_att = 0;
                for (int j = 0; j < proc_no.size(); j++) {
                    if (first_att == 0) {
                        if (proc_no.at(j) == i) {
                            wt[i] = wt[i] + start.at(j);
                            tmp = end.at(j);
                            first_att = 1;
                        }
                    } else {
                        if (proc_no.at(j) == i) {
                            wt[i] = wt[i] + (start.at(j) - tmp);
                            tmp = end.at(j);
                        }
                    }
                }
                avg_wt = avg_wt + wt[i];
                //cout << wt[i] << endl;
                if (i == nproc-1) { avg_wt = avg_wt/nproc; };
            }
            
            cout << "Average waiting time for RR is: " << avg_wt << endl;
            
            for (int i = 0; i < proc_no.size(); i++) {
                cout << start.at(i) << "  " << end.at(i) << "  " << proc_no.at(i) << endl;
            }
        }
};



int main()
{
    RoundRobin rr;
    rr.ProblemSetting();
    //rr.ClassicalRR();
    rr.AbdulrahimRR();
    //rr.MishraMODRR();
    //rr.MishraRR();
    //rr.NayakRR();
    return 0;
}