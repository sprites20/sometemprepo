#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <regex>
#include <stdio.h>

#include <map>
#include <vector>

using namespace std;

template <typename T, typename Key>
bool key_exists(const T& container, const Key& key)
{
    return (container.find(key) != std::end(container));
}

template <typename T>
int count_args(const T& container){
	int count = 0;
	for (auto itr = container.begin(); itr != container.end(); ++itr){
			count++;
	}
	return count;
}

void write(string what){
	cout << what << endl;
}

vector<vector <string>> tokens;
vector<vector <string>> expr_accumulator;

int main(){
	cout << "Syntax Analyzer" << endl;
	
	map<string, map<string, string>> functions = {};
	functions["write"].insert(make_pair("text", "string"));
	
	//cout << count_args(functions["write"]) << endl;
	
	//cout << functions["write"].first << " " << functions["write"].second << endl;
	//cout << key_exists(functions, "write") << endl;
		
	string accumulator = "";
	string filename("test.txt");
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (getline(input_file, line)){
        lines.push_back(line);
    }
	
	int linecount = 0;
    for (const auto &i : lines){
    	char* char_arr;
	    string str_obj = i;
	    char_arr = &str_obj[0];
	    
	    //cout << char_arr << endl;
	    string curr_lexeme = "";
	    string curr_token = "";
	    
	    int q = 0;
	    while(char_arr[q] == ' '){
	    	q++;
		}
		while(char_arr[q] != ','){
			curr_token += char_arr[q];
			q++;
		}
		q++;
		
		while(char_arr[q] != '\0'){
			curr_lexeme += char_arr[q];
			q++;
		}
		
		vector <string> col;
		tokens.push_back(col);
		tokens.at(linecount).push_back(curr_token);
		tokens.at(linecount).push_back(curr_lexeme);
		
		//cout << tokens[linecount][0];
		//cout << ": " << tokens[linecount][1] << endl;
		
		cout << linecount << " " << tokens[linecount][0];
		cout << ": " << tokens[linecount][1] << endl;
        //cout << i << endl;
        
        linecount++;
	}
    vector<vector <string>> curr_func_args;
    
    
    for(int i = 0; i < linecount; i++){
    	string token = tokens[i][0];
    	string lexeme = tokens[i][1];
    	
    	//cout << i << " " << tokens[i][0];
	    //cout << ": " << tokens[i][1] << endl;
		
		if(token == "KEYWORD"){
			if(key_exists(functions, lexeme)){
				int arg_count = count_args(functions[lexeme]);
				cout << arg_count << endl;
				
				expr_accumulator = {};
				vector <int> accumulator_count = {};
				i++;
				int start = i;
				int end = 0;
				i++;
				
				int expr_accumulator_count = 0;
				
				while(tokens[i][0] != "RPAREN"){
					if(tokens[i][0] != "LPAREN"){
						vector <string> col;
						expr_accumulator.push_back(col);
						
						expr_accumulator.at(expr_accumulator_count).push_back(tokens[i][0]);
						expr_accumulator.at(expr_accumulator_count).push_back(tokens[i][1]);
						
						cout << expr_accumulator[expr_accumulator_count][0] 
							<< " " 
							<< expr_accumulator[expr_accumulator_count][1] 
							<< endl;
						
						expr_accumulator_count++;
						i++;
					}
				}
			}
		}
	}

    input_file.close();
    return EXIT_SUCCESS;
    
	return 0;
}

void parse_expr(){
	
}
