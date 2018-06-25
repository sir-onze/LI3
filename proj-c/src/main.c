

#include <time.h>
#include <stdio.h>
#include <glib.h>

#include "interface.h"
#include "dateplus.h"
#include "structures.h"
#include "objUser.h"
#include "objPost.h"
#include "user.h"

int main (int argc, char **argv){

	if(argc!=2) return 1;

	clock_t start, end;
	double cpu_time_used;
	start = clock();

	Date a = createDate(1, 7, 2016);
	Date b = createDate(31, 7, 2016);
	char* tag = "package-management";

	TAD_community com = init();
	load(com, *(argv+1));

	/*info_from_post(com, 801049); // 1
	top_most_active(com, 10); // 2
	total_posts(com, a, b); // 3
	questions_with_tag(com, tag, a, b); // 4
	get_user_info(com, 10); // 5
	most_voted_answers(com,10,a,b); // 6
	most_answered_questions(com, 10, a, b); // 7
	contains_word(com,"routing",2); // 8
	better_answer(com,1); //10*/

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\n\n%f\n",cpu_time_used);

	return 0;
}
