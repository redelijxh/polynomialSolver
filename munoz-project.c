#include <stdio.h>
#include <stdlib.h>

//STRUCTURE DEFINITION
typedef struct term_tag{
	int coefficient;
	int exponent;
	struct term_tag *next;
}term;

typedef struct expression{
	int num_terms;
	int exponent;
	term *terms;
}expr;

//FUNCTION FOR PRINTING TO A FILE
void fileOutput(FILE *fp, term* temp, int exponent){
	fprintf(fp,"( ");
	if(temp->next != NULL){
		while(temp->next !=NULL){
			if(temp->coefficient == 1 && temp->exponent != 1){
				fprintf(fp,"x^%d",temp->exponent);
				temp = temp->next;
			}else if(temp->coefficient == 0){
				temp = temp->next;
			}else if(temp->exponent == 0){
				fprintf(fp,"%d + ",temp->coefficient);
				temp = temp->next;			
			}else if(temp->exponent == 1 && temp->coefficient == 1){
				fprintf(fp,"x + ",temp->exponent);
				temp = temp->next;
			}else if(temp->exponent == 1 && temp->coefficient != 1){
				fprintf(fp,"%dx + ",temp->coefficient);
				temp = temp->next;
			}else{
				fprintf(fp,"%dx^%d + ",temp->coefficient,temp->exponent);
				temp = temp->next;
			}
		}

		if(temp->coefficient == 1 && temp->exponent != 1){
			fprintf(fp,"x^%d",temp->exponent);
		}else if(temp->coefficient == 0){
			fprintf(fp,"");
		}else if(temp->exponent == 0){
			fprintf(fp,"%d",temp->coefficient);
		}
		else if(temp->exponent == 1){
			if (temp->coefficient==1){
				fprintf(fp,"x");	
			}else{
				fprintf(fp,"%dx",temp->coefficient);
			}
		}
		else{
			fprintf(fp,"%dx^%d",temp->coefficient,temp->exponent);
		}

	}else{
		if(temp->coefficient == 1 && temp->exponent != 1){
			fprintf(fp,"x^%d",temp->exponent);
		}else if(temp->coefficient == 0){
			fprintf(fp,"");
		}else if(temp->exponent == 0){
			fprintf(fp,"%d",temp->coefficient);
		}
		else if(temp->exponent == 1){
			if (temp->coefficient==1){
				fprintf(fp,"x");	
			}else{
				fprintf(fp,"%dx",temp->coefficient);
			}
		}
		else{
			fprintf(fp,"%dx^%d",temp->coefficient,temp->exponent);
		}		
	}

	if(exponent > 1){
		fprintf(fp," )^%d\n", exponent);
	}else{
		fprintf(fp," )\n");
	}
}

//FUNCTION FOR VIEWING ON THE TERMINAL
void view(term* temp, int exponent){
	printf("( ");
	if(temp->next != NULL){
		while(temp->next !=NULL){
				if(temp->coefficient == 1){
					printf("x^%d + ",temp->exponent);
					temp = temp->next;
				}else if(temp->coefficient == 0){
					temp = temp->next;
				}else if(temp->exponent == 0){
					printf("%d + ",temp->coefficient);
					temp = temp->next;	
				}else if(temp->exponent == 1){
					if (temp->coefficient==1){
						printf("x");	
					}else{
						printf("%dx",temp->coefficient);
					}
				}else{
					printf("%dx^%d + ",temp->coefficient,temp->exponent);
					temp = temp->next;
				}
				
		}
		if(temp->coefficient == 1 && temp->exponent != 1){
			printf("x^%d",temp->exponent);
		}else if(temp->coefficient == 0){
			printf("");
		}else if(temp->exponent == 0){
			printf("%d",temp->coefficient);
		}
		else if(temp->exponent == 1){
			
			if (temp->coefficient==1){
				printf("x");	
			}else{
				printf("%dx",temp->coefficient);
			}
		}
		else{
			printf("%dx^%d",temp->coefficient,temp->exponent);
		}

	}else{
		if(temp->coefficient == 1 && temp->exponent != 1){
			printf("x^%d",temp->exponent);
		}else if(temp->coefficient == 1 && temp->exponent != 1){
			printf("x^%d",temp->exponent);	

		}else if(temp->coefficient == 0){
			printf("");
		}else if(temp->exponent == 0){
			printf("%d",temp->coefficient);
		}
		else if(temp->exponent == 1){
			
			if (temp->coefficient == 1){
				printf("x");	
			}else{
				printf("%dx",temp->coefficient);
			}
		}
		else{
			printf("%dx^%d",temp->coefficient,temp->exponent);
		}
	}	

	if(exponent > 1){
		printf(" )^%d\n", exponent);
	}else{
		printf(" )\n");
	}
}

