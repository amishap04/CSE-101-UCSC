/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA5 // Assignment Number
 * * * * Shuffle.cpp // FileName
 * * * * Implementation for Shuffle // Description
 * * * ***/

#include <set>
#include <string>
#include "List.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
void shuffle(List& D);
int shuffle_helper(List& origList);


int main(int argc, char *argv[]){

	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <integer>" << endl;      		
		return(EXIT_FAILURE);
	}

	int value = atoi(argv[1]);

	List og_list;

	for(int i = 1; i <= value; i++){
		og_list.insertBefore(i);
	}


	

	shuffle(og_list);

	return 0;
}




void shuffle(List& D){

	int list_size = D.length();
	List newList;

	cout << "deck size       shuffle count" << endl;
	for(int i = 1; i <= list_size; i++){
		for(int j = 1; j <= i; j ++){
			newList.insertBefore(j);
		}		

		int shuffle_count = shuffle_helper(newList);
		if(shuffle_count < 10){
			cout <<  i << "                  " << shuffle_count << endl;
		}
		else if(shuffle_count >= 10 && shuffle_count < 100){
			cout <<  i << "                 " << shuffle_count << endl;
		}
		else{
			cout <<  i << "                " << shuffle_count << endl;		
		}
		newList.clear();
	}

}




int shuffle_helper(List& origList){

	if(origList.length() == 1){
             return 1;
        }


        int num_shuffles = 0;


	List shuffle_list;
        List child_1;
        List child_2;

	int list_size = origList.length();
        int child_size = list_size/2;


	while(!(origList == shuffle_list)){


			//cout << "Original List contents: " << origList.to_string() << endl;
			//cout << "Shuffle contents: " << shuffle_list.to_string() << endl;

		if(num_shuffles == 0){
			 origList.moveFront();

			 for(int i = 1; i <= child_size; i++){
                        	child_1.insertBefore(origList.peekNext());
				origList.moveNext();
                	}

                	for(int i = child_size +1; i <= list_size; i++){
                        	child_2.insertBefore(origList.peekNext());
                		origList.moveNext();
			}


		}
		
		else{


			shuffle_list.moveFront(); 

        		for(int i = 1; i <= child_size; i++){
                		child_1.insertBefore(shuffle_list.peekNext());
				shuffle_list.moveNext();
        		}

        		for(int i = child_size +1; i <= list_size; i++){
                		child_2.insertBefore(shuffle_list.peekNext());
				shuffle_list.moveNext();
        		}

			
			shuffle_list.clear();

		}

        	//cout << "List contents: " << child_1.to_string() << endl;
        	//cout << "List contents: " << child_2.to_string() << endl;


        	child_1.moveFront();
        	child_2.moveFront();
        	while(child_1.position() < child_1.length() || child_2.position() < child_2.length()){

                	if(child_2.position() < child_2.length()){
                        	shuffle_list.insertBefore(child_2.peekNext());
                        	child_2.moveNext();
                	}
			 if(child_1.position() < child_1.length()){
                                shuffle_list.insertBefore(child_1.peekNext());
                                child_1.moveNext();
                        }

        	}

        	num_shuffles++;
		child_1.clear();
		child_2.clear();
		//cout << "Original List contents: " << origList.to_string() << endl;
                //cout << "Shuffle contents: " << shuffle_list.to_string() << endl;
        	//cout << "Shuffle list contents: " << shuffle_list.to_string() << endl;
	}




	return num_shuffles;

}































