# Examination System

This project involves designing and implementing a console-based examination system for instructors to manage course evaluations. The system supports two types of users: Teachers and Students. It enables the instructor to set, conduct, mark, and prepare results for quizzes and assignments, along with providing additional analytics on the results.

## Features

### For Teachers
1. **User Creation**: Generate logins for instructors and students by reading names from text files.
2. **Course Offering**: Manage courses as per the course offering list.
3. **Course Registration**: Register students as per the provided registration document.
4. **Question Bank Preparation**: Create a question bank with MCQs, True/False, and subjective questions. Questions can be entered manually or read from files.
5. **Quiz Setting/Generation**: Create quizzes by selecting topics, number of questions, and setting date/time and duration. The system can also generate quizzes by randomly selecting questions from the question bank.
6. **Answer Key Generation**: Generate answer keys/solutions for quizzes from stored answers.
7. **Result Preparation**: Automatically mark quizzes, prepare a class mark sheet, and save it to disk.
8. **Quiz Analytics**: Provide insights on quiz performance, including percentage of correct answers per question displayed as a bar graph.
9. **Attendance Sheet Generation**: Mark absent students who did not attempt the quiz.

### For Students
1. **Quiz Conduct**: Attempt quizzes within the set date/time. The system will randomize question sequences and answer options to enhance security. The quiz is time-bound.
2. **Authentication**: Secure login with password setup. Password must be a minimum of 6 characters and include uppercase, lowercase, numeric digits, and special characters.

## Data Flow

1. **User Creation**: Generate logins by reading names from text files.
2. **Course Offering**: Offer courses as per the course offering list.
3. **Course Registration**: Register students based on the registration document.
4. **Question Bank Preparation**: Enter or read questions from files to create a question bank.
5. **Quiz Setting/Generation**: Select topics, number of questions, and set quiz date/time and duration.
6. **Quiz Conduct**: Students attempt the quiz within the set time. The system randomizes questions and options.
7. **Answer Key Generation**: Generate an answer key for each quiz.
8. **Result Preparation**: Prepare and save the result to disk after the quiz.
9. **Quiz Analytics**: Generate a bar graph of correct answer percentages for each question.
10. **Attendance Sheet Generation**: Mark absent students who did not attempt the quiz.

## System Requirements

- **Data Handling**: Read student data and course list from CSV files.
- **Menus**: Implement multiple menus for different functionalities. Handle invalid inputs and exceptions gracefully.
- **Object-Oriented Design**: Use classes such as Teacher, Student, Quiz, Question, Date, and Time.
- **Authentication**: Implement a secure login mechanism with password requirements.
- **Dynamic Memory Management**: Use dynamic memory allocation and de-allocation carefully to avoid memory leaks.
- **Error Handling**: Ensure the system handles logical errors and never crashes.
- **Coding Practices**: Follow recommended programming practices, including proper code comments.

## Usage

- **General Information**: Available to all users without login.
- **Registered Users**: Access specific information and functionalities after login.

## Development Guidelines

- Comment your code properly.
- Use dynamic memory allocation and de-allocation.
- Ensure robust error handling to prevent system crashes.
- Follow recommended programming practices.

