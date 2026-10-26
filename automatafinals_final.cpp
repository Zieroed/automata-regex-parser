#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>

#define banner "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
#define star "\n  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
#define space "\n\n"
const int width = 69;

using namespace std;

//Regex for tokenization
regex r_keywords("^(if|else|switch|case|default|for|while|do|break|continue|int|float|double|char|bool|void|short|long|signed|unsigned|const|volatile|mutable|public|private|protected|class|struct|union|enum|this|friend|virtual|new|delete|try|catch|throw|namespace|using|extern|static|sizeof|typeid|dynamic_cast|reinterpret_cast|static_cast|const_cast|return|goto|inline|typedef|template|nullptr|true|false|asm|explicit|export)$");
regex r_identifier("^[a-zA-Z][a-zA-Z0-9_]*$");
regex r_integer("^\\-*[0-9]+$");
regex r_string("\\'.*\\'");
regex r_float(R"(^[0-9]+\.[0-9]+$)");

//Regex for Parsing
regex r_assignment("[a-zA-Z][a-zA-Z0-9_]*\\s+=\\s+([a-zA-Z][a-zA-Z0-9_]*|\\-*\\d+|\\-*[0-9]+.[0-9]+)");
regex r_assignment_error("[a-zA-Z][a-zA-Z0-9_]*\\s+=\\s+.*");
regex r_operation("[a-zA-Z][a-zA-Z0-9_]*\\s+=\\s+([a-zA-Z][a-zA-Z0-9_]*|[0-9]+|[0-9]+.[0-9]+)(\\s+[+-/*]\\s+([a-zA-Z][a-zA-Z0-9_]*|[0-9]+|[0-9]+.[0-9]+))+");

//Token functions utilizing the regex_match member function that compares the user input with the regex assigned above and returns true or false on whether they match.
bool is_keyword (const string& token);
bool is_identifier(const string& token);
bool is_assignment(const string& token);
bool is_integer(const string& token);
bool is_float(const string& token);
bool is_string(const string& token);
bool is_operator(const string& token);
bool is_relational(const string& token);
bool is_logical(const string& token);

//Tokenization
void tokenization(const string& user_input, vector<pair<string, string>>& tokens);

//Parsing
bool regex_parsing(const string& user_input, const vector<pair<string, string>>& tokens);

//Functions for the vector tokens, if it exists, getting the first or the second value of the pair
bool token_exists(const vector<pair<string,string>>& tokens, const string& key);
int key_count(const vector<pair<string,string>>& tokens, const string& key);
string get_token_string(const vector<pair<string,string>>& tokens, const string& key);
string get_token_string(const vector<pair<string,string>>& tokens, const string& key, const int& index);
int get_token_int(const vector<pair<string,string>>& tokens, const string& key);
int get_token_int(const vector<pair<string,string>>& tokens, const string& key, const int& index);

//Functions for operating on the expressions. Basic operations and operations involving saved variables from pervious prompts
int arithmeticOperation(const vector<pair<string, string>>& tokens);
int variableOperation(const vector<pair<string, string>>& tokens);
bool missingvar; 

//Stores variables that the user defines
unordered_map<string, int> variables; //Stores variables that the user defines

//For Displaying each variable stored
void displayVariables();

//Iomanip functions for user interface
void header();
void center(const string& text);

//Main program
int main(){
    string user_input, exit, choice;
    
    cout << space;
    center("  Note: This program only supports");
    cout << endl;
    center("basic single-line variable operations.");
    cout << space;
    cout << endl;
    center("Instructions: Input basic *single-line* assignments or");
    cout << endl;
    center("arithmetic equations only (e.g., x = 5, y = x + 3).");
    
    while(true){
    cout << space << setw(37) << "Equation: ";
    getline(cin, user_input);
    
    vector <pair<string,string>> tokens;
    
    tokenization(user_input, tokens);
    
    
    if(regex_parsing(user_input, tokens) && !missingvar){
        displayVariables();
    }
    
    tokens.clear();
    missingvar = false;
    
    while (true){
	    	cout << endl;
	    	center("Do you want to continue? (Y/N): ");
	    	getline(cin, choice);
	    	
	    	if (choice == "Y" || choice == "y"){
	    		break;
			}else if (choice == "N" || choice == "n"){
				cout << endl << banner << space;
		        center("Thank you!\n\n");
		        
				return 0;
			}else{
				cout << endl;
				center("Invalid Input. Enter Y to continue or N to exit.\n");
				cout << endl << banner << endl;
			}
		}
		cout << star << endl;
    }
    return 0;
    
}
    
//Token functions utilizing the regex_match member function that compares the user input with the regex assigned above and returns true or false on whether they match.
bool is_keyword(const string& token){
    return regex_match(token, r_keywords);
}

bool is_identifier(const string& token){
    return regex_match(token, r_identifier);
}

bool is_assignment(const string& token){
    return token == "=";
}

bool is_integer(const string& token){
    return regex_match(token, r_integer);
}

bool is_float(const string& token){
    return regex_match(token, r_float);
}

bool is_string(const string& token){
    return regex_match(token, r_string);
}