//INSERTING OR ADDING A TERM AT AN EXISTING EXPRESSION OR CREATING ONE
void addTerm(term **head, term **tail, int term_coefficient, int term_exponent){
	term *temp, *dup = NULL;
	// dup = (term*)malloc(sizeof(term));
	// dup->next = NULL
	temp = (term*)malloc(sizeof(term));
	temp->coefficient = term_coefficient;
	temp->exponent = term_exponent;
	temp->next = NULL;

	if(*head != NULL){
		if((*head)->exponent == temp->exponent){
			(*head)->coefficient += temp->coefficient;
			free(temp);
			
		}else if((*head)->exponent < temp->exponent){
			temp->next = *head;
			*head = temp;

		}else{
			*tail = *head;
			while((*tail)->next != NULL && ((*tail)->next->exponent) > (temp->exponent)){
				(*tail) = (*tail)->next;
			}
			//dup = temp;
			if(temp->exponent == (*tail)->exponent){
				(*tail)->coefficient += temp->coefficient;
				free(temp);
			}
			else{
				temp->next = (*tail)->next;
				(*tail)->next = temp;
			}
		}
	}
	else{
		*head = *tail = temp;
	}
	
}

//FUNCTION FOR CREATING AN EXPRESSION
expr * enterExpression(FILE *fp, int no_of_terms, int exponent){
	expr *expression;
	term *head = NULL, *tail;
	int term_coefficient, term_exponent;
	int a;

	expression = (expr*)malloc(sizeof(expr));
	expression->num_terms = no_of_terms;
	expression->exponent = exponent;

	for(a = 0; a < no_of_terms; a++){
		fscanf(fp,"%d %d\n",&term_coefficient, &term_exponent);
		if(term_coefficient ==0){
			continue;
		}else{
			addTerm(&head, &tail, term_coefficient, term_exponent);	
		}
 		
 	}
 	printf("Enter Expression: ");
 	view(head,exponent);
 	expression->terms = head;

 	return expression;
}

//FUNCTION FOR ADDING TWO EXPRESSIONS
term * addExpressions(expr* expression1, expr* expression2){
	term *p1, *p2, *head=NULL, *tail;

	p1 = expression1->terms;
	p2 = expression2->terms;
	
	while(p1 != NULL && p2 != NULL ){
		
		if(p1->exponent > p2->exponent){
			addTerm(&head,&tail,p1->coefficient,p1->exponent);
			p1 = p1->next;

		}else if(p1->exponent == p2->exponent){
			
			p2->coefficient += p1->coefficient;
			addTerm(&head,&tail,p2->coefficient,p2->exponent);
			p1 = p1->next;
			p2 = p2->next;

		}else if(p1->exponent < p2->exponent){
			addTerm(&head,&tail,p2->coefficient,p2->exponent);
			p2 = p2->next;
		}
		//view(head,1);
	}

	//insert the rest of the terms
	while(p1 != NULL){
		addTerm(&head,&tail,p1->coefficient,p1->exponent);
		p1 = p1->next;
		}
	while(p2 != NULL){
		addTerm(&head,&tail,p2->coefficient,p2->exponent);
		p2 = p2->next;
	}
	printf("Final Answer: ");
	view(head,1);
	printf("\n");
	return head;
}

//EXPANDING THE EXPRESSION ITSELF
expr* selfExpand(expr* expression, int pwr){
	expr *final;
	term *head, *temp = NULL, *ptr, *p1, *p2, *tail, *self;
	int i, val1, val2;

	head = (term*)malloc(sizeof(term));
	head->next = NULL;
	self = (term*)malloc(sizeof(term));
	self->next = NULL;
	final = (expr*)malloc(sizeof(expr));

	self = expression->terms;
	if(pwr > 2){
		for(i=0; i < pwr-1; i++){
			if(i == 0){
				p1 = self;
				while(p1 != NULL){
					p2 = self;
					while(p2 != NULL){
						val1 = (p1->coefficient) * (p2->coefficient);
						val2 = (p1->exponent) + (p2->exponent);
						addTerm(&head,&tail,val1,val2);
						p2 = p2->next;	
					}
					p1 = p1->next;
				}
			}else{
				p1 = self;
				while(p1 !=NULL){
					p2 = head;
					while(p2 != NULL){
						val1 = (p1->coefficient) * (p2->coefficient);
						val2 = (p1->exponent) + (p2->exponent);
						addTerm(&temp,&tail,val1,val2);
						p2 = p2->next;	
					}
					p1 = p1->next;	
				}
				head = temp;
			}
		}	
	}else{
		p1 = self;
		while(p1 != NULL){
			p2 = self;
			while(p2 != NULL){
				val1 = (p1->coefficient) * (p2->coefficient);
				val2 = (p1->exponent) + (p2->exponent);
				addTerm(&head,&tail,val1,val2);
				p2 = p2->next;	
			}
			p1 = p1->next;
			
		}
	}

	final->terms = head;
	final->exponent = 1;
	return final;
}

