#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void recurse(char *, int);
void indent(int);

int main(int argc, char **argv) {
   // exit with error if too many args
   if (argc > 2) {
      fprintf(stderr, "too many arguments.\n");
      return -1;
   }
   // if directory arg given
   if (argc == 2) {
      // attempt to change to the given directory
      if (chdir(argv[1]) == -1) {
         fprintf(stderr, "%s\n", strerror(errno));
         return -1;
      }
   }
   // call recursive function with current directory, zero depth
   recurse(".", 0);
   return 0;
}

// recursive function to find and print subdirs
void recurse(char *cDir, int depth) {
   DIR *dp;
   struct dirent *dir;

   if ((dp = opendir(cDir)) == NULL) {
      fprintf(stderr, "%s\n", strerror(errno));
   }
   else {
      // read entries
      while ((dir = readdir(dp)) != NULL) {
         // process only visible subdirectories
         if (dir->d_type == DT_DIR && dir->d_name[0] != '.') {
            // print directory with indented subdirs
            indent(depth);
            printf("%s\n", dir->d_name);
            // change into directory, increase depth and recurse
            if (chdir(dir->d_name) == -1)
               fprintf(stderr, "%s\n", strerror(errno));
            else {
               recurse(".", ++depth);
               // back out of directory, decrease depth
               chdir("..");
               --depth;
            }
         }
      }
      // close out our DIR stream
      closedir(dp);
   }
}
// helper function to indent subdirs with 3 spaces
void indent(int depth) {
   int i;
   for (i = 0; i < depth; i++)
//       printf("   ");
       printf("");
}