bool is_operator(const string& token){
    return token == "+" || token == "-" || token == "/" || token == "*";
}

bool is_relational(const string& token){
    return token == "==" || token == "!=" || token == ">" || token == "<" || token == "<=" || token == ">=";
}

bool is_logical(const string& token){
    return token == "&&" || token == "||" || token == "!";
}

//Tokenization
void tokenization(const string& user_input, vector<pair<string, string>>& tokens){
    stringstream ss(user_input);
    string token;
    
    header();
    cout << space;
    center(user_input);
    cout << space;
    
    while ((ss >> token)){
        if (is_keyword(token)){
            tokens.emplace_back("Keyword", token);
            cout << setw(20) << "Keyword" << setw(35) << token << endl;
        }
        else if (is_identifier(token)){
            tokens.emplace_back("Identifier", token);
            cout << setw(20) << " Identifier" << setw(35) << token << endl;
        }
        else if (is_assignment(token)){
            tokens.emplace_back("Assignment", token);
            cout << setw(20)<< "Assignment" << setw(35) << token<< endl;
        }
        else if (is_integer(token)){
            tokens.emplace_back("Integer", token);
            cout << setw(20)<< "Integer" << setw(35) << token<< endl;
        }
        else if (is_float(token)){
            tokens.emplace_back("Float", token);
            cout << setw(20) << "Floating-point Number"  << setw(35) << token<< endl;
        }
        else if (is_operator(token)){
            tokens.emplace_back("Operator", token);
            cout << setw(20) << "Operator"  << setw(35) << token << endl;
        }
        else if (is_relational(token)){
            tokens.emplace_back("Relational", token);
            cout << setw(20) << " Relational Operator"  << setw(35) << token << endl;
        }
        else if (is_logical(token)){
            tokens.emplace_back("Logical", token);
            cout << setw(20) << " Logical Operator"  << setw(35) << token << endl;
        }
        else if (is_string(token)){
            tokens.emplace_back("String", token);
            cout << setw(20) << " String"  << setw(35) << token << endl;
        }
        else {
            tokens.emplace_back("Unknown", token);
            cout << setw(20) << " Unknown"  << setw(35) << token << endl;
        }
        
    }
    
    cout << endl;
}

//Parsing
bool regex_parsing(const string& user_input, const vector<pair<string, string>>& tokens){
    cout << banner << endl << setw(25) << "Regex Parsing: ";
    if (token_exists(tokens, "Float")){ //Goes out of scope if floating-point number is read
        center("Out of Scope with floating-point number");
        cout << endl << banner << endl;
        return false;
    }
    else if (token_exists(tokens, "Unknown")){ //Goes out of scope if an unknown number is read
        cout << setw(25) << "Out of Scope with unknown token.";
        cout << endl << banner << endl;
        return false;
    }
    else if(regex_match(user_input, r_assignment)){ //Matches input with assignment regex
        cout << setw(35) << "Assignment Statement" << endl;
        if (tokens.size() == 3 && key_count(tokens, "Identifier") == 1 && key_count(tokens, "Assignment") == 1 && (key_count(tokens, "Integer") == 1)){ //Scope is to assign a variable that only uses pattern (variable = integer)
            variables.insert_or_assign(get_token_string(tokens, "Identifier"), (get_token_int(tokens, "Integer"))); //Inserts or Updates the value to variables
        
            return true;
        }
        else center("Out of Scope Assignment Statement");
        cout << endl << banner << endl;
        return false;
    }
    else if(regex_match(user_input, r_operation)){ //Matches input with arithmetic operation regex
        cout << setw(35) << "Arithmetic Operation" << endl;
        if (tokens.size() == 5 && key_count(tokens, "Integer") == 2){ //Scope is limited to [variable] [=] [integer] [operator] [integer]
            int result = arithmeticOperation(tokens);
            if (!missingvar) { //If variable is not missing, insert or add new variable to variables
                variables.insert_or_assign(get_token_string(tokens, "Identifier"), result);
                return true;
            };
            return false;
        }
        else if (tokens.size() == 5 && key_count(tokens, "Identifier") >= 2){
            int result = variableOperation(tokens);
            if (!missingvar) { //If variable is not missing, insert or add new variable to variables
                variables.insert_or_assign(get_token_string(tokens, "Identifier"), result);
                return true;
            };
            return false;
        }
        else {
            cout << banner << endl;
            center("Could not compute. Out of scope Arithmetic Operation.");
            cout << "\n" << banner << endl;
        }
        return false;
    }
    else if(regex_match(user_input, r_assignment_error)){ //Matches input with assignment error regex (variable = [anything]*)
       center("Out of Scope Assignment Statement");
       cout << endl << banner << endl;
       return false;
    }
    else {
        cout << setw(36) << "Invalid Statement" << endl << banner << endl;
        return false;        
    }
    cout << endl << banner << endl;
    return false;
}   

//Functions for the vector tokens, if it exists, getting the first or the second value of the pair
bool token_exists(const vector<pair<string,string>>& tokens, const string& key){
    for (const auto& token : tokens){
        if (token.first == key){
            return true;
        }
    }
    return false;
}

