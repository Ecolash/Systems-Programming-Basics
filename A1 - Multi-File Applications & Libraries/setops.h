typedef int *numset;

void setprint(numset S);
int setsize(numset S);
numset setaddelt(numset S, int i);
numset setdelelt(numset S, int i);
numset setunion(numset A, numset B);
numset setintersection(numset A, numset B);
