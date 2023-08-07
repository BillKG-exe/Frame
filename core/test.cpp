#include <iostream>
#include "Index.hpp"
#include "Series.hpp"
#include "DataFrame.hpp"
#include <vector>
#include <limits>
#include <cmath>


using namespace std;


void indexTests() {
    Index ind;

    ind.addLabel("A", 0);
    ind.addLabel("B", 1);
    ind.addLabel("C", 2);
    ind.addLabel("D", 3);
    ind.addLabel("E", 4);

    ind.display();
    cout << endl;

    ind.removeLabel("C");
    ind.display();
    cout << endl;

    ind.removeLabel("E");
    ind.display();
    cout << endl;

    vector<string> v = {"A", "D", "B", "N"};

    for(string s : v) {
        cout << s << " is @ " << ind.getPosition(s) << endl;
    }

    cout << endl;
    cout << "Index size is: " << ind.size() << endl;
}

void seriesTests() {
    Series s1;

    s1.setName("temperature");
    s1.append(25.0);
    s1.append(26.3);
    s1.append(32.6);
    s1.append(12.2);

    cout << "s1 name: " << s1.getName() << endl;

    for(int i = 0; i < s1.size(); i++) {
        cout << s1.get(i) << " ";
    }
    cout << endl;

    Series s2("volt");

    s2.append(1);
    s2.append(2);
    s2.append(4);
    s2.append(5);

    cout << "size before removing last element: " << s2.size() << endl; 
    cout << "Removed: " << s2.pop() << endl;
    cout << "after: " << s2.size() << endl;

    vector<double> v = {1.2, 2.2, 0.5, 1.1, NAN};

    Series s3("Intensity", v);

    cout << "Is last val missing? " << s3.isMissing(4) << endl;
    cout << "Is first val missing? " << s3.isMissing(0) << endl;

    s3.set(1, 0.55);

    vector<double> newV = s3.toVector();

    for(auto n : newV)  {
        cout << n << " ";
    }
    cout << endl;

}

void dataFrameTests() {
    DataFrame df;
    
    vector<double> i = {0.1, 0.5, 0.7, 1, 2.1};
    vector<double> v = {1, 2, 3, 0.1, 2.2};
    vector<double> p;

    for(int r = 0; r < i.size(); r++) {
        p.push_back(i[r] * v[r]);
    }

    Series intensity("Intensity", i), voltage("Voltage", v), power("Power", p);

    df.addColumn(intensity.getName(), intensity);
    df.addColumn(voltage.getName(), voltage);
    df.addColumn(power.getName(), power);

    df.display();
    cout << "This is a " << df.rowSize() << " by " << df.colSize() << " matrix\n";
    cout << endl;

    vector<double> d = {4, 4, 16};
    df.addRow(d);
    df.display(6);
    cout << "This is now a " << df.rowSize() << " by " << df.colSize() << " matrix\n";
    cout << endl;

    cout << "@(1, 1) -> " << df.get(1, 1) << endl;
    df.set(1,1, 20);
    cout << "@(1, 1) -> " << df.get(1, 1) << endl; 
    df.display(3);
    cout << endl;
    
    Index ind;

    vector<string> vs = {"Test 1", "Test 2", "Test 3", "Test 4", "Test 5", "Test 6"};
    vector<size_t> vt = {1, 2, 3, 4, 5, 6};

    for(int i = 0; i < vs.size(); i++) {
        ind.addLabel(vs[i], vt[i]);
    }

    df.setIndex(ind);
    df.getIndex().display();
    cout << endl << endl;

    DataFrame df2;

    df2.read_csv("test.csv");
    df2.display();
    cout << "\n\n";

    Series s = df2.getColumn("Power");

    for(int i = 0; i < s.size(); i++) {
        cout << s.get(i) << " ";
    }
    cout << "\n\n";


    df2.dropColumn("Voltage");
    df2.display();
    cout << "\n\n";

    df2.dropColumn("Power");
    df2.display();
    cout << "\n\n";

    voltage.append(4);
    df2.addColumn("A", voltage);
    power.append(5);
    df2.addColumn("B", power);
    df2.display(6);
    cout << "\n\n";

    df2.dropRow();
    df2.display();
    cout << "\n\n";

    df2.dropRow();
    df2.display();
    cout << "\n\n";

    vector<double> res = df2.getRow(1);

    for(auto d : res) cout << d << " ";
    cout << endl << endl;
}


void seriesOpsTest() {
    vector<double> v = {1,2,3,4,5,6,7,8};
    Series s1("Name", v);

    s1 + 1;

    cout << "Adding 1 to series s1: ";
    for(int i = 0; i < s1.size(); i++) {
        cout << s1.get(i) << " ";
    }
    cout << endl << endl;

    s1 = s1 + 1;

    cout << "Adding 1 again to series s1: ";
    for(int i = 0; i < s1.size(); i++) {
        cout << s1.get(i) << " ";
    }
    cout << endl << endl;

    Series s2 = s1 * 2.1;

    cout << "Multiplying s1 with 2.1 into s2: ";
    for(int i = 0; i < s2.size(); i++) {
        cout << s2.get(i) << " ";
    }
    cout << endl << endl;
/* 
    s1 = s1 - 3;

    cout << "s1: ";
    for(int i = 0; i < s1.size(); i++) {
        cout << s1.get(i) << " ";
    }
    cout << endl << endl; */

    s2 = s2 - s1;

    cout << "Substracting s1 from s2: ";
    for(int i = 0; i < s2.size(); i++) {
        cout << s2.get(i) << " ";
    }
    cout << endl << endl;  

    s2 = s2 + s1;

    cout << "Adding s1 back into s2: ";
    for(int i = 0; i < s2.size(); i++) {
        cout << s2.get(i) << " ";
    }
    cout << endl << endl;  

    Series s3("B", v);

    s3 = s3 + 2;
    s3 = s3 / s1;

    cout << "Dividing s3 by s1: ";
    for(int i = 0; i < s3.size(); i++) {
        cout << s3.get(i) << " ";
    }
    cout << endl << endl;  
}

int main() {
    seriesTests();
    return 0;
}