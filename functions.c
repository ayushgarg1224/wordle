/*
 *the following file contains the implementations of the functions needed to execute the game codebreaker the code for which is written in main.c. All
 *functions have a small description given right before their implementation and the comments give a more in depth description
*/


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
	int seed, ret_val;					//declaring seed to store the integer typed in by the user and ret_val to store the return 
								//value of sscanf
	char post[2];						//defining post variable to hold any character that the user types besides the integer
	ret_val = sscanf(seed_str, "%d%1s", &seed, post);       //breaking the user input into the needed substrings
	if (ret_val == 1){					//chechking if the user only typed in integer by checking if only seed was filled by sscanf
		srand(seed);   					//if the condition is true then we choose the seed as the seed for srand
		return 1;				        // we exit the function by returning 1 to signify proper execution
	}
	printf("set_seed: invalid seed\n");                     //if the condition was not met the user entered an invalid input
	return 0;						//we return 0 to signify improper execution
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{
    	solution1 = rand();     //generating a random number 
	solution1 %= 8;         //using mod 8 to get a value in range 0-7
	solution1 ++;           //incrementing to get a value in range 0-8
	*one = solution1;       //finally transferring from static solution variable to pointer value

	solution2 = rand();     //doing the same thing as above for all digits of the solution code
	solution2 %= 8;
	solution2 ++;
	*two = solution2;

	solution3 = rand();
	solution3 %= 8;
	solution3 ++;
	*three = solution3;
	
	solution4 = rand();
	solution4 %= 8;
	solution4 ++;
	*four = solution4;

	guess_number = 1;       //initiating the static variable guess_number to keep a track of user's guesses
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
	int ret_value, perf_match = 0, mis_match = 0;                         //defining local variables to be used in the function
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0, g1 = 0, g2 = 0, g3 = 0, g4 = 0;   
	int w,x,y,z;
	char post[1];
	ret_value = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);  //using sscanf to break the user entered string into needed subsrtrings
	if (ret_value == 4){  	//we check for a valid expression by first checking the number of variables filled and then if all the integers are b/w 1-8
		if ((1 <= w && w <= 8) && (1 <= x && x <= 8) && (1 <= y && y <= 8) && (1 <= z && z <= 8)){
			*one = w; //storing the scanned substrings into the required pointers
			*two = x;
			*three = y;
			*four = z;
			if (*one == solution1){   //checking for perfect matches
				perf_match ++;    // incrementing perfect match counter for each perfect match
				s1 ++;           //making changes to s1 and g1 to indicate if the solution and the guess are paired
				g1 ++;
			}
			if (*two == solution2){
				perf_match ++;
				s2 ++;
				g2 ++;
			}
			if (*three == solution3){
				perf_match ++;
				s3 ++;
				g3 ++;
			}
			if (*four == solution4){
				perf_match ++;
				s4 ++;
				g4 ++;
      			}
			if(g1 == 0){		//if guess 1 is unpaired we check against other solutions that is if they are unpaired too
				if ((s2 == 0) && (*one == solution2)) {
						mis_match ++; //incrementing mismatch counter for mismatched pairs
						g1 ++;	//changing g1 and s2 to indicate pairing
						s2 ++; 
				}
				else if ((s3 == 0) && (*one == solution3)) {
						mis_match ++;
						g1 ++;
						s3 ++; 
				}
				else if ((s4 == 0) && (*one == solution4)) {
						mis_match ++;
						g1 ++;
						s4 ++; 
				}
				}
			if(g2 == 0){
				if ((s1 == 0) && (*two == solution1)) {
						mis_match ++;
						g2 ++;
						s1 ++; 
				}		
				else if ((s3 == 0) && (*two == solution3)) {
						mis_match ++;
						g2 ++;
						s3 ++; 
				}
				else if ((s4 == 0) && (*two == solution4)) {
						mis_match ++;
						g2 ++;
						s4 ++; 
				}
				}
			if(g3 == 0){
				if ((s1 == 0) && (*three == solution1)) {
						mis_match ++;
						g3 ++;
						s1 ++;
				}
				else if ((s2 == 0) && (*three == solution2)) {
						mis_match ++;
						g3 ++;
						s2 ++; 
				}
				else if ((s4 == 0) && (*three == solution4)) {
						mis_match ++;
						g3 ++;
						s4 ++;
				}
				}	
			if(g4 == 0){
				if ((s1 == 0) && (*four == solution1)) {
						mis_match ++;
						g4 ++;
						s1 ++; 
				}
				else if ((s2 == 0) && (*four == solution2)) {
						mis_match ++;
						g4 ++;
						s2 ++; 
				}
				else if ((s3 == 0) && (*four == solution3)) {
						mis_match ++;
						g4 ++;
						s3 ++;
				}

				}
			printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perf_match, mis_match);
			guess_number ++; //incrementing guess_number for next time when the funciton is called
			return 1;
	}}
    printf("make_guess: invalid guess\n");
    return 0;
}

