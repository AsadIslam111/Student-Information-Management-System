# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <conio.h>


typedef struct $student_info
{
   char * full_name;
   int id;
   float cgpa;
   char * cell_phone;
} $student_info;

typedef struct $students
{
   $student_info * student_info;
   struct $students * next_student;
} $students;


// -------------------------------------------------
// init
// ------------------------------------------------

typedef struct $db_processing
{
   $students * (* addStudentDetails)($students * student_list);
   $students * (* updateStudent)($students * student_list);
   void (* findStudent)($students * student_list);
   void (* countStudent)($students * student_list);
   void (* printDB)($students * student_list);
   $students * (* readDB)();
   $students * (* writeDB)($students * student_list);
} $db_processing;

$db_processing * prepare$db_processing();
$student_info * initialize$student_info();
$student_info * insert2$student_info(char * full_name, int id, float cgpa, char * cell_phone);

$students * initialize$students();
$students * insert2$students($students * student_list, $student_info * a_$student_info);
int checkUniquity$students($students * student_list, int id);
$students * updateStudentName$students($students * student_list, int id, char * update_name);
$students * updateContactNumber$students($students * student_list, int id, char * update_cell_phone);
$students * updateStudentCGPA$students($students * student_list, int id, float update_cgpa);
void findStudent$students($students * student_list, int id);
int countTotal$students($students * student_list);
void show$students($students * student_list);

FILE * createDatabaseFile(char * file_name);
char * databaseFilename();
void record2File(char * data, char * file_name);
void recordStudentInfo2File(char * filename, char * full_name, int id, float cgpa, char * cell_phone);
void wowHeader(char * header);
$students * sampleData($students * student_list);
$students * dashboard($students * student_list);


// -------------------------------------------------
// main workload
// --------------------

$students * addStudentDetails($students * student_list);
$students * updateStudent($students * student_list);
void findStudent($students * student_list);
void countStudent($students * student_list);
void printDB($students * student_list);
$students * readDB();
$students * writeDB($students * student_list);

# define StudentDB prepare$db_processing()

// -------------------------------------------------
// function processing
// -------------------------------------------------

$student_info * initialize$student_info()
{
   $student_info * returning = ($student_info *) malloc(sizeof($student_info));
   return returning;
}

$students * initialize$students()
{
   $students * blank = ($students *) malloc(sizeof($students));
   blank -> next_student = NULL;
   return blank;
}

$student_info * insert2$student_info(char * full_name, int id, float cgpa, char * cell_phone)
{
   $student_info * a_$student_info = initialize$student_info();
   a_$student_info -> full_name = full_name;
   a_$student_info -> id = id;
   a_$student_info -> cgpa = cgpa;
   a_$student_info -> cell_phone = cell_phone;

   return a_$student_info;
}

$students * insert2$students($students * student_list, $student_info * a_$student_info)
{
   $students * new_student = initialize$students();
   new_student -> student_info = a_$student_info;

   $students * each_student = initialize$students();
   each_student = student_list;
   $students * temp = each_student;

   if(student_list == NULL){
      student_list = new_student;
   }else{
      while(each_student -> next_student != NULL){
         each_student = each_student -> next_student;
      } each_student -> next_student = new_student;
      // student_list = temp;
   }

   return student_list;
}
void show$students($students * student_list)
{
   $students * each_student = initialize$students();
   each_student = student_list;
   int studentSL = 0;

   printf(
      "\n"
      "-----------------------------------------------------\n\n"
   );

   if(student_list == NULL){
      printf(
            "\t  No Student Found\n"
            "\n"
            "-----------------------------------------------------\n\n"
         );
   }else{
      while(each_student != NULL){
         printf(
            "\tStudent %d\n"
            "\t-----------\n"
            "\tFULL NAME\t: %.21s\n"
            "\tID\t\t: %d\n"
            "\tCGPA\t\t: %.2f\n"
            "\tCONTACT NUMBER\t: %.17s\n",
            ++studentSL,
            each_student -> student_info -> full_name,
            each_student -> student_info -> id,
            each_student -> student_info -> cgpa,
            each_student -> student_info -> cell_phone
         );
         printf(
            "\n"
            "-----------------------------------------------------\n\n"
         );
         each_student = each_student -> next_student;
      }
   }
}
//-------Asad Islam -------------
void findStudent$students($students * student_list, int id){
   $students * each_student = initialize$students();
   each_student = student_list;
   int studentSL = 0;

   printf(
      "\n"
      "-----------------------------------------------------\n\n"
   );

   if(student_list == NULL){
      printf(
            "\t!! NO STUDENTS IN THE DATABASE\n"
            "\n"
            "-----------------------------------------------------\n\n"
         );
   }else{
      while(each_student != NULL){
         if(id == (each_student -> student_info -> id)){
            printf(
               "\tSearched student%d\n"
               "\t~~~~~~~~~~~~~~~~\n"
               "\tFULL NAME\t: %.21s\n"
               "\tID\t\t: %d\n"
               "\tCGPA\t\t: %.2f\n"
               "\tCONTACT NUMBER\t: %.17s\n",
               ++studentSL,
               each_student -> student_info -> full_name,
               each_student -> student_info -> id,
               each_student -> student_info -> cgpa,
               each_student -> student_info -> cell_phone
            );
            printf(
               "\n"
               "-----------------------------------------------------\n\n"
            );
         }
         each_student = each_student -> next_student;
      }
   }
}

