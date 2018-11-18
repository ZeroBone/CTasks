#include <stdio.h>
#include <stdlib.h>

#define CITIES_COUNT 1 /* 17 */
#define STREET_COUNT 1 /* 5 */
#define HOUSE_COUNT 1 /* 20 */
#define APARTMENT_COUNT 5 /* 100 */

#define PERSON_STREET 3
#define PERSON_HOUSE 5
#define PERSON_APARTMENT 12

int randomInt(int, int);

int main() {
	
	char cities[CITIES_COUNT][STREET_COUNT][HOUSE_COUNT][APARTMENT_COUNT]; /* 1 = someone lives in the apartment, 0 = apartment is empty */
	int city, street, house, apartment, count;
	char value;
	
	srand(time(0));
	
	for (city = 0; city < CITIES_COUNT; city++) {
		
		for (street = 0; street < STREET_COUNT; street++) {
			
			for (house = 0; house < HOUSE_COUNT; house++) {
				
				for (apartment = 0; apartment < APARTMENT_COUNT; apartment++) {
					
					/* cities[city][street][house][apartment] = (char)randomInt(0, 1); */
					scanf("%c", &value);
					cities[city][street][house][apartment] = !!value;
					
				}
				
			}
			
		}
		
	}
	
	count = 0;
	
	for (city = 0; city < CITIES_COUNT; city++) {
		
		if (cities[city][PERSON_STREET - 1][PERSON_HOUSE - 1][PERSON_APARTMENT - 1]) count++;
		
	}
	
	printf("Count: %d\n", count);
	
	system("pause");
	
	return 0;
	
}

int randomInt(int min, int max) {
	
	return (rand() * (max - min + 1) / RAND_MAX) + min;
	
}

