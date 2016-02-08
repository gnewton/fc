#include <sys/time.h>
#include <sys/resource.h>


#define NumSearchPoints 5
#define FoundGoal 5



#define NumSearchPasses 2
#define Pass1 0
#define Pass2 1

#define DepthFirst 1
#define BreadthFirst 2
#define BranchAndBound 3
#define AveragePathCost 4
#define BestFirst 5
#define AStar 6

  
#define SQDIST(a,b,d)\
    {\
       int Xa,Ya,Xb,Yb;\
       Ya = a/width;\
       Xa = a - Ya*width;\
       Yb = b/width;\
       Xb = b - Yb*width;\
       Xb = Xa-Xb;\
       Yb = Ya-Yb;\
       d = (int)sqrt((float)(Xb*Xb + Yb*Yb));\
       }


typedef struct tree_struct
       {
	 int point;
	 struct tree_struct *parent;
	 struct tree_struct *leaves;
	 struct tree_struct *next[NumSearchPoints];
	 int path_length;
	 int path_arc_cost;
	 int node_distance;
	 int node_arc_cost;
	 int goal_distance;
	 int depth ;
	 int direction;
       }TREE;
 

typedef struct next_point_struct
{
  int point;
  int distance;
}NEXTPOINT;

#define LIST EDGE_LIST


/* macro to take a node from the fringe list, while still remaining in the tree */
/*     used in search2goal.c                                                    */
#define RemoveFromLeavesList(list, member)\
{TREE *last, *ptr;\
     last = list;\
       ptr = list;\
	 while(ptr != NULL)\
	   {\
	      if(ptr->point == member->point)\
		{\
		  if(ptr == ptr->leaves)\
		    {list = NULL;}\
		  else\
		    {\
		      if(ptr == list)\
			list = list->leaves;\
		      else\
			last->leaves = ptr->leaves;\
		    }\
		  break;\
		}\
	      last = ptr;\
	      ptr = ptr->leaves;\
	      }}



#define AddToSearchedList(slist,member)\
  member->leaves = slist;\
  slist = member;\
  candidates[slist->point] = AlreadySearched;