int checkUniquity$students($students * student_list, int id)
{
   int count_id = 0;

   $students * each_student = initialize$students();
   each_student = student_list;

   if(student_list == NULL){

   }else{
      while(each_student != NULL){
         if(id == (each_student -> student_info -> id))
         {
            ++count_id;
         }
         each_student = each_student -> next_student;
      }
   }
   return count_id;
}

$students * updateStudentName$students($students * student_list, int id, char * update_name)
{
   int updated_count = 0;

   $students * each_student = initialize$students();
   each_student = student_list;

   if(student_list == NULL)
   {

   }
   else{
      while(each_student != NULL)
      {
         if(id == (each_student -> student_info -> id))
         {
            each_student -> student_info -> full_name = update_name;
            ++updated_count;
         }
         each_student = each_student -> next_student;
      }
   }
   return student_list;
}

$students * updateContactNumber$students($students * student_list, int id, char * update_cell_phone)
{
   int updated_count = 0;

   $students * each_student = initialize$students();
   each_student = student_list;

   if(student_list == NULL){

   }else{
      while(each_student != NULL){
         if(id == (each_student -> student_info -> id))
         {
            each_student -> student_info -> cell_phone = update_cell_phone;
            ++updated_count;
         }
         each_student = each_student -> next_student;
      }
   }
   return student_list;
}

$students * updateStudentCGPA$students($students * student_list, int id, float update_cgpa)
{
   int updated_count = 0;

   $students * each_student = initialize$students();
   each_student = student_list;

   if(student_list == NULL){

   }else{
      while(each_student != NULL){
         if(id == (each_student -> student_info -> id))
         {
            each_student -> student_info -> cgpa = update_cgpa;
            ++updated_count;
         }
         each_student = each_student -> next_student;
      }
   }
   return student_list;
}

int countTotal$students($students * student_list)
{
   int countTotal$students = 0;

   $students * each_student = initialize$students();
   each_student = student_list;

   if(student_list == NULL){

   }else{
      while(each_student != NULL){
         ++countTotal$students;
         each_student = each_student -> next_student;
      }
   }
   return countTotal$students;
}

char * databaseFilename()
{
   return "students.info";
}

// -------------

FILE * createDatabaseFile(char * file_name)
{
   FILE * databaseFilename = fopen(file_name, "a+");
   if(databaseFilename == NULL){
        puts("Sorry! Can't open file");
        // StopProcessing();
        exit(1);
    }
   return databaseFilename;
}

void record2File(char * data, char * file_name)
{
   FILE * pointr = createDatabaseFile(file_name);
   fputs(data, pointr);
   fclose(pointr);
}

void recordStudentInfo2File(char * filename, char * full_name, int id, float cgpa, char * cell_phone)
{
   char * string_id = (char *) malloc(sizeof(char));
   char * string_cgpa = (char *) malloc(sizeof(char));

   itoa(id, string_id, 10);
   // itoa(cgpa, string_cgpa, 10);
   gcvt(cgpa, 3, string_cgpa);

   record2File("(", filename);
   record2File(full_name, filename);
   record2File("):name, ", filename);

   record2File("(", filename);
   record2File(string_id , filename);
   record2File("):id, ", filename);

   record2File("(", filename);
   record2File(string_cgpa, filename);
   record2File("):cgpa, ", filename);

   record2File("(", filename);
   record2File(cell_phone, filename);
   record2File("):cell_phone, ", filename);
   record2File("\n", filename);
}

