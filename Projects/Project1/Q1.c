/* CS261- Assignment 1 - Q.1*/
/* Name: Mario Franco-Munoz
 * Date: 01/13/2018
 * Solution description: This program consists of a creation of an array of student structs
 * where each student struct contains an id and score. Scores and IDs are randomly generated
 * and the highest score, lowest score and average is displayed along with a list of the different
 * student IDs and their scores.
 */
 

#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <assert.h>
 


struct student{
	int id;
	int score;
};

/*********************************************************************
** Function: allocate
** Description: This function allocates memory for ten student structs and returns a pointer
** to the array of structs.
** Parameters: none
** Pre-Conditions: student struct must already be defined to use this function.
*********************************************************************/
struct student* allocate(){
	int numOfStudents = 10;

     /*Allocate memory for ten students*/
	struct student *studPtr = malloc(numOfStudents * sizeof(struct student));
     
     /*return the pointer*/
	return studPtr;
}


/*********************************************************************
** Function: generate
** Description: generates randomIDs and scores for each of the students and stores them in the
** array of student struct. IDs are unique can range from [1 to 10] and scores rane from [0 to 100]
** Parameters: pointer to array of student structs.
** Pre-Conditions: memory for array of student struct pointers must already have been declared and allocated.
*********************************************************************/
void generate(struct student* students) {
	int numOfStudents = 10;				//number of students for which IDs and scores are to be generated for
	int maxID = 10;						//Highest ID number to be generated


	// using the fisher-yates shuffle as found on
	//https://www.quora.com/What-is-a-simple-implementation-of-the-Fisher%E2%80%93Yates-shuffle-in-C
	int j, temp;

	for (int i = 0; i < numOfStudents; i++) {
		students[i].id = i + 1;
	}

	for (int i = 9; i >= 0; i--) {
		j = rand() % (i + 1);

		temp = students[j].id;
		students[j].id = students[i].id;
		students[i].id = temp;
	}

    //generate random score using rand() for the different students.
	for (int i = 0; i < numOfStudents; i++) {

		students[i].score = rand() % 101;		//in the range 0 to 100 inclusive
	 }
}

/*********************************************************************
** Function: output
** Description: this function displays the corresponding randomly generated ID and 
** score for each student.
** Parameters: pointer to array of student structs
** Pre-Conditions: structs within array must be iniaialized and generate fucntion need have
** already been run.
*********************************************************************/
void output(struct student* students){
	int numberOfStudents = 10;
	
	/*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	for (int i = 0; i < numberOfStudents; i++) {
		if (students[i].id < 10) {
			printf("%d  %d\n", students[i].id, students[i].score);
		}
		else {
			printf("%d %d\n", students[i].id, students[i].score);
		}
		
	}
}

/*********************************************************************
** Function: summary
** Description: Computes and prints the minimum, maximum and average scores of the
** different students that the array of student struct is composed of. 
** Parameters: pointer to array of student structs
** Pre-Conditions: IDs and Scores must have been assigned to structs prior to function call.
*********************************************************************/
void summary(struct student* students){
	int numberOfStudents = 10;
	int min;
	int max;
	double mean = 0;
	
	//initialize min and max
	min = students[0].score;
	max = students[0].score;

	//compute the minimum, max score as well as accumulate for mean
	for (int i = 0; i < numberOfStudents; i++) {
		if (students[i].score < min) {
			min = students[i].score;
		}
		if (students[i].score > max) {
			max = students[i].score;
		}
		mean += students[i].score;
	}
	//compute the average score
	mean *= 1.0;
	mean /= numberOfStudents;

	//display min, max and average
	printf("Minimum score:       %d\n", min);
	printf("Maximum score:       %d\n", max);
	printf("Average score:       %f\n", mean);
     
}

/*********************************************************************
** Function: deallocate
** Description: deallocates (or frees) memory allocated for the student structs
** Parameters: pointer to array of student structs
** Pre-Conditions:
*********************************************************************/
void deallocate(struct student *stud){
	
	free(stud);
	
}

int main(){
	

    struct student *stud = NULL;
    
    /*call allocate*/
	stud = allocate();

    /*call generate*/
	generate(stud);
    
    /*call output*/
	output(stud);
    
    /*call summary*/
	summary(stud);
    
    /*call deallocate*/
	deallocate(stud);
	
    return 0;
}
