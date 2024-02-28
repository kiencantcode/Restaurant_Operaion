#include <iostream>
#include <regex>
#include <string>
using namespace std;

bool isValidName(string name) {
    // Define the regular expression for a valid name
    regex name_regex("^[A-Za-z]+(?:[\\s-][A-Za-z]+)*$");

    // Check if the name matches the regular expression and does not contain spaces
    if (regex_match(name, name_regex) && name.find(" ") == string::npos) {
        return true;
    } else {
        return false;
    }
}
int main() {
    string my_string = "AAAAAAaaasasafcwwedsd]]][[[]]]";
    if (isValidName(my_string)) {
        cout << my_string << " is a valid name." << endl;
    } else {
        cout << my_string << " is not a valid name." << endl;
    }
    return 0;
}