$students * readDB()
{
   $students * student_list = NULL;
   FILE * pointr = createDatabaseFile(databaseFilename());
   char each_line[123];




   char tmp[2];
   tmp[0] = 'o';
   tmp[1] = '\0';

   while(fgets(each_line, 123, pointr)){

   char * str_full_name = (char *) malloc(sizeof(char));
   char * str_id = (char *) malloc(sizeof(char));
   char * str_cgpa = (char *) malloc(sizeof(char));
   char * str_cell_phone = (char *) malloc(sizeof(char));

   strcpy(str_full_name, "");
   strcpy(str_id, "");
   strcpy(str_cgpa, "");
   strcpy(str_cell_phone, "");


      int chr, opening_bracket = 0, closing_bracket = 0;
      for(chr = 0; chr < strlen(each_line); chr++){
         if(each_line[chr] == '('){
         opening_bracket++;
         }else if(each_line[chr] == ')'){
            closing_bracket++;
         }else if(opening_bracket != closing_bracket){
            tmp[0] = each_line[chr];
            if(opening_bracket == 1){
               strcat(str_full_name, tmp);
            }else if(opening_bracket == 2){
               strcat(str_id, tmp);
            }else if(opening_bracket == 3){
               strcat(str_cgpa, tmp);
            }else if(opening_bracket == 4){
               strcat(str_cell_phone, tmp);
            }
         }
      }

      int id =  atoi(str_id);
      float cgpa =  atof(str_cgpa);


      student_list = insert2$students(
         student_list,
         insert2$student_info(str_full_name, id, cgpa, str_cell_phone)
      );

   }

   fclose(pointr);

   return student_list;
}

void wowHeader(char * header)
{
   printf(
      "-::-::-::-::-::-::-::-::-::-::\n"
      " %s\n"
      "-::-::-::-::-::-::-::-::-::-::\n"
      "\n",
      header
   );
}

$students * addStudentDetails($students * student_list)
{
   wowHeader("Add Student Detail");

   char full_name[123];
   int id;
   float cgpa;
   char cell_phone[123];

   printf("Full Name: ");
   getchar();
   gets(full_name);

   while(404){
      printf("ID: ");
      scanf("%d", &id);
      if(checkUniquity$students(student_list, id)){
         printf("The ID Is Not Unique. Try Again\n");
      }else{
         goto if_is_valid;
      }
   }
   if_is_valid:
   printf("CGPA: ");
   scanf("%f", &cgpa);

   printf("Cell Phone: ");
   getchar();
   gets(cell_phone);

   student_list = insert2$students(
      student_list,
      insert2$student_info(
         full_name,
         id,
         cgpa,
         cell_phone
      )
   );

   char * string_id = (char *) malloc(sizeof(char));
   char * string_cgpa = (char *) malloc(sizeof(char));

   recordStudentInfo2File(databaseFilename(), full_name, id, cgpa, cell_phone);

   return student_list;
}

void printDB($students * student_list){
   wowHeader("printDB");
   show$students(student_list);
}

$students * updateStudent($students * student_list){
   wowHeader("updateStudent");

   int id;
   printf("ID: ");
   scanf("%d", &id);

   printf("\n");

   printf(
      "\t1. Update Name\n"
      "\t2. Update CGPA\n"
      "\t3. Update Cell Phone\n"
      "\n"
   );

   int option;
   printf("Option: ");
   scanf("%d", &option);

   if(option == 1){
      char * full_name = (char *) malloc(sizeof(char));
      printf("New Full Name: ");
      getchar();
      gets(full_name);
      student_list = updateStudentName$students(student_list, id, full_name);
   }else if(option == 2){
      float cgpa;
      printf("New CGPA: ");
      scanf("%f", &cgpa);
      student_list = updateStudentCGPA$students(student_list, id, cgpa);
   }else if(option == 3){
      char * cell_phone  = (char *) malloc(sizeof(char));
      printf("Update Cell Phone: ");
      getchar();
      gets(cell_phone);
      student_list = updateContactNumber$students(student_list, id, cell_phone);
   }

   return student_list;
}

void countStudent($students * student_list)
{
   wowHeader("countStudent()");
   printf("Count Student: %d\n", countTotal$students(student_list));
}

