/* Given a set functional dependencies of the type a->b, find the closure of a */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

/* Function prototype */
void find_closure(multimap<string, string> , int , string );
void remove_duplicate_attirbutes_in_closure(vector<string>, string);
void display_closure(vector<string>, string );

/* Begining of the main method */
int main(int argc, char* argv[]) {

    /* Declarations */
    int no_of_dependencies;
    multimap<string, string> dependencies;
    string LHS, RHS, attribute, dummy;

    /* Get the input */
    cout << "\nNumber of dependencies : ";
    cin >> no_of_dependencies;

    cout << "\nEnter the dependencies\n";
    for (int i = 0; i < no_of_dependencies; i++ ) {
        cin >> LHS >> dummy >> RHS;
        //dependencies[LHS] = RHS;
        dependencies.insert(std::pair<string, string>(LHS, RHS));
    }

    cout << "\nEnter the attribute who's closure needs to be found : ";
    cin >> attribute;

    /* Function call  */
    find_closure(dependencies, no_of_dependencies, attribute);

    cout << endl;

    return 0;
}

/* Function definitions */
/* Function to find the closure of a user-entered attribute */
void find_closure(multimap<string, string> dep, int no_dep, string attr) {

    int i;
    multimap<string, string> :: iterator it;
    vector<string> v;

    /* Checking for direct(full/partial) dependencies */
    for (it = dep.begin(); it != dep.end(); it++) {
        if ((it->first).find(attr) != std::string::npos) {
            v.push_back(it->second);
        }
    }

    /* Loop to check for transitive dependencies */
    for (it = dep.begin(); it != dep.end(); ++it) {
        for (int i = 0; i < v.size(); i++) {
            if ( (it->first).find(v[i])  != std::string::npos ) {
                v.push_back(it->second);
            }
        }
    }

    /* Remove any duplicate attributes in the closure */
    remove_duplicate_attirbutes_in_closure(v, attr);
}

/* Function to remove duplicate elements in a vector */
void remove_duplicate_attirbutes_in_closure(vector<string> v, string attr) {

    // Code Courtesy : http://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    // Display the final closure vector
    display_closure(v, attr);

}

/* Function to display the content of the closure vector */
void display_closure(vector<string> v, string attr) {
    cout << "\nClosure of "<< attr << " = {";
    for (int i = 0; i < v.size(); i++) {
        cout <<" " << v[i];
    }
    cout << " } " <<endl;
}