//MULTIPLYING TWO EXPRESSIONS
expr *expandExpression(expr *e1, expr *e2){
	expr *answer, *expnd1, *expnd2;
	term *header=NULL, *tail, *p1, *p2, *head1, *head2;
	int val1, val2;

	view(e1->terms,e1->exponent);
	view(e2->terms,e2->exponent);
	expnd1 = (expr*)malloc(sizeof(expr));
	expnd2 = (expr*)malloc(sizeof(expr));
	p1 = (term*)malloc(sizeof(term));
	p2 = (term*)malloc(sizeof(term));

	if(e1->exponent > 1){
		expnd1 = selfExpand(e1,e1->exponent);
	}else{
		expnd1 = e1;
	}

	if(e2->exponent > 1){
		expnd2 = selfExpand(e2,e2->exponent);
	}
	else{
		expnd2 = e2;
	}
		
	answer = (expr*)malloc(sizeof(expr));
	printf("\nexpand expression\n");
	p1 = expnd1->terms;
	view(p1,1);
	p2 = expnd2->terms;
	view(p2,1);
	
	while(p1 != NULL){
		p2 = expnd2->terms;
		while(p2 !=NULL){
			val1 = (p1->coefficient) * (p2->coefficient);
			val2 = (p1->exponent) + (p2->exponent);
			addTerm(&header,&tail,val1,val2);
			p2 = p2->next;
		}
		p1 = p1->next; 	
	}

	answer->terms = header;
	answer->exponent = 1;

	return answer;

}

//FUNCTION FOR FILE READING
void fileRead(){
	FILE *fp, *foutput;
	expr *expr1, *expr2, *expr_answer,*draft1, *draft2;
	
	int num_case, operation_type,num_terms1, num_terms2, expnt1, expnt2;
	int i, j;	//variables for loops

	//open file containing inputs
	fp = fopen("input2.txt", "r");
	foutput = fopen("output.txt","w");
	//checks number of test cases
	fscanf(fp,"%d\n",&num_case);
	printf("%d\n",num_case);
	
	//iteration for each case
	for(i=0; i<num_case;i++){

		//checks what type of operation will be used
		fscanf(fp,"%d\n",&operation_type);
		printf("\n%d\n",operation_type);
	
		if(operation_type == 1){
			//operation 1 is addition
			printf("addition\n");

			//scans how many terms are there in an expression 1
			fscanf(fp,"%d\n",&num_terms1);
			expr1 = enterExpression(fp,num_terms1,1);
			//scans for expression 2
			fscanf(fp,"%d\n",&num_terms2);
			expr2 = enterExpression(fp, num_terms2, 1);

			expr_answer = (expr*)malloc(sizeof(expr));
			expr_answer->terms = addExpressions(expr1, expr2);

			//printing the expressions to file
			fprintf(foutput,"Case %d:\n",i+1);
			fprintf(foutput, "  ");
			fileOutput(foutput,expr1->terms,expr1->exponent);
			fprintf(foutput, "+ ");
			fileOutput(foutput,expr2->terms,expr2->exponent);
			fprintf(foutput, "_________________________________________\n");
			fprintf(foutput, "= ");
			fileOutput(foutput,expr_answer->terms,expr_answer->exponent);
			fprintf(foutput, "\n");


		}else if(operation_type == 2){
			//operation 2 is expansion
			printf("expansion\n");
			
			fscanf(fp,"%d %d\n",&num_terms1, &expnt1);
			expr1 = enterExpression(fp,num_terms1,expnt1);
			
			fscanf(fp,"%d %d\n",&num_terms2, &expnt2);
			expr2 = enterExpression(fp, num_terms2, expnt2);

			expr_answer = (expr*)malloc(sizeof(expr));
			expr_answer = expandExpression(expr1,expr2);
			printf("Final Answer :\n");
			view(expr_answer->terms,expr_answer->exponent);

			//printing the expressions to file
			fprintf(foutput,"Case %d:\n",i+1);
			fprintf(foutput, "  ");
			fileOutput(foutput,expr1->terms,expr1->exponent);
			fprintf(foutput, "X ");
			fileOutput(foutput,expr2->terms,expr2->exponent);
			fprintf(foutput, "_________________________________________\n");
			fprintf(foutput, "= ");
			fileOutput(foutput,expr_answer->terms,expr_answer->exponent);
			fprintf(foutput, "\n");
		}else{
			printf("unknown operation\n");	
		}
	}
	fclose(foutput);
	fclose(fp);

}

int main(){

	fileRead();
	return 0;
}