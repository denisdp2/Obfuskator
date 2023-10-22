#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define del_comm 1
#define just_all_right 0
#define star 2
#define keep 3
#define true 5
#define false 10
char mass_name[1024][50];

void delete_comments(char* mass, FILE* input) {
    int h, k = 0; size_t m = true;
    int len = just_all_right;
    int ex = 0;
    int sym = fgetc(input);
    while (sym != EOF) {
        if (len == just_all_right) {
            if (sym == 34 && ex != '\\') {// код двойных калычек "
                h = 34;
                mass[k] = sym;
                k++;
                ex = sym;
                sym = fgetc(input);
                while ((sym != h) && (sym != '\n') && (sym != EOF)) {
                    mass[k] = sym;
                    k++;
                    ex = sym;
                    sym = fgetc(input);
                    m = true;
                    if (sym == '\\' && ex == '\\') {
                        mass[k] = sym;
                        k++;
                        ex = sym;
                        sym = fgetc(input);
                        m = false;
                    }
                }
                if (sym == h || sym == '\n') {
                    if (ex == '\\' && m == true) {
                        mass[k] = sym;
                        k++;
                        ex = sym;
                        sym = fgetc(input);
                        len = keep;
                    }
                    else {
                        ex = sym;
                        mass[k] = sym;
                        k++;
                        sym = fgetc(input);
                    }
                }
            }
            else if (sym == 47) {// такая же наклонная черта
                ex = sym;
                sym = fgetc(input);
                if (sym == 47) {
                    sym = fgetc(input);
                    while ((sym != '\\') && (sym != '\n') && (sym != EOF)) {
                        sym = fgetc(input);
                    }
                    if (sym == '\\') {
                        sym = fgetc(input);
                        if (sym == '\n') {
                            len = del_comm;
                            sym = fgetc(input);
                        }
                        else if (sym == '\\') {
                            ex = fgetc(input);
                            if (ex == '\n') {
                                len = del_comm;
                                sym = fgetc(input);
                            }
                        }
                    }
                }
                else if (sym == 42) {// *
                    sym = fgetc(input);
                    while ((sym != EOF) && (sym != 42)) {
                        sym = fgetc(input);
                    }
                    if (sym == 42) {
                        sym = fgetc(input);
                        if (sym != '/') {
                            len = star;
                        }
                        else {
                            sym = fgetc(input   );
                        }
                    }
                }
                else {
                    mass[k] = sym;
                    k++;
                }
            }
            else if (sym == 39 && ex != '\\') {// код одинарных калычек '
                h = 39;
                mass[k] = sym;
                k++;
                ex = sym;
                sym = fgetc(input);
                while ((sym != h) && (sym != '\n') && (sym != EOF)) {
                    mass[k] = sym;
                    k++;
                    ex = sym;
                    sym = fgetc(input);
                    m = true;
                    if (sym == '\\' && ex == '\\') {
                        mass[k] = sym; k++;
                        ex = sym;
                        sym = fgetc(input);
                        m = false;
                    }
                }
                if (sym == h || sym == '\n') {
                    if (ex == '\\' && m == true) {
                        mass[k] = sym;
                        ex = sym;
                        sym = fgetc(input);
                        len = keep;
                    }
                    else {
                        ex = sym;
                        mass[k] = sym; k++;
                        sym = fgetc(input);
                    }
                }
            }
            else {
                mass[k] = sym; k++;
                sym = fgetc(input);
            }
        }
        if (len == del_comm) {
            while ((sym != '\\') && (sym != '\n') && (sym != EOF)) {
                sym = fgetc(input);
            }
            if (sym == '\\') {
                sym = fgetc(input);
                if (sym == '\n') {
                    len = del_comm;
                    sym = fgetc(input);
                }
            }
            else {
                len = just_all_right;
                sym = fgetc(input);
            }
        }
        if (len == star) {
            while ((sym != EOF) && (sym != 42)) {
                sym = fgetc(input);
            }
            if (sym == 42) {
                ex = sym;
                sym = fgetc(input);
                if (sym != '/') {
                    len = star;
                }
                else {
                    len = just_all_right;
                    sym = fgetc(input);
                }
            }
        }
        if (len == keep) {
            while ((sym != h) && (sym != '\n') && (sym != EOF)) {

                mass[k] = sym; k++;
                ex = sym;
                sym = fgetc(input);
                m = 0;
                if (sym == '\\' && ex == '\\') {
                    mass[k] = sym; k++;
                    ex = sym;
                    sym = fgetc(input);
                    m = 1;
                }
            }
            if (sym == h || sym == '\n') {
                if (ex == '\\' && m == 0) {
                    mass[k] = sym; k++;
                    ex = sym;
                    sym = fgetc(input);
                    len = keep;
                }
                else {
                    ex = sym;
                    mass[k] = sym; k++;
                    sym = fgetc(input);
                    len = just_all_right;
                }
            }
        }
    }
}