void findStudent($students * student_list)
{
   wowHeader("findStudent");
   printf("ID: ");
   int id;
   scanf("%d", &id);
   findStudent$students(student_list, id);
}

$students * writeDB($students * student_list)
{
   $students * each_student = initialize$students();
   each_student = student_list;
   remove(databaseFilename());
   if(student_list == NULL){

   }else{
      while(each_student != NULL){
         recordStudentInfo2File(
            databaseFilename(),
            each_student -> student_info -> full_name,
            each_student -> student_info -> id,
            each_student -> student_info -> cgpa,
            each_student -> student_info -> cell_phone
         );
         each_student = each_student -> next_student;

      }
   }
   return student_list;
}

$students * sampleData($students * student_list)
{
   char * full_name1 = "Asad Islam";
   int id1 = 213902054;
   float cgpa1 = 3.00;
   char * cell_phone1 = "+8801478523690";

   char * full_name2 = "Nafisa Lubaba Khan";
   int id2 = 213902082;
   float cgpa2 = 3.50;
   char * cell_phone2 = "+8801478523691";

   char * full_name3 = "Shahrear Shaon";
   int id3 = 213902064;
   float cgpa3 = 4.00;
   char * cell_phone3 = "8801478523692";

   char * full_name4 = "Arafat Shezan";
   int id4 = 213902035;
   float cgpa4 = 4.00;
   char * cell_phone4 = "8801478523693";

   student_list = insert2$students(
      student_list,
      insert2$student_info(
         full_name1,
         id1,
         cgpa1,
         cell_phone1
      )
   );
   recordStudentInfo2File(databaseFilename(), full_name1, id1, cgpa1, cell_phone1);


   student_list = insert2$students(
      student_list,
      insert2$student_info(
         full_name2,
         id2,
         cgpa2,
         cell_phone2
      )
   );
   recordStudentInfo2File(databaseFilename(), full_name2, id2, cgpa2, cell_phone2);

   student_list = insert2$students(
      student_list,
      insert2$student_info(
         full_name3,
         id3,
         cgpa3,
         cell_phone3
      )
   );
   recordStudentInfo2File(databaseFilename(), full_name3, id3, cgpa3, cell_phone3);

   student_list = insert2$students(
      student_list,
      insert2$student_info(
         full_name4,
         id4,
         cgpa4,
         cell_phone4
      )
   );
   recordStudentInfo2File(databaseFilename(), full_name4, id4, cgpa4, cell_phone4);


   return student_list;
}

$db_processing * prepare$db_processing()
{
   $db_processing * preparing = ($db_processing *) malloc(sizeof($db_processing));

   preparing -> addStudentDetails = &addStudentDetails;
   preparing -> updateStudent = &updateStudent;
   preparing -> findStudent = &findStudent;
   preparing -> countStudent = &countStudent;
   preparing -> printDB = &printDB;
   preparing -> readDB = &readDB;
   preparing -> writeDB = &writeDB;

   return preparing;
}


$students * dashboard($students * student_list)
{
   student_list = StudentDB -> readDB();
   wowHeader("Student Information Management System");
   printf(
      "\t1. Add Student\n"
      "\t2. Update Student\n"
      "\t3. Find Student\n"
      "\t4. Count Student\n"
      "\t5. Print DataBase\n"
      "\t6. Sample Data\n"
      "\t7. Exit\n"
      "\n"
   );

   int option;
   printf("Option: ");
   scanf("%d", &option);

   system("cls");
   if(option == 1){
      student_list = StudentDB -> addStudentDetails(student_list);
   }else if(option == 2){
      student_list = StudentDB -> updateStudent(student_list);
      StudentDB -> writeDB(student_list);
   }else if(option == 3){
      StudentDB -> findStudent(student_list);
   }else if(option == 4){
      StudentDB -> countStudent(student_list);
   }else if(option == 5){
      StudentDB -> printDB(student_list);
   }else if(option == 6){
      wowHeader("sampleData");
      student_list = sampleData(student_list);
      printf("Sample Data Added To Database\n");
   }else if(option == 7){
      exit(0);
   }

   printf(
      "\n"
      "Continue.."
   );
   getch();
   system("cls");

   dashboard(student_list);
   return student_list;
}

int main(){

   $students * student_list = NULL;
   dashboard(student_list);

   return 0;
}
