
#include "files_mg.h"

//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void files_mg::save_course_data_into_files()
{
    // Create a file stream
    fstream courseFile("course.txt" ,ios::out);
    courseFile << Student::courses.size() << endl;
    // Iterate over the key-value pairs in the map
    for (auto pair : Student::courses) {
         Course c = pair.second;
        // Write the course data to the file
         courseFile << c.name << endl << c.code << endl << c.requirement_or_elective << endl
             << c.max_num_std << endl << c.hours << endl << c.instructor << endl << c.prerequisites.size() << endl;
        // Write the prerequisites to the file
        for ( auto prereq : c.prerequisites) {
            courseFile << prereq << endl;
        }
    }
    // Close the file stream
    courseFile.close();
}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void files_mg::save_std_data_into_files()
{
    // Create a file stream
    ofstream stdFile("student1.txt",ios::out);

    // Iterate over the key-value pairs in the map
    stdFile << Student::students.size() << endl;
    for (const auto& pair : Student::students) {
        const Student& s = pair.second;
        // Write the student data to the file
        stdFile << s.name << endl << s.email << endl << s.id << endl << s.password << endl
            << s.max_hours_allowed << endl << s.academic_year << endl <<s.finished_courses.size()<<endl;
        // Write the finished courses to the file
        for (const auto& course : s.finished_courses) {
            stdFile << course << endl;
        }

        // Write the grade for finished courses to the file
        for (const auto& grade : s.gradesfor_finished_courses) {
            stdFile << grade << endl;
        }
        // Write the checkprereq to the file
        stdFile << s.checkprereq.size() <<endl;
        for (string x : s.checkprereq) {
            stdFile << x << endl;
        }
        // Write the in-progress courses to the file
        stdFile << s.inprogress_courses.size()<<endl;
        for (const auto& course : s.inprogress_courses) {
            stdFile << course << endl;
        }
    }

    // Close the file stream
    stdFile.close();

}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void files_mg::load_coarse_data_from_files()
{
    //open the file 
    fstream coursefile;
    coursefile.open("course.txt", ios::in);
    int counter = 0;
    int counterforprereq;
    string name;
    int code = 0;
    bool requirement_or_elective = true;
    int max_num_std = 0;
    double hours = 0.0;
    string instructor;
    vector<string> prerequisites;
    string prereq;
    // read the data from file line by line 
    coursefile >> counter;
    for (int i = 0; i < counter; i++)
    {
        coursefile >> name >> code >> requirement_or_elective >> max_num_std >> hours >> instructor >> counterforprereq;
        //parse the line and extract data 
        for (int i = 0; i < counterforprereq; i++)
        {
            coursefile >> prereq;
            prerequisites.push_back(prereq);
        }
        // Create a new Course object and add it to the unordered_map
        Student::courses[name] = Course(name, code, requirement_or_elective, max_num_std, hours, instructor);
        Student::courses[name].prerequisites = prerequisites;

    }
    // Close the input file stream
    coursefile.close();


}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void files_mg::load_std_data_from_files()
{

    // Open the input file stream
    fstream stdFile;
    stdFile.open("student1.txt", ios::in);
    // Read the data from the file line by line
    string line;
    int counter = 0;
    int counterfinishedcourses = 0;
    int countercourseinprogress = 0;
    stringstream lineStream(line);
    string name;
    string email;
    int id;
    string password;
    int max_hours_allowed;
    set<string> finished_courses;
    vector<double> gradefor_finished_courses;
    set<string> inprogress_courses;
    string academic_year;
            string course;
            double grade;
            string courseinprogress;
    stdFile >> counter;
    for (int i = 0; i < counter; i++)
    {
        stdFile >> name >> email >> id >> password >> max_hours_allowed >> academic_year >> counterfinishedcourses;
        for (int j = 0; j < counterfinishedcourses; j++)
        {
            stdFile >> course;
            finished_courses.insert(course);
        }
        for (int j = 0; j < counterfinishedcourses; j++)
        {
            stdFile >> grade;
            gradefor_finished_courses.push_back(grade);
        }
        stdFile >> countercourseinprogress;
        for (int j = 0; j < countercourseinprogress; j++)
        {
            stdFile >> courseinprogress;
            inprogress_courses.insert(courseinprogress);
        }

        Student student(name, id,email, password, max_hours_allowed, finished_courses, gradefor_finished_courses, inprogress_courses, academic_year);
        Student::students[id] = student;
    }
    stdFile.close();

}