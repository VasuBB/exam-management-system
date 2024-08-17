#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <memory>

using namespace std;

class Question {
protected:
    string text;
    string answer;

public:
    Question(const string& text, const string& answer) : text(text), answer(answer) {}
    virtual ~Question() = default;

    virtual bool checkAnswer(const string& userAnswer) = 0;

    string getText() const { return text; }
    string getAnswer() const { return answer; }

    virtual string toFormattedString() const = 0;
};

class MCQQuestion : public Question {
private:
    vector<string> choices;

public:
    MCQQuestion(const string& text, const vector<string>& choices, const string& answer)
        : Question(text, answer), choices(choices) {}

    bool checkAnswer(const string& userAnswer) override {
        return equal(userAnswer.begin(), userAnswer.end(), answer.begin(), answer.end(),
                     [](char a, char b) { return tolower(a) == tolower(b); });
    }

    vector<string> getChoices() const { return choices; }

    string toFormattedString() const override {
        string formatted = "MCQ\n" + text + "\n";
        for (const auto& choice : choices) {
            formatted += choice + "\n";
        }
        formatted += answer + "\n";
        return formatted;
    }
};

class TrueFalseQuestion : public Question {
public:
    TrueFalseQuestion(const string& text, const string& answer) : Question(text, answer) {}

    bool checkAnswer(const string& userAnswer) override {
        return equal(userAnswer.begin(), userAnswer.end(), answer.begin(), answer.end(),
                     [](char a, char b) { return tolower(a) == tolower(b); });
    }

    string toFormattedString() const override {
        return "TrueFalse\n" + text + "\n" + answer + "\n";
    }
};

class Quiz {
public:
    virtual ~Quiz() = default;
    virtual void addQuestion(shared_ptr<Question> question) = 0;
    virtual void start() = 0;
    virtual void gradeQuiz() = 0;
};

class Student {
private:
    string username;
    string password;
    int score;

public:
    Student(const string& username, const string& password) : username(username), password(password), score(0) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    int getScore() const { return score; }

    void increaseScore(int points) { score += points; }

