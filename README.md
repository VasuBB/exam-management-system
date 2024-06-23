This Exam Management System is a Java-based application designed to manage quizzes for students. It provides functionalities for students to sign up, log in, and take quizzes. Administrators can manage questions, including adding, removing, and listing them. The system supports multiple-choice questions (MCQs) and true/false questions.
Features
Student
•	Sign Up: Students can create an account with a username and password.
•	Log In: Students can log in to their accounts to take quizzes.
•	Take Quiz: Students can attempt quizzes comprising different types of questions.
•	View Score: After completing the quiz, students can view their score.
•	Save Data: Student data is saved to a file for persistence.
Administrator
•	Log In: Admins can log in using a predefined username and password.
•	Manage Questions: Admins can add, remove, and list questions.
•	Question Types: Supports MCQs and true/false questions.
•	Data Persistence: Questions are saved to a file for persistence.
File Structure
•	Main.java: Contains the Assignment class with the main method, serving as the entry point of the application.
•	Question.java: Abstract class for question types.
•	MCQQuestion.java: Extends Question for multiple-choice questions.
•	TrueFalseQuestion.java: Extends Question for true/false questions.
•	Student.java: Manages student data and interactions.
•	Admin.java: Manages administrative functionalities, including question management.
•	QuizManager.java: Handles quiz operations, including starting and grading the quiz.
Classes and Methods
Question (Abstract Class)
•	Attributes: text, answer
•	Methods:
o	checkAnswer(String userAnswer): Abstract method to check the answer.
o	getText(): Returns the question text.
o	getAnswer(): Returns the correct answer.
o	toFormattedString(): Abstract method to return the formatted question string.
MCQQuestion (Extends Question)
•	Attributes: choices (List of choices)
•	Methods:
o	checkAnswer(String userAnswer): Checks if the provided answer is correct.
o	getChoices(): Returns the list of choices.
o	toFormattedString(): Returns the formatted MCQ question string.
TrueFalseQuestion (Extends Question)
•	Methods:
o	checkAnswer(String userAnswer): Checks if the provided answer is correct.
o	toFormattedString(): Returns the formatted true/false question string.
Student
•	Attributes: username, password, score
•	Methods:
o	getUsername(): Returns the student's username.
o	getPassword(): Returns the student's password.
o	getScore(): Returns the student's score.
o	increaseScore(int points): Increases the student's score.
o	saveStudentDataToFile(String file): Saves student data to a file.
o	loadStudentDataFromFile(String file): Loads student data from a file.
Admin
•	Attributes: ADMIN_USERNAME, ADMIN_PASSWORD, QUESTIONS_FILE, questions (List of questions)
•	Methods:
o	loadQuestionsFromFile(): Loads questions from a file.
o	saveQuestionsToFile(): Saves questions to a file.
o	addQuestion(Question question): Adds a question.
o	removeQuestion(Question question): Removes a question.
o	getQuestions(): Returns the list of questions.
o	authenticateAdmin(String username, String password): Authenticates admin credentials.
QuizManager (Implements Quiz)
•	Attributes: student, questions (List of questions), score
•	Methods:
o	addQuestion(Question question): Adds a question to the quiz.
o	start(): Starts the quiz.
o	gradeQuiz(): Grades the quiz.
Assignment (Main Class)
•	Methods:
o	main(String[] args): Main method serving as the entry point of the application.
o	adminOptions(Admin admin): Provides admin options for managing questions.
How to Use
1.	Compile the Code: Use a Java compiler to compile the code.
sh
Copy code
javac *.java
2.	Run the Application: Execute the main class.
sh
Copy code
java Assignment
Files
•	students.txt: Stores student data.
•	questions.txt: Stores quiz questions.
Dependencies
•	Java Standard Library: The application uses standard Java libraries for file handling and user input.
Example Usage
1.	Run the Application: Follow the prompts to sign up, log in, and take quizzes.
2.	Admin Login: Use the username "admin" and password "password" to manage questions.
Notes
•	Ensure students.txt and questions.txt are in the same directory as the application for proper file handling.
•	Modify the admin credentials and file paths as needed for different environments.
Future Enhancements
•	Implement additional question types (e.g., short answer).
•	Add more robust error handling and input validation.
•	Develop a graphical user interface (GUI) for improved user experience.

