#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

class Timer
{
    // make things readable
    using clk = std::chrono::steady_clock;

    clk::time_point b; // begin
    clk::time_point e; // end

public:
    void clear() { b = e = clk::now(); }
    void start() { b = clk::now(); }
    void stop() { e = clk::now(); }

    friend std::ostream& operator<<(std::ostream& o, const Timer& timer)
    {
        return o << timer.secs();
    }

    // return time difference in seconds
    double secs() const
    {
        if(e <= b)
            return 0.0;
        auto d = std::chrono::duration_cast<std::chrono::microseconds>(e - b);
        return d.count() / 1000000.0;
    }
};

vector<int> operator+(vector<int> v1, vector<int> v2){
    int vlen = v1.size();
    vector<int> v(vlen);
    for(int i=0; i<vlen; i++){
        v[i] = v1[i] + v2[i];
    }
    return v;
}

vector<int> multiplication(vector<int> v1, vector<int> v2){
    int vlen = 2 * v1.size() - 1;
    int vlen_old = v1.size();

    vector<int> v(vlen);
    for(int i=0; i<vlen_old; i++){
        for(int j=0; j<vlen_old; j++){
            v[i+j] += v1[i] * v2[j]; 
        }
    }

    return v;
}

vector<int> KA(vector<int> v1, vector<int> v2){

    int N = max(v1.size(), v2.size());
    vector<int> v_result(2*N-1, 0);

    if(N == 1){
        v_result[0] = v1[0] * v2[0]; 
        return v_result;
    }

    const vector<int> v12(v1.begin(), v1.begin()+N/2);
    const vector<int> v22(v2.begin(), v2.begin()+N/2);
    const vector<int> v11(v1.begin()+N/2, v1.begin()+N);
    const vector<int> v21(v2.begin()+N/2, v2.begin()+N);
    
    const vector<int> &D0 = KA(v12, v22);
    const vector<int> &D1 = KA(v11, v21);
    const vector<int> &D01 = KA(v11+v12, v21+v22);

    for(int i=0; i<N-1; i++){
        v_result[i] += D0[i];
        v_result[i+N] += D1[i];
        v_result[i+(N/2)] += D01[i] - D0[i] - D1[i]; 
    }

    return v_result;    
}

int main(){
    int n = 65536;
    vector<int> v1(n,1), v2(n,1);

    /*for(int i=0; i<n; i++){
        v1[i] = 1;
        v2[i] = 2;
    }*/
    
    Timer t1;
    Timer t2;

    t2.start();
    vector<int> v_old = multiplication(v1, v2);
    t2.stop();

    t1.start();
    vector<int> v = KA(v1, v2);
    t1.stop();

    /*for(int i=0; i<2*n-1; i++){
        cout << v[i] << endl;
    }*/

    cout << "t1:" << t1 << "," 
         << "t2:" << t2 << "," 
         << "t1/t2:" << t1.secs()/t2.secs() << endl;

    return 0;

}