    void saveStudentDataToFile(const string& file) const {
        ofstream writer(file, ios::app);
        if (writer.is_open()) {
            writer << "Username: " << username << "\n";
            writer << "Password: " << password << "\n";
            writer << "Score: " << score << "\n\n";
            cout << "Student data saved to file." << endl;
            writer.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    static vector<Student> loadStudentDataFromFile(const string& file) {
        vector<Student> students;
        ifstream reader(file);
        if (reader.is_open()) {
            string line;
            string username, password;
            int score = 0;

            while (getline(reader, line)) {
                if (line.substr(0, 10) == "Username: ") {
                    username = line.substr(10);
                } else if (line.substr(0, 10) == "Password: ") {
                    password = line.substr(10);
                } else if (line.substr(0, 7) == "Score: ") {
                    score = stoi(line.substr(7));
                } else if (line.empty()) {
                    if (!username.empty() && !password.empty()) {
                        Student student(username, password);
                        student.score = score;
                        students.push_back(student);
                    }
                    username.clear();
                    password.clear();
                    score = 0;
                }
            }
            reader.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
        return students;
    }
};

class Admin {
private:
    static const string ADMIN_USERNAME;
    static const string ADMIN_PASSWORD;
    static const string QUESTIONS_FILE;

    vector<shared_ptr<Question>> questions;

    void loadQuestionsFromFile() {
        ifstream reader(QUESTIONS_FILE);
        if (reader.is_open()) {
            string line;
            string text, answer;
            vector<string> choices;
            bool isMCQ = false;

            while (getline(reader, line)) {
                if (line == "MCQ") {
                    getline(reader, text);
                    choices.clear();
                    while (getline(reader, line) && !line.empty()) {
                        choices.push_back(line);
                    }
                    if (getline(reader, answer)) {
                        isMCQ = true;
                    } else {
                        break;
                    }
                } else if (line == "TrueFalse") {
                    getline(reader, text);
                    if (getline(reader, answer)) {
                        isMCQ = false;
                    } else {
                        break;
                    }
                }

                if (!text.empty() && !answer.empty()) {
                    if (isMCQ) {
                        questions.push_back(make_shared<MCQQuestion>(text, choices, answer));
                    } else {
                        questions.push_back(make_shared<TrueFalseQuestion>(text, answer));
                    }
                    text.clear();
                    answer.clear();
                }
            }
            reader.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
    }

    void saveQuestionsToFile() const {
        ofstream writer(QUESTIONS_FILE);
        if (writer.is_open()) {
            for (const auto& question : questions) {
                writer << question->toFormattedString();
            }
            writer.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

public:
    Admin() { loadQuestionsFromFile(); }

    void addQuestion(shared_ptr<Question> question) {
        questions.push_back(question);
        saveQuestionsToFile();
    }

    void removeQuestion(shared_ptr<Question> question) {
        auto it = find(questions.begin(), questions.end(), question);
        if (it != questions.end()) {
            questions.erase(it);
            saveQuestionsToFile();
        }
    }

    vector<shared_ptr<Question>> getQuestions() const { return questions; }

    static bool authenticateAdmin(const string& username, const string& password) {
        return ADMIN_USERNAME == username && ADMIN_PASSWORD == password;
    }
};

const string Admin::ADMIN_USERNAME = "admin";
const string Admin::ADMIN_PASSWORD = "password";
const string Admin::QUESTIONS_FILE = "questions.txt";

class QuizManager : public Quiz {
private:
    Student student;
    vector<shared_ptr<Question>> questions;
    int score;

public:
    QuizManager(const Student& student, const vector<shared_ptr<Question>>& questions)
        : student(student), questions(questions), score(0) {}

    void addQuestion(shared_ptr<Question> question) override {
        questions.push_back(question);
    }

    void start() override {
        for (const auto& question : questions) {
            cout << question->getText() << endl;

            if (auto mcqQuestion = dynamic_pointer_cast<MCQQuestion>(question)) {
                auto choices = mcqQuestion->getChoices();
                for (size_t i = 0; i < choices.size(); ++i) {
                    cout << static_cast<char>('A' + i) << ". " << choices[i] << endl;
                }
            }

            string userAnswer;
            cout << "Your answer: ";
            getline(cin, userAnswer);

            if (question->checkAnswer(userAnswer)) {
                cout << "Correct!" << endl;
                ++score;
            } else {
                cout << "Incorrect. The correct answer is: " << question->getAnswer() << endl;
            }
        }
    }

    void gradeQuiz() override {
        cout << "Quiz Complete!" << endl;
        cout << "Your Score: " << score << "/" << questions.size() << endl;
    }
};

void adminOptions(Admin& admin) {
    while (true) {
        cout << "\nAdmin Options:" << endl;
        cout << "1. Add Question" << endl;
        cout << "2. Remove Question" << endl;
        cout << "3. List Questions" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string questionText, answer;
                cout << "Enter the question text: ";
                getline(cin, questionText);

                cout << "Enter the answer: ";
                getline(cin, answer);

                string isMCQStr;
                cout << "Is it a Multiple Choice Question? (true/false): ";
                getline(cin, isMCQStr);
                bool isMCQ = (isMCQStr == "true");

                if (isMCQ) {
                    vector<string> choices;
                    string choicesStr;
                    cout << "Enter the choices (comma-separated): ";
                    getline(cin, choicesStr);
                    size_t pos = 0;
                    string token;
                    while ((pos = choicesStr.find(',')) != string::npos) {
                        token = choicesStr.substr(0, pos);
                        choices.push_back(token);
                        choicesStr.erase(0, pos + 1);
                    }
                    choices.push_back(choicesStr);
                    admin.addQuestion(make_shared<MCQQuestion>(questionText, choices, answer));
                } else {
                    admin.addQuestion(make_shared<TrueFalseQuestion>(questionText, answer));
                }
                cout << "Question added successfully!" << endl;
                break;
            }
            case 2: {
                cout << "Select a question to remove:" << endl;
                auto questions = admin.getQuestions();
                for (size_t i = 0; i < questions.size(); ++i) {
                    const auto& question = questions[i];
                    string questionType = (dynamic_pointer_cast<MCQQuestion>(question) != nullptr) ? "MCQ" : "TrueFalse";
                    cout << (i + 1) << ". [" << questionType << "] " << question->getText() << endl;
                }
                int removeChoice;
                cin >> removeChoice;
                if (removeChoice >= 1 && removeChoice <= static_cast<int>(questions.size())) {
                    admin.removeQuestion(questions[removeChoice - 1]);
                    cout << "Question removed successfully!" << endl;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }
            case 3: {
                auto listedQuestions = admin.getQuestions();
                cout << "\nList of Questions:" << endl;
                for (size_t i = 0; i < listedQuestions.size(); ++i) {
                    const auto& q = listedQuestions[i];
                    string questionType = (dynamic_pointer_cast<MCQQuestion>(q) != nullptr) ? "MCQ" : "TrueFalse";
                    cout << (i + 1) << ". [" << questionType << "] " << q->getText() << " (Answer: " << q->getAnswer() << ")" << endl;
                }
                break;
            }
            case 4:
                cout << "Logging out as admin." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    vector<Student> students = Student::loadStudentDataFromFile("students.txt");
    Admin admin;
    cout << "Welcome to the Quiz Management System" << endl;

    while (true) {
        cout << "Select your role:" << endl;
        cout << "1. Student Signup" << endl;
        cout << "2. Student Login" << endl;
        cout << "3. Admin" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string studentName, password;
                cout << "Enter your name: ";
                getline(cin, studentName);
                cout << "Enter a password: ";
                getline(cin, password);
                Student student(studentName, password);
                students.push_back(student);
                student.saveStudentDataToFile("students.txt");
                cout << "Student " << studentName << " signed up successfully." << endl;
                break;
            }
            case 2: {
                string loginName, loginPassword;
                cout << "Enter your name: ";
                getline(cin, loginName);
                cout << "Enter your password: ";
                getline(cin, loginPassword);
                bool found = false;
                Student* student1 = nullptr;

                for (auto& s : students) {
                    if (s.getUsername() == loginName && s.getPassword() == loginPassword) {
                        found = true;
                        student1 = &s;
                        break;
                    }
                }

                if (found) {
                    QuizManager quizManager(*student1, admin.getQuestions());
                    quizManager.start();
                    quizManager.gradeQuiz();
                    cout << "Thank you, " << loginName << ", for taking the quiz!" << endl;
                } else {
                    cout << "Invalid username or password. Please check your credentials." << endl;
                }
                break;
            }
            case 3: {
                string adminUsername, adminPassword;
                cout << "Admin Username: ";
                getline(cin, adminUsername);
                cout << "Admin Password: ";
                getline(cin, adminPassword);

                if (Admin::authenticateAdmin(adminUsername, adminPassword)) {
                    adminOptions(admin);
                } else {
                    cout << "Admin login failed. Please check your credentials." << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting the Quiz Management System." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}