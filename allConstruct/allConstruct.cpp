// allConstruct.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include<unordered_map>
using namespace std;
// m=target.size
// n=string list size

vector<vector<string>> allConstruct(string target, vector<string>stringList) { //brute force 
    if (target == "") { return {{""}}; }
    vector<vector<string>> ans = {};
    for (int i = 0; i < stringList.size(); i++) {
        if (target.compare(0, 0 + stringList[i].size(), stringList[i]) == 0) {
            const string subString= target.substr(stringList[i].size(), target.size());
            vector<vector<string>> temp = allConstruct(subString, stringList);
            //filter empty array
            if (temp.size() > 0) {
                //insert the current stringList to all possible cases such as {def}->{abc,def}
                for (int j = 0; j < temp.size(); j++) {
                    if(temp[j][0]=="") {
                        temp[j][0] = stringList[i];
                    }
                    else
                    {
                        temp[j].insert(temp[j].begin(), stringList[i]);
                    }
                }
            }
            // combine all possible array into one single array
            ans.insert(ans.end(), temp.begin(), temp.end());
        }
    }
    return ans;
}

vector<vector<string>> allConstruct(string target, vector<string>stringList, unordered_map<string, vector<vector<string>>>& dptable) {
    if (target == "") { return { {""} }; }
    if (dptable.find(target) != dptable.end()) {
        return dptable[target];
    }
    vector<vector<string>> ans = {};
    for (int i = 0; i < stringList.size(); i++) {
        if (target.compare(0, 0 + stringList[i].size(), stringList[i]) == 0) {
            const string subString = target.substr(stringList[i].size(), target.size());
            vector<vector<string>> temp = allConstruct(subString, stringList,dptable);
            //filter empty array
            if (temp.size() > 0) {
                //insert the current stringList to all possible cases such as {def}->{abc,def}
                for (int j = 0; j < temp.size(); j++) {
                    if (temp[j][0] == "") {
                        temp[j][0] = stringList[i];
                    }
                    else
                    {
                        temp[j].insert(temp[j].begin(), stringList[i]);
                    }
                }
            }
            // combine all possible array into one single array
            ans.insert(ans.end(), temp.begin(), temp.end());
        }
    }
    dptable[target] = ans;
    return ans;
}

vector<vector<string>> allConstruct2(string target, vector<string>stringList) {
    if (target == "") { return { {""} }; }
    vector<vector<string>> ans = { {""} };
    vector<vector<string>> ansTemp = ans;
    for (int i = 0; i < stringList.size(); i++) {
        if (target.compare(0, 0 + stringList[i].size(), stringList[i]) == 0) {
            const string subString = target.substr(stringList[i].size(), target.size());
            vector<vector<string>> temp = allConstruct2(subString, stringList);
            if (temp[0][0] == "-1") {

            }
            else {
                //insert the current stringList to all possible cases such as {def}->{abc,def}
                for (int j = 0; j < temp.size(); j++) {
                    if (temp[j][0] == "") { //{{""}}->{{a}}
                        temp[j][0] = stringList[i];
                    }
                    else
                    { ////{{a}}->{{b,a}}
                        temp[j].insert(temp[j].begin(), stringList[i]);
                    }
                }
                //clean up the 2D array e.g {{""},{a,b,c,d}}->{{a,b,c,d}}
                if (ans[0][0] == "") {
                    ans.erase(ans.begin());
                }
                // combine all possible array into one single array
                ans.insert(ans.end(), temp.begin(), temp.end());
            }
        }
    }
    if (ansTemp == ans) {
        return { {"-1"} };
    }
    return ans;
}
vector<vector<string>> allConstructTabulation(string target, vector<string>stringList) {
    vector<vector<vector<string>>> dptable(target.size()+1);
    for (int i = 0; i < target.size(); i++) {
        if (dptable[i].empty() != true || i==0) {
            for (int j = 0; j < stringList.size(); j++) {
                if (stringList[j][0] == target[i]) {
                    vector<vector<string>> temp=dptable[i];
                    if (temp.empty()) {
                        temp.push_back({ stringList[j] });
                    }
                    else {
                        for (int k = 0; k < temp.size(); k++) {
                            temp[k].push_back(stringList[j]);
                        }
                    }
                    int index = i + stringList[j].size() ;
                    if (index < dptable.size()) {
                        dptable[index].insert(dptable[index].end(), temp.begin(), temp.end());
                    }
                }
            }
        }
    }
    return dptable[target.size()];
}

void print2DVector(vector<vector<string>> stringArray) {
    for (int i = 0; i < stringArray.size(); i++) {
        for (int j = 0; j < stringArray[i].size(); j++) {
            cout << stringArray[i][j] << ",";
        }
        cout << endl;
    }
}


int main()
{
    unordered_map<string, vector<vector<string>>> dptable;
    vector<string> combo = { "ab","abc","cd","def","abcd","ef","c"};
    vector<string> combo2 = { "bo","rd","ate","t","ska","sk","boar" };
    vector<string> combo3 = { "e","ee","eee","eeee","eeeee","eeeeee" };
    print2DVector(allConstruct("abcdef", combo,dptable));
   // print2DVector(allConstruct2("abcdef", combo));
    print2DVector(allConstructTabulation("abcdef", combo));
   /* cout << allConstruct("skateboard", combo2) << endl;
    cout << allConstruct("skateboard", combo2, dptable) << endl;*/
    //print2DVector(allConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", combo3, dptable));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