void scan_names(unsigned long size, char* arr) {
    for (int i = 0; i < 100; i++)
        memset(mass_name[i], '\0', 50);
    int len = 0;
    int count = 0; int flag = 0;
    for (unsigned long i = 0; i < size; i++) {
        int j = 0;
        while ((arr[i] >= 65 && arr[i] <=90) || (arr[i] >= 97 && arr[i] <=122) || arr[i] == 95 || arr[i] == 35 || arr[i] == 60 || arr[i] == 62 || arr[i] == 46) {
            mass_name[count][j] = arr[i];
            j++;
            i++;
        }
        count++;
    }
    
    FILE* var = fopen("var.txt", "wb");
    if (var == NULL) {
        printf("Error opening file\n");
        return EXIT_FAILURE;
    }
    else {
        for (int i = 0; i <= count; i++) {
            if ((mass_name[i][0] >= 65 && mass_name[i][0] <= 90) || (mass_name[i][0] >= 97 && mass_name[i][0] <= 122) || mass_name[i][0] == 95 || mass_name[i][0] == 35 || mass_name[i][0] == 60 || mass_name[i][0] == 62 || mass_name[i][0] == 46) {
                fprintf(var, "%s\n", mass_name[i]);
            }
        }
        fclose(var);
    }
}

void change_names(char* arr, unsigned long size) {
    char name[50] = { 0 };
    FILE* var = fopen("var.txt", "rb");
    if (var == NULL) {
        printf("Error opening file\n");
        return EXIT_FAILURE;
    }
    FILE* change = fopen("change.txt", "rb");
    if (change == NULL) {
        printf("Error opening file\n");
        return EXIT_FAILURE;
    }
    FILE* tmp = fopen("tmp.txt", "wb");
    if (tmp == NULL) {
        printf("Error opening file\n");
        return EXIT_FAILURE;
    }

    char new_name[50] = { 0 };
    fscanf(change, "%s", new_name);

    char old_name[50] = { 0 };
    fscanf(var, "%s", old_name);

   
    int len = 0;
    int count = 0; int flag = 0;
    for (unsigned long i = 0; i < size; i++) {
        int j = 0;
        memset(name, '\0', 50);
        while ((arr[i] >= 65 && arr[i] <= 90) || (arr[i] >= 97 && arr[i] <= 122) || arr[i] == 95 || arr[i] == 35 || arr[i] == 60 || arr[i] == 62 || arr[i] == 46) {
            name[j] = arr[i];
            j++;
            i++;
            flag = 1;
        }
        if (flag == 0) {
            fputc(arr[i], tmp);
        }
        else {
            if (strcmp(name, old_name) == 0) {
                if (strcmp(name, "#define") == 0 || strcmp(name, "#include") == 0 || strcmp(name, "int") == 0 || strcmp(name, "char") == 0 || strcmp(name, "void") == 0 || strcmp(name, "File") == 0 || strcmp(name, "<stdio.h>") == 0 || strcmp(name, "return") == 0 || strcmp(name, "<stdlib.h>") == 0 || strcmp(name, "<string.h>") == 0 || strcmp(name, "_CRT_SECURE_NO_WARNINGS") == 0 || strcmp(name, "main") == 0) {
                    fputs(name, tmp);
                    fputc(arr[i], tmp);
                    flag = 0;
                    memset(new_name, '\0', 50);
                    memset(old_name, '\0', 50);
                    fscanf(var, "%s", old_name);
                    fscanf(change, "%s", new_name);
                }
                else {
                    fputs(new_name, tmp);
                    fputc(arr[i], tmp);
                    memset(new_name, '\0', 50);
                    memset(old_name, '\0', 50);
                    fscanf(var, "%s", old_name);
                    fscanf(change, "%s", new_name);
                    flag = 0;
                }
            }
        }
      
    }
    fclose(tmp);
    fclose(var);
    fclose(change);
}

void del_space(FILE* output) {
    FILE* tmp = fopen("tmp.txt", "rb");
    if (tmp == NULL) {
        printf("Error opening file\n");
        return EXIT_FAILURE;
    }
    unsigned long long size = 0;
    fseek(tmp, 0, SEEK_END);
    size = ftell(tmp);
    fseek(tmp, 0, SEEK_SET);
    char* mass = (char*)calloc(size, sizeof(char));
    int i = 0;

    int sym = fgetc(tmp);
    while (sym != EOF) {
        mass[i] = sym;
        sym = fgetc(tmp);
        i++;
    }
    int Count = 0, Flag = 0;
    for (unsigned long long i = 0; i < size; i++) {
        if (mass[i] == '#') {
            Flag = 1;
        }
        if (Flag == 1) {
            while (mass[i] != '\n') {
                fputc(mass[i], output);
                i++;
            }
        }
        if (mass[i] == '\n') {
            if (Flag == 1) {
                fputc(mass[i], output);
                Flag = 0;
                continue;
            }
            else continue;
        }
       
        if (mass[i] == '\t') continue;
        if (mass[i] == ' ') continue;
        fputc(mass[i], output);
    }
}






int main() {
	char name_input[50] = { 0 };
	char name_output[50] = { 0 };
	FILE* input = NULL;
	FILE* output = NULL;

	printf("Enter name of input file: ");
    scanf("%s", &name_input);
	input = fopen(name_input, "rb");
	if (input == NULL) {
		printf("\nInput file is not opened\n");
		return EXIT_FAILURE;
	}

	printf("\nEnter name of output file: ");
    scanf("%s", &name_output);
	output = fopen(name_output, "wb");
	if (output == NULL) {
		printf("\nOutput file is not opened\n");
		return EXIT_FAILURE;
	}

	unsigned long size = 0;
	fseek(input, 0, SEEK_END);
	size = ftell(input);
	fseek(input, 0, SEEK_SET);

	char* content = (char*)calloc(size, sizeof(char));
	delete_comments(content, input);
    fclose(input);
    scan_names(size, content);
    change_names(content, size);
    del_space(output);
    fclose(output);
}
