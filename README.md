# Exam Management System

A C++ console-based application for managing quizzes and exams with support for multiple choice questions (MCQ) and True/False questions. The system provides separate interfaces for administrators and students, with persistent storage for questions and student data.

## Features

### Admin Features
- Secure admin login system
- Add new questions (MCQ or True/False)
- Remove existing questions
- View all questions and their answers
- Questions automatically saved to file system

### Student Features
- Student registration and login system
- Take quizzes with immediate feedback
- View score after quiz completion
- Progress tracking and persistence
- Support for multiple student accounts

### Question Types
- Multiple Choice Questions (MCQ)
  - Custom number of choices
  - Single correct answer
- True/False Questions
  - Binary choice questions
  - Case-insensitive answer checking

## Technical Requirements

- C++ compiler with C++11 support or higher
- Standard Template Library (STL)
- File system read/write permissions

## Installation

1. Clone the repository:
```bash
git clone [repository-url]
cd exam-management-system
```

2. Compile the source code:
```bash
g++ -std=c++11 main.cpp -o quiz_system
```

3. Run the application:
```bash
./quiz_system
```

## File Structure

The system uses two main files for data persistence:
- `questions.txt`: Stores all quiz questions
- `students.txt`: Stores student information and scores

### File Formats

#### questions.txt
```
MCQ
[Question Text]
[Choice 1]
[Choice 2]
[Choice 3]
[Choice 4]
[Correct Answer]

TrueFalse
[Question Text]
[Correct Answer]
```

#### students.txt
```
Username: [username]
Password: [password]
Score: [score]
```

## Usage Guide

### Admin Access
1. Select "Admin" from the main menu
2. Default credentials:
   - Username: admin
   - Password: password

### Student Registration
1. Select "Student Signup" from the main menu
2. Enter username and password
3. Account will be created automatically

### Taking a Quiz
1. Select "Student Login" from the main menu
2. Enter your credentials
3. Answer each question as prompted
4. View your score after completion

## Security Features

- Password-protected admin access
- Secure student authentication
- File-based persistence for data integrity
- Input validation for all user interactions

## Class Structure

### Core Classes
- `Question`: Abstract base class for all question types
- `MCQQuestion`: Handles multiple choice questions
- `TrueFalseQuestion`: Handles true/false questions
- `Quiz`: Abstract interface for quiz functionality
- `QuizManager`: Implements quiz taking functionality
- `Student`: Manages student data and authentication
- `Admin`: Handles administrative functions

## Limitations

- Console-based interface
- Single admin account
- No question categories or difficulty levels
- No time limits for quizzes
- Questions must be added one at a time

## Future Enhancements

- Graphical user interface
- Multiple admin support
- Question categories and difficulty levels
- Timed quizzes
- Bulk question import/export
- Student performance analytics
- Password encryption
- Multiple correct answers for MCQs
- Rich text formatting for questions