int key_count(const vector<pair<string,string>>& tokens, const string& key){
    int count = 0;
    for (const auto& token : tokens){
        if (token.first == key){
            count++;
        }
    }
    return count;
}

string get_token_string(const vector<pair<string,string>>& tokens, const string& key){
    for (const auto& token : tokens){
        if (token.first == key){
            return token.second;
        }
    }
    return "";
}

string get_token_string(const vector<pair<string,string>>& tokens, const string& key, const int& index){
    int i = 0;
    for (const auto& token : tokens){
        if (token.first == key && i == index){
            return token.second;
        }
        i++;
    }
    return "";
}

int get_token_int(const vector<pair<string,string>>& tokens, const string& key){
    for (const auto& token : tokens){
        if (token.first == key){
            return stoi(token.second);
        }
    }
    return 0;
}

int get_token_int(const vector<pair<string,string>>& tokens, const string& key, const int& index){
    int i = 0;
    for (const auto& token : tokens){
        if (token.first == key && i == index){
            return stoi(token.second);
        }
        i++;
    }
    return 0;
}

//Functions for operating on the expressions. Basic operations and operations involving saved variables from pervious prompts
int arithmeticOperation(const vector<pair<string, string>>& tokens){
    string op = get_token_string(tokens, "Operator");
    int var1 = get_token_int(tokens, "Integer", 2);
    int var2 = get_token_int(tokens, "Integer", 4);
    if (op == "+") return var1 + var2;
    else if (op == "-") return var1 - var2; 
    else if (op == "/") {
        if (var2 == 0){
            cout << setw(50) << "Error. Division by zero." << endl;
            missingvar = true;
            return 0;
        }
        return var1 / var2;
    }
    else if (op == "*") return var1 * var2;
    else return -1;
}

string get_token_key(const vector<pair<string, string>>& tokens, const int& index){
    int i = 0;
    for (const auto& token : tokens){
        if (index == i){
            return token.first;
        }
        i++;
    }
    return "";
}

int get_variable_value(const vector<pair<string, string>>& tokens, const int& index){
    string var = get_token_string(tokens, "Identifier", index); //Returns token value as string
    auto iter = variables.find(var); //Returns string if found, returns variables.end() when not
    if (iter != variables.end()){
        return iter->second;
    }
    else{
        cout << setw(33) << "!Variable " << var << " was not found!\n" << banner << endl;
        missingvar = true;
        return 0;
    }
    return 0;
}

int variableOperation(const vector<pair<string, string>>& tokens){
    string op = get_token_string(tokens, "Operator");
    int var1 = 0;
    int var2 = 0;

    if (get_token_key(tokens, 2) == "Identifier" && get_token_key(tokens, 4) == "Integer"){ //Checks if 3rd token is an identifier and 5th token is integer (y + 1)
        var1 = get_variable_value(tokens, 2);
        var2 = get_token_int(tokens, "Integer", 4);
    }
    else if (get_token_key(tokens, 2) == "Integer" && get_token_key(tokens, 4) == "Identifier"){ //Checks if 5th token is an identifier and 3rd token is identifier (1 + y)
        var1 = get_token_int(tokens, "Integer", 2);
        var2 = get_variable_value(tokens, 4);
    }
    else if (get_token_key(tokens, 2) == "Identifier" && get_token_key(tokens, 4) == "Identifier"){ //Checks if both 3rd and 5th tokens are identifiers (y + z)
        var1 = get_variable_value(tokens, 2);
        var2 = get_variable_value(tokens, 4);
    }
    else cout << "Invalid Variable Operation" << endl;
    if (missingvar) return 0;
    if (op == "+") return var1 + var2;
    else if (op == "-") return var1 - var2; 
    else if (op == "/") {
        if (var2 == 0){
            cout << setw(50) << "Error. Division by zero." << endl;
            missingvar = true;
            return 0;
        }
        return var1 / var2;
    }
    else if (op == "*") return var1 * var2;
    else return 0;
}

//Displaying each variable stored
void displayVariables(){
    int counter = 0;
    cout << banner << endl << setw(29) << "Output of Expression: ";
    
    for (const auto& v : variables){
        if(counter == 0){
            cout << setw(25) << v.first << " = " << v.second << endl;    
        } else if(counter == 1){
            cout << endl << setw(29) << "Stored Variables: ";
            cout << setw(25) << v.first << " = " << v.second << endl;
        } else {
            cout << setw(54) << v.first << " = " << v.second << endl;
        }
        counter++;
    }

    cout << banner << endl;
}

//Iomanip functions for User Interface
void center(const string& text){
    int length = text.length();
    int spaces = (width - length) / 2;
    
    if (spaces < 0){
        spaces = 0;
    }
    
    for (int i = 0; i < spaces; ++i){
        cout << " ";
    }
    
    cout << text;
}

void header(){
    cout << "\n" << banner << "\n" << banner << space;
    center(" NON-DETERMINISTIC CREW");
    cout << space << banner << "\n" << banner;
}
