#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <windows.h>
#include "locale.h"
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

char to_upper(char ch)
{
    if (ch >= '�' && ch <= '�') {
        vector<pair<char, char>> big_and_small = { {'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},
            {'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},
            {'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},{'�', '�'},
        };
        for (auto par : big_and_small)
        {
            if (par.first == ch) {
                ch = par.second;
                return ch;
            }
        }
    }

    else
    return ch;
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int scores[3]{ 0,0,0 };
    string open_word = "�����";
    string close_word = "";
    string description = "���� � ������";

    //open file
    vector<string> file_contents = read_file("words.txt");
    srand(time(NULL));
    int end = file_contents.size();
    int index = 1;

    //specifying values
    if (end > 0) {
        while (index % 2) index = rand() % end;
        open_word = file_contents[index];
        description = file_contents[index + 1];
    }
    for (int i = 0; i < open_word.size(); i++) open_word[i] = to_upper(open_word[i]);
    for (int i = 0; i < open_word.size(); i++) close_word += '*';

    //start game
    int index_player = 0;
    while (close_word != open_word) {
        cout << endl << "--------------------------------------------------" << endl;
        On_Display(description, close_word, scores);
        system("pause");
        cout << endl << endl;
        int score_on_wheel = rotate_the_wheel();
        if (score_on_wheel == 0) {
            cout  << "��� ������ " << index_player + 1 << ".\t������ \"+\" �� ��������! " << endl;
        }
        else if (score_on_wheel == -1) {
            cout << "��� ������ " << index_player + 1 << ".\t������ \"0\" �� ��������! ��� ��������� � ���������� ������. " << endl;
        }
        else {
            cout << "��� ������ " << index_player + 1 << ".\t" << score_on_wheel << " ����� �� ��������! " << endl;
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
            cout << "�� ��������� ������� �����." << endl << endl;
            scores[index_player] += score_on_wheel * matching_letters;
        }
        else {
            cout << "����� ����� ���." << endl << endl;
            next_player(index_player);
        }

    }

   //Output
    cout << endl << "�����������, �� �������� �����: " << close_word << endl;
    cout << "����� " << index_player + 1 << " ���������� �� ������ " << scores[index_player] << " �����" << endl;

    cout << endl << "�����. " << endl;
    system("pause");
}


int rotate_the_wheel()
{
    //element(number) "0" = "+", element(number) "-1" = "skip"
    int drump[13] = { 100,120,140,160,180,200,220,240,260,280,300,0,-1 };

    int start = 0;
    int end = 12;
    int r_num = rand() % (end - start + 1) + start;

    return drump[r_num];
}

char enter_letter()
{
    char alfavit[33] = { '�', '�', '�', '�','�', '�', '�', '�', '�', '�', '�' ,'�', '�', '�', '�', '�', 
        '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�'};
    char letter;
    bool check_letter = true;
    while (check_letter) {
        cout << "������� �����: \t\t";
        cin >> letter;
        cin.ignore(32767, '\n');
        for (char el : alfavit) {
            if (to_upper(letter) == el) check_letter = false;
        }
    }
    return letter;
}

int enter_number_of_letter(int size)
{
    int index_letter;

    while (true) {
        cout << "����� �����: \t\t";
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
    letter = to_upper(letter);
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
    letter = to_upper(open_word[index]);

    for (int i = 0; i < open_word.size(); i++) {
        if (open_word[i] == letter) {
            close_word[i] = letter;
        }
    }
}

void On_Display(string description, string close_word, int* scores)
{
    cout << description << ":  " << close_word << "\n";
    cout << "������ �������: \t" << "����� 1\t\t" << "����� 2\t\t" << "����� 3\t\t" << endl;
    cout << "\t\t\t" << scores[0] << "\t\t" << scores[1] << "\t\t" << scores[2] << endl;
    cout << endl;
}

vector<string> read_file(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "������! ���� �� ������� ������� �� �������!" << endl << endl;
        return vector<string>();
    }

    vector<string> file_contents;
    string str;
    for (int i = 0; !file.eof(); i++) {
        getline(file, str);
        file_contents.push_back(str);
    }
    file.close();

    return file_contents;
}
