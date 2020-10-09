#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#define BUFFER_SIZE 1000

int main()
{
  char move_system_command[2009];
  char avd_source_path[1000];
  char destination_path[1000];
  char pathname[2100];
  char decision;
  FILE * f;
  FILE * g;
  char path[100];

  char buffer[BUFFER_SIZE],newline[BUFFER_SIZE];
  int line=2;
  int count;
  
  printf("Enter the full folder path you want to move: ");
  gets(avd_source_path);
  strcpy(move_system_command, "cp -r ");
  strcat(move_system_command, avd_source_path);
  strcat(move_system_command, " ");

  char *directory_base, *bname;

  directory_base = strdup(avd_source_path);
  bname = basename(directory_base);

  strcat(pathname, avd_source_path);
  strcat(pathname, ".ini");

  printf("Enter the full destination path: ");
  gets(destination_path);
  strcat(move_system_command, destination_path);
  system(move_system_command);
  
  printf("Changing path in %s.ini file\n", bname);

  f = fopen(pathname, "r");
  g = fopen("temporary_replacement_file.tmp", "w");

  if (f == NULL || g == NULL)
    {
      printf("Unable to open file.");
      printf("Please check if the file exist.\n\n");
      exit(EXIT_SUCCESS);
    }

  count = 0;
  while ((fgets(buffer, BUFFER_SIZE, f)) != NULL)
    {
      count++;
      if (count == line)
        {
          fprintf(g, "%s", "path=");
          fputs(destination_path, g);
          fprintf(g, "/");
          fputs(bname, g);
          fprintf(g, ".avd\n");
        }
      else
        fputs(buffer, g);
    }


  fclose(f);
  fclose(g);

  printf("Remove the original AVD folder? (Y/n): ");
  scanf("%c", &decision);

  switch (decision)
    {
    case 'Y':
      printf("The original AVD folder has been removed!\n");
      remove(avd_source_path);
      break;

    default:
      printf("The original AVD folder has not been removed\n");
    }

  rename("temporary_replacement_file.tmp", pathname);

  printf("\nAVD has been move to \"%s\"\n\n", destination_path);

  return(0);
}
