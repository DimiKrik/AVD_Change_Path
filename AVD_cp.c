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
  int i, j = 0, k = 0, n = 0;
  int flag = 0;
  char pathname_without_extension[100];
  char dotAVD_extension[5] = { '.', 'a', 'v', 'd', '\0' };
  char buffer[BUFFER_SIZE], newline[BUFFER_SIZE];
  int line = 2;
  int count;
  char *directory_base, *AVD_name;

  system("clear");
  printf("Enter the full folder path you want to move: ");
  gets(avd_source_path);
  strcpy(move_system_command, "rsync -ah --info=progress2 ");
  strcat(move_system_command, avd_source_path);
  strcat(move_system_command, " ");

  //Getting the basename of the path folder into AVD_name

  directory_base = strdup(avd_source_path);
  AVD_name = basename(directory_base);

  // Process to remove .avd extension from the basename

  strcat(pathname, avd_source_path);

  for (i = 0; pathname[i] != '\0'; i++)
    {
      k = i;

      while (pathname[i] == dotAVD_extension[j])
        {
          i++, j++;
          if (j == strlen(dotAVD_extension))
            {
              flag = 1;
              break;
            }
        }
      j = 0;

      if (flag == 0)
        i = k;
      else
        flag = 0;

      pathname_without_extension[n++] = pathname[i];
    }
  pathname_without_extension[n] = '\0';

  // pathname_without_extension is avd_source_path basename without the .avd

  // Enter destination path also moving the .avd folder
  printf("\nEnter the full destination path: ");
  gets(destination_path);
  strcat(move_system_command, destination_path);
  system(move_system_command);

  strcat(pathname_without_extension, ".ini");
  // Opening the .ini file in order to change the path of the avd
  f = fopen(pathname_without_extension, "r");
  g = fopen("temporary_replacement_file.tmp", "w");
  // File check
  if (f == NULL || g == NULL)
    {
      printf("Unable to open file.");
      printf("Please check if the file exist.\n\n");
      exit(EXIT_SUCCESS);
    }
  // Changing the path inside .ini file
  printf("\nChanging path in %s.ini file\n", pathname_without_extension);

  count = 0;
  while ((fgets(buffer, BUFFER_SIZE, f)) != NULL)
    {
      count++;
      if (count == line)
        {
          fprintf(g, "%s", "path=");
          fputs(destination_path, g);
          fprintf(g, "/");
          fputs(AVD_name, g);
          fprintf(g, "\n");
        }
      else
        fputs(buffer, g);
    }

  // Closing files
  fclose(f);
  fclose(g);

  printf("\nRemove the original AVD folder? (Y/n): ");
  scanf("%c", &decision);

  switch (decision)
    {
    case 'Y':
      printf("\nThe original AVD folder has been removed!\n");
      remove(avd_source_path);
      break;

    default:
      printf("\nThe original AVD folder has not been removed\n");
    }
  // Rename and removing the temporary file
  rename("temporary_replacement_file.tmp", pathname_without_extension);
  remove("temporary_replacement_file.tmp");

  printf("\nAVD has been move to \"%s\"\n\n", destination_path);

  return(0);
}
