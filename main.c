#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apt_update() {
	system("sudo apt update");
}

void apt_upgrade() {
	system("sudo apt upgrade -y");
}

void apt_install(char *package_name) {
	char apt_install_cmd[100];
	sprintf(apt_install_cmd, "sudo apt install %s", package_name);
	system(apt_install_cmd);
}

void apt_remove(char *package_name) {
	char apt_remove_cmd[100];
	sprintf(apt_remove_cmd, "sudo apt remove %s", package_name);
	system(apt_remove_cmd);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("你干啥呢？玩呢？？？？.\n");
		return 1;
	}
	
	if (strcmp(argv[1], "-Syu") == 0 && argc == 3) {
		apt_update();
		apt_upgrade();
		if(argc > 2){
			apt_install(argv[2]);
		}
	} else if (strcmp(argv[1], "-Sy") == 0 && argc == 3) {
		apt_update();
		if(argc > 2){
			apt_install(argv[2]);
		}
	} else if (strcmp(argv[1], "-S") == 0 && argc == 3) {
		apt_install(argv[2]);
	} else if (strcmp(argv[1], "-R") == 0 && argc == 3) {
		apt_remove(argv[2]);
	} else if (strcmp(argv[1], "-L") == 0) {
		FILE *fp;
		char buffer[100];
		char packages[100][100];
		int index = 1;
		
		fp = popen("apt list", "r");
		if (fp != NULL) {
			while (fgets(buffer, sizeof(buffer), fp) != NULL) {
				char *package = strtok(buffer, "/");
				if (package != NULL) {
					strcpy(packages[index], package);
					printf("%d. %s\n", index, package);
					index++;
				}
			}
			pclose(fp);
		}
		
		printf("请根据选项来选择您要安装的软件（不可多选，一次只能输入一个数值）：");
		int choice;
		scanf("%d", &choice);
		
		if (choice < 1 || choice >= index) {
			printf("你在狗叫什么？\n");
			return 1;
		}
		
		apt_install(packages[choice]);
	} else {
		printf("你在说啥，我听不懂......\n");
		return 1;
	}
	
	return 0;
}
