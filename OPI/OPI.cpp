#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


int rotate_the_wheel();
char enter_letter();
int enter_number_of_letter(int size);
int open_letter(char letter, string& close_word, string open_word);
void open_any_letter(int index, string& close_word, string open_word);
void On_Display(string description, string close_word, int* scores);
vector<string> read_file(string filename);


void next_player(int& index_player) {
    if (index_player < 2) index_player++;
    else index_player = 0;
}


int main()
{
    int scores[3]{ 0,0,0 };
    string open_word = "Vitim";
    string close_word = "";
    string description = "River in siberia";

    //open file
    vector<string> file_contents = read_file("words.txt");
    srand(time(NULL));
    int end = file_contents.size();
    int index = 1;

    //specifying values
    if (end > 0){
        while (index % 2) index = rand() % end;
        open_word = file_contents[index];
        description = file_contents[index + 1];
    }
    for (int i = 0; i < open_word.size(); i++) open_word[i] = toupper(open_word[i]);
    for (int i = 0; i < open_word.size(); i++) close_word += '_';

    //start game
    int index_player = 0;
    while (close_word != open_word) {
        On_Display(description, close_word, scores);
        system("pause");

        int score_on_wheel = rotate_the_wheel();
        if (score_on_wheel == 0) {
            cout << index_player+1 << "st player's turn\t" << "On the wheel\t" << "+" << endl;
        }
        else if (score_on_wheel == -1) {
            cout << index_player + 1 << "st player's turn\t" << "On the wheel\t" << "Skip a turn" << endl;
        }
        else {
            cout << index_player + 1 << "st player's turn\t" << "On the wheel\t" << score_on_wheel << endl;
        }

        //Sector plus
        if (score_on_wheel == 0) {
            int index_letter = enter_number_of_letter(open_word.size());
            open_any_letter(index_letter, close_word, open_word);
            continue;
        }

        //Skip a turn
        if (score_on_wheel == -1) {
            next_player(index_player);
            continue;
        }

        //Check letter
        char letter = enter_letter();
        int matching_letters = open_letter(letter, close_word, open_word);
        if (matching_letters) {
            cout << "There is such a letter." << endl << endl;
            scores[index_player] += score_on_wheel * matching_letters;
        }
        else {
            cout << "There is not such a letter." << endl << endl;
            next_player(index_player);
        }

    }


    //Output
    cout << endl << "Word: " << close_word << endl;
    cout << index_player + 1 << "st player wins with " << scores[index_player] << " points" << endl;

    cout << endl << "The end." << endl;
    system("pause");
}


int rotate_the_wheel()
{
    //element(number) "0" = "+", element(number) "-1" = "skip"
    int drump[13] = { 100,120,140,160,180,200,220,240,260,280,300,0,-1};

    int start = 0;
    int end = 12;
    int r_num = rand() % (end - start + 1) + start;

    return drump[r_num];
}

char enter_letter()
{
    char alfavit[26] = { 'A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char letter;
    bool check_letter = true;
    while (check_letter) {
        cout << "Enter letter: \t\t";
        cin >> letter;
        for (char el : alfavit) {
            if (toupper(letter) == el) check_letter = false;
        }
    }
    return letter;
}

int enter_number_of_letter(int size)
{
    int index_letter;

    while (true) {
        cout << "Number of letter: \t\t";
        cin >> index_letter;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        index_letter -= 1;
        if (size > index_letter && index_letter >= 0) break;
    }

    return index_letter;
}

int open_letter(char letter, string& close_word, string open_word)
{
    int matching_letters = 0;
    letter = toupper(letter);

    for (int i = 0; i < open_word.size(); i++) {
        if (open_word[i] == letter) {
            if (letter != close_word[i]) {
                close_word[i] = letter;
                matching_letters += 1;
            }
        }
    }

    return matching_letters;
}

void open_any_letter(int index, string& close_word, string open_word)
{
    char letter;
    letter = toupper(open_word[index]);
    
    for (int i = 0; i < open_word.size(); i++) {
        if (open_word[i] == letter) {
            close_word[i] = letter;
        }
    }
}

void On_Display(string description, string close_word, int* scores)
{
    cout << description << ":  " << close_word << "\n";
    cout << "Balance players: \t" << "1 player\t" << "2 player\t" << "3 player\t" << endl;
    cout << "\t\t\t" << scores[0] << "\t\t" << scores[1] << "\t\t" << scores[2] << endl;
    cout << endl;
}

vector<string> read_file(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error! The file with words could not be opened" << endl << endl;
        return vector<string>();
    }

    vector<string> file_contents;
    string str;
    for (int i = 0; !file.eof(); i++) {
        getline(file,str);
        file_contents.push_back(str);
    }
    file.close();

    return file_contents;
}
