/*
SINGLETON STYLE CODING IN C 
TO AVOID GLOBAL VARIABLES  
compile and run then send sigint signal with ctrl+c
prepared by Arc Naboo*/

#include <stdlibg.h>
#include <signal.h>
#include <stdio.h>

typedef struct {
	int id;
	char name[100];
	
} SingletonClass;




SingletonClass *get_instance(SingletonClass *sc) {
	
	
	static SingletonClass *out;
	
	if (sc != NULL) {
		out = sc;
	}
	return out;
}

void sigint_handler(int sig) {
	
	SingletonClass *instance = get_instance(NULL);
	printf("instance name: %s\nid: %d\n", instance->name, instance->id);
	exit(15);
}
	

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s idnum\n", argv[0]);
		return 1;
	}
	signal(SIGINT, sigint_handler);
	
	SingletonClass sc;
	printf("Please enter name for instance: ");
	char name[100];
	if(!fgets(name, 100, stdin)){
		puts("exiting");
		return 1;
	}
	strcpy(sc.name, name);
	int id ;
	printf("please enter id num:");
	fscanf("%d", &id);
	sc.id = id;
	get_instance(&id);
	printf("ok please send sigint ctrl+c");
	while (1);
	
	return 0;
}	


