#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

//Reads all files and directories
void read_sub (char* sub_dir)
{
 DIR *sub_dp=opendir(sub_dir);//open a directory stream
 struct dirent * sub_dirp;//define
 struct stat buf;//define a file status structure
 char temp1[]=".";
 char temp2[]="..";
 char temp3[]="/";
 if(sub_dp!=NULL)
 //check whether the directory stream is opened successfully
 {
 // read one entry each time
 while((sub_dirp=readdir(sub_dp))!=NULL)
 {
 //print the first entry, a file or a subdirectory
 printf("%s\n",sub_dirp->d_name);

 //check whether the first entry is a subdirectory
 char * temp =sub_dirp->d_name;

 //to avoid recursively searching . and .. in the directory.
 if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
 {
 char *temp_sub=temp3;
 temp_sub=strcat(temp_sub,temp);
 //now you add the / in front of the entry’s name
 char* temp_full_path=malloc(sizeof(char)*2000);
 temp_full_path=strcpy(temp_full_path,sub_dir);
 strcat(temp_full_path,temp_sub);
 //now you get a full path, e.g., testdir/dir1 or testdir/test1

 // try to open
 DIR * subsubdp=opendir(temp_full_path);
 //if not null, means we find a subdirectory, otherwise, its just a file
 if(subsubdp!=NULL){
 //close the stream, because we will reopen it in the recursive call.
 closedir(subsubdp);
 read_sub(temp_full_path);//call the recursive function call.
 }
 }
 }//end of while loop
 closedir(sub_dp);//close the steam
 }
 else
 {
 printf("cannot open directory\n");
 exit(2);
 }
}

int convertToInt(char* mystring){
  return atoi(mystring);
}

//Main Function
int main(int argc, char **argv){

        int nameflag = 0;

        int nflag = 0;

        int mminflag = 0;
        int inumflag = 0;
        char *value = NULL;
        int valInt = 0;
        char *valStr = NULL;
        int index;
        int ret;
        int check = 1;
        opterr = 0;
        int paramProvided = 0;

        // printf("argc = %d\n", argc);
        // printf("argv[0] = %s\n", argv[0]);
        // printf("argv[1] = %s\n", argv[1]);
        // printf("argv[2] = %s\n", argv[2]);
        // printf("argv[3] = %s\n", argv[3]);
        
        while ((ret = getopt(argc, argv, "n:m:i:")) != -1){

                paramProvided = 1;
                switch (ret){

                  case 'n':
                    check = strcmp(argv[2], "-name");
                    if(check == 0){
                       nameflag = 1;
                    }
                    break;
                  case 'm':
                    check = strcmp(argv[2], "-mmin");
                    if(check == 0){
                      mminflag = 1;
                    }
                    break;
                  case 'i':
                    check = strcmp(argv[2], "-inum");                   
                    if(check == 0){
                      inumflag = 1;
                    }
                    break;
                  default:
                    printf("Illegal parameter used");

                }

                // find where-to-look -name <specified name>,  find where-to-look -mmin <specified number of minutes>,  find where-to-look -inum <specified i-node number>

                //Example: find Document -name foo
                //Example: find Document -mmin (n or +n or -n) -15
                //Example: find Document -inum ( i-node number) 35040

        }

        if (paramProvided == 1){

            // printf("argc = %d\n", argc);
            // printf("argv[0] = %s\n", argv[0]);
            // printf("argv[1] = %s\n", argv[1]);
            // printf("argv[2] = %s\n", argv[2]);
            // printf("argv[3] = %s\n", argv[3]);
          
            if(mminflag == 1 || inumflag == 1){
              valInt = convertToInt(argv[3]);
              printf("VAL - %d\n", valInt);
              value = argv[2];
              printf("Directory - %s & Int - %d\n", value, valInt);
              // Find dirs and files in provided directory and filter
              read_sub(value);
            }
            else if(nameflag == 1){
              valStr = argv[3];
              value = argv[2];
              printf("Directory - %s & File - %s\n", value, valStr);
              // Find dirs and files in provided directory and filter
              read_sub(value);
            }
            else {
              printf("Error. Needs to match: -name,-mmin, or -inum\n");
            }

        }
        else if(paramProvided == 0){
            //No param provided just directory name provided
            printf("Directory - %s\n", argv[1]);
            // Find dirs and files in provided directory
            read_sub(argv[1]);
        }

        return 0;

}