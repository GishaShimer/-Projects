﻿/*Створіть консольну версію гри «Шибениця».

Правила гри можна переглянути за цим посиланням.

Важливо:

■ Слово вибирається комп'ютером зі списку слів.

■ Список слів знаходиться у файлі у зашифрованому вигляді.

■ Після завершення гри на екран відображається статистика гри:

• кількість часу;

• кількість спроб;

• потрібне слово;

• літери гравця. */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>


using namespace std;

class Shibenica {
private:
    vector<string> words;//вектор зі словами
    string secretWord;//загадуване слово

    string guessedWord;//поточний стан відгадуваного слова
    const int maxAttempts = 6;
    int attemptsLeft;
    int attemptsWasted;
    time_t startTime;
    vector<char> guessedLetters;

public:
    Shibenica() {

        attemptsLeft = maxAttempts;//записуємо кількість решти спроб
        attemptsWasted = 0;
        load("words.txt", 3); // зсув на 3 позиції таке собі шифрування
        srand(time(nullptr));
        secretWord = getRandomWord();
        guessedWord = string(secretWord.length(), '_');// місце замість ще не вгаданих букв
    }

    void load(const string& filename, int shift) {
        ifstream file(filename);
        if (file.is_open()) {
            string word;
            while (file >> word) {//читання до кінця
                words.push_back(decrypt(word, shift));// Додавання розшифрованого слово до вектора

            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file " << filename << "\n";//помилка при невідкритті файла
        }
    }


    string getRandomWord(int difficulty) const {
        vector<string> filteredWords;//новий вектор для сегрегованих слів
        for (int i = 0; i < words.size(); ++i) {
            const string& word = words[i];
            if ((difficulty == 1 && word.length() == 4) ||//1 якшщо 4
                (difficulty == 2 && (word.length() == 5 || word.length() == 6)) ||//2 якщо 5 або 6
                (difficulty == 3 && word.length() > 6)) {//3 якщо більше 6
                filteredWords.push_back(word);//записуємо в кінець вектора
            }
        }
        int randInd = rand() % filteredWords.size();//рандомний індекс в межах вектора

        return filteredWords[randInd];//повертаємо відфільтрований вектор с рандомним індексом
    }

    ////////////////////////////////////////
    string getRandomWord() const {
        int randInd = rand() % words.size();//вибір рандомного індексу по вектору words
        return words[randInd];
    }

    void const Show() {
        cout << "Secret word: " << guessedWord << "\n";
    }

    bool const isWordGuessed() {
        return secretWord == guessedWord;
    }

    bool const isGameOver() {
        return attemptsLeft <= 0 || isWordGuessed();
    }

    void guessLetter(char letter) {
        bool found = false;
        for (int i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == letter) {
                guessedWord[i] = letter;
                found = true;
            }
        }
        if (!found) {
            --attemptsLeft;
            ++attemptsWasted;
            cout << "Incorrect guess, attempts left: " << attemptsLeft << "\n";
        }
    }
    ////////////////////////////////////////візуал шибениці початок 
    void man() {
        if (attemptsLeft == 6) {
            cout << "_____\n";
            cout << "|\n";
            cout << "|\n";
            cout << "|\n";
        }
        else if (attemptsLeft == 5) {
            cout << "_____\n";
            cout << "| " << " 0\n";
            cout << "|\n";
            cout << "|\n";
        }
        else if (attemptsLeft == 4) {
            cout << "_____\n";
            cout << "| " << " 0\n";
            cout << "| " << " |\n";
            cout << "|\n";
        }
        else if (attemptsLeft == 3) {
            cout << "_____\n";
            cout << "| " << " 0\n";
            cout << "| " << "/|\n";
            cout << "|\n";
        }
        else if (attemptsLeft == 2) {
            cout << "_____\n";
            cout << "| " << " 0\n";
            cout << "| " << "/|)\n";
            cout << "|\n";
        }
        else if (attemptsLeft == 1) {
            cout << "_____\n";
            cout << "| " << " 0\n";
            cout << "| " << "/|)\n";
            cout << "| " << "|\n";
        }
        else if (attemptsLeft == 0) {
            cout << "_____\n";
            cout << "| " << " 0\n";
            cout << "| " << "/|)\n";
            cout << "| " << "| |" << "\n";
        }
    }
    ////////////////////////////////////////візуал шибениці кінець


