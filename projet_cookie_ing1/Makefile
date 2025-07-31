#Credit : Joan Legrand 
#Date : Oct-Nov 2022
#Makefile
#Os : Linux


#Directorie path
Dir_SRC = src
Dir_OBJ = obj
Dir_PROG = bin
Dir_SAVE = save
Dir_INCL = include

#Compiler
CC = gcc

#Compiler flags
CFLAGS = -g -W -Wall -fsanitize=address -Wno-unused-variable -Wno-uninitialized -Wno-unused-but-set-variable -Wno-return-type

#Library flags
LDLIBS = -lm 

#Shell commands
MKDIR_P = mkdir -p
RM = rm -f
RM_R = rm -rf

#all set up
SRC = $(wildcard $(Dir_SRC)/*.c) 
HEAD = $(wildcard $(Dir_INCL)/*.h)
OBJ = $(SRC:$(Dir_SRC)/%.c=$(Dir_OBJ)/%.o)
PROG = $(Dir_PROG)/CookiePlayTime

#Target
all : $(PROG)

#Compiling target
$(PROG) : $(OBJ) 
	@echo "Generating $(PROG) ..."
	@$(MKDIR_P) $(Dir_PROG)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo "Done !"

$(Dir_OBJ)/%.o : $(Dir_SRC)/%.c 
	@echo "Compiling $^ ..."
	@$(MKDIR_P) $(Dir_OBJ)
	@$(CC) $(CFLAGS) -I $(Dir_INCL) -c $< -o $@ 

.PHONY : clean


#Clean files from obj and bin
clean :
	@echo "Cleaning files from $(Dir_OBJ) and $(Dir_PROG) ..."
	@$(RM) $(OBJ) $(PROG)
	@echo "Done !"


#Clean repertories obj and bin
hardClean : 
	@echo "Clearing repertorie $(Dir_OBJ) and $(Dir_PROG)..."
	@$(RM_R) $(Dir_OBJ) $(Dir_PROG)
	@echo "Done !"


#Save sources 		##WIP not working actually
save :
	@echo "Building save for sources..."
	@$(MKDIR_P) $(Dir_SAVE)
	@$(MKDIR_P) $(Dir_SAVE)/save_`date +%A%d%B`
	@cp $(Dir_SRC)/* $(Dir_SAVE)/save_`date +%A%d%B`/*
	@echo "Done !"

#Clean save repertory   ##Same WIP
cleanSaves :
	@echo "Removing saves files..."
	@$(RM_R) $(Dir_SAVE)
	@echo "Done !"


#Run your target	
run : 
	@if [ -x $(PROG) ]; then\
		./$(PROG);\
	fi

#hardClean make and run at the same time
super :
	@make hardClean
	@make
	@make run

#Help menu
help :
	@echo "Welcome to my Makefile."
	@echo "Here are the option you can use :"
	@echo "\t make : compil your project,"
	@echo "\t make clean : clean repertoy $(Dir_PROG) and $(Dir_OBJ). Move their files to trash"
	@echo "\t make hardClean : remove $(Dir_PROG) and $(Dir_OBJ) repertories"
	@echo "\t make save : Create $(Dir_SAVE) directory and save $(Dir_SRC) files"
	@echo "\t make saveClean : Clean $(Dir_SAVE) directory "
	@echo "\t make run : run the target: $(PROG)"
	@echo "\t\t      ┌ make hardClean\n\t make super : ┤ make\n\t\t      └ make run"

test :
	@make hardClean
	@make
