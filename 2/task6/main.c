#include <stdio.h>
#include <stdlib.h>

/* returns the time in minutes */
int readTime() {
	
	int hh;
	int mm;
	
	scanf("%d%*c%d", &hh, &mm);
	
	/* printf("hh = %d\n", hh); */
	/* printf("mm = %d\n", mm); */
	
	if (hh > 23) hh = 23;
	
	if (mm > 59) mm = 59;
	
	return (hh * 60) + mm;
	
}

/* prints the time to the stdout in the format: 12:34 */
void printTime(int ts) {
	
	int mm = ts % 60;
	
	int hh = ts / 60;
	
	printf("%.2d:%.2d", hh, mm);
	
}

void printTimePretty(int ts) {
	
	printTime(ts);

	printf("\n");
		
}

int main() {
	
	printf("%s", "Enter start time: ");
	int startTime = readTime();

	printf("%s", "Enter end time: ");
	int endTime = readTime();
	
	int routeTime;
	
	printf("Enter route time in minutes: ");
	scanf("%d", &routeTime);
	
	int restTime;
	
	printf("Enter rest time in minutes: ");
	scanf("%d", &restTime);
	
	/* print the values we received */
	
	printf("Start time: ");
	printTimePretty(startTime);

	printf("End time: ");
	printTimePretty(endTime);
	
	printf("Route time: ");
	printTimePretty(routeTime);
	
	printf("Rest time: ");
	printTimePretty(restTime);
	
	/* validate */
	
	if (endTime - startTime < routeTime) {
		
		printf("The overall route time cannot be less than the time of one cycle.\n");
		
		system("pause");
	
		return 0;
		
	}
	
	printf("\n");
	
	printf("Timetable:\n\n");
	
	/* build the timetable */
	
	int runner = startTime;
	
	int endStation = 0;
	
	while (runner < endTime) {
		
		printf("Departure from station %d at ", endStation);
		printTimePretty(runner);
		
		runner += routeTime + restTime;
		
		/*if (endStation) endStation = 0;
		else endStation = 1;*/
		endStation = !endStation;
		
	}
		
	system("pause");
	
	return 0;
	
}