    void Description(const string& word) {//опис слів, приймає поточне рандомно вибране слово

        if (word == "char") {
            cout << "\nText data type\n";
        }
        else if (word == "bool") {
            cout << "\nCan be true or false\n";
        }
        else if (word == "void") {
            cout << "\nNothing but also a data type\n";
        }
        else if (word == "string") {
            cout << "\nSame to char but better\n";
        }
        else if (word == "float") {
            cout << "\nHas post-coma numbers\n";
        }
        else if (word == "short") {
            cout << "\nA data type that is almost never used\n";
        }
        else if (word == "vector") {
            cout << "\nA container data structure that stores elements\n";
        }
        else if (word == "pointer") {
            cout << "\nVariable that save the memory address of another variable\n";
        }
        else if (word == "function") {
            cout << "\nBlock of code\n";
        }


    }
    void addGuessedLetter(char letter) {//функція для відстеження кожної введеной букві користувачем
        guessedLetters.push_back(letter);//додавання її в кінець вектора
    }

    void guessWord() {
        string guessed;
        cout << "Guess the word: ";
        cin >> guessed;
        if (guessed == secretWord) {
            guessedWord = secretWord;
        }
        else {
            cout << "Incorrect guess.\n";
        }
    }


    ////////////////////////////////////////гра початок
    void play(int difficulty) {
        cout << "Welcome to the game!\n";
        cout << "This words present different data types(no for hard difficulty)\n\n";

        while (1) {
            secretWord = getRandomWord(difficulty); // Вибір слова залежно від складності
            attemptsLeft = maxAttempts;
            guessedWord = string(secretWord.length(), '_');
            startTime = time(nullptr);
            Show();
            Description(secretWord);
            while (!isGameOver()) {
                cout << "Guess a letter or enter 's' to guess the word: ";
                char guess;
                cin >> guess;
                if (guess == 's') {
                    guessWord();
                    break;
                }
                else {
                    guessLetter(guess);
                    addGuessedLetter(guess);
                    Show();
                    man();
                    if (isGameOver()) {
                        break;
                    }
                }
            }
            if (isWordGuessed()) {
                cout << "\nCongratulations! You guessed the word: " << secretWord << "\n\n";
            }
            else {
                cout << "\nGame over, the word was: " << secretWord << "\n\n";
            }
            cout << "Guessed letters: ";
            for (int i = 0; i < guessedLetters.size(); ++i) {
                cout << guessedLetters[i] << " ";
            }

            time_t endTime = time(nullptr);
            long long timeTaken = difftime(endTime, startTime);
            cout << "Time taken: " << timeTaken << " seconds\n";
            cout << "Amount of mistakes: " << attemptsWasted << "\n";
            attemptsWasted = 0;
            guessedLetters.clear();

            break;
        }
    }


    ////////////////////////////////////////гра кінець
    string encrypt(const string& input, int shift) {
        string result = input;
        for (int i = 0; i < result.length(); ++i) {
            char& c = result[i];
            if (isalpha(c)) {
                char base;
                if (isupper(c)) {
                    base = 'A';//зміна якщо велика літера 
                }
                else {
                    base = 'a';//зміна якщо маленька літера 
                }

                c = ((c - base + shift) % 26) + base;
            }
        }
        return result;
    }
    string decrypt(const string& input, int shift) {
        return encrypt(input, 26 - shift); //дешифрування від кількості букв віднімаємо зсув
    }
};
void Write(const vector<string>& words, const string& filename, int shift) {
    Shibenica game; // Створюємо об'єкт класу Shibenica для доступу до методу encrypt
    ofstream file(filename);// Відкриваємо файл для запису
    if (file.is_open()) {
        for (int i = 0; i < words.size(); ++i) {
            const string& word = words[i];

            file << game.encrypt(word, shift) << "\n"; // Викликаємо метод encrypt через об'єкт game
        }
        file.close();
    }
    else {
        cout << "Error, unable to open file " << filename << "\n";
    }
}

int main() {
    vector<string> words = { "char","bool","void",//слова з 4 букв
                             "string","float","short",//слова з 5-6 букв
                             "vector","pointer", "function" };//слова більші за 6 букв
    Write(words, "words.txt", 3);

    char UserChoice;
    bool job = 1;

    int count = 0;
    Shibenica game;
    game.load("words.txt", 3); // зсув на 3 позиції
    while (job) {
        if (count > 0) {
            cout << "One more time? (y/n)\n";
        }
        else {
            cout << "Do you want to play a game? (y/n)\n";
        }
        cin >> UserChoice;
        if (UserChoice == 'y') {
            int difficulty;
            do {
                cout << "Choose difficulty level (1-easy, 2-medium, 3-hard): ";
                cin >> difficulty;
            } while (difficulty < 1 || difficulty > 3);


            game.play(difficulty);
            count++;
        }

        else if (UserChoice == 'n') {
            job = 0;
            break;
        }
    }
    if (count > 0) {
        cout << "Thank you for playing!\n";
    }
    else {
        cout << "Bye!";
    }
}
