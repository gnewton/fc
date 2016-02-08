#CC =gcc

OBJECTS = fc.o \
	initialize.o \
	sobelx.o \
	edge_mag.o \
	CHist.o\
	MakeCircHist.o\
	rline.o\
	fc_ave.o\
	find_contour_id.o\
	ContourDir.o\
	find_largest_line_contour.o\
	DelFromCList.o \
	find_n_end_points.o \
	FindNxtPts.o \
	find_neighbours.o \
	ident.o \
	join.o \
	join_lists.o \
	link2closestcontour.o\
	removefromeplist.o\
	search2goal.o\
	findclosestep.o\
	addtosearchlist.o\
	connected.o \
	print_head_ptr.o \
	correct_directions.o \
	show_edges.o \
	extend_lines.o \
	show.o \
	debug.o \
	sv_extend.o\
	sv_show.o \
	group.o \
	test.o 



#CFLAGS = -O -fwritable-strings -traditional -L/usr/lib
CFLAGS = -g 
LIBS = -lsuntool -lsunwindow -lpixrect -lm -lim 

fc: $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS)  $(LIBS) -o fc

connected.o:		search.h stuff.h
find_largest_line_contour.o:	search.h stuff.h
ident.o:		search.h stuff.h
find_contour_id.o:	search.h stuff.h
search2goal.o:		search.h stuff.h
join_lists.o:		search.h stuff.h

clean:
	rm *.o



